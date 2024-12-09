project('isen-devoir-c', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

cc = meson.get_compiler('c')
incdir = include_directories('include')

src = files('src/main.c', 'src/file.c', 'src/linkedlist.c', 'src/word.c','src/linenumbers.c','src/filters.c','src/search.c')


exe = executable('c-search', src, include_directories : incdir)
