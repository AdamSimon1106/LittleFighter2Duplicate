# Collect all files recursively under this folder
file(GLOB_RECURSE RESOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*"
)

# Make this list visible to parent CMakeLists
set(ALL_RESOURCE_FILES ${RESOURCE_FILES} PARENT_SCOPE)
