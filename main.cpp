#include <QApplication>
#include <QObject>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <videoplayer.h>
#include <shower.h>
#include <QDebug>

#include <QMainWindow>
#include <QShortcut>

VideoPlayer* myPlayer;


void speed_pluse(){
    auto fps = myPlayer->getFPS();
    myPlayer->setFPS(++fps);
    qDebug() << "PLUSE : " << QString::number(fps);
}

void speed_minus(){
    auto fps = myPlayer->getFPS();
    myPlayer->setFPS(--fps);
    qDebug() << "MINUS : " << QString::number(fps);
}

void show(cv::Mat img){
    cv::imshow("test", img);
    img.release();
    char k = cvWaitKey(100);

    if(k == 'q'){
        qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        speed_pluse();
    }
    if(k == 'w'){
        qDebug() << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
        speed_minus();
    }
}



int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QApplication::setOrganizationName("formoza");
    QApplication::setApplicationName("TruckDetector");

    myPlayer = new VideoPlayer();
    Shower* shower = new Shower();
//    QObject::connect(myPlayer, SIGNAL(processedImage(cv::Mat)),
//                               shower, SLOT(show(cv::Mat)));

    //QObject::connect(myPlayer, &VideoPlayer::processedImage, shower, &Shower::show);
    //QObject::connect(myPlayer, &VideoPlayer::processedImage, [](cv::Mat img){qDebug() << "Tick";});
    QObject::connect(myPlayer, &VideoPlayer::processedImage, show);




    if (myPlayer->loadVideo(QString("rtsp://stream.lesohranitel.ru/RU.43.01"), 3)) {
        qDebug() << "True";
    } else {
        qDebug() << "ELSE";
    }

    myPlayer->Play();
    qDebug() << "Play";
    return app.exec();
}
