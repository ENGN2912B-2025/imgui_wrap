
add_library(imgui_wrap STATIC
  Backend.cpp
  Backend_Null.cpp
  Application.cpp
  Window.cpp
  Frame.cpp
  Sizer.cpp
  VerticalSizer.cpp
)

target_link_libraries(imgui_wrap PUBLIC imgui)

target_include_directories(imgui_wrap
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

if (USE_GLFW_GL3)
  target_sources(imgui_wrap PRIVATE
    Backend_GLFW_GL3.cpp
  )
endif()
