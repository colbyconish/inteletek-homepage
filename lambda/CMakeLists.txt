cmake_minimum_required(VERSION 3.15...4.0)

find_package(aws-lambda-runtime REQUIRED)

add_executable(
    contact-lambda
    main.cpp
    ../src/MainController.cpp
)

target_link_libraries(
    contact-lambda
    PRIVATE homepage
    PRIVATE AWS::aws-lambda-runtime
)

# Command: make aws-lambda-package-contact-lambda
aws_lambda_package_target(contact-lambda)
