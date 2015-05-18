#include "genlad.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QIntValidator>

int skud_ = 0;

Genlad::Genlad(MatrixKeyboard *keyboard, QLabel *msg, QWidget *parent)
    : keyboard(keyboard), msg_(msg), QDialog(parent)
{

    QVBoxLayout *vbox = new QVBoxLayout(this);
    QHBoxLayout *hbox = new QHBoxLayout();

    ok_ = new QPushButton("Ok");

    connect(ok_, SIGNAL(pressed()), this, SLOT(OnOkPressed()));

    info_ = new QLabel("Indtast antal skud og afslut med #. * for at slette (annullerer hvis feltet er tomt).");
    antal_= new QLabel("Antal skud: ");
    les_ = new QLineEdit(this);
    les_->setValidator( new QIntValidator(0, 100, this));

    hbox->setSpacing(3);
    hbox->addStretch(1);
    hbox->addWidget(antal_);
    hbox->addWidget(les_);
    hbox->addStretch(1);

    vbox->setSpacing(5);
    vbox->addStretch(1);
    vbox->addWidget(info_,0,Qt::AlignCenter);
    vbox->addLayout(hbox);
    vbox->addWidget(ok_,0,Qt::AlignCenter);
    vbox->addStretch(1);

    this->keyboard->setTarget(this);
}

Genlad::~Genlad()
{

}

void Genlad::OnOkPressed()
{
    int temp = 0;

    for (int var = 0; var < les_->text().length(); ++var)
    {
        int digit = les_->text().at(var).digitValue();
        temp=temp*10;
        temp+=digit;
    }

    skud_ = temp;

    //info_->setText(QString::number(skud_));

    msg_->setText("");

    this->close();

}

void Genlad::keyPressEvent(QKeyEvent *ke) {
    switch (ke->key()) {
    case Qt::Key_NumberSign:
        OnOkPressed();
        break;
    case Qt::Key_Asterisk:
        if (les_->text().isEmpty())
        {
            this->close();
        }
        else {
            les_->backspace();
        }
        break;
    default:
        les_->insert(ke->text());
        break;
    }
}
