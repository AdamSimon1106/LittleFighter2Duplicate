# Recursively include all directories under "include"
file(GLOB_RECURSE HEADER_FILES 
    CONFIGURE_DEPENDS 
    LIST_DIRECTORIES false 
    RELATIVE ${CMAKE_CURRENT_LIST_DIR} 
    *.h
)

# Add the include/ path and its subfolders
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})

# Add headers to the project (mainly for IDEs)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${HEADER_FILES})
