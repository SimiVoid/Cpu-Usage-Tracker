
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests)

function(create_test)
    set(TEST_NAME ${ARGV0})
    set(TEST_SOURCES ${ARGV1})

    add_executable(${TEST_NAME} ${TEST_SOURCES})
    target_link_libraries(${TEST_NAME} pthread ${PROJECT_NAME}-modules)
    add_test(${TEST_NAME} ${TEST_NAME})

endfunction(create_test)

create_test(analyzer analyzer.c)
create_test(reader reader.c)