MITK_CREATE_MODULE(TestModuleSL4
  DEPENDS Mitk
  INTERNAL_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/../libSL1"
)

add_dependencies(${TESTDRIVER} TestModuleSL4)
