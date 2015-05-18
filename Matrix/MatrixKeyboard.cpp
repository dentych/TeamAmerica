#include "MatrixKeyboard.h"

MatrixKeyboard::MatrixKeyboard(QObject *target) : target(target) {
	std::cout << "Constructing keyboard object." << std::endl;

	// Setup output pins (rows)
	pinMode(MK1_0, OUTPUT); // Row 1
	pinMode(MK1_1, OUTPUT); // Row 2
	pinMode(MK1_2, OUTPUT); // Row 3
	pinMode(MK1_3, OUTPUT); // Row 4

	// Setup input pins (columns)
	pinMode(MK1_4, INPUT); // Column 1
	pinMode(MK1_5, INPUT); // Column 2
	pinMode(MK1_6, INPUT); // Column 3
	pinMode(MK1_7, INPUT); // Column 4

	// Set all output to high
	digitalWrite(MK1_0, HIGH);
	digitalWrite(MK1_1, HIGH);
	digitalWrite(MK1_2, HIGH);
	digitalWrite(MK1_3, HIGH);

	// Construct arrays with row and column numbers
	mk_rows[0] = MK1_0;
	mk_rows[1] = MK1_1;
	mk_rows[2] = MK1_2;
	mk_rows[3] = MK1_3;

	mk_columns[0] = MK1_4;
	mk_columns[1] = MK1_5;
	mk_columns[2] = MK1_6;
	mk_columns[3] = MK1_7;

	// Create array of the matrix chars
    matrixChars[0] = "123A";
	matrixChars[1] = "456B";
	matrixChars[2] = "789C";
    matrixChars[3] = "*0#D";
}

void MatrixKeyboard::poll() {
	std::cout << "Polling!" << std::endl;
	int row, column;
	int previousRead[2];
	bool dirtyBit = false;
 	while (1) {
		for (row = 0; row < 4; row++) {
			if (row == 0) {
				if (dirtyBit) {
					dirtyBit = false;
				}
				else {
					previousRead[0] = -1;
					previousRead[1] = -1;
				}
			}
			digitalWrite(mk_rows[row], LOW);
			for (column = 0; column < 4; column++) {
				if (digitalRead(mk_columns[column]) == 0) {
					dirtyBit = true;
					if (previousRead[0] != row || previousRead[1] != column) {
						std::cout << "Read: " << findMatrixChar(row, column) << std::endl;
						char read_char = findMatrixChar(row, column);
                        QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, findQtKey(read_char), Qt::NoModifier, (QString)read_char);
                        QApplication::postEvent(target, event);
					}
					previousRead[0] = row;
					previousRead[1] = column;
				}
			}
			digitalWrite(mk_rows[row], HIGH);
		}
		usleep(100000);
	}
}

char MatrixKeyboard::findMatrixChar(int row, int column) {
	return matrixChars[row][column];
}

void MatrixKeyboard::run() {
    poll();
}

int MatrixKeyboard::findQtKey(char key) {
    switch (key) {
    case '0':
        return Qt::Key_0;
        break;
    case '1':
        return Qt::Key_1;
        break;
    case '2':
        return Qt::Key_2;
        break;
    case '3':
        return Qt::Key_3;
        break;
    case '4':
        return Qt::Key_4;
        break;
    case '5':
        return Qt::Key_5;
        break;
    case '6':
        return Qt::Key_6;
        break;
    case '7':
        return Qt::Key_7;
        break;
    case '8':
        return Qt::Key_8;
        break;
    case '9':
        return Qt::Key_9;
        break;
    case 'A':
        return Qt::Key_A;
        break;
    case 'B':
        return Qt::Key_B;
        break;
    case 'C':
        return Qt::Key_C;
        break;
    case 'D':
        return Qt::Key_D;
        break;
    case '*':
        return Qt::Key_Asterisk;
        break;
    case '#':
        return Qt::Key_NumberSign;
        break;
    }
}

void MatrixKeyboard::setTarget(QObject *target) {
	std::cout << "Setting new target." << std::endl;
    this->target = target;
}
