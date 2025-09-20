cmake_minimum_required(VERSION 3.15...4.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
    inteletek-homepage
    VERSION 1.0.0
    LANGUAGES CXX
)

include(FetchContent)

# Confugure drgon
FetchContent_Declare(
    drogon
    GIT_REPOSITORY https://github.com/drogonframework/drogon.git
    GIT_TAG v1.9.11
    OVERRIDE_FIND_PACKAGE
)

# Configure C-ares
FetchContent_Declare(
    c-ares_lib
    GIT_REPOSITORY https://github.com/c-ares/c-ares.git
    GIT_TAG v1.34.5
    OVERRIDE_FIND_PACKAGE
)

# Fetch all dependencies
FetchContent_MakeAvailable(drogon c-ares_lib)

find_package(Drogon CONFIG REQUIRED)

add_executable(
    homepage
    src/main.cpp 
    src/MainController.cpp
    ${compiled_views}
)

drogon_create_views(
    homepage 
    ${CMAKE_CURRENT_SOURCE_DIR}/views
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_include_directories(
    homepage
    PRIVATE include
)

target_link_libraries(
    homepage
    PRIVATE drogon
    PRIVATE c-ares
)
