CC = gcc -g
STD = -std=c11
WFLAGS = -Wall -Werror -Wextra
TEST_FLAGS = -lcheck
S21_LIB = s21_3dviewer.a
PATH_BACK = 3dviewer_v1/back/
PATH_FRONT = 3dviewer_v1/front/
C_FILES = $(wildcard 3dviewer_v1/back/s21_*.c)
OBJ_FILES = $(patsubst %.c, %.o, $(C_FILES))
TEST_C_FILES = $(wildcard tests.c)
TEST_OBJ_FILES = $(patsubst %.c, %.o, $(TEST_C_FILES))
WSL_LINK_FLAGS = -lsubunit `pkg-config --cflags --libs check`
TRASH = $(wildcard *.o *.a *.gc* *.out *.tar Documentation html latex tests test.info report $(PATH_BACK)*.o *.dSYM models/*.gif models/*.bmp models/*.jpeg .clang-format)
UNAME = $(shell uname -s)

all: rebuild
ifeq ($(UNAME), Linux)
	cd build && ./3dviewer_v1
else
	cd build/3dviewer_v1.app/Contents/MacOS && ./3dviewer_v1
endif
	

install: $(S21_LIB)
	mkdir build
	cd build; cmake ../3dviewer_v1 -Wno-dev
	cd build && make
	
uninstall:
	rm -rf build

rebuild: uninstall install

dvi:
	doxygen doxyconfig
	open ./html/index.html

dvi_clean:
	rm -rf doxyconfig.bak
	rm -rf html
	rm -rf latex

dist:
	rm -rf dist_archive.tar
	cp ../materials/linters/.clang-format ./
	tar -cf dist_archive.tar 3dviewer_v1/ Makefile models/ convert.sh doxyconfig tests.c .clang-format
	rm -rf clang-format

clean: pure dvi_clean uninstall

$(S21_LIB): clean $(OBJ_FILES)
	ar rc $(S21_LIB) $(OBJ_FILES)
	ranlib $(S21_LIB)
	rm -f $(BACK_P)*.o

test: clean $(S21_LIB)

ifeq ($(UNAME), Linux)
	$(CC) $(STD) $(WFLAGS) -c $(TEST_C_FILES) $(TEST_FLAGS) $(WSL_LINK_FLAGS)
	$(CC) $(STD) $(WFLAGS) $(TEST_OBJ_FILES) $(OBJ_FILES) -o tests $(TEST_FLAGS) $(WSL_LINK_FLAGS)
	./tests
else
	$(CC) $(STD) $(WFLAGS) -c $(TEST_C_FILES) $(TEST_FLAGS)
	$(CC) $(STD) $(WFLAGS) $(TEST_OBJ_FILES) $(OBJ_FILES) -o tests  $(TEST_FLAGS) 
	./tests
endif

gcov_report: clean $(S21_LIB)
ifeq ($(UNAME), Linux)
	$(CC) $(STD) --coverage $(C_FILES) $(S21_LIB) $(TEST_C_FILES) $(TEST_FLAGS) $(WSL_LINK_FLAGS) -o tests
else
	$(CC) $(STD) --coverage $(C_FILES) $(S21_LIB) $(TEST_C_FILES) $(TEST_FLAGS) -o tests
endif
	./tests
	lcov -t "test" --no-external -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

check_style:
	cp ../materials/linters/.clang-format ../src
	clang-format -n -style=google *.c $(PATH_BACK)*.c $(PATH_BACK)*.h $(PATH_FRONT)*.cpp $(PATH_FRONT)*.h 3dviewer_v1/main.cpp
	rm -rf .clang-format

correct_style:
	cp ../materials/linters/.clang-format ../src
	clang-format -i -style=google *.c $(PATH_BACK)*.c $(PATH_BACK)*.h $(PATH_FRONT)*.cpp $(PATH_FRONT)*.h 3dviewer_v1/main.cpp
	rm -rf .clang-format

convert:
	sh convert.sh

check_mem: clean test
ifeq ($(UNAME), Linux)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./tests
else
	leaks -atExit -- ./tests
endif

pure:
	rm -rf $(TRASH)

rebuild: clean all
