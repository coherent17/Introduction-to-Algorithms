CC = g++
CXXFLAGS = -g -Wall
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full --show-leak-kinds=all -s --track-origins=yes

BIN = Lab2

all: $(BIN)

$(BIN): 0811562.cpp
	$(CC) $(CXXFLAGS) $< -o $@

do0:
	./$(BIN) Testcase/case0.txt Testcase/0.out

runall:
	./$(BIN) Testcase/case1.txt Testcase/1.out
	./$(BIN) Testcase/case2.txt Testcase/2.out
	./$(BIN) Testcase/case3.txt Testcase/3.out

clean:
	rm $(BIN) Testcase/*.out HiddenCase/*.out *.log