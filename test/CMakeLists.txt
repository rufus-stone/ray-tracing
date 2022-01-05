# +-------------+
# | Tests setup |
# +-------------+

message(STATUS "Configuring ${PROJECT_NAME}_tests...")

add_executable(${PROJECT_NAME}_tests "")

# Set source files
target_sources(${PROJECT_NAME}_tests PRIVATE tests.cpp ${SOURCE_FILES})

# Add the include directory to the target
target_include_directories(${PROJECT_NAME}_tests
                           PRIVATE ${PROJECT_SOURCE_DIR}/include)

# We're using C++20
set_target_properties(
  ${PROJECT_NAME}_tests
  PROPERTIES CXX_STANDARD 20
             CXX_STANDARD_REQUIRED YES
             CXX_EXTENSIONS NO)

# Set compiler warnings
if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE -W4 -WX)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Werror -Wall -Wextra
                                                 -Wold-style-cast -Wpedantic)
endif()

# +--------------+
# | Dependencies |
# +--------------+

include(FetchContent)

# Download Catch2
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.0.0-preview3)

FetchContent_MakeAvailable(Catch2)

# Link in the dependenices
target_link_libraries(${PROJECT_NAME}_tests PRIVATE Catch2::Catch2WithMain
                                                    spdlog::spdlog)
