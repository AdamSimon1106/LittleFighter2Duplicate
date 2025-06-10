# Recursively find all files in the resources folder
file(GLOB_RECURSE RESOURCE_FILES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*"
)

foreach(RESOURCE ${RESOURCE_FILES})
    # Get the path relative to the resources/ folder
    file(RELATIVE_PATH REL_PATH "${CMAKE_CURRENT_SOURCE_DIR}" "${RESOURCE}")

    # Reconstruct the destination path under the binary dir
    set(DEST "${CMAKE_BINARY_DIR}/resources/${REL_PATH}")

    # Use configure_file to copy file and preserve structure
    configure_file(
        "${RESOURCE}"         # Input
        "${DEST}"             # Output
        COPYONLY              # Don't process the file
    )
endforeach()
