cmake_minimum_required(VERSION 3.29)
project(crime-sphere LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_LIBRARIES "${CMAKE_CXX_STANDARD_LIBRARIES} -lstdc++")

# Use shared libraries on macOS to avoid linking issues
if(APPLE)
    option(BUILD_SHARED_LIBS "Build shared libraries" ON)
else()
    option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
endif()

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main
        main.cpp
        FileProcessing.cpp
        FileProcessing.h
        Frame.cpp
        Frame.h
        UI.cpp
        UI.h
        kdtree/KDTwoTree.cpp
        kdtree/KDTwoTree.h
        heap/CrimeHeap.cpp
        heap/CrimeHeap.h
)

target_link_libraries(main PRIVATE sfml-graphics sfml-window sfml-system)
target_compile_features(main PRIVATE cxx_std_17)

# On macOS, make sure to link against the C++ standard library
if(APPLE)
    target_link_libraries(main PRIVATE "-lstdc++")
endif()

if(WIN32)
    add_custom_command(
            TARGET main
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
            VERBATIM)
endif()