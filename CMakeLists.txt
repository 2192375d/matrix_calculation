
cmake_minimum_required(VERSION 3.20)
project(MatrixCalculation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Your math library
add_library(linalg
  src/matrix.cpp
  src/square-matrix.cpp
  src/triangular-matrix.cpp
  src/vector.cpp
)
target_include_directories(linalg PUBLIC ${CMAKE_SOURCE_DIR}/include)

# --- Dependencies via FetchContent
include(FetchContent)

# replxx
FetchContent_Declare(
  replxx
  GIT_REPOSITORY https://github.com/AmokHuginnsson/replxx.git
  GIT_TAG        master        # (better: pin a commit/release for reproducible builds)
)

# tabulate (header-only)
FetchContent_Declare(
  tabulate
  GIT_REPOSITORY https://github.com/p-ranav/tabulate.git
  GIT_TAG        master        # (better: pin a commit/release)
)

# Make both available
FetchContent_MakeAvailable(replxx tabulate)

# --- REPL executable
add_executable(linalg_repl apps/repl/main.cpp)
target_link_libraries(linalg_repl PRIVATE linalg replxx tabulate::tabulate)
target_include_directories(linalg_repl PRIVATE ${CMAKE_SOURCE_DIR}/include)

