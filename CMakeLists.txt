cmake_minimum_required(VERSION 3.0)
project(whatever)

file(GLOB SRC ./*.cpp)
add_executable(whatever ${SRC})

include(ExternalProject)

set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/Rust)
ExternalProject_Add(
        rust_module
        DOWNLOAD_COMMAND ""
        CONFIGURE_COMMAND ""
        BUILD_COMMAND cargo build COMMAND cargo build --release
        BINARY_DIR "${CMAKE_SOURCE_DIR}/rust_module"
        INSTALL_COMMAND ""
        LOG_BUILD ON
)

add_dependencies(whatever rust_module)
target_link_libraries(whatever
        debug "${CMAKE_SOURCE_DIR}/rust_module/target/debug/librust_module.a"
        optimized "${CMAKE_SOURCE_DIR}/rust_module/target/release/librust_module.a"
)
set_target_properties(whatever PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
