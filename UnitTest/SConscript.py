#!python
Import('env','target_name')
local_env = env.Clone()


src = 'src/'
src_files=  [
src + 'UnitTest_Main.cpp',
src + 'Card_Test.cpp',
src + 'ConsoleTest.cpp',
src + 'Dealer_Test.cpp',
src + 'Deck_Test.cpp',
src + 'HoleCards_Test.cpp',
src + 'Player_Test.cpp',
src + 'PlayerHand_Test.cpp',
src + 'PlayerStrategy_Test.cpp',
]

local_env.Append(LIBPATH=['/home/stefan/repos/gtest/'])
local_env.Append(LIBS=['gtest',
                       'gtest_main']) 
local_env.Append(CPPPATH=['/usr/src/gtest/include'])


ret = local_env.Program(target=target_name, source=src_files)

Return('ret')