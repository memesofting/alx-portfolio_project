build:
	gcc -Wall -Werror -Wextra -std=gnu89 -I./headers src/*.c -lSDL2 -lSDL2_ttf -lm -o game
