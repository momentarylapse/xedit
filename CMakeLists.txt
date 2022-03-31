# created by xmake

project(xhui)
cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(SOURCE 
	src/lib/base/array.cpp
	src/lib/base/pointer.cpp
	src/lib/base/strings.cpp
	src/lib/file/file.cpp
	src/lib/file/file_op.cpp
	src/lib/file/msg.cpp
	src/lib/file/path.cpp
	src/lib/image/color.cpp
	src/lib/image/image.cpp
	src/lib/image/image_bmp.cpp
	src/lib/image/image_jpg.cpp
	src/lib/image/image_png.cpp
	src/lib/image/image_tga.cpp
	src/lib/image/ImagePainter.cpp
	src/lib/math/complex.cpp
	src/lib/math/interpolation.cpp
	src/lib/math/math.cpp
	src/lib/math/matrix.cpp
	src/lib/math/matrix3.cpp
	src/lib/math/plane.cpp
	src/lib/math/quaternion.cpp
	src/lib/math/random.cpp
	src/lib/math/ray.cpp
	src/lib/math/rect.cpp
	src/lib/math/vector.cpp
	src/lib/nix/nix.cpp
	src/lib/nix/nix_draw.cpp
	src/lib/nix/nix_light.cpp
	src/lib/nix/nix_shader.cpp
	src/lib/nix/nix_textures.cpp
	src/lib/nix/nix_vertexbuffer.cpp
	src/lib/nix/nix_view.cpp
	src/lib/xhui/Controls/Button.cpp
	src/lib/xhui/Controls/Control.cpp
	src/lib/xhui/Controls/DrawingArea.cpp
	src/lib/xhui/Controls/Grid.cpp
	src/lib/xhui/Controls/Label.cpp
	src/lib/xhui/Painter.cpp
	src/lib/xhui/Window.cpp
	src/lib/xhui/xhui.cpp
	src/main.cpp
)

find_package(PkgConfig REQUIRED)


# zlib mandatory
pkg_check_modules(ZLIB REQUIRED zlib)
include_directories(${ZLIB_INCLUDE_DIRS})
link_directories(${ZLIB_LIBRARY_DIRS})
list(APPEND DEPS ${ZLIB_LIBRARIES})
add_definitions(${ZLIB_CFLAGS_OTHER})
add_compile_definitions(HAS_LIB_ZLIB=1)

# gl mandatory
pkg_check_modules(GL REQUIRED gl)
include_directories(${GL_INCLUDE_DIRS})
link_directories(${GL_LIBRARY_DIRS})
list(APPEND DEPS ${GL_LIBRARIES})
add_definitions(${GL_CFLAGS_OTHER})
add_compile_definitions(HAS_LIB_GL=1)

# glfw mandatory
pkg_check_modules(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})
list(APPEND DEPS ${GLFW_LIBRARIES})
add_definitions(${GLFW_CFLAGS_OTHER})
add_compile_definitions(HAS_LIB_GLFW=1)

# freetype2 mandatory
pkg_check_modules(FREETYPE2 REQUIRED freetype2)
include_directories(${FREETYPE2_INCLUDE_DIRS})
link_directories(${FREETYPE2_LIBRARY_DIRS})
list(APPEND DEPS ${FREETYPE2_LIBRARIES})
add_definitions(${FREETYPE2_CFLAGS_OTHER})
add_compile_definitions(HAS_LIB_FREETYPE2=1)

add_executable(xhui ${SOURCE})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(xhui PRIVATE Threads::Threads ${DEPS})

add_compile_definitions(INSTALL_PREFIX="${CMAKE_INSTALL_PREFIX}")

install(TARGETS xhui DESTINATION bin)
