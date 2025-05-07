# Copyright (c) 2025 STMicroelectronics
#
# SPDX-License-Identifier: Apache-2.0
zephyr_library()

zephyr_library_compile_definitions(H1_INTERNAL)
zephyr_library_compile_definitions(H1_HAVE_ENCDEBUG_H)
zephyr_include_directories(inc)
zephyr_include_directories(source/common)
zephyr_include_directories(source/h264)

zephyr_library_sources(source/common/encasiccontroller.c)
zephyr_library_sources(source/common/encasiccontroller_v2.c)
zephyr_library_sources(source/common/encpreprocess.c)
zephyr_library_sources(source/common/encswhwregisters.c)

zephyr_library_sources(source/h264/H264Cabac.c)
zephyr_library_sources(source/h264/H264CodeFrame.c)
zephyr_library_sources(source/h264/H264Denoise.c)
zephyr_library_sources(source/h264/H264EncApi.c)
zephyr_library_sources(source/h264/H264Init.c)
zephyr_library_sources(source/h264/H264Mad.c)
zephyr_library_sources(source/h264/H264NalUnit.c)
zephyr_library_sources(source/h264/H264PictureBuffer.c)
zephyr_library_sources(source/h264/H264PictureParameterSet.c)
zephyr_library_sources(source/h264/H264PutBits.c)
zephyr_library_sources(source/h264/H264RateControl.c)
zephyr_library_sources(source/h264/H264Sei.c)
zephyr_library_sources(source/h264/H264SequenceParameterSet.c)
zephyr_library_sources(source/h264/H264Slice.c)
zephyr_library_sources(source/h264/h264encapi_ext.c)
