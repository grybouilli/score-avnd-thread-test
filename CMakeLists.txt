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
  TARGET threadtest
  MAIN_CLASS ThreadTest
  NAMESPACE Example
)

avnd_score_plugin_finalize(
  BASE_TARGET score_addon_threadtest
  PLUGIN_VERSION 1
  PLUGIN_UUID "f8221248-ed1e-4049-b2ad-11f91387997c"
)
