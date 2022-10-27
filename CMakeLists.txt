cmake_minimum_required(VERSION 3.23)
project(lge)

set(CMAKE_CXX_STANDARD 17)

# GLFW
set(GLFW_DIR vendor/glfw) # Set this to point to an up-to-date GLFW repo
option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
option(GLFW_DOCUMENT_INTERNALS "Include internals in documentation" OFF)
add_subdirectory(${GLFW_DIR} binary_dir EXCLUDE_FROM_ALL)
include_directories(${GLFW_DIR}/include)

# Dear ImGui
set(IMGUI_DIR vendor/imgui)
include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends ..)

# Libraries
set(ENV{VULKAN_SDK} "/Users/maartenpeels/VulkanSDK/1.3.231.0/macOS") # Can this be done better?
find_package(Vulkan REQUIRED)
set(LIBRARIES "glfw;Vulkan::Vulkan")

# Use vulkan headers from glfw:
include_directories(${GLFW_DIR}/deps)

file(GLOB sources Engine/*.cpp Engine/*.h)

add_executable(gle
        ${sources}
        main.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_vulkan.cpp
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        /Users/maartenpeels/VulkanSDK/1.3.231.0/macOS/include
)

# GLM
add_subdirectory(vendor/glm)
target_include_directories(gle PUBLIC vendor/glm)

target_link_libraries(gle ${LIBRARIES})
target_compile_definitions(gle PUBLIC -DImTextureID=ImU64)