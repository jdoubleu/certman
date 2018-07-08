find_package(Doxygen)

if(NOT DOXYGEN_FOUND)
    message(SEND_ERROR "Doxygen is needed to build the documentation.")
else()
    set(doxyfile_in ${PROJECT_SOURCE_DIR}/cmake/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(${PROJECT_NAME}_doc_reference
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
endif()
