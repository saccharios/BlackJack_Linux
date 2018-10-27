#!python
Import('env')
# Import('env','lib_name')
local_env = env.Clone()

src = 'src/'
src_files=  [
src + 'Card.cpp',
src + 'Console.cpp',
src + 'Dealer.cpp',
src + 'Deck.cpp',
src + 'Game.cpp',
src + 'HoleCards.cpp',
src + 'Player.cpp',
src + 'PlayerHand.cpp',
src + 'PlayerStrategy.cpp',
]
lib_name = 'Black_Jack_lib'
ret = local_env.Library(target=lib_name, source=src_files)
local_env.AlwaysBuild(ret)

Return('ret')
