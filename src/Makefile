CFLAGS=-Wall -Werror -Wextra -std=c11 #-pedantic -fsanitize=address
OPEN=open ./report/index.html
LIBS= -L /usr/local/lib
BUILD= build

ifeq ($(OS), Linux) # LINUX
LEAKS=valgrind --tool=memcheck --leak-check=yes  ./tests
endif

ifeq ($(OS), Darwin) # MAC
LEAKS=leaks -atExit -- ./test
endif

all: clean install gcov_report 

install:
	qmake CONFIG+=release -o $(BUILD)/Makefile 3DViewer/3DViewer.pro
	cd $(BUILD); make
	rm -rf $(BUILD)/*.o
	rm -rf $(BUILD)/*.cpp
	rm -rf $(BUILD)/*.h
	rm -rf $(BUILD)/Makefile


uninstall: clean
	rm -rf $(BUILD)

clean:
	rm -rf *.o main tests new_cube.obj *.dSYM
	rm -rf $(BUILD)/*.o
	rm -rf $(BUILD)/*.cpp
	rm -rf $(BUILD)/*.h
	rm -rf $(BUILD)/Makefile
	rm -rf *.o *.a
	rm -rf *.info
	rm -rf *.dSYM
	rm -rf tests test
	rm -rf main
	rm -rf report
	rm -rf *.gcno *.gcda
	rm -rf doc
	rm -rf build_tar
	rm -rf .clang-format
	

dvi:
	@makeinfo --html --no-warn --no-validate --force doc.texi
	@open ./doc/index.html

dist:
	@mkdir -p ./build_tar
	@tar -cvzf ./build_tar/3DViewer.tgz Back/* Makefile doc.texi 3DViewer/* 

clang:
	cp ../materials/linters/.clang-format .
	clang-format -i Back/*.c Back/*.h 3DViewer/*.cpp 3DViewer/*.h
	clang-format -n Back/*.c Back/*.h 3DViewer/*.cpp 3DViewer/*.h

leaks: tests
	$(LEAKS)

tests: clean 3d_tests.o
	gcc *.o -o test -lcheck -lm $(LIBS) -g
	./test


3d_tests.o: Back/*.c Back/*.h
	gcc -c Back/*.c -g

gcov_report: clean
	gcc -fprofile-arcs -ftest-coverage --coverage Back/test_model.c Back/common.c Back/s_object.c Back/transform.c -o test -lcheck -lm $(LIBS) -g
	./test
	lcov -t test -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html
