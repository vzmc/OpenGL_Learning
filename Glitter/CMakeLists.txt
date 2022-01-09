project(GlitterLib)

include_directories(Headers/
                    Vendor/assimp/include/
                    Vendor/bullet/src/
                    Vendor/glad/include/
                    Vendor/glfw/include/
                    Vendor/glm/
                    Vendor/stb/)

file(GLOB VENDORS_SOURCES Vendor/glad/src/glad.c)
file(GLOB PROJECT_HEADERS Headers/*.hpp)
file(GLOB PROJECT_SOURCES Sources/*.cpp)
file(GLOB PROJECT_CONFIGS ${CMAKE_SOURCE_DIR}/Readme.md
                          ${CMAKE_SOURCE_DIR}/.gitattributes
                          ${CMAKE_SOURCE_DIR}/.gitignore
                          ${CMAKE_SOURCE_DIR}/.gitmodules)

source_group("Headers" FILES ${PROJECT_HEADERS})
source_group("Sources" FILES ${PROJECT_SOURCES})
source_group("Vendors" FILES ${VENDORS_SOURCES})

add_definitions(-DGLFW_INCLUDE_NONE
                -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\"
                -DUNICODE
                -D_UNICODE)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${VENDORS_SOURCES} ${PROJECT_CONFIGS})

target_link_libraries(${PROJECT_NAME} assimp glfw
                      ${GLFW_LIBRARIES} ${GLAD_LIBRARIES}
                      BulletDynamics BulletCollision LinearMath)
