#include "login.h"


Login::Login(MatrixKeyboard *keyboard, QWidget *parent)
    : keyboard(keyboard), QWidget(parent)
{
     le1 = new QLineEdit(this);
     password_ = "1905";
     status_ = new QLabel();

     QVBoxLayout *vbox = new QVBoxLayout(this);
     QHBoxLayout *hbox = new QHBoxLayout();

     login_ = new QPushButton("Log Ind");


     connect(login_, SIGNAL(pressed()), this, SLOT(OnLogIndPressed()));
     connect(le1, SIGNAL(returnPressed()), this, SLOT(OnLogIndPressed()),Qt::UniqueConnection);

     QLabel *kode = new QLabel("Kode: ");
     le1->setEchoMode(QLineEdit::Password);
     hbox->setSpacing(3);
     hbox->addStretch(1);
     hbox->addWidget(kode);
     hbox->addWidget(le1);
     hbox->addStretch(1);

     vbox->setSpacing(5);
     vbox->addStretch(1);
     vbox->addLayout(hbox);
     vbox->addWidget(login_,0,Qt::AlignCenter);
     vbox->addWidget(status_,0,Qt::AlignCenter);
     vbox->addStretch(1);

     if (keyboard == NULL) {
        this->keyboard = new MatrixKeyboard(this);
        this->keyboard->start();
     }
     else {
         this->keyboard->setTarget(this);
     }
}
void Login::OnLogIndPressed()
{

     if(password_==le1->text())
     {

     //status_->setText("Kode korrekt!!");

     cameraFeed *cam = new cameraFeed(keyboard);
     cam->setAttribute(Qt::WA_DeleteOnClose);
     cam->show();

     this->close();

     }
     else
     status_->setText("<font color='red'>Forkert kode, prøv igen..</font>");
}

void Login::keyPressEvent(QKeyEvent *k) {
    switch (k->key()) {
    case Qt::Key_Asterisk:
        le1->backspace();
        break;
    case Qt::Key_NumberSign:
        OnLogIndPressed();
        break;
    default:
        le1->insert(k->text());
        break;
    }
}

Login::~Login()
{

}

