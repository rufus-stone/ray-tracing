cmake_minimum_required(VERSION 3.15...3.21)

# +---------------+
# | Project setup |
# +---------------+

project(
  raytracer
  VERSION 0.1.0
  DESCRIPTION "Following the Ray Tracing in One Weekend tutorial"
  HOMEPAGE_URL "https://github.com/rufus-stone/ray-tracing"
  LANGUAGES CXX)

# Create our executable
add_executable(${PROJECT_NAME})

# Create a variable to hold our source files (so we don't have to copy/paste the
# source files into the tests CMakeLists.txt)
set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/ppm.cpp
    ${PROJECT_SOURCE_DIR}/src/vec3.cpp
    ${PROJECT_SOURCE_DIR}/src/ray.cpp
    ${PROJECT_SOURCE_DIR}/src/hittable.cpp
    ${PROJECT_SOURCE_DIR}/src/hittable_list.cpp
    ${PROJECT_SOURCE_DIR}/src/sphere.cpp
    ${PROJECT_SOURCE_DIR}/src/camera.cpp)

# Set source files
target_sources(${PROJECT_NAME} PRIVATE src/main.cpp ${SOURCE_FILES})

# Add the include directory to the target
target_include_directories(${PROJECT_NAME}
                           PRIVATE ${PROJECT_SOURCE_DIR}/include)

# We're using C++17
set_target_properties(
  ${PROJECT_NAME}
  PROPERTIES CXX_STANDARD 20
             CXX_STANDARD_REQUIRED YES
             CXX_EXTENSIONS NO)

# Set compiler warnings
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE -W4 -WX)
else()
  target_compile_options(
    ${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra -Wold-style-cast -Wpedantic
  )# -fsanitize=undefined,address
endif()

# +--------------+
# | Dependencies |
# +--------------+

# Download Conan script if needed
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(
    "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(
    DOWNLOAD
    "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
    "${CMAKE_BINARY_DIR}/conan.cmake"
    EXPECTED_HASH
      SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
    TLS_VERIFY ON)
endif()

# Load the Conan script
include(${CMAKE_BINARY_DIR}/conan.cmake)

# Configure Conan to grab our dependencies
conan_cmake_configure(REQUIRES spdlog/1.9.2 GENERATORS cmake_find_package)

# Do some settings stuff??
conan_cmake_autodetect(settings)

# Install the dependencies
conan_cmake_install(
  PATH_OR_REFERENCE
  .
  BUILD
  missing
  REMOTE
  conancenter
  SETTINGS
  ${settings})

# This is necessary otherwise find_package() doesn't look in the right place for
# the conan dependencies
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

# Find the Conan dependencies
find_package(spdlog REQUIRED)

# Link in the dependenices
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog
)# -fsanitize=undefined,address

# +-------+
# | Tests |
# +-------+

# Enable testing
include(CTest)
message("BUILD_TESTING: ${BUILD_TESTING}")
if(BUILD_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()
