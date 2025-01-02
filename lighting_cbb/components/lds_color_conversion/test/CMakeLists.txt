# Change name of the test suite to the component name
set(TEST_NAME lds_color_conversion)

project(cmocka-${TEST_NAME} C)
set(TEST_LIBRARIES PkgConfig::CMOCKA m)
set(COMPONENT_ROOT ..)

# Add test source files here
set(TEST_SOURCES
  lds_color_conversion_test.c
  ${COMPONENT_ROOT}/src/lds_color_conversion.c
  ${COMPONENT_ROOT}/../lds_color_algorithm/src/lds_det_array.c
)

include_directories(
  ${COMPONENT_ROOT}/inc
  ${COMPONENT_ROOT}/../lds_color_algorithm/inc
)

# Add the mocked functions you use here
set(
  MOCKED_FUNCTIONS
)

string(REPLACE ";" "" MOCKED_FUNCTIONS "${MOCKED_FUNCTIONS}")

add_cmocka_test(${TEST_NAME}
  SOURCES ${TEST_SOURCES}
  COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
  LINK_LIBRARIES ${TEST_LIBRARIES})

add_cmocka_test_environment(${TEST_NAME})

set_property(TARGET
  ${TEST_NAME}
  PROPERTY
  LINK_FLAGS
  "${DEFAULT_LINK_FLAGS} ${MOCKED_FUNCTIONS}")

target_compile_options(${TEST_NAME} PRIVATE -Werror)
