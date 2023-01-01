CC = g++
CXXFLAGS = -g -Wall -std=c++11

BIN = Lab3

all: $(BIN)

$(BIN): 0811562.cpp
	$(CC) $(CXXFLAGS) $< -o $@

do0:
	time ./$(BIN) ./Testcase/case0.txt ./Testcase/case0.out

do1:
	time ./$(BIN) ./Testcase/case1.txt ./Testcase/case1.out

do2:
	time ./$(BIN) ./Testcase/case2.txt ./Testcase/case2.out

do3:
	time ./$(BIN) ./Testcase/case3.txt ./Testcase/case3.out

do4:
	time ./$(BIN) ./Testcase/case4.txt ./Testcase/case4.out

do5:
	time ./$(BIN) ./Testcase/sample1.txt ./Testcase/sample1.out

do6:
	time ./$(BIN) ./Testcase/sample2.txt ./Testcase/sample2.out

clean:
	rm $(BIN) Testcase/*.out