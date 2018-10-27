#!python
Import('env','target_name')
local_env = env.Clone()


src = 'src/'
src_files=  [
src + 'UnitTest_Main.cpp',
src + 'PlayerStrategy_Test.cpp',
src + 'PlayerHand_Test.cpp',
src + 'Player_Test.cpp',
src + 'HoleCards_Test.cpp',
src + 'Deck_Test.cpp',
src + 'Dealer_Test.cpp',
src + 'ConsoleTest.cpp',
src + 'Card_Test.cpp',
src + 'PlayerStrategy_Test.cpp',
]

# L{$GTEST_LOC:\\gtestbuild-1.7.0}" "-LE:\\Code\\GTest\\gtestbuild-1.7.0"


# local_env.Append(LIBPATH='E:\Code\GTest\gtestbuild-1.7.0')
# local_env.Append(LIBS='gtest') 
local_env.Append(CPPPATH=['E:\Code\GTest\googletest-release-1.7.0\include'])

ret = local_env.Program(target=target_name, source=src_files)

Return('ret')