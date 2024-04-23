
# from here: https://cliutils.gitlab.io/modern-cmake/chapters/projects/submodule.html

# include this file only once
include_guard(GLOBAL)

# Update submodules as needed
option(GIT_CHECKOUT_SUBMODULES "Checkout submodules during build" ON)

if (GIT_CHECKOUT_SUBMODULES)
  find_package(Git QUIET)
endif()

function(checkout_submodules)
  if(NOT GIT_CHECKOUT_SUBMODULES OR NOT GIT_FOUND OR NOT EXISTS "${PROJECT_SOURCE_DIR}/.git")
    return()
  endif()

  set(options RECURSIVE)
  set(oneValueArgs)
  set(multiValueArgs)
  cmake_parse_arguments(CHECKOUT_SUBMODULES "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  set(OPTIONS "")
  if(CHECKOUT_SUBMODULES_RECURSIVE)
    set(OPTIONS "--recursive")
  endif()

  foreach(submodule ${ARGN})
    message(STATUS "Updating submodule: ${submodule}")
    execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init ${OPTIONS} --checkout ${submodule}
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    RESULT_VARIABLE GIT_SUBMOD_RESULT)
    if(NOT GIT_SUBMOD_RESULT EQUAL "0")
    message(FATAL_ERROR "git submodule update ${submodule}: failed with ${GIT_SUBMOD_RESULT}")
    endif()
  endforeach()
endfunction(checkout_submodules)
