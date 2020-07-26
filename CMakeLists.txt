cmake_minimum_required(VERSION 3.16)
project(ExchangeSimulator)

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(src/model model_dir)
aux_source_directory(src/service service_dir)
aux_source_directory(src/utils utils_dir)

find_package(Boost COMPONENTS log log_setup thread filesystem system unit_test_framework REQUIRED)

add_executable(ExchangeSimulator main.cpp
        ${model_dir}
        ${utils_dir}
        ${service_dir}
        )

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        ${Boost_LOG_SETUP_LIBRARY}
        ${Boost_LOG_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        )

add_subdirectory(test)
enable_testing()