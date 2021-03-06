project(
	'mrsh',
	'c',
	version: '0.0.0',
	license: 'MIT',
	meson_version: '>=0.43.0',
	default_options: [
		'c_std=c11',
		'warning_level=2',
		'werror=true',
	],
)

add_project_arguments('-Wno-unused-parameter', language: 'c')
add_project_arguments('-Wno-missing-braces', language: 'c')
add_project_arguments('-Wno-missing-field-initializers', language: 'c')

cc = meson.get_compiler('c')

rt = cc.find_library('rt')

mrsh_inc = include_directories('include')

install_subdir('include/mrsh', install_dir: get_option('includedir'))

libmrsh_sym_path = meson.current_source_dir() + '/libmrsh.sym'

lib_mrsh = library(
	meson.project_name(),
	files(
		'array.c',
		'ast_print.c',
		'ast.c',
		'buffer.c',
		'builtin/alias.c',
		'builtin/cd.c',
		'builtin/builtin.c',
		'builtin/colon.c',
		'builtin/eval.c',
		'builtin/exit.c',
		'builtin/export.c',
		'builtin/set.c',
		'builtin/shift.c',
		'builtin/source.c',
		'builtin/times.c',
		'builtin/true.c',
		'builtin/false.c',
		'builtin/unset.c',
		'hashtable.c',
		'parser/parser.c',
		'parser/program.c',
		'parser/word.c',
		'shell/path.c',
		'shell/process.c',
		'shell/shell.c',
		'shell/shm.c',
		'shell/tasks.c',
		'shell/task/assignment.c',
		'shell/task/async.c',
		'shell/task/binop.c',
		'shell/task/command.c',
		'shell/task/if_clause.c',
		'shell/task/list.c',
		'shell/task/loop_clause.c',
		'shell/task/pipeline.c',
		'shell/task/subshell.c',
		'shell/task/task.c',
		'shell/task/word.c',
		'shell/word.c',
	),
	dependencies: [rt],
	include_directories: mrsh_inc,
	version: meson.project_version(),
	link_args: ['-Wl,--version-script=' + libmrsh_sym_path],
	install: true,
)

mrsh = declare_dependency(
	link_with: lib_mrsh,
	include_directories: mrsh_inc,
)

mrsh_exe = executable(
	'mrsh',
	files([
		'main.c',
	]),
	dependencies: [mrsh],
	install: true,
)

executable(
	'highlight',
	files([
		'highlight.c',
	]),
	dependencies: [mrsh],
)

subdir('test')

pkgconfig = import('pkgconfig')
pkgconfig.generate(
	libraries: lib_mrsh,
	version: meson.project_version(),
	filebase: meson.project_name(),
	name: meson.project_name(),
	description: 'POSIX shell library',
)
