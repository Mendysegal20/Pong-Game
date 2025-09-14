cmake_minimum_required(VERSION 3.10)
project(PongGame)

set(CMAKE_CXX_STANDARD 17)

# ---------- vcpkg Toolchain ----------
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "יש להגדיר את CMAKE_TOOLCHAIN_FILE לנתיב של vcpkg.cmake")
endif()

# ---------- Include Paths ----------
include_directories(${PROJECT_SOURCE_DIR}/include)

# ---------- Sources ----------
file(GLOB_RECURSE SRC_FILES "src/*.cpp")

# ---------- Build the main game ----------
add_executable(PongGame ${SRC_FILES})



# ---------- Copy assets ----------
add_custom_command(TARGET PongGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/assets
    $<TARGET_FILE_DIR:PongGame>/assets
)

# ---------- Find packages ----------
find_package(raylib CONFIG REQUIRED)
if(raylib_FOUND)
    target_link_libraries(PongGame PRIVATE raylib)
else()
    message(FATAL_ERROR "raylib לא נמצא – בדוק את vcpkg וה־triplet")
endif()

# ---------- Testing ----------
enable_testing()

file(GLOB_RECURSE TEST_FILES "tests/*.cpp")

if(TEST_FILES)
    add_executable(PongGameTests ${TEST_FILES})
    find_package(Catch2 CONFIG REQUIRED)
    target_link_libraries(PongGameTests PRIVATE Catch2::Catch2WithMain raylib)
    add_test(NAME PongTests COMMAND PongGameTests)
endif()
