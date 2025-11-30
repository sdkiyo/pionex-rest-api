cmake_minimum_required(VERSION 4.1.2)

project(test1 LANGUAGES C)

set(P ../../sources/)
add_library(PionexRest SHARED
	${P}getBalance.c
	${P}signature.c
	${P}restInit.c
	${P}newLimitOrder.c
)
target_include_directories(PionexRest PRIVATE ../../includes/)
target_link_libraries(PionexRest PRIVATE crypto)

add_executable(${PROJECT_NAME} main.c)
