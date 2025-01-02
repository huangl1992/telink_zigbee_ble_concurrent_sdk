
project(matter_unit_test LANGUAGES C)
cmake_minimum_required(VERSION 3.10.2)
include(FindPkgConfig)
include(CMakePackageConfigHelpers)

message("ROOT_DIR=${ROOT_DIR}")

set(VS_ROOT ${ROOT_DIR} CACHE STRING "Value stream root path")
set(VS_COMPONENTS ${VS_ROOT}/components CACHE STRING "Value stream default components path")

# Add compile flags to build
SET(GCC_UNITTEST_COMPILE_FLAGS "-Wall -Werror")
SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_UNITTEST_COMPILE_FLAGS}")

# Setup cmocka
find_package(PkgConfig REQUIRED)
pkg_check_modules(CMOCKA REQUIRED IMPORTED_TARGET cmocka)
list(APPEND CMAKE_MODULE_PATH "../../../thirdparty/cmocka/cmake/Modules")
include(AddCMockaTest)
# Add component dirs here
set(COMPONENT_DIRS
    ${ROOT_DIR}/components
)

# Macro for finding test case directories
MACRO(FIND_TEST_DIRECTORIES return_list subdir)
    FILE(GLOB_RECURSE new_list LIST_DIRECTORIES true ${subdir}/*/test/*)
    SET(dir_list "")
    FOREACH(file_path ${new_list})
       # MESSAGE( STATUS "File path " ${file_path} )
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        if(IS_DIRECTORY ${dir_path})
            if (EXISTS ${dir_path}/CMakeLists.txt)
                SET(dir_list ${dir_list} ${dir_path})
            endif()
        endif()
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO()

# Add all found test directories to unit test build
foreach(subdir ${COMPONENT_DIRS})
    if(IS_DIRECTORY ${subdir})
        SET(test_list "")
        FIND_TEST_DIRECTORIES(test_list ${subdir})
        foreach(testfile ${test_list})
            SET(test_found true)
            SET(TEST_NAME "")

            #Find the name of the test in the path
            string(REPLACE "/" ";" TEST_PATH_LIST ${testfile})
            list(LENGTH TEST_PATH_LIST len)
            MATH(EXPR len "${len}-2")
            list(GET TEST_PATH_LIST ${len} TEST_NAME)

            #Apply filter if any
            if(NOT ${FILTER} STREQUAL "")
                string(COMPARE EQUAL  ${TEST_NAME} ${FILTER} test_found)
            endif()
            if(test_found)
                # Add the found testname as build directory
                MESSAGE( STATUS "Including unittest dir " ${testfile} " " ${TEST_NAME} )
                add_subdirectory(${testfile} ${TEST_NAME})
            endif()
        endforeach()
    endif()
endforeach()