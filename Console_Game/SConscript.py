#!python
Import('env','target_name')
local_env = env.Clone()


src = 'src/'
src_files=  [
src + 'ConsoleGame_Main.cpp',
src + 'ConsoleGame.cpp',
]

ret = local_env.Program(target=target_name, source=src_files)

Return('ret')
