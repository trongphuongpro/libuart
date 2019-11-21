cmake_minimum_required(VERSION 3.0)


set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_C_COMPILER avr-gcc)

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})


set(LIB_NAME uart)

add_library(${LIB_NAME} src/uart_atmega.c)
target_include_directories(${LIB_NAME} PUBLIC include)
target_compile_options(${LIB_NAME} PUBLIC
    -mmcu=${MCU}
    -std=gnu11
    -O2
    -Wall
    -Werror
)
target_compile_definitions(${LIB_NAME} PUBLIC
	F_CPU=${F_CPU}	
)