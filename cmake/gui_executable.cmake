
# include this file only once
include_guard(GLOBAL)

function(add_gui_executable target)
  add_executable(${target} ${ARGN})
  if(MSVC AND NOT BUILD_TESTS)
    target_link_options(${target}
      PRIVATE "/SUBSYSTEM:WINDOWS" "/ENTRY:mainCRTStartup")
  endif()
endfunction()
