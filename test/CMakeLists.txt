cmake_minimum_required(VERSION 3.10)

aux_source_directory(../src/model test_model_dir)
aux_source_directory(../src/service test_service_dir)
aux_source_directory(../src/utils test_utils_dir)

add_executable(Test TestCases.cpp
        ${test_model_dir}
        ${test_utils_dir}
        ${test_service_dir}
        )

target_link_libraries(Test
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_LOG_SETUP_LIBRARY}
        ${Boost_LOG_LIBRARY})

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)