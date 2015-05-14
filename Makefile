OBJ=test/UARTtest.o src/UART.o

all: $(OBJ)
	$(CXX) $^ -lwiringPi -lpthread

.PHONY: clean

clean:
	rm -rf a.out $(OBJ)
