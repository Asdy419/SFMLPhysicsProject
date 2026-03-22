cmake_minimum_required(VERSION 3.16)
project(Kinemechanics LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build SFML statically so no DLLs need to be distributed
set(BUILD_SHARED_LIBS FALSE CACHE BOOL "" FORCE)

# Automatically download and build SFML 2.6.0
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        2.6.0
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(SFML)

add_executable(Kinemechanics
    SFMLPhysicsProject/main.cpp
    SFMLPhysicsProject/Button.cpp
    SFMLPhysicsProject/CheckBox.cpp
    SFMLPhysicsProject/StatesManager.cpp
)

target_include_directories(Kinemechanics PRIVATE SFMLPhysicsProject)

# Required when linking SFML statically
target_compile_definitions(Kinemechanics PRIVATE SFML_STATIC)

target_link_libraries(Kinemechanics PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

# Set VS debugger working directory to project root so assets resolve correctly
set_target_properties(Kinemechanics PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
)

# Copy assets next to the executable after every build
add_custom_command(TARGET Kinemechanics POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/Kinemechanics assets"
        "$<TARGET_FILE_DIR:Kinemechanics>/Kinemechanics assets"
    COMMENT "Copying assets to output directory"
)
