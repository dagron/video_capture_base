#ifndef SHOWER_H
#define SHOWER_H

#include <opencv2/opencv.hpp>
#include <QObject>

#include <QObject>

class Shower : public QObject
{
    Q_OBJECT
public:
    Shower(QObject *parent = 0);
public slots:
    void show(cv::Mat);
};

#endif // SHOWER_H
