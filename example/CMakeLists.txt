
add_executable(simple_test simple_test.cpp)

if (TARGET simple_test)
    target_link_libraries(simple_test jsonutil)
endif ()
