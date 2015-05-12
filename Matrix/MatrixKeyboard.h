#ifndef MATRIXKEYBOARD_H_
#define MATRIXKEYBOARD_H

#include <iostream>
#include <unistd.h>

// Rows
#define MK1_0 4
#define MK1_1 17
#define MK1_2 27
#define MK1_3 22

// Colums
#define MK1_4 5
#define MK1_5 6
#define MK1_6 13
#define MK1_7 19

#include <wiringPi.h>

class MatrixKeyboard {
	public:
		MatrixKeyboard();
		void poll();
		char findMatrixChar(int row, int column);
	private:
		int mk_rows[4];
		int mk_columns[4];
		std::string matrixChars[4];
};

#endif
