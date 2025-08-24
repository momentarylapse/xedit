# created by xmake

cmake_minimum_required(VERSION 3.21)
project(xedit)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)

if(WIN32)
	list(APPEND COMPILE_OPTIONS /permissive-)
endif()


#=======================================================================================
#    libraries
#=======================================================================================

find_package(PkgConfig REQUIRED)



# lib: zlib (mandatory)
find_package(ZLIB REQUIRED)
list(APPEND DEPS ZLIB::ZLIB)
list(APPEND COMPILE_DEFINITIONS HAS_LIB_ZLIB=1)


# lib: vulkan or gl (mandatory)
set(VULKAN_OR_GL "vulkan" CACHE STRING "Use vulkan or gl?")
find_package(Vulkan COMPONENTS shaderc_combined)
if(VULKAN_FOUND)
	list(APPEND VULKAN_OR_GL_FOUND "vulkan")
endif()
find_package(OpenGL)
if(OPENGL_FOUND AND NOT APPLE AND NOT WIN32)
	list(APPEND VULKAN_OR_GL_FOUND "gl")
endif()
if(VULKAN_OR_GL_FOUND)
	if(NOT ${VULKAN_OR_GL} IN_LIST VULKAN_OR_GL_FOUND)
		list(GET VULKAN_OR_GL_FOUND 0 X)
		set(VULKAN_OR_GL ${X} CACHE STRING "choose" FORCE)
		message(WARNING "Choice for VULKAN_OR_GL invalid, using ${VULKAN_OR_GL} instead")
	endif()
else()
	message(SEND_ERROR "Neither vulkan or gl found") #  or/nor..
	set(VULKAN_OR_GL "")
endif()
if(VULKAN_OR_GL STREQUAL "vulkan")
	list(APPEND DEPS Vulkan::Vulkan Vulkan::shaderc_combined)
	list(APPEND COMPILE_DEFINITIONS HAS_LIB_VULKAN=1)
endif()
if(VULKAN_OR_GL STREQUAL "gl")
	list(APPEND DEPS OpenGL::OpenGL)
	list(APPEND COMPILE_DEFINITIONS HAS_LIB_GL=1)
endif()


# lib: shaderc (optional)
set(LIB_SHADERC_ENABLED true CACHE BOOL "Use shaderc library?")
pkg_check_modules(SHADERC shaderc)
if(SHADERC_FOUND)
else()
	set(LIB_SHADERC_ENABLED false CACHE BOOL "shaderc library not found" FORCE)
endif()
if(${LIB_SHADERC_ENABLED})
	list(APPEND INCLUDE_DIRECTORIES ${SHADERC_INCLUDE_DIRS})
	list(APPEND LINK_DIRECTORIES ${SHADERC_LIBRARY_DIRS})
	list(APPEND DEPS ${SHADERC_LIBRARIES})
	list(APPEND COMPILE_OPTIONS ${SHADERC_CFLAGS_OTHER})
	list(APPEND COMPILE_DEFINITIONS HAS_LIB_SHADERC=1)
else()
	list(APPEND COMPILE_DEFINITIONS HAS_LIB_SHADERC=0)
endif()


# lib: glfw (mandatory)
find_package(glfw3 REQUIRED)
list(APPEND DEPS glfw)
list(APPEND COMPILE_DEFINITIONS HAS_LIB_GLFW=1)


# lib: freetype2 (mandatory)
find_package(Freetype REQUIRED)
list(APPEND DEPS Freetype::Freetype)
list(APPEND COMPILE_DEFINITIONS HAS_LIB_FREETYPE2=1)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
list(APPEND DEPS Threads::Threads)


#=======================================================================================
#    target xedit
#=======================================================================================

