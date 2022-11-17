CC = g++
CXXFLAGS = -g -Wall
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full --show-leak-kinds=all -s --track-origins=yes

BIN = Lab1

all: $(BIN)

$(BIN): 0811562.cpp
	$(CC) $(CXXFLAGS) $< -o $@

check:
	$(CHECKCC) $(CHECKFLAGS) ./$(BIN) Test\ Case/sample.txt mysample.out

runall:
	./$(BIN) Testcase/case1.txt Testcase/1.out
	./$(BIN) Testcase/case2.txt Testcase/2.out
	./$(BIN) Testcase/case3.txt Testcase/3.out
	./$(BIN) Testcase/case4.txt Testcase/4.out
	./$(BIN) Testcase/case5.txt Testcase/5.out
	./$(BIN) Testcase/case6.txt Testcase/6.out
	./$(BIN) Testcase/case7.txt Testcase/7.out
	./$(BIN) Testcase/case8.txt Testcase/8.out
	./$(BIN) Testcase/case9.txt Testcase/9.out

runtest:
	./$(BIN) HiddenCase/small_case1.txt HiddenCase/1.out
	./$(BIN) HiddenCase/small_case2.txt HiddenCase/2.out
	./$(BIN) HiddenCase/small_case3.txt HiddenCase/3.out
	./$(BIN) HiddenCase/small_case4.txt HiddenCase/4.out
	./$(BIN) HiddenCase/small_case5.txt HiddenCase/5.out

	./$(BIN) HiddenCase/big_case1.txt HiddenCase/6.out
	./$(BIN) HiddenCase/big_case2.txt HiddenCase/7.out
	./$(BIN) HiddenCase/big_case3.txt HiddenCase/8.out

	diff -b HiddenCase/1.out HiddenCase/small_golden1.txt > 1.log
	diff -b HiddenCase/2.out HiddenCase/small_golden2.txt > 2.log
	diff -b HiddenCase/3.out HiddenCase/small_golden3.txt > 3.log
	diff -b HiddenCase/4.out HiddenCase/small_golden4.txt > 4.log
	diff -b HiddenCase/5.out HiddenCase/small_golden5.txt > 5.log
	diff -b HiddenCase/6.out HiddenCase/big_golden1.txt > 6.log
	diff -b HiddenCase/7.out HiddenCase/big_golden2.txt > 7.log
	diff -b HiddenCase/8.out HiddenCase/big_golden3.txt > 8.log


compare:
	diff -b Testcase/1.out Testcase/golden_case1.txt
	diff -b Testcase/2.out Testcase/golden_case2.txt
	diff -b Testcase/3.out Testcase/golden_case3.txt
	diff -b Testcase/4.out Testcase/golden_case4.txt
	diff -b Testcase/5.out Testcase/golden_case5.txt
	diff -b Testcase/6.out Testcase/golden_case6.txt
	diff -b Testcase/7.out Testcase/golden_case7.txt
	diff -b Testcase/8.out Testcase/golden_case8.txt
	diff -b Testcase/9.out Testcase/golden_case9.txt

clean:
	rm $(BIN) Testcase/*.out HiddenCase/*.out *.log