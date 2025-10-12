cmake_minimum_required(VERSION 3.10)

project(MatrixMultiplication C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(OpenMP REQUIRED)

include_directories(include)

add_library(matrix_functions SHARED src/matrix_functions.c)

add_executable(multiply_static_bucket  src/main_static_bucket.c)
target_link_libraries(multiply_static_bucket PRIVATE matrix_functions OpenMP::OpenMP_C)
add_executable(multiply_id src/main_id.c)
target_link_libraries(multiply_id PRIVATE matrix_functions OpenMP::OpenMP_C)

add_executable(multiply_bucket src/main_bucket.c)
target_link_libraries(multiply_bucket PRIVATE matrix_functions OpenMP::OpenMP_C)

add_executable(multiply_bucket_simd src/main_bucket_simd.c)
target_link_libraries(multiply_bucket_simd PRIVATE matrix_functions OpenMP::OpenMP_C)

add_executable(multiply_id_simd src/main_id_simd.c)
target_link_libraries(multiply_id_simd PRIVATE matrix_functions OpenMP::OpenMP_C)

add_executable(multiply_sequencial src/main.c)
target_link_libraries(multiply_sequencial PRIVATE matrix_functions OpenMP::OpenMP_C)



