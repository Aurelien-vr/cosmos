cmake_minimum_required(VERSION 3.15)
project(cosmos VERSION 0.1 LANGUAGES CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default to Debug for faster iteration (so sanitizers are enabled by default)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Basic warning flags (apply globally)
add_compile_options(-Wall -Wextra)

option(ENABLE_ASAN "Enable AddressSanitizer for Debug builds" ON)

# If this CMakeLists is in cmake/, PROJECT_ROOT points to repo root
set(PROJECT_ROOT "${CMAKE_CURRENT_LIST_DIR}/../src")
set(PROJECT_SOURCES
  "${PROJECT_ROOT}/main.cpp"
)

# Create the target first
add_executable(cosmos ${PROJECT_SOURCES})

# Find libraries and link AFTER target creation
find_package(glfw3 3.4 REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(cosmos PRIVATE glfw OpenGL::GL)

# Apply sanitizer and related flags to the target for Debug config only
if(ENABLE_ASAN)
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    target_compile_options(cosmos PRIVATE
      $<$<CONFIG:Debug>:-fsanitize=address -fno-omit-frame-pointer -g -O1>
    )
    target_link_options(cosmos PRIVATE
      $<$<CONFIG:Debug>:-fsanitize=address -fno-omit-frame-pointer>
    )
  else()
    message(WARNING "AddressSanitizer flags enabled but compiler is not Clang/GNU.")
  endif()
endif()

# Platform notes: -fPIC isn't usually needed for executables on most desktop cases
