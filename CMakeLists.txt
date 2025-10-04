project("dkdsp")

add_library(${PROJECT_NAME} INTERFACE)

target_include_directories(${PROJECT_NAME} INTERFACE ${${PROJECT_NAME}_SOURCE_DIR/lib})
install(TARGETS dkdsp DESTINATION lib)
