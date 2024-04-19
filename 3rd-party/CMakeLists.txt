
# GLFW #######################################################################
if (USE_GLFW_GL3)
  if (LINUX)
    set(GLFW_BUILD_WAYLAND 0)
    set(GLFW_BUILD_X11 1)
  endif()
  add_subdirectory(glfw)
endif(USE_GLFW_GL3)

# Dear ImGui #################################################################
set(IMGUI_DIR ${CMAKE_CURRENT_LIST_DIR}/imgui)

add_library(imgui STATIC
  imgui/imgui.cpp
  #imgui/imgui_demo.cpp
  imgui/imgui_draw.cpp
  imgui/imgui_tables.cpp
  imgui/imgui_widgets.cpp
)

target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/backends)
target_link_libraries(imgui PUBLIC glfw)
#target_compile_definitions(imgui PUBLIC -DGL_SILENCE_DEPRECATION)
target_compile_definitions(imgui
  PUBLIC -DIMGUI_USER_CONFIG="${CMAKE_CURRENT_LIST_DIR}/imconfig.h")

if (USE_GLFW_GL3)
  target_sources(imgui PRIVATE
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
  )

  target_compile_definitions(imgui
    PUBLIC
      -DUSE_GLFW_GL3
      -DGLFW_HAS_PER_MONITOR_DPI=1
  )

  if (WIN32)
    target_link_libraries(imgui PUBLIC "opengl32")
  elseif(APPLE)
    target_link_libraries(imgui PUBLIC "-framework OpenGL")
  elseif(LINUX)
    target_link_libraries(imgui PUBLIC "-lGL")
  endif()

endif(USE_GLFW_GL3)

# Dear ImGui Test Engine #####################################################
set(IMGUI_TEST_ENGINE_DIR ${CMAKE_CURRENT_LIST_DIR}/imgui_test_engine)

# add_library(imgui_app STATIC
#   ${IMGUI_TEST_ENGINE_DIR}/shared/imgui_app.h
#   ${IMGUI_TEST_ENGINE_DIR}/shared/imgui_app.cpp
# )
# target_include_directories(imgui_app PUBLIC ${IMGUI_TEST_ENGINE_DIR}/shared)
# target_link_libraries(imgui_app PUBLIC imgui)
