#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H
#define Multimedia_And_Widgets_Enabled
#define Multimedia_Private_Enabled
#include <QWidget>
#include "api.h"
#include <QLabel>
#include <QFileInfo>
#include <QKeyEvent>
#ifdef Multimedia_And_Widgets_Enabled
#include <QImageWriter>
#include <QCamera>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaMetaData>
#include <QVideoFrame>
#include <QGraphicsVideoItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QAudioOutput>
#include <QMediaRecorder>
#include <QAudioDecoder>
#if(QT_VERSION>=QT_VERSION_CHECK(6,0,0))
#include <QVideoSink>
#include <QVideoFrameFormat>
#else
#ifdef Multimedia_Private_Enabled
#include <private/qvideoframe_p.h>
#endif
#include <QVideoProbe>
#include <QAbstractVideoSurface>
#include <QAudioRecorder>
#include <QAudioEncoderSettings>
#include <QVideoEncoderSettings>
#endif
#endif

class PlayerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit PlayerWidget(QWidget *parent = nullptr);
    ~PlayerWidget();
    enum State
    {
        StoppedState,
        PlayingState,
        PausedState
    };
    bool eventFilter(QObject *watched, QEvent *event);
    bool setFilePath(QString p);
    QString filePath() {return filepath;}
    QMediaPlayer* mediaPlayer() {return player;}
    bool play();
    void pause() {player->pause();}
    void stop() {player->stop();}
    void setPosition(int position);
    qint64 duration() {return player->duration();}
    qint64 position() {return player->position();}
    int volume();
    void setVolume(int v);
    bool hasVideo() {return videoAvailable;}
    bool hasAudio() {return audioAvailable;}
    QVideoFrame videoFrame() {return frame;}
    QMediaPlayer::MediaStatus mediaStatus() {return player->mediaStatus();}
    PlayerWidget::State state();
    void lock() {enable = false;}
    void unlock() {enable = true;}
    bool isLocked() {return !enable;}
    QMediaPlayer::Error errorType() {return player->error();}
    QString errorString() {return player->errorString();}
    void clear();
    void setTransformationMode(Qt::TransformationMode m) {mode = m;}
    Qt::TransformationMode transformationMode() {return mode;}
signals:
    void keyRelease(QKeyEvent* event);
    void error(QMediaPlayer::Error e,QString errorString);
    void statusChanged(QMediaPlayer::MediaStatus status);
    void positionChanged(int position);
    void durationChanged(int duration);
    void videoFrameChanged(QVideoFrame frame);
    void hasVideoChanged(bool available);
    void hasAudioChanged(bool available);
    void stateChanged(PlayerWidget::State state);
    void filePathChanged(QString oldpath,QString newpath);
private:
    Q_SIGNAL void statusChanged_private(QMediaPlayer::MediaStatus status);
    Q_SIGNAL void error_private(QMediaPlayer::Error e,QString errorString);
    Qt::TransformationMode mode = Qt::FastTransformation;
    QEventLoop* loop;
    QMediaPlayer* player;
    QVideoWidget* videowidget;
    QLabel* label;
    QAudioOutput* audiooutput;
    QVideoFrame frame;
    QString filepath = "";
    bool videoAvailable = false;
    bool audioAvailable = false;
    bool enable = true;
    bool ret;
    bool widgetmode = false;
    QPoint startpoint = QPoint(-1,-1);
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    QVideoSink* sink;
#else
    QVideoProbe* probe;
#endif
};
#endif // PLAYERWIDGET_H
