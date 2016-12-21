cmake_minimum_required(VERSION 3.0)
project(whatever)

file(GLOB SRC ./*.cpp)
add_executable(whatever ${SRC})

include(ExternalProject)

set_directory_properties(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/rust_module)
ExternalProject_Add(
        rust_module
        DOWNLOAD_COMMAND ""
        CONFIGURE_COMMAND ""
        UPDATE_COMMAND cd ${CMAKE_SOURCE_DIR}/rust_module; cargo build; cargo build --release
        BUILD_COMMAND cargo build COMMAND cargo build --release
        INSTALL_COMMAND ""
        LOG_BUILD ON
        BINARY_DIR "${CMAKE_SOURCE_DIR}/rust_module"
)

add_dependencies(whatever rust_module)
target_link_libraries(whatever
        debug "${CMAKE_SOURCE_DIR}/rust_module/target/debug/librust_module.a"
        optimized "${CMAKE_SOURCE_DIR}/rust_module/target/release/librust_module.a"
        dl pthread gcc_s c m rt util
)
set_target_properties(whatever PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED ON)
