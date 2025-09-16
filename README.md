# Pong Game 


## 🎥 Videos of the game in action
![Gameplay 1](https://github.com/user-attachments/assets/e1512543-3b65-4b80-92b2-f6816064b9c4)
![Gameplay 2](https://github.com/user-attachments/assets/feb81bdf-9d3b-4563-bfff-6b3ae1b9ee40)


# 🚀 How to clone and build the game
### Pre-Requirements
- C++ compiler (Visual Studio / GCC / Clang)
- [vcpkg](https://github.com/microsoft/vcpkg) - for managing dependencies
- [CMake](https://cmake.org/download/) (3.20+ recommended)
- [raylib](https://www.raylib.com/) (required to build the game)
- [Catch2](https://github.com/catchorg/Catch2) (required to run the tests)


## 1️⃣ For Visual Studio users (Windows)

1.  Open **Visual Studio**.  
2.  Go to **File → Clone Repository…**  
3.  Paste the URL: https://github.com/Mendysegal20/Pong-Game
4.  Choose a local folder and click **Clone**.
5.  Visual Studio will detect `CMakeLists.txt` automatically and configure the project.
6.  Build and run the game by clicking the **Run / Play** button.
7.  ✅ No need to manually run CMake or create build directories. Visual Studio handles that.



## 2️⃣ For users on other platforms (Windows / Linux / macOS)
## Steps
  1. Clone the repository:
  - Go to bash
  - git clone https://github.com/Mendysegal20/Pong-Game.git
  - cd Pong-Game


  2. Create a build directory:
  - mkdir build
  - cd build


  3. Run CMake to generate build files:
  - cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake



  4. Build the project:
  - cmake --build .


  5. Run the game:
  - On Windows - ./PongGame.exe
  - On Linux - ./PongGame
    
