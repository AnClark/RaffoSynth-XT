#  CMakeLists.txt - Build system for RaffoSynth
#
#  Copyright (C) 2023 AnClark Liu. All rights reserved.
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

cmake_minimum_required(VERSION 3.20)

project(RaffoSynth
    VERSION 0.1.0
    LANGUAGES C CXX
)

option(CONFIG_ASM_IMPLEMENTATION "Enable ASM implementaton of synth engine (Intel SIMD enabled)" OFF)

if(CONFIG_ASM_IMPLEMENTATION)
    message(STATUS "Use optimized ASM synth engine implementation (Intel SIMD enabled)")

    enable_language(ASM_NASM)
    set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS asm)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_ASM_NASM_FLAGS "${ASM_NASM_FLAGS} -g")
    else()
        set(CMAKE_ASM_NASM_FLAGS "${ASM_NASM_FLAGS}")
    endif()
else()
    message(STATUS "Use standard synth engine implementation")
endif()

add_subdirectory(dpf)

include_directories(src)

if(CONFIG_ASM_IMPLEMENTATION)
    add_library(${PROJECT_NAME}-core STATIC
        src/oscillators.asm
        src/equalizer.asm
        src/fft.h
        src/tiempo.h
    )
else()
    add_library(${PROJECT_NAME}-core STATIC
        src/oscillators.c
        src/equalizer.c
        src/fft.h
        src/tiempo.h
    )

    target_compile_options(${PROJECT_NAME}-core PRIVATE -fPIC)
endif()

dpf_add_plugin(${PROJECT_NAME}
    TARGETS vst2 vst3 lv2 clap
    FILES_DSP
        plugin/raffo_plugin.cpp
        plugin/raffo.cpp
        plugin/params.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC plugin/)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-core)
