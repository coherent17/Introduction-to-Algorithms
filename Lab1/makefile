CC = g++
CXXFLAGS = -g -Wall
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full --show-leak-kinds=all -s --track-origins=yes


BIN = Lab1

all: $(BIN)

$(BIN): 0811562.cpp
	$(CC) $(CXXFLAGS) $< -o $@

check1:
	$(CHECKCC) $(CHECKFLAGS) ./$(BIN) Test\ Case/case1.txt

check2:
	$(CHECKCC) $(CHECKFLAGS) ./$(BIN) Test\ Case/case2.txt

check3:
	$(CHECKCC) $(CHECKFLAGS) ./$(BIN) Test\ Case/case3.txt

do1:
	./$(BIN) Test\ Case/case1.txt

do2:
	./$(BIN) Test\ Case/case2.txt

do3:
	./$(BIN) Test\ Case/case3.txt

clean:
	rm $(BIN)