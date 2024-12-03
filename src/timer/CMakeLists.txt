
target_sources(imgui_wrap
  PUBLIC
    Timer.cpp
)

if (USE_TIMERCPP)
  target_link_libraries(imgui_wrap PUBLIC timercpp)
  target_compile_definitions(imgui_wrap PUBLIC USE_TIMERCPP)
endif(USE_TIMERCPP)
