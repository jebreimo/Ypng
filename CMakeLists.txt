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

# Set Ypng_MASTER_PROJECT to ON if Argos is the root level project.
if (NOT DEFINED Ypng_MASTER_PROJECT)
    if (CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
        set(Ypng_MASTER_PROJECT ON)
    else ()
        set(Ypng_MASTER_PROJECT OFF)
    endif ()
endif ()

# Install option
option(Ypng_INSTALL "Generate the install target" ${Ypng_MASTER_PROJECT})

add_library(Ypng_PngWriter
    include/Ypng/YpngException.hpp
    include/Ypng/PngInfo.hpp
    include/Ypng/PngTransform.hpp
    include/Ypng/PngWriter.hpp
    src/Ypng/PngInfo.cpp
    src/Ypng/PngTransform.cpp
    src/Ypng/PngWriter.cpp
    )

include(GNUInstallDirs)

target_include_directories(Ypng_PngWriter
    PUBLIC
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
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

if (Ypng_INSTALL)
    install(TARGETS Ypng_PngWriter
        EXPORT YpngConfig
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        )

    install(EXPORT YpngConfig
        FILE
            YpngConfig.cmake
        NAMESPACE
            Ypng::
        DESTINATION
            ${CMAKE_INSTALL_LIBDIR}/cmake/Ypng
        )

    install(
        DIRECTORY
            include/Ypng
        DESTINATION
            ${CMAKE_INSTALL_INCLUDEDIR}
    )

    #    install(
    #        FILES
    #            ${CMAKE_CURRENT_BINARY_DIR}/YpngVersion.hpp
    #        DESTINATION
    #            ${CMAKE_INSTALL_INCLUDEDIR}/Ypng
    #    )

    include(CMakePackageConfigHelpers)

    write_basic_package_version_file(YpngConfigVersion.cmake
        COMPATIBILITY SameMajorVersion
        )

    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/YpngConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Ypng
        )
endif ()
