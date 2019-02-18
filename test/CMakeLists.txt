find_package(Boost 1.65.0 REQUIRED COMPONENTS unit_test_framework)

add_executable(demoTest demoTest.cpp)

target_compile_definitions(demoTest PRIVATE BOOST_TEST_DYN_LINK BOOST_TEST_MAIN)

target_link_libraries(demoTest demo Boost::unit_test_framework)

add_test(NAME demoTest COMMAND $<TARGET_FILE:demoTest>)
