project(
    'Crank Example',
    'cpp',
    version : '0.3.0',
    meson_version : '>= 0.60.0',
    license : 'MIT',
    default_options : [
        'warning_level=3',
        'cpp_std=c++20',
    ]
)

include = include_directories('include')
srcs = files([
    'src/main.cxx'
])

subdir('src/basic')

crank_dep = dependency('crank', fallback : ['crank', 'crank'])

main = executable(
    'basic-crank-example-main',
    srcs,
    include_directories: include,
    dependencies : [crank_dep]
)
