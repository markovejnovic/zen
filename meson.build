project('zen', 'cpp', default_options: [
  'cpp_std=c++20'
], version: '0.1.0')

include_dirs = ['include']

run_target('lint', command: 'tools/lint.sh')
run_target('auto-lint', command: 'tools/auto-lint.sh')

test_includes = [include_dirs]
test_sources = [
]

libzen_dep = declare_dependency(include_directories: include_dirs)

foreach test_src : test_sources
  test(
    test_src[0],
    executable(test_src[0], test_src[1], include_directories: test_includes)
  )
endforeach
