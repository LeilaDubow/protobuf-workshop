cmake_minimum_required(VERSION 3.12)

set(PICO_SDK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/pico-sdk)
include_directories(${PICO_SDK_PATH})
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(Protobuf C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

set(NANOPB_PATH ${CMAKE_SOURCE_DIR}/lib/nanopb)
include_directories(${NANOPB_PATH})

include_directories(src)

add_library(nanopb STATIC
    ${NANOPB_PATH}/pb_common.c
    ${NANOPB_PATH}/pb_encode.c
    ${NANOPB_PATH}/pb_decode.c
)

add_executable(${PROJECT_NAME}
	src/main.c
	src/protos/message.pb.c
)

target_link_libraries(${PROJECT_NAME}
	pico_stdlib
	nanopb
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_add_extra_outputs(${PROJECT_NAME})
