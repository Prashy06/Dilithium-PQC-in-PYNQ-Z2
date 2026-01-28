# ==============================================================
# Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
# Tool Version Limit: 2025.05
# Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
# Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
# 
# ==============================================================
cmake_minimum_required(VERSION 3.15)
project(top_ntt)
find_package(common)
collector_create (PROJECT_LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}")
collect (PROJECT_LIB_SOURCES xtop_ntt.c)
collect (PROJECT_LIB_SOURCES xtop_ntt_sinit.c)
collect (PROJECT_LIB_SOURCES xtop_ntt_linux.c)
collect (PROJECT_LIB_SOURCES xtop_ntt_g.c)
collector_list (_sources PROJECT_LIB_SOURCES)
collector_create (PROJECT_LIB_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}")
collect (PROJECT_LIB_HEADERS xtop_ntt.h)
collect (PROJECT_LIB_HEADERS xtop_ntt_hw.h)
collector_list (_headers PROJECT_LIB_HEADERS)
file(COPY ${_headers} DESTINATION ${CMAKE_BINARY_DIR}/include)
include_directories(${CMAKE_BINARY_DIR}/include)
add_library(top_ntt STATIC ${_sources})
set_target_properties(top_ntt PROPERTIES LINKER_LANGUAGE C)

