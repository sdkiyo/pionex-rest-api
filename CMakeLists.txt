cmake_minimum_required(VERSION 4.1.2)

project(rest_pionex LANGUAGES C)


add_executable(${PROJECT_NAME} main.c test.c)

target_link_libraries(${PROJECT_NAME} PUBLIC crypto)
