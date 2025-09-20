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

# Configure AWS sdk
FetchContent_Declare(
    aws-sdk-cpp
    GIT_REPOSITORY https://github.com/aws/aws-sdk-cpp.git
    GIT_TAG 1.11.652 
    OVERRIDE_FIND_PACKAGE
)

set(BUILD_SHARED_LIBS ON CACHE INTERNAL "Build shared libs")

set(ENABLE_TESTING OFF CACHE INTERNAL "Don't waste my time")
set(AUTORUN_UNIT_TESTING OFF CACHE INTERNAL "Please no")
set(BUILD_ONLY "sesv2" CACHE INTERNAL "Build only the ses aws sdk")

# Fetch all dependencies
FetchContent_MakeAvailable(drogon c-ares_lib aws-sdk-cpp)

find_package(Drogon CONFIG REQUIRED)

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
    PRIVATE include
    PRIVATE ${aws-sdk-cpp_SOURCE_DIR}/src/aws-cpp-sdk-core/include
    PRIVATE ${aws-sdk-cpp_SOURCE_DIR}/crt/aws-crt-cpp/include
    PRIVATE ${aws-sdk-cpp_SOURCE_DIR}/crt/aws-crt-cpp/crt/aws-c-common/include/
    PRIVATE ${aws-sdk-cpp_SOURCE_DIR}/crt/aws-crt-cpp/crt/aws-c-common/verification/cbmc/include/
    PRIVATE ${aws-sdk-cpp_SOURCE_DIR}/crt/aws-crt-cpp/crt/aws-c-io/include/
    PRIVATE ${aws-sdk-cpp_SOURCE_DIR}/crt/aws-crt-cpp/crt/aws-c-mqtt/include/
    PRIVATE ${aws-sdk-cpp_SOURCE_DIR}/crt/aws-crt-cpp/crt/aws-c-auth/include/
    PRIVATE ${aws-sdk-cpp_SOURCE_DIR}/crt/aws-crt-cpp/crt/aws-c-sdkutils/include/
)

target_link_libraries(
    homepage
    PRIVATE drogon
    PRIVATE c-ares
    PRIVATE aws-cpp-sdk-core
    PRIVATE aws-cpp-sdk-sesv2
)
