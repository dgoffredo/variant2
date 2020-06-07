test: test.C variant2.h
	clang++-6.0 -g --std=c++11 -o $@ -I. -Wall -Wextra -pedantic -Werror $<
