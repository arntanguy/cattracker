# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

project(led-blink)

set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

include($ENV{IDF_PATH}/tools/cmake/idf.cmake)

idf_build_process(esp32
                COMPONENTS freertos esptool_py driver
                SDKCONFIG ${CMAKE_BINARY_DIR}/sdkconfig
                BUILD_DIR ${CMAKE_BINARY_DIR})

# FIXME: fails for now, see https://github.com/espressif/esp-idf/issues/10122
# add_subdirectory(main)


set(elf_file ${CMAKE_PROJECT_NAME}.elf)
add_executable(${elf_file} main/led-blink.cpp)
target_link_libraries(${elf_file} idf::freertos idf::spi_flash idf::driver)
idf_build_executable(${elf_file})


