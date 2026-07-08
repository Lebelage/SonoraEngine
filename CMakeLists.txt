cmake_minimum_required(VERSION 4.3)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")


if(APPLE)
    set(LLVM_PREFIX "/opt/homebrew/opt/llvm")
    
    set(CMAKE_C_COMPILER "${LLVM_PREFIX}/bin/clang" CACHE PATH "" FORCE)
    set(CMAKE_CXX_COMPILER "${LLVM_PREFIX}/bin/clang++" CACHE PATH "" FORCE)
    
    set(CMAKE_CXX_STDLIB_MODULES_JSON "${LLVM_PREFIX}/lib/c++/libc++.modules.json" CACHE PATH "" FORCE)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

set(CMAKE_CXX_MODULE_STD ON) 

project(SonoraEngine LANGUAGES CXX)

if(APPLE)

    add_compile_options("-stdlib=libc++" "-I${LLVM_PREFIX}/include")
    add_link_options("-stdlib=libc++" "-L${LLVM_PREFIX}/lib" "-Wl,-rpath,${LLVM_PREFIX}/lib")
    
    execute_process(COMMAND xcrun --show-sdk-path
                    OUTPUT_VARIABLE CMAKE_OSX_SYSROOT
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
    set(CMAKE_OSX_SYSROOT ${CMAKE_OSX_SYSROOT} CACHE PATH "" FORCE)
endif()

add_subdirectory(engine)
add_subdirectory(sandbox)