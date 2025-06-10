cmake_minimum_required(VERSION 3.26)

project(LittleFighter2Duplicate)
set(MY_AUTHORS "Benny_Beer-Omer_Shimoni-Adam_Simonov")

# C++ standard settings
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Optional compiler settings
include(cmake/CompilerSettings.cmake)

# Create the main executable target early so subdirectories can modify it
add_executable(${CMAKE_PROJECT_NAME})

# Debug sanitizer for memory issues (use only on non-MSVC)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
if (NOT MSVC)
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
endif()

# Add internal project folders (must come AFTER add_executable)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(resources)

# SFML location and setup
set(SFML_LOCATION "C:/SFML/SFML-2.6.1")
set(SFML_DIR "${SFML_LOCATION}/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics REQUIRED)

# Link SFML to your target
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sfml-graphics sfml-main)

# Optional: set SFML properties per config
set_target_properties(sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})


# Custom ZIP or SFML setup if needed
include(cmake/Zip.cmake)
include(cmake/SFML.cmake)
