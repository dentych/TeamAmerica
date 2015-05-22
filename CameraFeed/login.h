#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QEvent>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../Matrix/MatrixKeyboard.h"
#include "camerafeed.h"

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(UARTQueue *queue, UART *uart, JoystickThread *joystick, MatrixKeyboard *keyboard = NULL, QWidget *parent = 0);
    ~Login();
private slots:
    void OnLogIndPressed();

protected:
    void keyPressEvent(QKeyEvent *k);

private:
    QPushButton *login_;
    QLineEdit *le1;
    QString password_;
    QLabel *status_;
    UARTQueue *uartQueue;
    UART *uart;
    JoystickThread *joystick;
    MatrixKeyboard *keyboard;
};

#endif // LOGIN_H
