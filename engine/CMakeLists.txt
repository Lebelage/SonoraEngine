# ==============================================================================
# Engine/CMakeLists.txt
# ==============================================================================

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)

if(NOT TARGET VulkanCppModule)
    add_library(VulkanCppModule STATIC)
    add_library(Vulkan::cppm ALIAS VulkanCppModule)

    target_compile_features(VulkanCppModule PUBLIC cxx_std_23)
    set_target_properties(VulkanCppModule PROPERTIES CXX_MODULE_STD ON)

    target_compile_definitions(VulkanCppModule PUBLIC
            VULKAN_HPP_DISPATCH_LOADER_DYNAMIC=1
            VULKAN_HPP_NO_STRUCT_CONSTRUCTORS=1
            VULKAN_HPP_NO_TO_STRING=1
    )

    target_include_directories(VulkanCppModule PRIVATE "${Vulkan_INCLUDE_DIR}")
    target_link_libraries(VulkanCppModule PUBLIC Vulkan::Vulkan)

    file(GLOB VULKAN_HPP_MODULES CONFIGURE_DEPENDS
            "${Vulkan_INCLUDE_DIR}/vulkan/*.cppm"
    )

    target_sources(VulkanCppModule
            PUBLIC
            FILE_SET cxx_modules TYPE CXX_MODULES
            BASE_DIRS "${Vulkan_INCLUDE_DIR}"
            FILES ${VULKAN_HPP_MODULES}
    )
endif()

add_library(Engine STATIC)
add_library(Sonora::Engine ALIAS Engine) 

target_compile_features(Engine PUBLIC cxx_std_23)
set_target_properties(Engine PROPERTIES CXX_MODULE_STD ON)

file(GLOB_RECURSE ENGINE_MODULES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cppm"
)
file(GLOB_RECURSE ENGINE_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

target_sources(Engine
        PUBLIC

        FILE_SET cxx_modules TYPE CXX_MODULES
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}"
        FILES ${ENGINE_MODULES}

        PRIVATE
        ${ENGINE_SOURCES}
)

# Экспортируем пути к заголовочным файлам (если есть обычные .h)
target_include_directories(Engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Линкуем зависимости движка
target_link_libraries(Engine
        PUBLIC
        Vulkan::cppm      

        PRIVATE
        glfw              
)