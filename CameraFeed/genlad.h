#ifndef GENLAD_H
#define GENLAD_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

class Genlad : public QDialog
{
    Q_OBJECT

public:
    Genlad(QWidget *parent = 0);
    ~Genlad();

private slots:
    void OnOkPressed();

private:
    QPushButton *ok_;
    QLineEdit *les_;
    QLabel *info_;
    QLabel *antal_;
};

#endif // GENLAD_H
