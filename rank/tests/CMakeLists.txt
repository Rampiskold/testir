#project(Example4Tests)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/..)

add_executable(itemtest ${SRC} itemtest.cpp)
target_compile_definitions(itemtest PRIVATE rank_STATIC_DEFINE )
add_test(itemtest ${EXECUTABLE_OUTPUT_PATH}/itemtest)

add_executable(ranktest ${SRC} ranktest.cpp)
target_compile_definitions(ranktest PRIVATE rank_STATIC_DEFINE )
add_test(ranktest ${EXECUTABLE_OUTPUT_PATH}/ranktest)

add_executable(ranktestrev ${SRC} ranktestrev.cpp)
target_compile_definitions(ranktestrev PRIVATE rank_STATIC_DEFINE )
add_test(ranktestrev ${EXECUTABLE_OUTPUT_PATH}/ranktestrev)

add_executable(sumtest ${SRC} sumtest.cpp)
target_compile_definitions(sumtest PRIVATE rank_STATIC_DEFINE )
add_test(sumtest ${EXECUTABLE_OUTPUT_PATH}/sumtest)

add_executable(sumtestrev ${SRC} sumtestrev.cpp)
target_compile_definitions(sumtestrev PRIVATE rank_STATIC_DEFINE )
add_test(sumtestrev ${EXECUTABLE_OUTPUT_PATH}/sumtestrev)
