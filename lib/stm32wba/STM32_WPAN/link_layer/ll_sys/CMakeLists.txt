
if (CONFIG_BT_STM32WBA)
zephyr_compile_definitions( -DBLE )
endif()
if (CONFIG_IEEE802154_STM32WBA)
zephyr_compile_definitions( -DMAC )
endif()

if (CONFIG_BT_STM32WBA)
zephyr_include_directories(../ll_cmd_lib/config/ble_full)
endif()
if (CONFIG_IEEE802154_STM32WBA)
zephyr_include_directories(../ll_cmd_lib/config/ieee_15_4_basic)
zephyr_include_directories(../ll_cmd_lib/inc/ot_inc)
endif()

zephyr_include_directories(${CMAKE_CURRENT_SOURCE_DIR})

zephyr_include_directories(inc)
zephyr_include_directories(../ll_cmd_lib/inc)
zephyr_include_directories(../ll_cmd_lib/inc/_40nm_reg_files)

zephyr_sources(src/ll_sys_cs.c)
zephyr_sources(src/ll_sys_dp_slp.c)
zephyr_sources(src/ll_sys_intf.c)
zephyr_sources(src/ll_sys_startup.c)