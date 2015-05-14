#include "camerafeed.h"
#include <iostream>
#include <stdio.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include "login.h"

using namespace std;
using namespace cv;


cameraFeed::cameraFeed(MatrixKeyboard *keyboard, QWidget *parent)
    : keyboard(keyboard), QWidget(parent)
{
	capture = 0;
	feed_ = new QLabel();
	msg_ = new QLabel();

    timer_ = new QTimer(this);

    connect(timer_, SIGNAL(timeout()), this, SLOT(updatePicture()));
    timer_->start(20);

    QHBoxLayout *hbox = new QHBoxLayout(this);
    QVBoxLayout *vbox = new QVBoxLayout();


    aktiver_ = new QPushButton("1: Aktiver");
    deaktiver_ = new QPushButton("2: Deaktiver");
    genlad_ = new QPushButton("3: Genlad");
    logud_ = new QPushButton("4: Log ud");

    connect(aktiver_, SIGNAL(pressed()), this, SLOT(OnAktiverPressed()));
    connect(deaktiver_, SIGNAL(pressed()), this, SLOT(OnDeaktiverPressed()));
    connect(genlad_, SIGNAL(pressed()), this, SLOT(OnGenladPressed()));
    connect(logud_, SIGNAL(pressed()), this, SLOT(OnLogUdPressed()));

    /*
    start_ = new QPushButton("Start");
    slut_ = new QPushButton("Slut");
    connect(start_, SIGNAL(pressed()), this, SLOT(Onstartpressed()));
    connect(slut_, SIGNAL(pressed()), this, SLOT(Onslutpressed()));
    */



    vbox->setSpacing(20);
    vbox->addStretch(1);
    vbox->addWidget(aktiver_);
    vbox->addWidget(deaktiver_);
    vbox->addWidget(genlad_);
    vbox->addWidget(logud_);
    vbox->addStretch(1);
    vbox->addWidget(msg_);


    hbox->setSpacing(20);
    hbox->addStretch(1);
    hbox->addWidget(feed_);
    hbox->addLayout(vbox);
    hbox->addStretch(1);



    capture = cvCaptureFromCAM( CV_CAP_ANY ); //0=default, -1=any camera, 1..99=your camera
    if( !capture )
    {
    cout << "No camera detected" << endl;
    }

	keyboard->setTarget(this);
}

void cameraFeed::updatePicture()
{

    if( capture )
    {
    IplImage* iplImg = cvQueryFrame( capture );

    feed_->setPixmap(QPixmap::fromImage(putImage(iplImg)));
    }

}

QImage cameraFeed::putImage(const Mat& mat)
{
    // 8-bits unsigned, NO. OF CHANNELS=1
    if(mat.type()==CV_8UC1)
    {
        // Set the color table (used to translate colour indexes to qRgb values)
        QVector<QRgb> colorTable;
        for (int i=0; i<256; i++)
            colorTable.push_back(qRgb(i,i,i));
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
        img.setColorTable(colorTable);
        return img;
    }
    // 8-bits unsigned, NO. OF CHANNELS=3
    if(mat.type()==CV_8UC3)
    {
        // Copy input Mat
        const uchar *qImageBuffer = (const uchar*)mat.data;
        // Create QImage with same dimensions as input Mat
        QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
        return img.rgbSwapped();
    }
    else
    {
        qDebug() << "ERROR: Mat could not be converted to QImage.";
        return QImage();
    }
}

void cameraFeed::OnAktiverPressed()
{
    msg_->setText("Aktiver Trykket");
}

void cameraFeed::OnDeaktiverPressed()
{
    msg_->setText("Deaktiver Trykket");
}

void cameraFeed::OnGenladPressed()
{
    msg_->setText("Genlad Trykket");
}

void cameraFeed::OnLogUdPressed()
{
    Login *log = new Login(keyboard);
    log->setFixedSize(500,300);
    log->setWindowTitle("Login");
    log->show();

	cvReleaseCapture(&capture);

    this->close();
}

/*
void cameraFeed::Onstartpressed()
{
    cout << "In capture ..." << endl;
    if(feed_->isVisible() == false)
    {
        feed_->show();
    }


}

void cameraFeed::Onslutpressed()
{
    feed_->hide();
}
*/

void cameraFeed::keyPressEvent(QKeyEvent *k) {
        switch (k->key()) {
        case Qt::Key_1:
            OnAktiverPressed();
            break;
        case Qt::Key_2:
            OnDeaktiverPressed();
            break;
        case Qt::Key_3:
            OnGenladPressed();
            break;
        case Qt::Key_4:
            OnLogUdPressed();
            break;
        default:
            break;
        }
}

cameraFeed::~cameraFeed()
{
    cvReleaseCapture( &capture );
}
