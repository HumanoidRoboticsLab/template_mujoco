# Copyright 2021 DeepMind Technologies Limited
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.16)

# INTERPROCEDURAL_OPTIMIZATION is enforced when enabled.
set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)
# Default to GLVND if available.
set(CMAKE_POLICY_DEFAULT_CMP0072 NEW)

# This line has to appear before 'PROJECT' in order to be able to disable incremental linking
set(MSVC_INCREMENTAL_DEFAULT ON)

project(
  mujoco_template
  VERSION 2.3.6
  DESCRIPTION "MuJoCo Template Project for cross-platform"
)

enable_language(C)
enable_language(CXX)
if(APPLE)
  enable_language(OBJC)
  enable_language(OBJCXX)
endif()

add_subdirectory(${PROJECT_SOURCE_DIR}/libraries/mujoco)                             # Add subdirectory
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/libraries/mujoco/sample/cmake") # CMake Path append

# Check if we are building as standalone project.
set(SAMPLE_STANDALONE OFF)
set(_INSTALL_SAMPLES ON)
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
  set(SAMPLE_STANDALONE ON)
  # If standalone, do not install the samples.
  set(_INSTALL_SAMPLES OFF)
endif()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(SAMPLE_STANDALONE)
  include(SampleOptions)
else()
  enforce_mujoco_macosx_min_version()
endif()
include(SampleDependencies)

set(MUJOCO_SAMPLE_COMPILE_OPTIONS "${AVX_COMPILE_OPTIONS}" "${EXTRA_COMPILE_OPTIONS}")
set(MUJOCO_SAMPLE_LINK_OPTIONS "${EXTRA_LINK_OPTIONS}")

if(MUJOCO_HARDEN)
  if(WIN32)
    set(MUJOCO_SAMPLE_LINK_OPTIONS "${MUJOCO_SAMPLE_LINK_OPTIONS}" -Wl,/DYNAMICBASE)
  else()
    set(MUJOCO_SAMPLE_COMPILE_OPTIONS "${MUJOCO_SAMPLE_COMPILE_OPTIONS}" -fPIE)
    if(APPLE)
      set(MUJOCO_SAMPLE_LINK_OPTIONS "${MUJOCO_SAMPLE_LINK_OPTIONS}" -Wl,-pie)
    else()
      set(MUJOCO_SAMPLE_LINK_OPTIONS "${MUJOCO_SAMPLE_LINK_OPTIONS}" -pie)
    endif()
  endif()
endif()


# Custom Starts from here
find_package(Eigen3 REQUIRED)

include_directories(
    include
    INCLUDE_DIRS include
    LIBRARIES ${PROJECT_NAME}
    ${EIGEN3_INCLUDE_DIR}
    DEPENDS system_lib
)
add_executable(template src/template.cpp ${SIMULATE_RESOURCE_FILES})
target_include_directories(template PUBLIC
  ${CMAKE_SOURCE_DIR}/include
)
target_link_libraries(
  template
  libsimulate
  mujoco::mujoco
  glfw
  Threads::Threads
  lodepng
)
target_compile_options(template PUBLIC ${MUJOCO_SIMULATE_COMPILE_OPTIONS})

if(APPLE AND MUJOCO_BUILD_MACOS_FRAMEWORKS)
  embed_in_bundle(template)
endif()

# Do not install if macOS Bundles are created as RPATH is managed manually there.
if(APPLE AND MUJOCO_BUILD_MACOS_FRAMEWORKS)
  set(_INSTALL_SAMPLES OFF)
endif()