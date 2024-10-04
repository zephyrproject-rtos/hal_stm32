/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dm_alloc.c
  * @author  GPM WBL Application Team
  * @brief   Dynamic Memory Allocator
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/******************************************************************************
 * INCLUDE HEADER FILES
 *****************************************************************************/
#include "dm_alloc.h"
#include "osal.h"
#include <string.h>

/******************************************************************************
 * LOCAL MACROS
 *****************************************************************************/
#define ALIGN_UPTO_32BITS(VAL)          (((((unsigned int)(VAL)) - 1U) | (sizeof(uint32_t) - 1U)) + 1U)
#define DM_SLICE_THRESHOLD              (3 * sizeof(db_alloc_header_t))
#define DM_FREE                         0x00
#define DM_ALLOC                        0x01
/*#define DM_DEBUG                        (1) */
#if defined(DM_DEBUG)
#define DM_DEBUG_STAMP                  (0xBEAF)
#endif

#define MIN(a,b)                        (((a) < (b))? (a) : (b))

/******************************************************************************
 * LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
 *****************************************************************************/
typedef struct db_alloc_header_s {
    uint16_t buffer_size;
    uint16_t flags;
    uint32_t buffer_a[];
} db_alloc_header_t;

typedef struct db_free_header_s {
    uint16_t buffer_size;
    uint16_t flags;
    struct db_free_header_s *next;
    uint32_t buffer_a[];
} dm_free_header_t;

typedef struct dm_ctx_s {
#if defined(DM_DEBUG)
    uint16_t alloc_size;
    uint16_t alloc_max_size;
#endif
    dm_free_header_t *head;
    uint32_t *alloc_space_p;
    uint16_t buffer_size;
} dm_ctx_t;

/******************************************************************************
 * LOCAL FUNCTION PROTOTYPES
 *****************************************************************************/
/******************************************************************************
 * Local Variables
 *****************************************************************************/
static dm_ctx_t dm_ctx;

void dm_init(uint16_t buffer_size, uint32_t *buffer_p)
{
    dm_ctx.alloc_space_p = (void *)buffer_p;
    dm_ctx.head = (dm_free_header_t *)buffer_p;
    dm_ctx.head->buffer_size = buffer_size;
    dm_ctx.buffer_size = buffer_size;
    dm_ctx.head->flags = DM_FREE;
#if defined(DM_DEBUG)
    dm_ctx.alloc_size = 0U;
    dm_ctx.alloc_max_size = 0U;
#endif
    dm_ctx.head->next = NULL;
}

static void db_extract_from_free_list(dm_free_header_t *entry_p)
{
    dm_free_header_t *e_p;

#if defined(DM_DEBUG)
    if (entry_p->flags != DM_FREE)
    {
        while (1)
            ;
    }
#endif
    if (entry_p == dm_ctx.head)
    {
        dm_ctx.head = entry_p->next;
    }
    else
    {
        e_p = dm_ctx.head;
        while (e_p != NULL)
        {
            if (e_p->next == entry_p)
            {
                e_p->next = entry_p->next;
                break;
            }
            e_p = e_p->next;
        }
    }
}

static void db_add_to_free_list(dm_free_header_t *free_entry_p)
{
    dm_free_header_t *prev_p;

    if (free_entry_p != NULL)
    {
#if defined(DM_DEBUG)
        if (free_entry_p->flags != DM_FREE)
        {
            while (1)
                ;
        }
#endif
        prev_p = NULL;
        if (dm_ctx.head == NULL)
        {
            /**
             * The free list is empty. Assign the new entry to the list.
             */
            dm_ctx.head = free_entry_p;
        }
        else
        {
            if ((uintptr_t)free_entry_p < (uintptr_t)dm_ctx.head)
            {
                /**
                 * Insert the new element at the head of the list.
                 */
                free_entry_p->next = dm_ctx.head;
                dm_ctx.head = free_entry_p;
            }
            else
            {
                prev_p = dm_ctx.head;
                while (prev_p->next != NULL)
                {
                    /**
                     * The free list is ordered by index (address) then search
                     * into the list to find the previous node.
                     */
                    if ((uintptr_t)prev_p->next > (uintptr_t)free_entry_p)
                    {
                        break;
                    }
                    prev_p = prev_p->next;
                }

                /**
                 * Insert the new element.
                 */
                free_entry_p->next = prev_p->next;
                prev_p->next = free_entry_p;

                /**
                 * Try to make the new free entry coalesce with the previous.
                 */
                if (((uintptr_t)prev_p + prev_p->buffer_size) ==
                    (uintptr_t)free_entry_p)
                {
                    prev_p->next = free_entry_p->next;
                    prev_p->buffer_size += free_entry_p->buffer_size;
                }
            }

            /**
             * Try to make the new free entry coalesce with the next.
             */
            if (((uintptr_t)free_entry_p + free_entry_p->buffer_size) ==
                (uintptr_t)free_entry_p->next)
            {
                dm_free_header_t *ne_p;

                ne_p = free_entry_p->next;
                free_entry_p->next = ne_p->next;
                free_entry_p->buffer_size += ne_p->buffer_size;
            }
        }
    }
}

/* Release part of a free block and add it to the list of free blocks.
 Returns the size of the slot not freed. */
