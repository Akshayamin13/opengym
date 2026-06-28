cmake_minimum_required(VERSION 3.16)
project(OpenGym VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBPQXX REQUIRED libpqxx)

include_directories(include)
include_directories(${LIBPQXX_INCLUDE_DIRS})

add_executable(opengym
    src/main.cpp
    src/Member.cpp
    src/MemberRepository.cpp
    src/Contract.cpp
    src/ContractRepository.cpp
)

target_link_libraries(opengym ${LIBPQXX_LIBRARIES})
target_link_directories(opengym PRIVATE ${LIBPQXX_LIBRARY_DIRS})