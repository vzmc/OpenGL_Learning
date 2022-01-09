project(Template)

include_directories(Headers/
                    ${CMAKE_SOURCE_DIR}/Glitter/Headers/
                    ${CMAKE_SOURCE_DIR}/Glitter/Vendor/assimp/include/
                    ${CMAKE_SOURCE_DIR}/Glitter/Vendor/bullet/src/
                    ${CMAKE_SOURCE_DIR}/Glitter/Vendor/glad/include/
                    ${CMAKE_SOURCE_DIR}/Glitter/Vendor/glfw/include/
                    ${CMAKE_SOURCE_DIR}/Glitter/Vendor/glm/
                    ${CMAKE_SOURCE_DIR}/Glitter/Vendor/stb/)

file(GLOB PROJECT_HEADERS Headers/*.hpp)
file(GLOB PROJECT_SOURCES Sources/*.cpp)
file(GLOB PROJECT_SHADERS Shaders/*.comp
                          Shaders/*.frag
                          Shaders/*.geom
                          Shaders/*.vert)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Shaders" FILES ${PROJECT_SHADERS})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\"
                -DUNICODE
                -D_UNICODE)

add_executable(${PROJECT_NAME} ${PROJECT_HEADERS} ${PROJECT_SOURCES} ${PROJECT_SHADERS})

target_link_libraries(${PROJECT_NAME} GlitterLib)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${PROJECT_SHADERS})

set_target_properties(${PROJECT_NAME} PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
    FOLDER "SubProjects")
