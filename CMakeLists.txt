cmake_minimum_required(VERSION 3.15)
project(cosmos VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -g -O0)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

add_compile_options(-Wall -Wextra -g)

option(ENABLE_ASAN "Enable AddressSanitizer for Debug builds" ON)

set(PROJECT_SOURCES
  "${PROJECT_SOURCE_DIR}/src/main.cpp"
  "${PROJECT_SOURCE_DIR}/src/glad.c"  
  "${PROJECT_SOURCE_DIR}/src/auFontRendering.cpp"
  "${PROJECT_SOURCE_DIR}/src/auCharacter.cpp"
  "${PROJECT_SOURCE_DIR}/src/Shader.cpp"
  "${PROJECT_SOURCE_DIR}/src/VBO.cpp"
  "${PROJECT_SOURCE_DIR}/src/VAO.cpp"
  "${PROJECT_SOURCE_DIR}/src/EBO.cpp"
)

add_executable(cosmos ${PROJECT_SOURCES})

find_package(glfw3 3.4 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(Freetype REQUIRED)

# Link using the modern imported target for GLFW
target_link_libraries(cosmos PRIVATE glfw OpenGL::GL Freetype::Freetype)

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
