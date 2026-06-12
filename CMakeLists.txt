cmake_minimum_required(VERSION 3.20)

project(whvp VERSION 1.0.0 LANGUAGES NONE)

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
