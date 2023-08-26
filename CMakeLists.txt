cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

if(NOT TARGET score_lib_base)
  include(ScoreExternalAddon)
endif()

if(NOT TARGET score_plugin_avnd)
  return()
endif()

project(score_addon_threadtest LANGUAGES CXX)

avnd_score_plugin_init(
  BASE_TARGET score_addon_threadtest
)

avnd_score_plugin_add(
  BASE_TARGET score_addon_threadtest
  SOURCES
    ThreadTest/ThreadTest.hpp
    ThreadTest/ThreadTestModel.hpp
    ThreadTest/ThreadTestModel.cpp
    ThreadTest/numpyToCppUtils.cpp
    ThreadTest/numpyToCppUtils.hpp
    ThreadTest/PythonEnvModel.cpp
    ThreadTest/PythonEnvModel.hpp
  TARGET threadtest
  MAIN_CLASS ThreadTest
  NAMESPACE Example
)

find_package(Python3 REQUIRED COMPONENTS Interpreter Development NumPy)
if(VERBOSE)
    cmake_print_variables(Python3_INCLUDE_DIRS)
    cmake_print_variables(Python3_NumPy_INCLUDE_DIRS)
endif()
find_package(Boost COMPONENTS python numpy REQUIRED)
target_link_libraries(score_addon_threadtest PRIVATE  ${Boost_LIBRARIES} ${Python3_LIBRARIES} ${Python3_NumPy_LIBRARIES})
target_include_directories(score_addon_threadtest  PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})

avnd_score_plugin_finalize(
  BASE_TARGET score_addon_threadtest
  PLUGIN_VERSION 1
  PLUGIN_UUID "f8221248-ed1e-4049-b2ad-11f91387997c"
)
