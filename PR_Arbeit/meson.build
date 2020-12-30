project('santa_claus', 'cpp',
    default_options : ['cpp_std=c++14'])

thread_dep = dependency('threads')

inc_dir = include_directories('include')
src = ['src/main.cpp']

executable('santa_claus',
sources : src,
include_directories : inc_dir,
dependencies : thread_dep)
