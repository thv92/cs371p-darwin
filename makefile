all:

Darwin.log:
	git log > Darwin.log

Doxyfile:
	doxygen -g

html: Doxyfile Darwin.h Darwin.c++ RunDarwin.c++ TestDarwin.c++
	doxygen Doxyfile

RunDarwin: Darwin.h Darwin.c++ RunDarwin.c++
	g++-4.7 -pedantic -std=c++11 -Wall Darwin.c++ RunDarwin.c++ -o RunDarwin

RunDarwin.out: RunDarwin
	RunDarwin > RunDarwin.tmp

RunDarwin.tmp: RunDarwin
	RunDarwin > RunDarwin.tmp
	diff RunDarwin.tmp RunDarwin.out

TestDarwin: Darwin.h Darwin.c++ TestDarwin.c++
	g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Darwin.c++ TestDarwin.c++ -o TestDarwin -lgtest -lgtest_main -lpthread

TestDarwin.out: TestDarwin
	valgrind TestDarwin        >  TestDarwin.out 2>&1
	gcov-4.7 -b Darwin.c++     >> TestDarwin.out
	gcov-4.7 -b TestDarwin.c++ >> TestDarwin.out

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunDarwin
	rm -f RunDarwin.out
	rm -f RunDarwin.tmp
	rm -f TestDarwin
	rm -f TestDarwin.out
