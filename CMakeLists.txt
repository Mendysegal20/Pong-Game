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
file(GLOB_RECURSE HEADER_FILES "include/*.h")

# ---------- Build the main game ----------
add_executable(PongGame
    ${SRC_FILES}
    ${HEADER_FILES}
)

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

# Glob עם CONFIGURE_DEPENDS – יגרום ל־CMake לבדוק מחדש את הקבצים בכל build
file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS "tests/*.cpp")
file(GLOB_RECURSE IMPLEMENTATION_FILES CONFIGURE_DEPENDS "src/*.cpp")
list(FILTER IMPLEMENTATION_FILES EXCLUDE REGEX "src/Source\\.cpp$")

if(TEST_FILES)
    add_executable(PongGameTests ${TEST_FILES} ${IMPLEMENTATION_FILES})
    
    # include directories
    target_include_directories(PongGameTests PRIVATE ${PROJECT_SOURCE_DIR}/include)
    
    # find Catch2
    find_package(Catch2 CONFIG REQUIRED)
    target_link_libraries(PongGameTests PRIVATE Catch2::Catch2WithMain raylib)

    # register the test
    add_test(NAME PongTests COMMAND PongGameTests)

    # optional: make the main build depend on the tests to ensure rebuild אוטומטי
    # add_dependencies(PongGameTests PongGame)
endif()
