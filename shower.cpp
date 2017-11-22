#include "shower.h"
#include <QDebug>

Shower::Shower(QObject *parent)
{

}


void Shower::show(cv::Mat img){
    qDebug() << "show";
    imshow("TEST", img);
}
