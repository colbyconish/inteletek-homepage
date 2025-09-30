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

set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "Don't build shared libs")
set(CARES_SHARED OFF CACHE INTERNAL "Don't build shared libs")
set(CARES_STATIC ON CACHE INTERNAL "Build static libs")

# Fetch all dependencies
FetchContent_MakeAvailable(drogon c-ares_lib)

find_package(Drogon CONFIG REQUIRED)
find_package(AWSSDK REQUIRED COMPONENTS core sesv2)

set(CMAKE_ENABLE_EXPORTS TRUE)

add_executable(
    homepage
    src/main.cpp 
    src/MainController.cpp
)

drogon_create_views(
    homepage 
    ${CMAKE_CURRENT_SOURCE_DIR}/views
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_include_directories(
    homepage
    PUBLIC include
)

target_link_libraries(
    homepage
    PUBLIC drogon
    PUBLIC c-ares
    PUBLIC aws-cpp-sdk-core
    PUBLIC aws-cpp-sdk-sesv2
)

if(DEFINED BUILD_LAMBDA)
    add_subdirectory(lambda)
endif()
