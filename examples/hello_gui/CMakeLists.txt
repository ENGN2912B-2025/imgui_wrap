
add_gui_executable(hello_gui hello_gui.cpp)
target_link_libraries(hello_gui PUBLIC imgui_wrap)

if (USE_GUI_TEST_ENGINE)
  target_sources(hello_gui PRIVATE hello_gui_tests.cpp)
  target_link_libraries(hello_gui PUBLIC imgui_test_engine)
endif()
