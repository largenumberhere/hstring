test:
	clear
	clang -std=c11 -gdwarf-4 -ggdb3 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o hstring.o hstring.c
	clang -std=c11 -gdwarf-4 -ggdb3 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -o testing testing.c hstring.o
	valgrind ./testing
	rm -v vgcore.*
	#todo: learn to use builtin -fsanitize=address for clang