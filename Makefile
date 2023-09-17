# Sanitizer libraries install: sudo apt update && sudo apt upgrade && sudo apt install llvm-14
test:
	clear
	# Update the source files in the cargo project
	cp ./hstring.c ./rust/hstring.c
	cp ./hstring.h ./rust/hstring.h

	# Compile hstring.c and main.c with full warnigs, debug information and adress santizier.
	ASAN_SYMBOLIZER_PATH="/usr/lib/llvm-14/llvm-symbolizer" clang -std=c11 -gdwarf-4 -ggdb3 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -c -o hstring.o -fsanitize=address -g -fno-omit-frame-pointer hstring.c
	ASAN_SYMBOLIZER_PATH="/usr/lib/llvm-14/llvm-symbolizer" clang -std=c11 -gdwarf-4 -ggdb3 -Wall -Werror -Wextra -Wno-gnu-folding-constant -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow -o testing testing.c -fsanitize=address -g -fno-omit-frame-pointer -Lhstring hstring.o

	# Run test file with stdin from testinginput.txt
	cat testinput.txt | ./testing

