cmake_minimum_required(VERSION 3.20)

project(whvp VERSION 10.0.28000.0 LANGUAGES NONE)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(_whvp_is_top_level TRUE)
else()
    set(_whvp_is_top_level FALSE)
endif()

include(GNUInstallDirs)

option(WHVP_INSTALL "Install the whvp CMake package" "${_whvp_is_top_level}")

if(DEFINED WDK7_ARCH AND NOT WDK7_ARCH STREQUAL "amd64")
    message(FATAL_ERROR "wdk-whvp only provides amd64 import libraries.")
endif()

set(WHVP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(WHVP_AMD64_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/amd64")

function(_whvp_add_imported_library target_name library_name)
    set(_whvp_library_path "${WHVP_AMD64_LIBRARY_DIR}/${library_name}.lib")
    if(NOT EXISTS "${_whvp_library_path}")
        message(FATAL_ERROR "Missing import library: ${_whvp_library_path}")
    endif()

    add_library("${target_name}" UNKNOWN IMPORTED GLOBAL)
    set_target_properties("${target_name}" PROPERTIES
        IMPORTED_LOCATION "${_whvp_library_path}"
        INTERFACE_INCLUDE_DIRECTORIES "${WHVP_INCLUDE_DIR}")
endfunction()

_whvp_add_imported_library(whvp_platform WinHvPlatform)
add_library(whvp::whvp ALIAS whvp_platform)

_whvp_add_imported_library(whvp_emu WinHvEmulation)
add_library(whvp::emu ALIAS whvp_emu)

if(WHVP_INSTALL)
    install(
        DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

    install(
        DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib/"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        FILES_MATCHING
            PATTERN "*.lib")

    include(CMakePackageConfigHelpers)

    write_basic_package_version_file(
        "${PROJECT_BINARY_DIR}/whvpConfigVersion.cmake"
        VERSION "${PROJECT_VERSION}"
        COMPATIBILITY SameMajorVersion)

    configure_package_config_file(
        "${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in"
        "${PROJECT_BINARY_DIR}/whvpConfig.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/whvp")

    install(
        FILES
            "${PROJECT_BINARY_DIR}/whvpConfig.cmake"
            "${PROJECT_BINARY_DIR}/whvpConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/whvp")
endif()
