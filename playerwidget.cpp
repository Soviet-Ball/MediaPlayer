#include "playerwidget.h"
PlayerWidget::PlayerWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setStyleSheet("background-color: black;");
    this->setAttribute(Qt::WA_AcceptTouchEvents, true);

    player = new QMediaPlayer;
    videowidget = new QVideoWidget(this);
    audiooutput = new QAudioOutput;
    label = new QLabel(this);
    loop = new QEventLoop(this);
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    sink = new QVideoSink;
#else
    probe = new QVideoProbe;
#endif

    label->setStyleSheet("background-color: black;");
    label->resize(this->size());
    label->setAlignment(Qt::AlignCenter);
    if(widgetmode)
    {
        videowidget->show();
        label->hide();
    }
    else
    {
       videowidget->hide();
       label->show();
    }
    player->setVideoOutput(videowidget);

#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    player->setAudioOutput(audiooutput);
    player->setVideoSink(sink);
#else
    probe->setSource(player);
#endif

    this->installEventFilter(this);
    label->installEventFilter(this);

#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    connect(player,&QMediaPlayer::errorChanged,[this](){
        emit error_private(player->error(),player->errorString());
        emit error(player->error(),player->errorString());
    });
    connect(player,&QMediaPlayer::hasVideoChanged,[this](){
        videoAvailable = player->hasVideo();
        emit hasVideoChanged(videoAvailable);
        if(this->hasVideo())
        {
            label->show();
        }
        else
        {
            label->clear();
            label->hide();
        }
    });
    connect(player,&QMediaPlayer::hasAudioChanged,[this](){
        audioAvailable = player->hasAudio();
        emit hasAudioChanged(audioAvailable);
        if(this->hasVideo())
        {
            label->show();
        }
        else
        {
            label->clear();
            label->hide();
        }
    });
    connect(player,&QMediaPlayer::playbackStateChanged,[this](){
        emit stateChanged(this->state());
    });
    connect(sink,&QVideoSink::videoFrameChanged,[this](const QVideoFrame &f){
        frame = f;
        emit videoFrameChanged(frame);
        if(f.isValid() && widgetmode == false && enable == true && label->width() > 0 && label->height() > 0)
        {
            label->setPixmap(QPixmap::fromImage(f.toImage().scaled(label->size(),Qt::KeepAspectRatio,mode)));
        }
    });
#else

    QObject::connect(player,QOverload<QMediaPlayer::Error>::of(&QMediaPlayer::error),[=](){
        emit error_private(player->error(),player->errorString());
        emit error(player->error(),player->errorString());
    });

    QObject::connect(player,QOverload<bool>::of(&QMediaPlayer::videoAvailableChanged),[=](bool available){
        videoAvailable = available;
        emit hasVideoChanged(videoAvailable);
        if(this->hasVideo())
        {
            label->show();
        }
        else
        {
            label->clear();
            label->hide();
        }
    });

    QObject::connect(player,QOverload<bool>::of(&QMediaPlayer::audioAvailableChanged),[=](bool available){
        audioAvailable = available;
        emit hasAudioChanged(audioAvailable);
        if(this->hasVideo())
        {
            label->show();
        }
        else
        {
            label->clear();
            label->hide();
        }
    });

    QObject::connect(probe,QOverload<const QVideoFrame &>::of(&QVideoProbe::videoFrameProbed),[=](const QVideoFrame &f){
        frame = f;
        emit videoFrameChanged(frame);
        if(f.isValid() && enable == true && widgetmode == false)
        {
            QImage image = qt_imageFromVideoFrame(f);
#ifdef Q_OS_WIN
            image = image.mirrored();
#endif
            if(!image.isNull() && label->width() > 0 && label->height() > 0)
            {
                image = image.scaled(label->size(),Qt::KeepAspectRatio,mode);
                label->setPixmap(QPixmap::fromImage(image));
            }
        }
    });

    QObject::connect(player,QOverload<QMediaPlayer::State>::of(&QMediaPlayer::stateChanged),[=](){
        emit stateChanged(this->state());
    });
