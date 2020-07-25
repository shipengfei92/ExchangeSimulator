cmake_minimum_required(VERSION 3.10)

add_executable(Test UnitTests.cpp)

target_link_libraries(Test ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
        ${Boost_DATE_TIME_LIBRARY})

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)