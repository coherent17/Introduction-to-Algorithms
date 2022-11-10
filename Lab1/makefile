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

compare:
	diff -b Testcase/1.out Testcase/golden_case1.txt
	diff -b Testcase/2.out Testcase/golden_case2.txt
	diff -b Testcase/3.out Testcase/golden_case3.txt
	diff -b Testcase/4.out Testcase/golden_case4.txt
	diff -b Testcase/5.out Testcase/golden_case5.txt
	diff -b Testcase/6.out Testcase/golden_case6.txt
	diff -b Testcase/7.out Testcase/golden_case7.txt

clean:
	rm $(BIN) Testcase/*.out