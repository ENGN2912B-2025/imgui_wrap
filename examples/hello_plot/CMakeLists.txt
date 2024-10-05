
add_gui_executable(hello_plot hello_plot.cpp)
target_link_libraries(hello_plot PUBLIC imgui_wrap)

# if (USE_GUI_TEST_ENGINE)
#   target_sources(hello_gui PRIVATE hello_gui_tests.cpp)
#   target_link_libraries(hello_gui PUBLIC imgui_test_engine)
#   target_compile_definitions(imgui_wrap
#     PRIVATE -DTEST_REGISTRATION_FUNCTION=registerHelloGuiTests)
# endif()