#endif
    connect(player,&QMediaPlayer::mediaStatusChanged,[this](){
        emit statusChanged_private(player->mediaStatus());
        emit statusChanged(player->mediaStatus());
    });
    connect(player,&QMediaPlayer::positionChanged,[this](){
        emit positionChanged(player->position());
    });
    connect(player,&QMediaPlayer::durationChanged,[this](){
        emit durationChanged(player->duration());
    });
}
bool PlayerWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::KeyRelease)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            emit keyRelease(keyEvent);
        }
        else if(event->type() == QEvent::Resize)
        {
            if(widgetmode)
                videowidget->resize(this->size());
            else
                label->resize(this->size());
        }
        else if(event->type() == QEvent::Close)
        {
            player->stop();
        }
        else if(event->type() == QEvent::Hide)
        {
            if(widgetmode)
                videowidget->hide();
            else
                label->hide();
        }
        else if(event->type() == QEvent::Show)
        {
            if(widgetmode)
                videowidget->show();
            else
                label->show();
        }
    }
    if(watched == label)
    {
        if(event->type() == QEvent::Resize)
        {
            if(frame.isValid())
            {
                QImage img = frameToImage(frame);
                img = img.scaled(label->size(),Qt::KeepAspectRatio,mode);
                label->setPixmap(QPixmap::fromImage(img));
            }
        }
    }
    return QObject::eventFilter(watched,event);
}
PlayerWidget::~PlayerWidget()
{
}
bool PlayerWidget::setFilePath(QString p)
{
    if(QFileInfo(p).isFile() && hasFilePermission(p,QIODevice::ReadOnly))
    {
        emit filePathChanged(filepath,p);
        filepath = p;
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
        player->setSource(QUrl::fromLocalFile(filepath));
#else
        player->setMedia(QUrl::fromLocalFile(filepath));
#endif
        return true;
    }
    else
    {
        return false;
    }
}
bool PlayerWidget::play()
{
#if (QT_VERSION < QT_VERSION_CHECK(6,5,0)) || defined(Q_OS_ANDROID)
    //QEventLoop* loop = new QEventLoop(this);
    QObject::connect(this,QOverload<QMediaPlayer::Error,QString>::of(&PlayerWidget::error_private),[=](QMediaPlayer::Error error,QString string){
        if(error != QMediaPlayer::Error::NoError)
        {
            this->disconnect(this,SIGNAL(error_private(QMediaPlayer::Error,QString)),0,0);
            ret = false;
            filepath = "";
            loop->quit();
            return false;
        }
    });
    QObject::connect(this,QOverload<QMediaPlayer::MediaStatus>::of(&PlayerWidget::statusChanged_private),[=](QMediaPlayer::MediaStatus status){
        if(status == QMediaPlayer::BufferedMedia)
        {
            this->disconnect(this,SIGNAL(statusChanged_private(QMediaPlayer::MediaStatus)),0,0);
            ret = true;
            loop->quit();
            return true;
        }
    });
    player->play();
    if(player->mediaStatus()==QMediaPlayer::BufferedMedia)
        return true;
    loop->exec();
    //qDebug() << this->mediaStatus();
    //return bool;
    return ret;
#else
    player->play();
    //qDebug() << player->mediaStatus() << player->hasAudio() << player->hasVideo() << filepath;
    bool ok = bool(player->mediaStatus()==QMediaPlayer::BufferedMedia && (this->hasAudio() || this->hasVideo()));
    if(ok)
        label->clear();
    return ok;
#endif

    if(true)
    {
    /*
    if(QFileInfo(filepath).isFile() && hasFilePermission(filepath,QIODevice::ReadOnly))
    {
        int time_to_wait = 5000;
        player->play();
        QObject::connect(this,QOverload<QMediaPlayer::Error,QString>::of(&PlayerWidget::error_private),[=](QMediaPlayer::Error error,QString string){
            if(error != QMediaPlayer::Error::NoError)
            {
                this->disconnect(this,SIGNAL(error_private(QMediaPlayer::Error,QString)),0,0);
                ret = false;
                filepath = "";
                loop->quit();
                return false;
            }
        });
        QObject::connect(this,QOverload<QMediaPlayer::MediaStatus>::of(&PlayerWidget::statusChanged_private),[=](QMediaPlayer::MediaStatus status){
            if(status == QMediaPlayer::BufferedMedia)
            {
                this->disconnect(this,SIGNAL(statusChanged_private(QMediaPlayer::MediaStatus)),0,0);
                ret = true;
                loop->quit();
                return true;
            }
        });
        if(player->mediaStatus()==QMediaPlayer::BufferedMedia)
        {
            this->disconnect(this,SIGNAL(statusChanged_private(QMediaPlayer::MediaStatus)),0,0);
            this->disconnect(this,SIGNAL(error_private(QMediaPlayer::Error,QString)),0,0);
            return true;
        }
        else
        {
            QTimer::singleShot(time_to_wait,[=](){
                this->disconnect(this,SIGNAL(statusChanged_private(QMediaPlayer::MediaStatus)),0,0);
                this->disconnect(this,SIGNAL(error_private(QMediaPlayer::Error,QString)),0,0);
                loop->quit();
                return (player->mediaStatus() == QMediaPlayer::BufferedMedia);
            });
            loop->exec();
            return ret;
        }
    }
    else
    {
        return false;
    }
    */
    }
}
void PlayerWidget::setPosition(int position)
{
    if(position >= 0)
        player->setPosition(position);
}
int PlayerWidget::volume()
{
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
        return int(player->audioOutput()->volume()*100.0);
#else
        return player->volume();
#endif
}
void PlayerWidget::setVolume(int v)
{
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
        player->audioOutput()->setVolume(float(v)/100.0);
#else
        player->setVolume(v);
#endif
}
PlayerWidget::State PlayerWidget::state()
{
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    if(player->playbackState() == QMediaPlayer::PlaybackState::PlayingState)
    {
        return PlayerWidget::State::PlayingState;
    }
    else if(player->playbackState() == QMediaPlayer::PlaybackState::PausedState)
    {
        return PlayerWidget::State::PausedState;
    }
    else
    {
        return PlayerWidget::State::StoppedState;
    }
#else
    if(player->state() == QMediaPlayer::State::PlayingState)
    {
        return PlayerWidget::State::PlayingState;
    }
    else if(player->state() == QMediaPlayer::State::PausedState)
    {
        return PlayerWidget::State::PausedState;
    }
    else
    {
        return PlayerWidget::State::StoppedState;
    }
#endif
}
void PlayerWidget::clear()
{
    player->stop();
    label->clear();
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    player->setSource(QUrl());
#else
    player->setMedia(QUrl());
#endif
    frame = QVideoFrame();
    audioAvailable = false;
    videoAvailable = false;
}
