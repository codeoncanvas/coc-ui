if( NOT TARGET CoC-UI )
    get_filename_component( COC-UI_SOURCE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../src" ABSOLUTE )

    FILE(GLOB_RECURSE COC-UI_SOURCES ${COC-UI_SOURCE_PATH}/*.cpp)

    add_library( CoC-UI ${COC-UI_SOURCES} )
    target_include_directories( CoC-UI PUBLIC
            "${COC-UI_SOURCE_PATH}/button"
            "${COC-UI_SOURCE_PATH}/image"
            "${COC-UI_SOURCE_PATH}/scrollbar"
            "${COC-UI_SOURCE_PATH}/scrollview" )

    # If Cinder included from this block:

    target_include_directories( CoC-UI SYSTEM BEFORE PUBLIC "${CINDER_PATH}/include" )

    if( NOT TARGET cinder )
        include( "${CINDER_PATH}/proj/cmake/configure.cmake" )
        find_package( cinder REQUIRED PATHS
                "${CINDER_PATH}/${CINDER_LIB_DIRECTORY}"
                "$ENV{CINDER_PATH}/${CINDER_LIB_DIRECTORY}" )
    endif()

    #    target_link_libraries( ${BLOCK_NAME} PRIVATE cinder )

    # Add CoC-Core block as a dependency
    get_filename_component( COC-CORE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../../CoC-Core/proj/cmake" ABSOLUTE )
    find_package( CoC-Core REQUIRED PATHS "${COC-CORE_MODULE_PATH}" )
    if (CoC-Core_FOUND)
        add_dependencies( CoC-UI CoC-Core )
        target_link_libraries( CoC-UI PUBLIC CoC-Core)
    endif()

    target_link_libraries( CoC-UI PRIVATE cinder)

endif()