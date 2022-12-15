CC = g++
CXXFLAGS = -g -Wall -std=c++11
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full --show-leak-kinds=all -s --track-origins=yes

BIN = Lab2

all: $(BIN) verifier

$(BIN): 0811562.cpp
	$(CC) $(CXXFLAGS) $< -o $@

verifier:
	$(CC) $(CXXFLAGS) verifier.cpp -o verifier

runall:
	time ./$(BIN) Testcase/case0.txt Testcase/0.out
	time ./$(BIN) Testcase/case1.txt Testcase/1.out
	time ./$(BIN) Testcase/case2.txt Testcase/2.out
	time ./$(BIN) Testcase/case3.txt Testcase/3.out
	time ./$(BIN) Testcase/case4.txt Testcase/4.out

test:
	./verifier Testcase/0.out Testcase/golden0.txt
	./verifier Testcase/1.out Testcase/golden1.txt
	./verifier Testcase/2.out Testcase/golden2.txt
	./verifier Testcase/3.out Testcase/golden3.txt
	./verifier Testcase/4.out Testcase/golden4.txt

clean:
	rm $(BIN) Testcase/*.out verifier