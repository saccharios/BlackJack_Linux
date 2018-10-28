#!python
import os

# build with `scons --debug_build` for debug.
AddOption(
    '--debug_build',
    action='store_true',
    help='debug build',
    default=False)

# SetOption('cache_disable' ,True) --cache-disable
if(len(COMMAND_LINE_TARGETS) != 1):
    print('Error: Specify exactly one target. \nAborting...')
    Exit(0)
    
target_name =  COMMAND_LINE_TARGETS[0]

Target_List =[
    'Black_Jack_lib',
    'Console_Game',
    'Simulations',
    'UnitTest',
    ]


if (target_name not in Target_List):
    print('You have entered an invalid target. Aborting...')

print('Start to build ', target_name)


env = Environment(ENV = os.environ,)
env.Append(CXXFLAGS='--std=c++17') 



env.Append(CCCOMSTR = "Compiling $TARGET",
           LINKCOMSTR = "Linking $TARGET")


build_dir = '#build'
if GetOption('debug_build'):
    env.ParseFlags('-DDEBUG')
    mode = 'debug'
else:
    mode = 'release'


lib_name = 'Black_Jack_lib'
libpath = build_dir + '/' + lib_name + '_'+mode 
SConscript(lib_name +'/SConscript.py', variant_dir=libpath, duplicate=False, exports=['env','lib_name'])
 

env.Append(LIBPATH=[libpath, 'pthread'])
env.Append(LIBS=[lib_name]) 
env.Append(CPPPATH=[libpath + '/src', Dir('.').abspath + '/' + lib_name + '/src'])

env.Append(LINKFLAGS='-pthread')

variant_dir = build_dir + '/' + target_name + '_'+mode 
SConscript(target_name +'/SConscript.py', 
           variant_dir=variant_dir, 
           duplicate=False, 
           exports=['env','target_name'])

