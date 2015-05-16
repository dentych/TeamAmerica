#ifndef GENLAD_H
#define GENLAD_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include "../Matrix/MatrixKeyboard.h"

class Genlad : public QDialog
{
    Q_OBJECT

public:
    Genlad(MatrixKeyboard *keyboard, QWidget *parent = 0);
    ~Genlad();

protected:
    void keyPressEvent(QKeyEvent *ke);

private slots:
    void OnOkPressed();

private:
    QPushButton *ok_;
    QLineEdit *les_;
    QLabel *info_;
    QLabel *antal_;

    MatrixKeyboard *keyboard;
};

#endif // GENLAD_H
