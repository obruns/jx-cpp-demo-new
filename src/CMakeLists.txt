add_library(demo INTERFACE)

target_include_directories(demo INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

set_target_properties(demo PROPERTIES
    INTERFACE_COMPILE_FEATURES cxx_std_17
)

target_link_libraries(demo INTERFACE cxxDefaults)