add_executable(xedit
	src/dialogs/DocumentSwitcher.cpp
	src/lib/any/any.cpp
	src/lib/any/conversion.cpp
	src/lib/base/array.cpp
	src/lib/base/pointer.cpp
	src/lib/base/strings.cpp
	src/lib/image/color.cpp
	src/lib/image/image.cpp
	src/lib/image/image_bmp.cpp
	src/lib/image/image_jpg.cpp
	src/lib/image/image_png.cpp
	src/lib/image/image_tga.cpp
	src/lib/image/ImagePainter.cpp
	src/lib/math/Box.cpp
	src/lib/math/complex.cpp
	src/lib/math/interpolation.cpp
	src/lib/math/mat3.cpp
	src/lib/math/mat4.cpp
	src/lib/math/math.cpp
	src/lib/math/plane.cpp
	src/lib/math/quaternion.cpp
	src/lib/math/random.cpp
	src/lib/math/ray.cpp
	src/lib/math/rect.cpp
	src/lib/math/vec2.cpp
	src/lib/math/vec3.cpp
	src/lib/math/vec4.cpp
	src/lib/nix/_kaba_export.cpp
	src/lib/nix/nix.cpp
	src/lib/nix/nix_buffer.cpp
	src/lib/nix/nix_draw.cpp
	src/lib/nix/nix_framebuffer.cpp
	src/lib/nix/nix_light.cpp
	src/lib/nix/nix_shader.cpp
	src/lib/nix/nix_textures.cpp
	src/lib/nix/nix_vertexbuffer.cpp
	src/lib/nix/nix_view.cpp
	src/lib/os/app.cpp
	src/lib/os/CommandLineParser.cpp
	src/lib/os/config.cpp
	src/lib/os/date.cpp
	src/lib/os/file.cpp
	src/lib/os/filesystem.cpp
	src/lib/os/formatter.cpp
	src/lib/os/msg.cpp
	src/lib/os/path.cpp
	src/lib/os/stream.cpp
	src/lib/os/terminal.cpp
	src/lib/os/time.cpp
	src/lib/pattern/Observable.cpp
	src/lib/vulkan/_kaba_export.cpp
	src/lib/vulkan/AccelerationStructure.cpp
	src/lib/vulkan/Buffer.cpp
	src/lib/vulkan/CommandBuffer.cpp
	src/lib/vulkan/DescriptorSet.cpp
	src/lib/vulkan/Device.cpp
	src/lib/vulkan/FrameBuffer.cpp
	src/lib/vulkan/helper.cpp
	src/lib/vulkan/Instance.cpp
	src/lib/vulkan/Pipeline.cpp
	src/lib/vulkan/Queue.cpp
	src/lib/vulkan/RenderPass.cpp
	src/lib/vulkan/Semaphore.cpp
	src/lib/vulkan/Shader.cpp
	src/lib/vulkan/SwapChain.cpp
	src/lib/vulkan/Texture.cpp
	src/lib/vulkan/VertexBuffer.cpp
	src/lib/vulkan/vulkan.cpp
	src/lib/xhui/controls/Button.cpp
	src/lib/xhui/controls/CheckBox.cpp
	src/lib/xhui/controls/ColorButton.cpp
	src/lib/xhui/controls/ComboBox.cpp
	src/lib/xhui/controls/Control.cpp
	src/lib/xhui/controls/DrawingArea.cpp
	src/lib/xhui/controls/Edit.cpp
	src/lib/xhui/controls/Expander.cpp
	src/lib/xhui/controls/FileSelector.cpp
	src/lib/xhui/controls/Grid.cpp
	src/lib/xhui/controls/Group.cpp
	src/lib/xhui/controls/HeaderBar.cpp
	src/lib/xhui/controls/Image.cpp
	src/lib/xhui/controls/Label.cpp
	src/lib/xhui/controls/ListView.cpp
	src/lib/xhui/controls/MenuBar.cpp
	src/lib/xhui/controls/MultilineEdit.cpp
	src/lib/xhui/controls/Overlay.cpp
	src/lib/xhui/controls/RadioButton.cpp
	src/lib/xhui/controls/Separator.cpp
	src/lib/xhui/controls/Slider.cpp
	src/lib/xhui/controls/SpinButton.cpp
	src/lib/xhui/controls/TabControl.cpp
	src/lib/xhui/controls/ToggleButton.cpp
	src/lib/xhui/controls/Toolbar.cpp
	src/lib/xhui/controls/Viewport.cpp
	src/lib/xhui/dialogs/ColorSelectionDialog.cpp
	src/lib/xhui/dialogs/FileSelectionDialog.cpp
	src/lib/xhui/dialogs/MenuPopup.cpp
	src/lib/xhui/dialogs/QuestionDialog.cpp
	src/lib/xhui/draw/font.cpp
	src/lib/xhui/_kaba_export.cpp
	src/lib/xhui/Application.cpp
	src/lib/xhui/ContextGL.cpp
	src/lib/xhui/ContextVulkan.cpp
	src/lib/xhui/Dialog.cpp
	src/lib/xhui/language.cpp
	src/lib/xhui/Menu.cpp
	src/lib/xhui/Painter.cpp
	src/lib/xhui/PainterGL.cpp
	src/lib/xhui/PainterVulkan.cpp
	src/lib/xhui/Panel.cpp
	src/lib/xhui/Resource.cpp
	src/lib/xhui/Theme.cpp
	src/lib/xhui/Window.cpp
	src/lib/xhui/xhui.cpp
	src/parser/BaseParser.cpp
	src/parser/ParserC.cpp
	src/parser/ParserCmake.cpp
	src/parser/ParserHui.cpp
	src/parser/ParserIni.cpp
	src/parser/ParserKaba.cpp
	src/parser/ParserPython.cpp
	src/parser/ParserShader.cpp
	src/parser/ParserText.cpp
	src/DocumentEditor.cpp
	src/EditorWindow.cpp
	src/HighlightScheme.cpp
	src/main.cpp)
target_include_directories(xedit PUBLIC ${INCLUDE_DIRECTORIES})
target_link_directories(xedit PUBLIC ${LINK_DIRECTORIES})
target_compile_options(xedit PUBLIC ${COMPILE_OPTIONS})
target_compile_definitions(xedit PUBLIC ${COMPILE_DEFINITIONS}  SOURCE_ROOT="${CMAKE_SOURCE_DIR}" INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}")
target_link_libraries(xedit PUBLIC ${DEPS})
target_include_directories(xedit PUBLIC src)


#=======================================================================================
#    install
#=======================================================================================

set(RESOURCE_DESTINATION share/xedit)

# binaries
install(TARGETS xedit DESTINATION bin)	

# resources
install(DIRECTORY "static" DESTINATION ${RESOURCE_DESTINATION})