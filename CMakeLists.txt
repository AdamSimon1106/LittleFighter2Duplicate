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

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/libs)


# Debug sanitizer for memory issues (use only on non-MSVC)
target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
if (NOT MSVC)
    target_link_options(${CMAKE_PROJECT_NAME} PRIVATE $<$<CONFIG:DEBUG>:-fsanitize=address>)
endif()

# Add internal project folders (must come AFTER add_executable)
add_subdirectory(include)
add_subdirectory(src)
add_subdirectory(resources)

# Set the source and destination paths
set(DATA_SOURCE_DIR "${CMAKE_SOURCE_DIR}/data")
set(DATA_BINARY_DIR "${CMAKE_BINARY_DIR}/data")

# Copy the entire data folder before building
add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${DATA_SOURCE_DIR} ${DATA_BINARY_DIR}
    COMMENT "Copying all data files to build directory"
)
# Set the source and destination paths
set(LEVEL_SOURCE_DIR "${CMAKE_SOURCE_DIR}/levelsData")
set(LEVEL_BINARY_DIR "${CMAKE_BINARY_DIR}/levelsData")

# Copy the entire data folder before building
add_custom_command(
    TARGET ${CMAKE_PROJECT_NAME} PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${LEVEL_SOURCE_DIR} ${LEVEL_BINARY_DIR}
    COMMENT "Copying all data files to build directory"
)

# SFML location and setup
set(SFML_LOCATION "C:/SFML/SFML-2.6.1")
set(SFML_DIR "${SFML_LOCATION}/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics REQUIRED)

# Link SFML to your target
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sfml-graphics sfml-main sfml-audio)

# Optional: set SFML properties per config
set_target_properties(sfml-main sfml-system sfml-window sfml-graphics sfml-audio sfml-network PROPERTIES MAP_IMPORTED_CONFIG_RELWITHDEBINFO RELEASE)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

# Custom ZIP or SFML setup if needed
include(cmake/Zip.cmake)
include(cmake/SFML.cmake)
