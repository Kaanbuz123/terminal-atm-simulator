cmake_minimum_required(VERSION 3.15)
project(terminal_atm_simulator VERSION 1.0.0 LANGUAGES C)

add_executable(terminal-atm src/main.c)
set_target_properties(terminal-atm PROPERTIES C_STANDARD 11 C_STANDARD_REQUIRED YES)

if(MSVC)
  target_compile_options(terminal-atm PRIVATE /W4)
else()
  target_compile_options(terminal-atm PRIVATE -Wall -Wextra -Wpedantic)
endif()
