# CMake generated Testfile for 
# Source directory: C:/Users/mendy/source/repos/PongGame/PongGame
# Build directory: C:/Users/mendy/source/repos/PongGame/PongGame/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(PongTests "C:/Users/mendy/source/repos/PongGame/PongGame/build/Debug/PongGameTests.exe")
  set_tests_properties(PongTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/mendy/source/repos/PongGame/PongGame/CMakeLists.txt;46;add_test;C:/Users/mendy/source/repos/PongGame/PongGame/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(PongTests "C:/Users/mendy/source/repos/PongGame/PongGame/build/Release/PongGameTests.exe")
  set_tests_properties(PongTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/mendy/source/repos/PongGame/PongGame/CMakeLists.txt;46;add_test;C:/Users/mendy/source/repos/PongGame/PongGame/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(PongTests "C:/Users/mendy/source/repos/PongGame/PongGame/build/MinSizeRel/PongGameTests.exe")
  set_tests_properties(PongTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/mendy/source/repos/PongGame/PongGame/CMakeLists.txt;46;add_test;C:/Users/mendy/source/repos/PongGame/PongGame/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(PongTests "C:/Users/mendy/source/repos/PongGame/PongGame/build/RelWithDebInfo/PongGameTests.exe")
  set_tests_properties(PongTests PROPERTIES  _BACKTRACE_TRIPLES "C:/Users/mendy/source/repos/PongGame/PongGame/CMakeLists.txt;46;add_test;C:/Users/mendy/source/repos/PongGame/PongGame/CMakeLists.txt;0;")
else()
  add_test(PongTests NOT_AVAILABLE)
endif()
