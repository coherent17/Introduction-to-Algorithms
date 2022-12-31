CC = g++
CXXFLAGS = -g -Wall -std=c++11
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full --show-leak-kinds=all -s --track-origins=yes

BIN = Lab3

all: $(BIN)

$(BIN): 0811562.cpp
	$(CC) $(CXXFLAGS) $< -o $@

do0:
	./$(BIN) ./Testcase/case0.txt ./Testcase/case0.out

do1:
	./$(BIN) ./Testcase/case1.txt ./Testcase/case1.out

do2:
	./$(BIN) ./Testcase/case2.txt ./Testcase/case2.out

do3:
	./$(BIN) ./Testcase/case3.txt ./Testcase/case3.out

clean:
	rm $(BIN) Testcase/*.out