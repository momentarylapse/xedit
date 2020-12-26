project('xhui', 'cpp', default_options : ['cpp_std=c++17', 'warning_level=1', 'optimization=2', 'debug=true'])
add_project_arguments('-Wno-unused', '-Wstrict-aliasing=0', '-fno-omit-frame-pointer', language : ['cpp'])

#install_data
#meson.add_install_script('')
#install_subdir

cc = meson.get_compiler('cpp')

# mandatory dependencies
mdep = cc.find_library('m', required : false)
threaddep = dependency('threads')
zlibdep = dependency('zlib')
add_project_arguments('-DHAS_LIB_ZLIB=1', language : ['cpp'])
gldep = dependency('GL')
add_project_arguments('-DHAS_LIB_GL=1', language : ['cpp'])
glfwdep = dependency('glfw')
add_project_arguments('-DHAS_LIB_GLFW=1', language : ['cpp'])
deps = [mdep, threaddep, zlibdep, gldep, glfwdep]


sources = [
	'src/lib/base/array.cpp',
	'src/lib/base/pointer.cpp',
	'src/lib/base/strings.cpp',
	'src/lib/file/file.cpp',
	'src/lib/file/file_op.cpp',
	'src/lib/file/msg.cpp',
	'src/lib/file/path.cpp',
	'src/lib/image/color.cpp',
	'src/lib/image/image.cpp',
	'src/lib/image/image_bmp.cpp',
	'src/lib/image/image_jpg.cpp',
	'src/lib/image/image_png.cpp',
	'src/lib/image/image_tga.cpp',
	'src/lib/image/ImagePainter.cpp',
	'src/lib/math/complex.cpp',
	'src/lib/math/interpolation.cpp',
	'src/lib/math/math.cpp',
	'src/lib/math/matrix.cpp',
	'src/lib/math/matrix3.cpp',
	'src/lib/math/plane.cpp',
	'src/lib/math/quaternion.cpp',
	'src/lib/math/random.cpp',
	'src/lib/math/ray.cpp',
	'src/lib/math/rect.cpp',
	'src/lib/math/vector.cpp',
	'src/lib/nix/nix.cpp',
	'src/lib/nix/nix_draw.cpp',
	'src/lib/nix/nix_light.cpp',
	'src/lib/nix/nix_shader.cpp',
	'src/lib/nix/nix_textures.cpp',
	'src/lib/nix/nix_vertexbuffer.cpp',
	'src/lib/nix/nix_view.cpp',
	'src/lib/xhui/Window.cpp',
	'src/lib/xhui/xhui.cpp',
	'src/main.cpp'
]


executable('xhui', sources, dependencies : deps, install : true)

