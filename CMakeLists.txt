cmake_minimum_required(VERSION 3.20)
project(MatrixCalculation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
  replxx
  GIT_REPOSITORY https://github.com/AmokHuginnsson/replxx.git
  GIT_TAG        master
)

FetchContent_Declare(
  tabulate
  GIT_REPOSITORY https://github.com/p-ranav/tabulate.git
  GIT_TAG        master
)

FetchContent_MakeAvailable(replxx tabulate)

add_library(linalg
  src/matrix.cpp
  src/square-matrix.cpp
  src/triangular-matrix.cpp
  src/vector.cpp
)
target_include_directories(linalg PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(linalg_cli
  src/cli/engine.cpp
  src/cli/io.cpp
  src/cli/parser.cpp
)
target_include_directories(linalg_cli PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(linalg_cli PUBLIC linalg replxx tabulate::tabulate)

add_executable(linalg_repl apps/repl/main.cpp)
target_link_libraries(linalg_repl PRIVATE linalg linalg_cli replxx tabulate::tabulate)
target_include_directories(linalg_repl PRIVATE ${CMAKE_SOURCE_DIR}/include)
