# ===========================================================================
# Copyright © 2021 Jan Erik Breimo. All rights reserved.
# Created by Jan Erik Breimo on 2021-01-13.
#
# This file is distributed under the BSD License.
# License text is included with the source distribution.
# ===========================================================================
cmake_minimum_required(VERSION 3.17)
project(Ypng VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

find_package(PNG REQUIRED)

add_library(Ypng_PngWriter
    include/Ypng/YpngException.hpp
    include/Ypng/PngInfo.hpp
    include/Ypng/PngTransform.hpp
    include/Ypng/PngWriter.hpp
    src/Ypng/PngInfo.cpp
    src/Ypng/PngTransform.cpp
    src/Ypng/PngWriter.cpp
    )

target_include_directories(Ypng_PngWriter
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

target_link_libraries(Ypng_PngWriter
    PUBLIC
        PNG::PNG
    )

add_library(Ypng::PngWriter ALIAS Ypng_PngWriter)

add_subdirectory(extras/DemoApps)

set_target_properties(Ypng_PngWriter
    PROPERTIES
        EXPORT_NAME PngWriter
    )

export(TARGETS Ypng_PngWriter
    NAMESPACE Ypng::
    FILE YpngConfig.cmake)
