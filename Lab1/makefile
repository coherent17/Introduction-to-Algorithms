CC = g++
CXXFLAGS = -g -Wall
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full --show-leak-kinds=all -s --track-origins=yes


BIN = Lab1

all: $(BIN)

$(BIN): 0811562.cpp
	$(CC) $(CXXFLAGS) $< -o $@

check0:
	$(CHECKCC) $(CHECKFLAGS) ./$(BIN) Test\ Case/sample.txt mysample.out

check1:
	$(CHECKCC) $(CHECKFLAGS) ./$(BIN) Test\ Case/case1.txt mycase1.out

check2:
	$(CHECKCC) $(CHECKFLAGS) ./$(BIN) Test\ Case/case2.txt mycase2.out

check3:
	$(CHECKCC) $(CHECKFLAGS) ./$(BIN) Test\ Case/case3.txt mycase3.out

checkt1:
	$(CHECKCC) $(CHECKFLAGS) ./$(BIN) Test\ Case/testcase1.txt testcase1.out

checkt2:
	$(CHECKCC) $(CHECKFLAGS) ./$(BIN) Test\ Case/testcase2.txt testcase2.out

do0:
	./$(BIN) Test\ Case/sample.txt mysample.out

do1:
	./$(BIN) Test\ Case/case1.txt mycase1.out

do2:
	./$(BIN) Test\ Case/case2.txt mycase2.out

do3:
	./$(BIN) Test\ Case/case3.txt mycase3.out

t1:
	./$(BIN) Test\ Case/testcase1.txt testcase1.out

t2:
	./$(BIN) Test\ Case/testcase2.txt testcase2.out


compare:
	diff -b mycase1.out Test\ Case/golden1.txt
	diff -b mycase2.out Test\ Case/golden2.txt
	diff -b mycase3.out Test\ Case/golden3.txt

clean:
	rm $(BIN) *.out