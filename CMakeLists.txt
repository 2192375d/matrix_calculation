cmake_minimum_required(VERSION 3.20)
project(MatrixCalculation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(linalg
  src/matrix.cpp
  src/square-matrix.cpp
  src/triangular-matrix.cpp
  src/vector.cpp
)

target_include_directories(linalg PUBLIC ${CMAKE_SOURCE_DIR}/include)

# --- Bring in replxx without cloning ---
include(FetchContent)
FetchContent_Declare(
  replxx
  GIT_REPOSITORY https://github.com/AmokHuginnsson/replxx.git
  GIT_TAG        master   # or pin a commit for stability
)
FetchContent_MakeAvailable(replxx)  # adds a target named 'replxx'

# --- Your REPL executable ---
add_executable(linalg_repl apps/repl/main.cpp)
target_link_libraries(linalg_repl PRIVATE linalg replxx)
target_include_directories(linalg_repl PRIVATE ${CMAKE_SOURCE_DIR}/include)