static uint16_t dm_slice(dm_free_header_t *free_entry_p, uint16_t min_size)
{
    uint16_t slice_size;

    slice_size = free_entry_p->buffer_size - min_size;
    if (slice_size > DM_SLICE_THRESHOLD)
    {
        dm_free_header_t *slice_p;

        slice_p = (dm_free_header_t *)&free_entry_p->buffer_a[(min_size -
                                                               sizeof(dm_free_header_t)) >> 2];
        slice_p->buffer_size = slice_size;
        slice_p->flags = DM_FREE;
        slice_p->next = NULL;
        db_add_to_free_list(slice_p);
        return min_size;
    }

    return free_entry_p->buffer_size;
}

void *dm_alloc(uint16_t size)
{
    uint16_t alloc_size;
    dm_free_header_t *entry_p, *best_entry_p;

    best_entry_p = NULL;
    entry_p = dm_ctx.head;
    alloc_size = (uint16_t)(ALIGN_UPTO_32BITS(size) + sizeof(db_alloc_header_t));
#if defined(DM_DEBUG)
    if (entry_p != NULL)
    {
        if (entry_p->flags != DM_FREE)
        {
            while (1)
                ;
        }
    }
#endif
    while (entry_p != NULL)
    {
        /**
         * Best fit strategy: search for the entry that has the size closer to
         * the requested value.
         */
        if (entry_p->buffer_size >= alloc_size)
        {
            if ((best_entry_p == NULL) ||
                ((best_entry_p != NULL) &&
                 (best_entry_p->buffer_size > entry_p->buffer_size)))
            {
                best_entry_p = entry_p;
            }
        }
        entry_p = entry_p->next;
    }

    if (best_entry_p != NULL)
    {
        db_alloc_header_t *alloc_entry_p;

        /**
         * Detach entry by free list.
         */
        db_extract_from_free_list(best_entry_p);

        /**
         * If the extracted entry has a size "much" greater then the
         * requested one then slice it releasing the not requested space.
         */
        best_entry_p->buffer_size = dm_slice(best_entry_p, alloc_size);

        alloc_entry_p = (db_alloc_header_t *)best_entry_p;
#if defined(DM_DEBUG)
        if (alloc_entry_p->flags != DM_FREE)
        {
            while (1)
                ;
        }
        dm_ctx.alloc_size += alloc_size + sizeof(uint32_t);
        if (dm_ctx.alloc_size > dm_ctx.alloc_max_size)
        {
            dm_ctx.alloc_max_size = dm_ctx.alloc_size;
        }
#endif
        best_entry_p->flags = DM_ALLOC;

        return alloc_entry_p->buffer_a;
    }

    return NULL;
}

void dm_free(void *buffer_p)
{
    if (buffer_p == NULL)
        return;
    dm_free_header_t *free_entry_p;
    uint32_t *buffer32_p = buffer_p;

    free_entry_p = (dm_free_header_t *)(--buffer32_p);
    free_entry_p->flags = DM_FREE;
    free_entry_p->next = NULL;
#if defined(DM_DEBUG)
    dm_ctx.alloc_size -= free_entry_p->buffer_size;
#endif
    db_add_to_free_list(free_entry_p);
}

void *dm_realloc(void *buffer_p, uint16_t size)
{
    uint16_t total_alloc_size; /* Total size that needs to be allocated for new buffer (including existing one).  */
    uint16_t add_alloc_size; /* Additional space needed in case allocated memory needs to be increased. */
    dm_free_header_t *entry_p;
    uint32_t *next_addr, *new_buffer_p;
    uint32_t *buffer32_p = buffer_p;

    db_alloc_header_t *allocated_entry_p = (db_alloc_header_t *)(buffer32_p - 1);

    total_alloc_size = ALIGN_UPTO_32BITS(size) + sizeof(db_alloc_header_t);

    /* Check if current buffer has already the requested size.
       If this is the case, try to reduce it. */
    if(allocated_entry_p->buffer_size >= total_alloc_size)
    {
        allocated_entry_p->buffer_size = dm_slice((dm_free_header_t*)allocated_entry_p, total_alloc_size);

        return buffer_p;
    }

    add_alloc_size = total_alloc_size - allocated_entry_p->buffer_size;

    next_addr = &allocated_entry_p->buffer_a[(allocated_entry_p->buffer_size - sizeof(db_alloc_header_t)) >> 2];

    entry_p = (dm_free_header_t*)next_addr;

    /* Look into next block and check if it is free and has enough space to contain additional data. */
    if(next_addr < dm_ctx.alloc_space_p + dm_ctx.buffer_size && entry_p->flags == DM_FREE)
    {
        if(entry_p->buffer_size >= add_alloc_size)
        {
            /* Next contiguous slot is big enough. */

            db_extract_from_free_list(entry_p);

            allocated_entry_p->buffer_size += dm_slice(entry_p, add_alloc_size);

#if defined(DM_DEBUG)
            dm_ctx.alloc_size += alloc_size + sizeof(uint32_t);
            if (dm_ctx.alloc_size > dm_ctx.alloc_max_size)
            {
                dm_ctx.alloc_max_size = dm_ctx.alloc_size;
            }
#endif
            return allocated_entry_p->buffer_a;
        }
    }

    /* No contiguous free memory slot found with enough space.
       Need to allocate new slot. */

    new_buffer_p = dm_alloc(size);
    if (new_buffer_p != NULL)
    {
        /* Copy old data */
        uint16_t old_data_size = allocated_entry_p->buffer_size - sizeof(db_alloc_header_t);
        Osal_MemCpy(new_buffer_p, buffer_p, MIN(size, old_data_size));
        dm_free(buffer_p);
    }

    return new_buffer_p;
}

