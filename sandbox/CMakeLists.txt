# ==============================================================================
# Sandbox/CMakeLists.txt
# ==============================================================================

add_executable(Sandbox)

target_compile_features(Sandbox PUBLIC cxx_std_23)
set_target_properties(Sandbox PROPERTIES CXX_MODULE_STD ON)

# Поиск исходников песочницы
file(GLOB_RECURSE SANDBOX_MODULES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cppm"
)
file(GLOB_RECURSE SANDBOX_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

target_sources(Sandbox
        PRIVATE
        FILE_SET cxx_modules TYPE CXX_MODULES
        FILES ${SANDBOX_MODULES}

        PRIVATE
        ${SANDBOX_SOURCES}
)

target_include_directories(Sandbox PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(Sandbox
        PRIVATE
        Sonora::Engine
)