project('isen-devoir-c', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

cc = meson.get_compiler('c')

raylibdep = cc.find_library('raylib',
                dirs : ['C:/raylib/raylib/src']) # Le répertoire doit contenir libraylib.a
inc_raylib = include_directories('C:/raylib/raylib/src') # Le répertoire doit contenir raylib.h 


exe = executable('isen_devoir_c', 'isen_devoir_c.c', 
  dependencies: [raylibdep],  include_directories : inc_raylib
  )