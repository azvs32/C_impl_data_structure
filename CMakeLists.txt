cmake_minimum_required(VERSION 3.29)
project(C_impl_data_structure C)

set(CMAKE_C_STANDARD 11)

set(SOURCES
        impl/azvs_list.c
        impl/azvs_queue.c
        impl/azvs_stack.c
        impl/base/__base_log.c
        impl/base/__base_memory.c
        impl/azvs_linear.c
)

add_executable(C_impl_data_structure main.c ${SOURCES})
