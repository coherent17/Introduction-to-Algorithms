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
	./$(BIN) Test\ Case/sample.txt mysample.out
	./$(BIN) Test\ Case/case1.txt mycase1.out
	./$(BIN) Test\ Case/case2.txt mycase2.out
	./$(BIN) Test\ Case/case3.txt mycase3.out
	./$(BIN) Test\ Case/testcase1.txt testcase1.out
	./$(BIN) Test\ Case/testcase2.txt testcase2.out
	./$(BIN) Test\ Case/testcase3.txt testcase3.out
	./$(BIN) Test\ Case/testcase4.txt testcase4.out

compare:
	diff -b mycase1.out Test\ Case/golden1.txt
	diff -b mycase2.out Test\ Case/golden2.txt
	diff -b mycase3.out Test\ Case/golden3.txt

clean:
	rm $(BIN) *.out