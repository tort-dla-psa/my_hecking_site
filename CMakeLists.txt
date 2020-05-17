cmake_minimum_required(VERSION 3.0.0)
project(my_hecking_site VERSION 0.1.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)

find_package(Wt REQUIRED Wt HTTP)
find_package(Boost COMPONENTS
    system
    program_options
    filesystem
    thread
  REQUIRED
)

add_executable(my_hecking_site main.cpp)
target_link_libraries(my_hecking_site
                    Wt::Wt
                    Wt::HTTP
                    Boost::system
                    Boost::thread
                    Boost::filesystem
                    Boost::program_options
                    stdc++fs)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)