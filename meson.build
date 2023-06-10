project(
    'crank',
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
srcs = files()

subdir('include')
subdir('src')

crank_lib_args = ['-DBUILDING_CRANK']

crank_lib = library(
    'crank',
    srcs,
    install : true,
    include_directories : include,
    cpp_args : crank_lib_args,
    gnu_symbol_visibility : 'hidden',
    version : '0.3.0',
    soversion : '0'
)

if meson.is_subproject()
    crank = declare_dependency(
        include_directories : include,
        dependencies : crank_lib
    )
endif

pkgcfg = import('pkgconfig')

pkgcfg.generate(
    name : 'crank',
    filebase : 'crank',
    description : 'A state management framework.',
    libraries : crank_lib
)
