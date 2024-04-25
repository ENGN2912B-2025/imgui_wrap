
include(cmake/common.cmake)

option(USE_GLFW_GL3 "Enable GLFW/OpenGL3 backend" ON)
option(USE_GUI_TEST_ENGINE "Enable Dear ImGui test engine" OFF)

checkout_submodules(${PROJECT_SOURCE_DIR}/3rd-party/imgui)
if(USE_GLFW_GL3)
  checkout_submodules(${PROJECT_SOURCE_DIR}/3rd-party/glfw)
endif()
if(USE_GUI_TEST_ENGINE)
  checkout_submodules(${PROJECT_SOURCE_DIR}/3rd-party/imgui_test_engine)
endif()
