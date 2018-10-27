#!python
Import('env','target_name')
local_env = env.Clone()


src = 'src/'
src_files=  [
src + 'Simulations_Main.cpp',
src + 'SimulationGame.cpp',
]

ret = local_env.Program(target=target_name, source=src_files)

Return('ret')