#include "login.h"
#include <Qstring>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "camerafeed.h"


Login::Login(QWidget *parent)
    : QWidget(parent)
{

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
}

void Login::OnLogIndPressed()
{

     if(password_==le1->text())
     {

     //status_->setText("Kode korrekt!!");

     cameraFeed *cam = new cameraFeed;
     cam->setAttribute(Qt::WA_DeleteOnClose);
     cam->show();

     this->close();

     }
     else
     status_->setText("<font color='red'>Forkert kode, prøv igen..</font>");
}
Login::~Login()
{

}

