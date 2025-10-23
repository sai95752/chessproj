cmake_minimum_required(VERSION 3.28)
project(Chess LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3.0 COMPONENTS Graphics Window System Network REQUIRED)

#ui/ux library tgui
find_package(TGUI 1.0 REQUIRED)

add_executable(Chess
    src/main.cpp
    src/renderer.cpp
    src/board.cpp
    src/theme.cpp
    src/game.cpp
    src/validator.cpp
    src/menu.cpp
    
    
    include/renderer.h
    include/theme.h
    include/board.h
    include/piece.h
    include/game.h
    include/validator.h
    include/menu.h
)

# sfml 3 uses :: 
target_link_libraries(Chess PRIVATE
    SFML::Graphics 
    SFML::Window 
    SFML::System
    SFML::Network
    TGUI::TGUI
)

target_include_directories(Chess PRIVATE include)

add_custom_command(TARGET Chess POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Chess>/assets
)

set_target_properties(Chess PROPERTIES
    XCODE_GENERATE_SCHEME YES
    XCODE_SCHEME_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
