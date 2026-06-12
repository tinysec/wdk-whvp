# wdk-whvp

[![WDK](https://img.shields.io/badge/WDK-7.1-blue)](#)
[![arch](https://img.shields.io/badge/arch-amd64-informational)](#)
[![CMake](https://img.shields.io/badge/CMake-targets-064f8c)](#cmake-usage)

## Introduction

`wdk-whvp` is a standalone WDK 7 compatible package for the Windows Hypervisor
Platform user-mode API. It is not a source library; it only provides rewritten
public headers and amd64 import libraries for downstream projects that need to
build with the Windows 7 WDK toolchain.

The headers are adapted from Windows SDK headers and remove dependencies on
newer API-set and WinAPI-family headers that are unavailable in WDK 7.

## Features

- WDK 7 friendly `WinHvPlatformDefs.h`, `WinHvPlatform.h`, and
  `WinHvEmulation.h`.
- amd64 import library for `C:\Windows\System32\WinHvPlatform.dll`.
- amd64 import library for `C:\Windows\System32\WinHvEmulation.dll`.
- No bundled source code, generated code, submodules, or configure-time
  downloads.
- CMake imported targets: `whvp::whvp` and `whvp::emu`.
- amd64 only.

## CMake Usage

Use `FetchContent`:

```cmake
include(FetchContent)

FetchContent_Declare(
    whvp
    GIT_REPOSITORY https://github.com/tinysec/wdk-whvp.git
    GIT_TAG v0.1.0)
FetchContent_MakeAvailable(whvp)

target_link_libraries(your_target PRIVATE whvp::whvp)
```

`whvp::whvp` links `WinHvPlatform.lib`. Link `whvp::emu` separately when using
the emulator API:

```cmake
target_link_libraries(your_target PRIVATE whvp::whvp whvp::emu)
```
