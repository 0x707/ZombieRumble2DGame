cmake_minimum_required(VERSION 3.1)
project(ZombieRumble)

set(SFML_DIR "~/SFML/SFML_build")
find_package(SFML 2.5 COMPONENTS graphics system audio window REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/inc" "~/cpp/SCDS/")
file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(ZombieRumble ${SOURCES})
target_link_libraries(ZombieRumble sfml-graphics sfml-system sfml-audio sfml-window)
