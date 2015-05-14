#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QKeyEvent>
#include "MatrixKeyboard.h"

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(MatrixKeyboard *keyboard = NULL, QWidget *parent = 0);
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
	MatrixKeyboard *keyboard;
};

#endif // LOGIN_H
