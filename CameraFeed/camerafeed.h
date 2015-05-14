#ifndef CAMERAFEED_H
#define CAMERAFEED_H
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <QWidget>
#include <QPushButton>
#include <QImage>
#include <QLabel>
#include <QTimer>
#include <QDialog>
#include <fstream>
#include "MatrixKeyboard.h"

using namespace cv;

class cameraFeed : public QWidget
{
    Q_OBJECT

public:
    cameraFeed(MatrixKeyboard *keyboard, QWidget *parent = 0);
    ~cameraFeed();
    QImage putImage(const Mat& mat);

private slots:
    //void Onstartpressed();
    //void Onslutpressed();

    void OnAktiverPressed();
    void OnDeaktiverPressed();
    void OnGenladPressed();
    void OnAdvarselPressed();
    void OnLogUdPressed();

    void updatePicture();

protected:
    void keyPressEvent(QKeyEvent *k);

private:
    QPushButton *aktiver_;
    QPushButton *deaktiver_;
    QPushButton *genlad_;
    QPushButton *advarsel_;
    QPushButton *logud_;

    //QPushButton *start_;
    //QPushButton *slut_;
    CvCapture* capture = 0;
    QLabel *feed_ = new QLabel();
    QLabel *msg_ = new QLabel();
    QLabel *text_ = new QLabel();
    QLabel *sstat_ = new QLabel();
    QTimer *timer_;

    MatricKeyboard *keyboard;

};

#endif // CAMERAFEED_H
