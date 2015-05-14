#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <Qstring>
#include <QEvent>
#include <QKeyEvent>

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = 0);
    ~Login();
private slots:
    void OnLogIndPressed();


private:
    QPushButton *login_;
    QLineEdit *le1 = new QLineEdit(this);
    QString password_ = "1905";
    QLabel *status_ = new QLabel();
};

#endif // LOGIN_H
