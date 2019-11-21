cmake_minimum_required(VERSION 3.0)

set(LIB uart)
#set(MCU atmega328p)
#set(F_CPU 8000000UL)

#-----------------------------------------------------------------------------#
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_CXX_COMPILER avr-g++)
set(CMAKE_C_COMPILER avr-gcc)

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})
#-----------------------------------------------------------------------------#

add_library(${LIB} src/uart_atmega.c)
target_include_directories(${LIB} PUBLIC include)

#-----------------------------------------------------------------------------#
target_compile_options(${LIB} PUBLIC
    -mmcu=${MCU}
    -std=gnu11
    -O2
    -Wall
    -Werror
)
target_compile_definitions(${LIB} PUBLIC
	F_CPU=${F_CPU}	
)
#-----------------------------------------------------------------------------#