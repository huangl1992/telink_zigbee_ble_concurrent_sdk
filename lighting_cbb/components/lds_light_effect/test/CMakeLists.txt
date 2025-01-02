# Change name of the test suite to the component name
set(TEST_NAME lds_light_effect_test)

project(cmocka-${TEST_NAME} C)
set(TEST_LIBRARIES PkgConfig::CMOCKA)
set(COMPONENT_ROOT ..)

# Add test source files here
set(TEST_SOURCES 
  lds_light_effect_test.c
  # ${COMPONENT_ROOT}/src/lds_light_effect.c
)

include_directories(
  ${COMPONENT_ROOT}/inc
)

# Add the mocked functions you use here
#set(
  #MOCKED_FUNCTIONS
#)

#string(REPLACE ";" "" MOCKED_FUNCTIONS "${MOCKED_FUNCTIONS}")

add_cmocka_test(${TEST_NAME}
  SOURCES ${TEST_SOURCES}
  COMPILE_OPTIONS ${DEFAULT_C_COMPILE_FLAGS}
  LINK_LIBRARIES ${TEST_LIBRARIES})

add_cmocka_test_environment(${TEST_NAME})

set_property(TARGET
  ${TEST_NAME}
  PROPERTY
  LINK_FLAGS
  "${DEFAULT_LINK_FLAGS}")

target_compile_options(${TEST_NAME} PRIVATE -Werror)

