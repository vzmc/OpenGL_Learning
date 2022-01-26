set(PROJECT_NAME "CameraSystems")

include_directories(Headers/
                    ${CMAKE_SOURCE_DIR}/Glitter/Headers/
                    ${CMAKE_SOURCE_DIR}/Glitter/Vendor/assimp/include/
                    ${CMAKE_SOURCE_DIR}/Glitter/Vendor/bullet/src/
                    ${CMAKE_SOURCE_DIR}/Glitter/Vendor/glad/include/
                    ${CMAKE_SOURCE_DIR}/Glitter/Vendor/glfw/include/
                    ${CMAKE_SOURCE_DIR}/Glitter/Vendor/glm/
                    ${CMAKE_SOURCE_DIR}/Glitter/Vendor/stb/
                    ${CMAKE_SOURCE_DIR}/Glitter/Vendor/imgui/)

file(GLOB PROJECT_HEADERS Headers/*)
file(GLOB PROJECT_SOURCES Sources/*)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\"
                -DUNICODE
                -D_UNICODE)

add_executable(${PROJECT_NAME} ${PROJECT_HEADERS} ${PROJECT_SOURCES})

target_link_libraries(${PROJECT_NAME} GlitterLib)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Glitter/Shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>/Shaders
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Glitter/Textures $<TARGET_FILE_DIR:${PROJECT_NAME}>/Textures)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Glitter/"
    FOLDER "SubProjects")
