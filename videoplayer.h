#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QString>

using namespace cv;

class VideoPlayer : public QThread
{
    Q_OBJECT
private:
    bool stop;
    QMutex mutex;
    QWaitCondition condition;
    Mat frame;
    int frameRate;
    int fps;
    VideoCapture capture;
//  Mat RGBframe;
//  Mat img;

signals:
//Signal to output frame to be displayed
     void processedImage(cv::Mat &image);


protected:
    void run();
    void msleep(int ms);

public:
    VideoPlayer(QObject *parent = 0);
    ~VideoPlayer();
    //Load a video from memory
    bool loadVideo(QString filename);
    bool loadVideo(QString filename, int fps);

    bool setFPS(int fps);
    int getFPS();

    //Play the video
    void Play();
    //Stop the video
    void Stop();
    //check if the player has been stopped
    bool isStopped() const;

    //Release Camera
    void release();
};

#endif // VIDEOPLAYER_H
