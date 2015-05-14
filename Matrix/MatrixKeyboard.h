#ifndef MATRIXKEYBOARD_H_
#define MATRIXKEYBOARD_H_

#include <iostream>
#include <unistd.h>
#include <QKeyEvent>
#include <QApplication>
#include <QThread>

// Rows
#define MK1_0 4
#define MK1_1 17
#define MK1_2 27
#define MK1_3 22

// Colums
#define MK1_4 5
#define MK1_5 6
#define MK1_6 13
#define MK1_7 16

#include <wiringPi.h>

class MatrixKeyboard : public QThread {
	public:
        MatrixKeyboard(QObject *target);
        void poll();

        /*
         * Set the QWidget window receiving the QKeyEvents
         */
        void setTarget(QObject *target);

        /* Run method override */
        virtual void run();
	private:
        char findMatrixChar(int row, int column);
        int findQtKey(char key);

		int mk_rows[4];
		int mk_columns[4];
        std::string matrixChars[4];
        QObject *target;
        //int matrixKeys[16];
};

#endif
