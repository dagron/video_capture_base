#include "videoplayer.h"
#include "QDebug"
#include <QDateTime>

void VideoPlayer::run()
{
    qint64 begin_time, last_time_frame;
    last_time_frame = QDateTime::currentMSecsSinceEpoch();

    int delay = (1000/frameRate);
    while(!stop){
        begin_time = QDateTime::currentMSecsSinceEpoch();
        if (!capture.read(frame))
        {
            stop = true;
            qDebug() << "ALARM! STOP READ FRAME!";
        }

        if(!frame.empty()){
            qDebug() << "[VIDEO CAPTURE] last send(ms) :" << (begin_time - last_time_frame);
            qDebug() << "[VIDEO CAPTURE] send every(ms):" << (1000 / this->fps);
            if (( begin_time - last_time_frame) > (1000 / this->fps)){
                qDebug() << "[VIDEO CAPTURE] Send frame : " << capture.get(CV_CAP_PROP_POS_FRAMES);
                emit processedImage(frame);
                last_time_frame = begin_time;
            }
        } else {
            qDebug() << "[VIDEO CAPTURE] Read EMPTY frame";
        }

        qDebug() << "[VIDEO CAPTURE] FPS : " << QDateTime::currentMSecsSinceEpoch() - begin_time ;
        this->msleep(delay);
    }
}

void VideoPlayer::msleep(int ms)
{
    //QThread::msleep(ms);
    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}

VideoPlayer::VideoPlayer(QObject *parent) : QThread(parent)
{
    stop = true;
}

VideoPlayer::~VideoPlayer()
{
    mutex.lock();
    stop = true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}

bool VideoPlayer::loadVideo(QString filename) {
    return loadVideo(filename, 3);
}

bool VideoPlayer::loadVideo(QString filename, int fps)
{
    capture.open(filename.toUtf8().data());
    if (capture.isOpened())
    {
        //capture.set(CV_CAP_PROP_FPS, 1800);
        this->frameRate = capture.get(CV_CAP_PROP_FPS);
        qInfo() << "CV_CAP_PROP_FPS: " << capture.get(CV_CAP_PROP_FPS);
        if ((fps > 0) && (fps < 10)) {
          this->fps = fps;
        } else {
          return false;
        }

        return true;
    }
    else
        return false;
}

void VideoPlayer::Play()
{
    if (!isRunning()) {
            if (isStopped()){
                stop = false;
            }
            start(LowPriority);
    }
}

bool VideoPlayer::setFPS(int fps)
{
    if ((fps > 0) && (fps < 10)) {
      this->fps = fps;
      return true;
    } else {
      return false;
    }
}

int VideoPlayer::getFPS()
{
    return this->fps;
}

void VideoPlayer::Stop()
{
    stop = true;
}

bool VideoPlayer::isStopped() const
{
    return this->stop;
}

void VideoPlayer::release()
{
    Stop();
    capture.release();
}
