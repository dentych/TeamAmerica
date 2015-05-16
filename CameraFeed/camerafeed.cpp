#include "camerafeed.h"
#include <iostream>
#include <stdio.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include "login.h"
#include "genlad.h"

using namespace std;
using namespace cv;

extern int skud_;
ofstream file;

cameraFeed::cameraFeed(MatrixKeyboard *keyboard, QWidget *parent)
    : keyboard(keyboard), QWidget(parent)
{
    capture = 0;
    feed_ = new QLabel();
    msg_ = new QLabel();
    text_ = new QLabel();
    sstat_ = new QLabel();

    timer_ = new QTimer(this);

    connect(timer_, SIGNAL(timeout()), this, SLOT(updatePicture()));
    timer_->start(20);

    QHBoxLayout *hbox = new QHBoxLayout(this);
    QHBoxLayout *hbox2 = new QHBoxLayout();
    QVBoxLayout *vbox = new QVBoxLayout();
    QVBoxLayout *vbox2 = new QVBoxLayout();

    aktiver_ = new QPushButton("1: Aktiver");
    deaktiver_ = new QPushButton("2: Deaktiver");
    genlad_ = new QPushButton("3: Genlad");
    advarsel_ = new QPushButton("4: Advarsel");
    logud_ = new QPushButton("5: Log ud");

    connect(aktiver_, SIGNAL(pressed()), this, SLOT(OnAktiverPressed()));
    connect(deaktiver_, SIGNAL(pressed()), this, SLOT(OnDeaktiverPressed()));
    connect(genlad_, SIGNAL(pressed()), this, SLOT(OnGenladPressed()));
    connect(advarsel_, SIGNAL(pressed()), this, SLOT(OnAdvarselPressed()));
    connect(logud_, SIGNAL(pressed()), this, SLOT(OnLogUdPressed()));

    /*
    start_ = new QPushButton("Start");
    slut_ = new QPushButton("Slut");
    connect(start_, SIGNAL(pressed()), this, SLOT(Onstartpressed()));
    connect(slut_, SIGNAL(pressed()), this, SLOT(Onslutpressed()));
    */

    ifstream infile("AntalSkud.txt");
    infile>>skud_;

    text_->setText("Antal skud: ");
    QFont font = text_->font();
    font.setPointSize(16);
    text_->setFont(font);
    sstat_->setFont(font);
    sstat_->setNum(skud_);

    vbox->setSpacing(20);
    vbox->addStretch(1);
    vbox->addWidget(aktiver_);
    vbox->addWidget(deaktiver_);
    vbox->addWidget(genlad_);
    vbox->addWidget(advarsel_);
    vbox->addWidget(logud_);
    vbox->addStretch(1);
    vbox->addWidget(msg_);

    vbox2->setSpacing(20);
    vbox2->addStretch(1);
    vbox2->addWidget(feed_);
    vbox2->addLayout(hbox2);
    vbox2->addStretch(1);

    hbox2->addWidget(text_);
    hbox2->addWidget(sstat_,0,Qt::AlignLeft);
    hbox2->addStretch(1);

    hbox->setSpacing(20);
    hbox->addStretch(1);
    hbox->addLayout(vbox2);
    hbox->addLayout(vbox);
    hbox->addStretch(1);

    capture = cvCaptureFromCAM( CV_CAP_ANY ); //0=default, -1=any camera, 1..99=your camera
    if( !capture )
    {
    cout << "No camera detected" << endl;
    }

    // Direct keyboard events here.
	this->keyboard->setTarget(this);

    uartQueue = new UARTQueue();
    uart = new UART("/dev/ttyAMA0", 9600, uartQueue);
    uart->start();
    joystick = new JoystickThread(uartQueue, sstat_, &skud_);
    joystick->start();

    uartQueue->post(protocol.constructString(Protocol::CMD_LASER, '0'), 4);
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
    joystick->enableAlarm();
    msg_->setText("Alarm aktiveret");
}

void cameraFeed::OnDeaktiverPressed()
{
    joystick->disableAlarm();
    msg_->setText("Alarm deaktiveret");
}

void cameraFeed::OnGenladPressed()
{
    Genlad *genlad= new Genlad(keyboard);
    genlad->setWindowTitle("Genlad");
    genlad->exec();

    sstat_->setNum(skud_);

    this->keyboard->setTarget(this);
}

void cameraFeed::OnAdvarselPressed()
{
    uartQueue->post(protocol.constructString(Protocol::CMD_ALARM, '0'), 4);
    msg_->setText("Advarsel Trykket");

}


void cameraFeed::OnLogUdPressed()
{
    Login *log = new Login(keyboard);
    log->setFixedSize(500,300);
    log->setWindowTitle("Login");
    log->show();

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
                OnAdvarselPressed();
                break;
            case Qt::Key_5:
                OnLogUdPressed();
            default:
                break;
    }
}

cameraFeed::~cameraFeed()
{
    cvReleaseCapture( &capture );

    // Turn off laser
    /* LASER MAGIC */

    joystick->stop();
    uart->stop();

    uartQueue->post(protocol.constructString(Protocol::CMD_LASEROFF, '0'), 4);

    while (joystick->isRunning()) { /* WAIT TIME */ }
    if (!joystick->isRunning()) delete joystick;

    while (uart->isRunning()) { /* WAIT TIME */ }
    if (!uart->isRunning()) delete uart;

    delete uartQueue;

    file.open("AntalSkud.txt",ios_base::out);
    file << skud_;
    file.close();
}
