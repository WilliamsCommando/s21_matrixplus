CFLAGS = -Wall -Werror -Wextra -fsanitize=address

all: s21_matrix_oop.a

 build: s21_matrix_oop.cc
	gcc -c $(CFLAGS) -lstdc++ -std=c++17 s21_matrix_oop.cc -o s21_matrix_oop.o

s21_matrix_oop.a: build
	ar rcs s21_matrix_oop.a s21_matrix_oop.o
	ranlib s21_matrix_oop.a


clean:
	rm -rf *.0 *.out s21_matrix_oop.a s21_matrix_oop.o
	rm -rf *.gcda *.gcno report gcov_report.* gcov_report test

rb:
	make clean
	make build
	./a.out

leaks: test
	leaks -atExit -- ./test

test: s21_matrix_oop.a tests/s21_matrix_oop_tests.cc
	gcc -lgtest -lstdc++ -std=c++17 -fsanitize=address tests/s21_matrix_oop_tests.cc s21_matrix_oop.a -o test
	./test

gcov_report:
	gcc  --coverage test.cc s21_matrix_oop.cc -o gcov_report -lgtest -lstdc++
	./gcov_report
	lcov -t "./gcov_report" -o gcov_report.info -c -d .
	genhtml -o report gcov_report.info
	open ./report/index.html
