#include "widget.h"
QtMessageHandler defaultMessageHandler;
static QString toString(QtMsgType type)
{
    QString text;
    switch (type)
    {
        case QtDebugMsg:
            text = "Debug";
            break;
        case QtWarningMsg:
            text = "Warning";
            break;
        case QtInfoMsg:
            text = "Info";
            break;
        case QtCriticalMsg:
            text = "Critical";
            break;
        case QtFatalMsg:
            text = "Fatal";
            break;
    }
    return text;
}
static QString toString(QMediaPlayer::Error error)
{
    if(error == QMediaPlayer::NoError)
        return "QMediaPlayer::NoError";
    else if(error == QMediaPlayer::ResourceError)
        return "QMediaPlayer::ResourceError";
    else if(error == QMediaPlayer::FormatError)
        return "QMediaPlayer::FormatError";
    else if(error == QMediaPlayer::NetworkError)
        return "QMediaPlayer::NetworkError";
    else if(error == QMediaPlayer::AccessDeniedError)
        return "QMediaPlayer::AccessDeniedError";
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
    else if(error == QMediaPlayer::ServiceMissingError)
        return "QMediaPlayer::ServiceMissingError";
    else if(error == QMediaPlayer::MediaIsPlaylist)
        return "QMediaPlayer::MediaIsPlaylist";
    else
        return QString();
#else
    return QString();
#endif
}
static QString toLinkedString(QString s,QString url)
{
    return QString("<a href=\""+url+"\">"+s+"</a>");
}
void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    bool printcontext = false;
    QString text = toString(type);
    QString fileName = QFileInfo(QString(context.file)).fileName();
    QString functionName = QString(context.function);
    functionName.replace(" __cdecl "," ");
    QString line = QString::number(context.line);

    if(printcontext)
    {
        text = text + " at ";
        text = text + "File(" + fileName + ") ";
        text = text + "Function(" + functionName + ") ";
        text = text + "Line(" + line + ")";
        text = text + ":\n" + msg;
    }
    else
    {
        text = text + ":" + msg;
    }
#ifndef Q_OS_ANDROID
    if(defaultMessageHandler)
    {
        defaultMessageHandler(type,context,text);
    }
#else
    Android::showNativeToast(msg);
#endif
}
template<typename T>
QString toAddress(const T& variable)
{
    qintptr address = reinterpret_cast<qintptr>(&variable);
    return QString::number(address, 16);
}
static void printSettings(QSettings* setting)
{
    QString text = QString(setting->metaObject()->className()) + "(" + toAddress(setting) + "):\n";
    auto list = setting->allKeys();
    int i = 0;
    while(i < list.count())
    {
        QString string = list.at(i);
        text = text + string + "=" + setting->value(string).toString();
        if(i != list.count() - 1)
            text += "\n";
        i++;
    }
    qDebug() << text.toStdString().c_str();
}
void androidConfigurationChangedSender()
{
#if (QT_VERSION < QT_VERSION_CHECK(6,5,0))
    Widget* w = Widget::getCurrentWindow();
    if(w != nullptr)
    {
        w->systemThemeChanged(isSystemDarkMode());
    }
#endif
}
static int getMaxIntIndex(QList<int> list)
{
    int count = list.count();
    if(count == 0)
    {
        return -1;
        //return std::numeric_limits<int>::quiet_NaN();
    }

    int max_i = 0;
    int max = list.at(0);
    int i = 0;
    while(i < count)
    {
        if(list.at(i) > max)
        {
            max = list.at(i);
            max_i = i;
        }
        i++;
    }
    return max_i;
}
static bool hasPixmap(QLabel* label)
{
#if QT_VERSION_MAJOR == 5
    return !(label->pixmap() == nullptr);
#else
    return !label->pixmap().isNull();
#endif
}
void Widget::initSettings(bool clear)
{
    if(settings && settings != nullptr)
    {
        settings->sync();
        settings = nullptr;
    }
    if(clear && QFileInfo(settingpath).isFile())
    {
        if(!QFile::remove(settingpath))
            emit errorChanged("删除文件"+settingpath+"失败");
    }
#ifndef Q_OS_ANDROID
    settingpath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)+"/"+QApplication::applicationName()+"/settings.ini";
#else
    settingpath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)+"/settings.ini";
#endif
    if(!hasFilePermission(settingpath,QIODevice::ReadWrite))
        settingpath = QDir().homePath()+"/settings.ini";
    bool exists = QFileInfo(settingpath).isFile();
    settings = new QSettings(settingpath,QSettings::IniFormat,this);
    if(settings->status() == QSettings::NoError)
    {
        settings = new QSettings(settingpath,QSettings::IniFormat,this);
        QStringList keylist;
        QStringList valuelist;
        if(true)
        {
            keylist.append("x");
            valuelist.append("-1");
            keylist.append("y");
            valuelist.append("-1");
            keylist.append("width");
            valuelist.append("-1");
            keylist.append("height");
            valuelist.append("-1");
            keylist.append("appTheme");
            valuelist.append("system");
            keylist.append("loadGeometry");
            valuelist.append("false");
            keylist.append("volume");
            valuelist.append("100");
            keylist.append("openpath");
            valuelist.append("default");
            keylist.append("savepath");
            valuelist.append("default");
            keylist.append("filedialog");
            valuelist.append("default");
            keylist.append("mode");
            valuelist.append("single");
            keylist.append("transformationMode");
            valuelist.append("fast");
            keylist.append("showSmoothly");
            valuelist.append("true");
            keylist.append("staysOnTop");
            valuelist.append("false");
        }
        for(int i = 0;i < keylist.size();i++)
        {
            if(!settings->allKeys().contains(keylist.at(i)))
            {
                settings->setValue(keylist.at(i),valuelist.at(i));
                if(exists)
                {
                    emit errorChanged("在文件"+settingpath+"中无法找到键"+keylist.at(i));
                }
            }
        }
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
    settings->setIniCodec(QTextCodec::codecForName("utf-8"));
#endif
    settings->sync();
    }
    else
    {
        emit errorChanged("初始化配置文件时出错");
    }
}
void Widget::initList(bool clear)
{
    if(medialist && medialist != nullptr)
    {
        medialist->sync();
        medialist = nullptr;
    }
    if(clear && QFileInfo(listpath).isFile())
    {
        if(!QFile::remove(listpath))
            emit errorChanged("删除文件"+listpath+"失败");
    }
#ifndef Q_OS_ANDROID
    listpath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)+"/"+QApplication::applicationName()+"/list.ini";
#else
    listpath = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation)+"/list.ini";
#endif
    if(!hasFilePermission(listpath,QIODevice::ReadWrite))
        listpath = QDir().homePath()+"/list.ini";
    medialist = new QSettings(listpath,QSettings::IniFormat,this);
    if(medialist->status() == QSettings::NoError)
    {
        int i = 0;
        while(i < medialist->allKeys().count())
        {
            if(!isint(medialist->allKeys().at(i)))
            {
                medialist->remove(medialist->allKeys().at(i));
                emit errorChanged("媒体列表中包含非数字键: "+medialist->allKeys().at(i));
            }
            else
            {
                i++;
            }
        }
        i = 0;
        while(i < medialist->allKeys().count())
        {
            int current = medialist->allKeys().at(i).toInt();
            QString path = medialist->value(medialist->allKeys().at(i)).toString();
            if(!QFileInfo(path).isFile())
            {
                int j = current;
                while(medialist->allKeys().contains(QString::number(j+1)))
                {
                    medialist->setValue(QString::number(j),medialist->value(QString::number(j+1)));
                    j++;
                }
                medialist->remove(QString::number(j));
            }
            i++;
        }
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
    medialist->setIniCodec(QTextCodec::codecForName("utf-8"));
#endif
    medialist->sync();
    }
    else
    {
        emit errorChanged("初始化媒体列表时出错");
    }
}
void Widget::readSettings()
{
    if(!settings || settings == nullptr)
        return;
    if(!QList<QString>({"system","light","dark"}).contains(settings->value("appTheme").toString()))
    {
        settings->setValue("appTheme","system");
    }
    if(settings->value("appTheme").toString() == "dark")
        darkmode = true;
    else if(settings->value("appTheme").toString() == "light")
        darkmode = false;
    else
        darkmode = oldThemeIsDark;
    this->checkDarkMode();
    if(!isBool(settings->value("loadGeometry").toString()))
    {
        settings->setValue("loadGeometry","false");
    }
    if(settings->value("loadGeometry").toString() == "true")
    {
        if(settings->value("width").toInt() == -1 && settings->value("height") == -1)
        {
            this->maximumSize();
        }
        else if(settings->value("width").toInt() > 0 && settings->value("height").toInt() > 0)
        {
            this->move(settings->value("x").toInt(),settings->value("y").toInt());
            this->resize(settings->value("width").toInt(),settings->value("height").toInt());
        }
    }
    if(!isint(settings->value("volume").toString()) || settings->value("volume").toInt() > 100)
    {
        settings->setValue("volume","100");
        volumeslider->setValue(100);
    }
    else if(settings->value("volume").toInt() < 0)
    {
        settings->setValue("volume","0");
        volumeslider->setValue(0);
    }
    else
    {
        volumeslider->setValue(settings->value("volume").toInt());
    }
    if(!QList<QString>({"single","random","repeat"}).contains(settings->value("mode").toString()))
    {
        settings->setValue("mode","single");
    }
    if(settings->value("mode").toString() == "single")
        playmode = PlaySingle;
    else if(settings->value("mode").toString() == "repeat")
        playmode = PlayRepeat;
    else
        playmode = PlayRandom;
    this->setDarkMode(darkmode);
    if(!QList<QString>({"fast","smooth"}).contains(settings->value("transformationMode").toString()))
    {
        settings->setValue("transformationMode","fast");
    }
    if(settings->value("transformationMode").toString() == "fast")
    {
        playerwidget->setTransformationMode(Qt::FastTransformation);
    }
    else
    {
        playerwidget->setTransformationMode(Qt::SmoothTransformation);
    }
    if(!isBool(settings->value("showSmoothly").toString()))
    {
        settings->setValue("showSmoothly","true");
    }
    if(!isBool(settings->value("staysOnTop").toString()))
        settings->setValue("staysOnTop","false");
    if(toBool(settings->value("staysOnTop").toString()))
    {
        stayontopaction->setChecked(true);
        staysOnTop(this);
    }

}
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QObject::connect(this,QOverload<QString>::of(&Widget::errorChanged),[=](QString errorString){
        taskbar->show();
        taskbar->setState(MyTaskBarProgress::Stopped);
        QMessageBox::critical(this,"错误",errorString,"确定");
        taskbar->hide();
    });

    defaultMessageHandler = qInstallMessageHandler((QtMessageHandler)customMessageHandler);
    this->initSettings();
    this->initList();

    taskbar = new MyTaskBarProgress(this);
    playerwidget = new PlayerWidget(this);
    mainwidget = new QWidget(this);
    openbutton = new QPushButton(mainwidget);
    settingbutton = new QPushButton(mainwidget);
    controlwidget = new QWidget(this);
    mediawidget = new QWidget(mainwidget);
    iconlabel = new QLabel(controlwidget);
    namelabel = new QLabel(controlwidget);
    timelabel = new QLabel(this);
    slider = new QSlider(this);
    backwardbutton = new QPushButton(controlwidget);
    pausebutton = new QPushButton(controlwidget);
    forwardbutton = new QPushButton(controlwidget);
    modebutton = new QPushButton(controlwidget);
    volumebutton = new QPushButton(controlwidget);
    fullscreenbutton = new QPushButton(controlwidget);
    aboutbutton = new QPushButton(controlwidget);
    widget = new QWidget(mediawidget);
    area = new QScrollArea(mediawidget);
    volumedlg = new QWidget(nullptr);
    volumeslider = new QSlider(volumedlg);
    volumelabel = new QLabel(volumedlg);
#ifdef Q_Device_Mobile
    aboutdialog = new QDialog;
#else
    aboutdialog = new QDialog(this);
#endif
    filenamelabel1 = new QLabel(aboutdialog);
    filenamelabel2 = new QLabel(aboutdialog);
    filepathlabel1 = new QLabel(aboutdialog);
    filepathlabel2 = new QLabel(aboutdialog);
    widthlabel1 = new QLabel(aboutdialog);
    widthlabel2 = new QLabel(aboutdialog);
    heightlabel1 = new QLabel(aboutdialog);
    heightlabel2 = new QLabel(aboutdialog);
    existlabel1 = new QLabel(aboutdialog);
    existlabel2 = new QLabel(aboutdialog);
    readablelabel1 = new QLabel(aboutdialog);
    readablelabel2 = new QLabel(aboutdialog);
    durationlabel1 = new QLabel(aboutdialog);
    durationlabel2 = new QLabel(aboutdialog);
    copyaction = new QAction;
    opendiraction = new QAction;
    singleaction = new QAction;
    repeataction = new QAction;
    randomaction = new QAction;
    aboutaction = new QAction;
    stayontopaction = new QAction;
    saveframeaction = new QAction;
    loop = new QEventLoop(this);

    mainwidget->move(0,0);
    mainwidget->resize(this->size());
    //mainwidget->setStyleSheet("background-color:rgba(255,255,255,0);");
    openbutton->resize(mainwidget->width()*0.2,mainwidget->height()*0.1);
    openbutton->move(10,10);
    openbutton->setText("打开");
    settingbutton->setText("设置");
    //openbutton->setStyleSheet("QPushButton{background-color:rgb(255,255,255);border: 0.5px solid rgb(195, 195, 195);border-radius:4;}QPushButton:pressed{background-color: rgb(224,238,249);border: 0.5px solid #0078D4;}QPushButton:hover{background-color: rgb(224,238,249);border: 0.5px solid #0078D4;}");

    playerwidget->move(0,0);
    playerwidget->resize(mainwidget->size());
    playerwidget->hide();

    controlwidget->resize(this->width(),100);
    controlwidget->move(0,this->height()-controlwidget->height());

    iconlabel->resize(controlwidget->height()-20,controlwidget->height()-20);
    iconlabel->move(10,10);
    namelabel->resize(iconlabel->width()*1.5,iconlabel->height());
    namelabel->move(iconlabel->x()+iconlabel->width(),iconlabel->y());
    iconlabel->setStyleSheet("background-color:white");
    //namelabel->setStyleSheet("background-color:yellow");
    iconlabel->setAlignment(Qt::AlignCenter);
    namelabel->setAlignment(iconlabel->alignment());
    namelabel->setWordWrap(true);
    if(namelabel->x()+namelabel->width() > controlwidget->width()/5*2  || namelabel->width() <= namelabel->height()/2)
        namelabel->hide();
    else if(!iconlabel->isHidden())
        namelabel->show();

    timelabel->resize(60,30);
    timelabel->move(controlwidget->x()+controlwidget->width()-timelabel->width()-10,controlwidget->y()-timelabel->height());
    timelabel->setAlignment(Qt::AlignCenter);

    slider->resize(controlwidget->width()-30-timelabel->width(),30);
    slider->move(controlwidget->x()+10,timelabel->y());
    slider->setSingleStep(5000);
    slider->setRange(0,1);
    slider->setEnabled(false);
    slider->setTracking(true);
    slider->setOrientation(Qt::Horizontal);

    mediawidget->move(openbutton->x(),openbutton->y()+openbutton->height()+10);
    mediawidget->resize(mainwidget->width()-2*mediawidget->x(),slider->y()-openbutton->height()-openbutton->y()-20);
    //mediawidget->setStyleSheet("background-color:yellow;");

    int x;
    if(iconlabel->isHidden())
        x = 0;
    else if(namelabel->isHidden())
        x = iconlabel->x()+iconlabel->width();
    else
        x = namelabel->x()+namelabel->width();
#ifdef Q_Device_Mobile
    pausebutton->resize(35,35);
#else
    pausebutton->resize(50,50);
#endif
    forwardbutton->resize(pausebutton->size());
    backwardbutton->resize(pausebutton->size());
    if(controlwidget->width()/2-namelabel->x()-namelabel->width()-pausebutton->width()/2-backwardbutton->width()-10 >= 10)
        pausebutton->move(controlwidget->width()/2-pausebutton->width()/2,controlwidget->height()/2-pausebutton->height()/2);
    else
        pausebutton->move(controlwidget->width()/2-x/2-pausebutton->width()/2+x,controlwidget->height()/2-pausebutton->height()/2);
    //pausebutton->setIcon(pausebutton->style()->standardIcon(QStyle::SP_MediaPlay));
#ifdef Q_Device_Mobile
    forwardbutton->move(pausebutton->x()+pausebutton->width()+5,pausebutton->y());
    backwardbutton->move(pausebutton->x()-backwardbutton->width()-5,pausebutton->y());
#else
    forwardbutton->move(pausebutton->x()+pausebutton->width()+10,pausebutton->y());
    backwardbutton->move(pausebutton->x()-backwardbutton->width()-10,pausebutton->y());
#endif

    aboutbutton->resize(35,35);
    fullscreenbutton->resize(aboutbutton->size());
    volumebutton->resize(aboutbutton->size());
    modebutton->resize(aboutbutton->size());
    aboutbutton->move(controlwidget->width()-aboutbutton->width()-5,controlwidget->height()/2-aboutbutton->height()/2);
    fullscreenbutton->move(aboutbutton->x()-fullscreenbutton->width()-5,aboutbutton->y());
    volumebutton->move(fullscreenbutton->x()-volumebutton->width()-5,aboutbutton->y());
    modebutton->move(volumebutton->x()-modebutton->width()-5,aboutbutton->y());

    if(modebutton->x() <= forwardbutton->x()+forwardbutton->width()+5)
    {
        int delta = forwardbutton->x()+forwardbutton->width()+5-modebutton->x();
        backwardbutton->move(backwardbutton->x()-delta,backwardbutton->y());
        pausebutton->move(pausebutton->x()-delta,pausebutton->y());
        forwardbutton->move(forwardbutton->x()-delta,forwardbutton->y());
        if(backwardbutton->x() <= namelabel->x()+namelabel->width()+10)
        {
            delta = namelabel->width()+namelabel->x()+10-backwardbutton->x();
            namelabel->resize(namelabel->width()-delta,namelabel->height());
        }
    }
    if(namelabel->x()+namelabel->width() > controlwidget->width()/5*2  || namelabel->width() <= namelabel->height()/2)
        namelabel->hide();
    else if(!iconlabel->isHidden())
        namelabel->show();

    if(backwardbutton->x() < iconlabel->x()+iconlabel->width()+5)
    {
        iconlabel->resize(iconlabel->width()-(iconlabel->x()+iconlabel->width()+5-backwardbutton->x()),iconlabel->height());
    }

    volumedlg->hide();
    volumedlg->setWindowFlags(Qt::FramelessWindowHint);
    volumeslider->setRange(0,100);
    volumeslider->setOrientation(Qt::Horizontal);
    volumeslider->setTracking(true);
    volumeslider->setValue(playerwidget->volume());
    volumeslider->move(10,10);
    volumeslider->resize(80,20);
    volumelabel->move(volumeslider->x()+volumeslider->width(),volumeslider->y());
    volumelabel->resize(50,30);
    volumelabel->setAlignment(Qt::AlignCenter);
    volumelabel->setText(QString::number(playerwidget->volume()));
    volumedlg->resize(volumelabel->x()+volumelabel->width()+10,volumelabel->y()+volumelabel->height()+10);

    QScroller::grabGesture(area->viewport(),QScroller::LeftMouseButtonGesture);
    area->setWidget(widget);
    area->setGeometry(0,0,mediawidget->width(),mediawidget->height());
    area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    widget->resize(mediawidget->size());
    widget->move(0,0);

    aboutdialog->hide();
    aboutdialog->setWindowTitle("媒体信息");
    filenamelabel1->setAlignment(Qt::AlignCenter);
    filenamelabel2->setAlignment(filenamelabel1->alignment());
    filepathlabel1->setAlignment(filenamelabel1->alignment());
    filepathlabel2->setAlignment(filenamelabel1->alignment());
    widthlabel1->setAlignment(filenamelabel1->alignment());
    widthlabel2->setAlignment(filenamelabel1->alignment());
    heightlabel1->setAlignment(filenamelabel1->alignment());
    heightlabel2->setAlignment(filenamelabel1->alignment());
    existlabel1->setAlignment(filenamelabel1->alignment());
    existlabel2->setAlignment(filenamelabel1->alignment());
    readablelabel1->setAlignment(filenamelabel1->alignment());
    readablelabel2->setAlignment(filenamelabel1->alignment());
    durationlabel1->setAlignment(filenamelabel1->alignment());
    durationlabel2->setAlignment(filenamelabel1->alignment());
    filenamelabel1->setText("文件名");
    filepathlabel1->setText("文件路径");
    widthlabel1->setText("帧宽度");
    heightlabel1->setText("帧高度");
    existlabel1->setText("是否存在");
    readablelabel1->setText("是否可读");
    durationlabel1->setText("时长");
    copyaction->setText("复制");
#ifndef Q_OS_ANDROID
    opendiraction->setText("打开文件夹");
#else
    opendiraction->setText("分享");
#endif
    aboutaction->setText("属性");
    stayontopaction->setText("置顶");
    saveframeaction->setText("保存当前帧");
    stayontopaction->setCheckable(true);
    filenamelabel1->resize(50,30);
    filepathlabel1->resize(filenamelabel1->size());
    widthlabel1->resize(filenamelabel1->size());
    heightlabel1->resize(filenamelabel1->size());
    existlabel1->resize(filenamelabel1->size());
    readablelabel1->resize(filenamelabel1->size());
    durationlabel1->resize(filenamelabel1->size());
    singleaction->setText("单次播放");
    randomaction->setText("随机播放");
    repeataction->setText("循环播放");

    oldThemeIsDark = isSystemDarkMode();
    this->loadMediaList();
    //this->setWindowFlag(Qt::MaximizeUsingFullscreenGeometryHint,true);
    this->setAcceptDrops(true);
    if(Windows::isAdmin() && this->acceptDrops())
    {
        Windows::setUACAcceptNativeDrops(this);
    }
    QObjectList list1 = {this,openbutton,controlwidget,iconlabel,namelabel,slider,volumedlg,volumeslider,playerwidget,aboutdialog,filenamelabel2,filepathlabel2,widthlabel2,heightlabel2,durationlabel2};
    for(QObject* object : list1)
    {
        object->installEventFilter(this);
    }
    QWidgetList list2 = {controlwidget,pausebutton,forwardbutton,backwardbutton,modebutton,volumebutton,aboutbutton,fullscreenbutton};
    for(QWidget* w : list2)
    {
        w->setAutoFillBackground(true);
    }
    this->setAttribute(Qt::WA_AcceptTouchEvents, true);
    controlwidget->setAttribute(Qt::WA_AcceptTouchEvents, true);

    QObject::connect(slider,QOverload<int>::of(&QSlider::valueChanged),[=](int value){
        if(!lockslider)
        {
            playerwidget->setPosition(value);
            if(playerwidget->state() == PlayerWidget::State::StoppedState)
                playerwidget->mediaPlayer()->play();
        }
    });
    QObject::connect(volumeslider,QOverload<int>::of(&QSlider::valueChanged),[=](int value){
        if(volumeslider->isEnabled() && value != playerwidget->volume())
        {
            playerwidget->setVolume(value);
            volumelabel->setText(QString::number(value));
            settings->setValue("volume",QString::number(volumeslider->value()));
        }
    });
    QObject::connect(playerwidget,QOverload<int>::of(&PlayerWidget::durationChanged),[=](int duration){
            slider->setRange(0,playerwidget->duration());
    });
    QObject::connect(playerwidget,QOverload<int>::of(&PlayerWidget::positionChanged),[=](int position){
        if(slider->isEnabled())
        {
            lockslider = true;
            if(slider->maximum() != playerwidget->duration())
                slider->setRange(0,playerwidget->duration());
            slider->setValue(position);
            lockslider = false;

            int sec = floor(double(position)/1000);
            int min = floor(double(sec)/60);
            sec = sec - 60 * min;
            QString str = "";
            if(min < 10)
                str = str + "0";
            str = str + QString::number(min) + ":";
            if(sec < 10)
                str = str + "0";
            str = str + QString::number(sec);
            timelabel->setText(str);
        }
        //qDebug() << "setValue" << position;
        //qDebug() << "currentDuration" << playerwidget->mediaPlayer()->duration();
    });
    QObject::connect(playerwidget,QOverload<QVideoFrame>::of(&PlayerWidget::videoFrameChanged),[=](QVideoFrame frame){
        QVideoFrame f(frame);
        if(f.isValid() && playing == false && playerwidget->isLocked() == false)
        {
            iconlabel->setStyleSheet("");
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
            iconlabel->setPixmap(QPixmap::fromImage(f.toImage().scaled(iconlabel->size(),Qt::KeepAspectRatio)));
#else
            QImage image = qt_imageFromVideoFrame(f);
#ifdef Q_OS_WIN
            image = image.mirrored();
#endif
            /*
            f.map(QAbstractVideoBuffer::ReadOnly);
            QImage image = QImage(f.bits(),f.width(),f.height(),f.bytesPerLine(),QVideoFrame::imageFormatFromPixelFormat(f.pixelFormat()));
            //QImage image = QImage::fromData(f.bits(),int(f.mappedBytes()));
            f.unmap();
            */
            if(!image.isNull())
            {
                image = image.scaled(iconlabel->size(),Qt::KeepAspectRatio);
                iconlabel->setPixmap(QPixmap::fromImage(image));
            }
#endif
        }
    });
    QObject::connect(playerwidget,QOverload<bool>::of(&PlayerWidget::hasVideoChanged),[=](){
        if(playerwidget->hasVideo() && !playing)
        {
#if (QT_VERSION > QT_VERSION_CHECK(6,5,0)) && (QT_VERSION < QT_VERSION_CHECK(6,7,0))
            QTimer::singleShot(1000,[=](){
                this->showPlayerWidget();
            });
#else
            this->showPlayerWidget();
#endif
        }
        else if(!playerwidget->hasVideo() && playing)
        {
            this->hidePlayerWidget();
        }
    });
    QObject::connect(playerwidget,QOverload<PlayerWidget::State>::of(&PlayerWidget::stateChanged),[=](){
        if(hasPixmap(iconlabel))
        {
            iconlabel->setStyleSheet("");
        }
        else if(darkmode)
        {
            QColor color = QColor(100,100,100);
            iconlabel->setStyleSheet("background-color:"+color.name());
        }
        else
        {
            iconlabel->setStyleSheet("background-color:white");
        }
        if(playerwidget->state() == PlayerWidget::PlayingState)
        {
            if(darkmode || playing)
            {
                pausebutton->setIcon(QIcon(":/icon/pause_white.png"));
            }
            else
            {
                pausebutton->setIcon(QIcon(":/icon/pause_black.png"));
            }
        }
        else
        {
            if(darkmode || playing)
            {
                pausebutton->setIcon(QIcon(":/icon/play_white.png"));
            }
            else
            {
                pausebutton->setIcon(QIcon(":/icon/play_black.png"));
            }

            if(playerwidget->state() == PlayerWidget::StoppedState)
            {
                if(playmode == Widget::PlayRepeat)
                {
                    if(playerwidget->position() == playerwidget->duration() && playerwidget->duration() > 0)
                    {
                        playerwidget->play();
                    }
                }
                else if(playmode == Widget::PlayRandom)
                {
                    if(playerwidget->position() == playerwidget->duration() && playerwidget->duration() > 0)
                    {
                        if(medialist->allKeys().count() == 0 || medialist->allKeys().count() == 1)
                        {
                            playerwidget->play();
                        }
                        else
                        {
                            bool ret = this->playMedia(medialist->value(QString::number(QRandomGenerator::global()->bounded(1,widgetlist.count()+1))).toString());
                            int i = 0;
                            while(!ret && medialist->contains(QString::number(i)))
                            {
                                ret = this->playMedia(medialist->value(QString::number(i)).toString());
                                i++;
                            }
                        }
                    }
                }
            }
        }
    });
    QObject::connect(openbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
#ifdef Q_OS_ANDROID
        if(!Android::hasStroagePermission())
        {
            int ret = OkCancelBox(this,QMessageBox::NoIcon,"","若要正常使用本程序，需要授予文件的访问权限，否则部分功能无法正常使用","现在不要","请求权限");
            if(ret == 2 || ret == 0)
            {
                Android::requestStroagePermission();
            }
        }
#endif
        if(!settings->contains("filedialog"))
        {
            settings->setValue("filedialog","default");
        }

        QString mode = settings->value("filedialog").toString();
        if(mode != "default" && mode != "qfiledialog" && mode != "myfiledialog")
        {
            mode = "default";
            settings->setValue("filedialog","default");
        }
        if(mode == "default")
        {
#ifdef Q_OS_ANDROID
            mode = "myfiledialog";
#else
            mode = "qfiledialog";
#endif
        }

        QString path = settings->value("openpath").toString();
        if(path == "default" || !QFileInfo(path).isDir())
        {
#ifdef Q_OS_ANDROID
            if(QFileInfo("/sdcard/Music").isDir())
                path = "/sdcard/Music";
            else if(QFileInfo("/sdcard/Download").isDir())
                path = "/sdcard/Download";
            else if(QFileInfo("/sdcard/Movie").isDir())
                path = "/sdcard/Movie";
            else if(QFileInfo("/sdcard/Document").isDir())
                path = "/sdcard/Document";
            else
                path = "/sdcard";
#else
            path = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
#endif

        }

        QString ret = "";
        if(mode == "qfiledialog")
        {
            ret = QFileDialog::getOpenFileName(this,"打开",path);
#ifdef Q_OS_ANDROID
            ret = Android::getRealPathFromUri(ret);
#endif
        }
        else if(mode == "myfiledialog")
        {
            MyFileDialog* dlg = new MyFileDialog();
#ifdef Q_OS_ANDROID
            dlg->fileSystemModel()->registerIcons();
#endif
            ret = dlg->getOpenFileName(this,"打开",path);
        }

        if(QFileInfo(ret).isFile())
        {
            settings->setValue("openpath",QFileInfo(ret).absolutePath());
            this->playMedia(ret);
        }
    });
    QObject::connect(settingbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
#ifdef Q_OS_ANDROID
        if(!Android::hasStroagePermission())
        {
            int ret = OkCancelBox(this,QMessageBox::NoIcon,"","若要正常使用本程序，需要授予文件的访问权限，否则部分功能无法正常使用","现在不要","请求权限");
            if(ret == 2 || ret == 0)
            {
                Android::requestStroagePermission();
            }
        }
#endif
        QString link1 = "https://space.bilibili.com/558616097";
        QString link2 = "https://github.com/Soviet-Ball/MediaPlayer";
        QString name = "Soviet-Ball";
        QDialog* dlg = new QDialog(this);
        SettingWidget* w = new SettingWidget(dlg);
#ifdef Q_Device_Desktop
        dlg->resize(350,300);
#else
        dlg->resize(screensize());
#endif
        int defaultIndex1 = 0;
        int defaultIndex2 = 0;
        int defaultIndex3 = 0;
        QString str = "打开文件夹";
#ifdef Q_OS_ANDROID
        str = "分享";
#endif
        bool defaultIndex4 = true;
        if(settings->value("appTheme").toString() == "light")
            defaultIndex1 = 1;
        else if(settings->value("appTheme").toString() == "dark")
            defaultIndex1 = 2;
        if(!isBool(settings->value("loadGeometry").toString()))
            settings->setValue("loadGeometry","false");
        if(settings->value("filedialog").toString() == "qfiledialog")
            defaultIndex2 = 1;
        else if(settings->value("filedialog").toString() == "myfiledialog")
            defaultIndex2 = 2;
        if(settings->value("transformationMode").toString() == "smooth")
            defaultIndex3 = 1;
        else if(settings->value("transformationMode").toString() != "fast")
            settings->setValue("transformationMode","fast");
        if(settings->value("showSmoothly").toString() == "false")
            defaultIndex4 = false;
        else if(settings->value("showSmoothly").toString() != "true")
            settings->setValue("showSmoothly","true");


        w->resize(dlg->width(),dlg->height());
        w->setItemHeight(40);
        w->addItem("application",qApp->applicationName(),SettingWidget::PushButton,"Github",0,getApplicationIcon());
        w->addItem("me",name+" 制作",SettingWidget::PushButton,"Bilibili",0,QIcon(":/icon/face.jpg"));
        w->addItem("appTheme","应用主题",SettingWidget::ComboBox,QStringList({"系统","浅色","深色"}),defaultIndex1);
        w->addItem("filedialog","文件对话框",SettingWidget::ComboBox,QStringList({"默认","QFileDialog","MyFileDialog"}),defaultIndex2);
        w->addItem("transformationMode","处理帧模式",SettingWidget::ComboBox,QStringList({"快速","平滑"}),defaultIndex3);
        w->addItem("showSmoothly","以动画弹出播放页",SettingWidget::RadioButton,QVariant(),defaultIndex4);
        w->addItem("loadGeometry","保存窗口位置",SettingWidget::RadioButton,QVariant(),settings->value("loadGeometry").toBool());
        w->addItem("settings","配置文件",SettingWidget::ComboBox,QStringList({"操作",str,"重置","导入","导出"}),0);
        w->addItem("list","媒体列表",SettingWidget::ComboBox,QStringList({"操作",str,"重置","导入","导出"}),0);

        std::function<void(QString s)> func = [=](QString filePath){
            settings->sync();
            medialist->sync();
#ifdef Q_OS_WIN
            ShellExecuteW(NULL, L"open", L"explorer", QString("/select, \"%1\"").arg(filePath.replace("/","\\")).toStdWString().c_str(), NULL, SW_SHOW);
#else
#ifdef Q_OS_ANDROID
            Android::shareFile(filePath);
#else
            QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(filePath).absolutePath()));
#endif
#endif
        };

        QObject::connect(w,QOverload<int,QString>::of(&SettingWidget::pushButtonClicked),[=](int index,QString key){
            if(key == "me")
            {
                QDesktopServices::openUrl(QUrl(link1));
            }
            else if(key == "application")
            {
                //QMessageBox::information(this,"提示","密码: "+QString::number(password),"确定");
                QDesktopServices::openUrl(QUrl(link2));
            }
        });
        QObject::connect(w,QOverload<int,QString,bool>::of(&SettingWidget::radioButtonClicked),[=](int index,QString key,bool check){
            if(key == "showSmoothly")
            {
                settings->setValue("showSmoothly",toString(check));
            }
            else if(key == "loadGeometry")
            {
                settings->setValue("loadGeometry",toString(check));
            }
        });
        QObject::connect(w,QOverload<int,QString,int,QString>::of(&SettingWidget::comboBoxChanged),[=](int index,QString key,int currentIndex,QString currentText){
            if(key == "appTheme")
            {
                if(currentIndex == 0)
                    settings->setValue("appTheme","system");
                else if(currentIndex == 1)
                    settings->setValue("appTheme","light");
                else
                    settings->setValue("appTheme","dark");
                this->checkDarkMode();
            }
            else if(key == "filedialog")
            {
                if(currentText == "QFileDialog")
                    settings->setValue("filedialog","qfiledialog");
                else if(currentText == "MyFileDialog")


                    settings->setValue("filedialog","myfiledialog");
                else
                    settings->setValue("filedialog","dafault");
            }
            else if(key == "transformationMode")
            {
                if(currentIndex == 0)
                    settings->setValue("transformationMode","fast");
                else
                    settings->setValue("transformationMode","smooth");
            }
            else if(key == "settings")
            {
                if(currentIndex == 0)
                    return;
                w->comboBox(key)->setCurrentIndex(0);
                if(currentText == str)
                    func(settingpath);
                else if(currentText == "重置")
                {
                    this->initSettings(true);
                    this->readSettings();
                    dlg->close();
                    settingbutton->click();
                }
                else if(currentText == "导出")
                {
                    QString dirpath;
                    QString defpath;
                    QString filepath;
                    QString value = settings->value("filedialog").toString();
#ifdef Q_OS_ANDROID
                    defpath = "/sdcard/Download";
                    if(!QFileInfo(defpath).isDir() || !hasPathPermission(defpath,QIODevice::WriteOnly))
                        defpath = "/sdcard/Documents";
                    if(!QFileInfo(defpath).isDir() || !hasPathPermission(defpath,QIODevice::WriteOnly))
                        defpath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
#else
                    defpath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
#endif

                    if(value != "myfiledialog" && value != "qfiledialog")
                    {
#ifdef Q_OS_ANDROID
                        value = "myfiledialog";
        #else
                        value = "qfiledialog";
#endif
                    }
                    if(value == "qfiledialog")
                    {
                        dirpath = QFileDialog::getExistingDirectory(this,"选择导出文件夹",defpath);
                    }
                    else
                    {
                        MyFileDialog* dlg = new MyFileDialog();
#ifdef Q_OS_ANDROID
                        dlg->fileSystemModel()->registerIcons();
#endif
                        dirpath = dlg->getExistingDirectory(this,"选择导出文件夹",defpath);
                    }
                    if(dirpath.isEmpty())
                        return;
                    filepath = dirpath + "/settings";
                    if(QFileInfo(filepath+".ini").isFile())
                    {
                        int i = 1;
                        filepath = filepath + "_" + QString::number(i);
                        while(QFileInfo(filepath+".ini").isFile())
                        {
                            i++;
                            while(!filepath.endsWith("_"))
                                filepath.chop(1);
                            filepath += QString::number(i);
                        }
                    }
                    filepath = filepath + ".ini";
                    settings->sync();
                    QByteArray content = readfile(settingpath);
                    if(!writefile(content,filepath))
                    {
                        emit errorChanged("导出设置到"+filepath+"失败");
                    }

                }
                else if(currentText == "导入")
                {
                    QString defpath;
                    QString filepath;
                    QString value = settings->value("filedialog").toString();
#ifdef Q_OS_ANDROID
                    defpath = "/sdcard/Download";
                    if(!QFileInfo(defpath).isDir() || !hasPathPermission(defpath,QIODevice::WriteOnly))
                        defpath = "/sdcard/Documents";
                    if(!QFileInfo(defpath).isDir() || !hasPathPermission(defpath,QIODevice::WriteOnly))
                        defpath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
#else
                    defpath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
#endif

                    if(value != "myfiledialog" && value != "qfiledialog")
                    {
#ifdef Q_OS_ANDROID
                        value = "myfiledialog";
        #else
                        value = "qfiledialog";
#endif
                    }
                    if(value == "qfiledialog")
                    {
                        filepath = QFileDialog::getOpenFileName(this,"选择导入文件",defpath);
                    }
                    else
                    {
                        MyFileDialog* dlg = new MyFileDialog();
#ifdef Q_OS_ANDROID
                        dlg->fileSystemModel()->registerIcons();
#endif
                        filepath = dlg->getOpenFileName(this,"选择导入文件",defpath);
                    }
                    if(filepath.isEmpty())
                        return;
                    if(!QFileInfo(filepath).isFile() || !hasFilePermission(filepath,QIODevice::ReadOnly))
                    {
                        emit errorChanged("访问文件"+filepath+"失败");
                        return;
                    }
                    settings = nullptr;
                    if(QFileInfo(settingpath).isFile() && !QFile::remove(settingpath))
                    {
                        this->initSettings();
                        emit errorChanged("删除"+settingpath+"失败");
                        return;
                    }
                    QByteArray ba = readfile(filepath);
                    writefile(ba,settingpath);
                    this->initSettings();
                    this->readSettings();
                    dlg->close();
                    settingbutton->click();
                }
            }
            else if(key == "list")
            {
                if(currentIndex == 0)
                    return;
                w->comboBox(key)->setCurrentIndex(0);
                if(currentText == str)
                    func(listpath);
                else if(currentText == "重置")
                {
                    playerwidget->clear();
                    namelabel->clear();
                    iconlabel->clear();
                    timelabel->clear();
                    this->checkDarkMode();
                    slider->setEnabled(false);
                    this->initList(true);
                    this->loadMediaList();
                    dlg->close();
                    settingbutton->click();
                }
                else if(currentText == "导出")
                {
                    QString dirpath;
                    QString defpath;
                    QString filepath;
                    QString value = settings->value("filedialog").toString();
#ifdef Q_OS_ANDROID
                    defpath = "/sdcard/Download";
                    if(!QFileInfo(defpath).isDir() || !hasPathPermission(defpath,QIODevice::WriteOnly))
                        defpath = "/sdcard/Documents";
                    if(!QFileInfo(defpath).isDir() || !hasPathPermission(defpath,QIODevice::WriteOnly))
                        defpath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
#else
                    defpath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
#endif

                    if(value != "myfiledialog" && value != "qfiledialog")
                    {
#ifdef Q_OS_ANDROID
                        value = "myfiledialog";
        #else
                        value = "qfiledialog";
#endif
                    }
                    if(value == "qfiledialog")
                    {
                        dirpath = QFileDialog::getExistingDirectory(this,"选择导出文件夹",defpath);
                    }
                    else
                    {
                        MyFileDialog* dlg = new MyFileDialog();
#ifdef Q_OS_ANDROID
                        dlg->fileSystemModel()->registerIcons();
#endif
                        dirpath = dlg->getExistingDirectory(this,"选择导出文件夹",defpath);
                    }
                    if(dirpath.isEmpty())
                        return;
                    filepath = dirpath + "/list";
                    if(QFileInfo(filepath+".ini").isFile())
                    {
                        int i = 1;
                        filepath = filepath + "_" + QString::number(i);
                        while(QFileInfo(filepath+".ini").isFile())
                        {
                            i++;
                            while(!filepath.endsWith("_"))
                                filepath.chop(1);
                            filepath += QString::number(i);
                        }
                    }
                    filepath = filepath + ".ini";
                    medialist->sync();
                    QByteArray content = readfile(listpath);
                    if(!writefile(content,filepath))
                    {
                        emit errorChanged("导出设置到"+filepath+"失败");
                    }
                }
                else if(currentText == "导入")
                {
                    QString defpath;
                    QString filepath;
                    QString value = settings->value("filedialog").toString();
#ifdef Q_OS_ANDROID
                    defpath = "/sdcard/Download";
                    if(!QFileInfo(defpath).isDir() || !hasPathPermission(defpath,QIODevice::WriteOnly))
                        defpath = "/sdcard/Documents";
                    if(!QFileInfo(defpath).isDir() || !hasPathPermission(defpath,QIODevice::WriteOnly))
                        defpath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
#else
                    defpath = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
#endif

                    if(value != "myfiledialog" && value != "qfiledialog")
                    {
#ifdef Q_OS_ANDROID
                        value = "myfiledialog";
        #else
                        value = "qfiledialog";
#endif
                    }
                    if(value == "qfiledialog")
                    {
                        filepath = QFileDialog::getOpenFileName(this,"选择导入文件",defpath);
                    }
                    else
                    {
                        MyFileDialog* dlg = new MyFileDialog();
#ifdef Q_OS_ANDROID
                        dlg->fileSystemModel()->registerIcons();
#endif
                        filepath = dlg->getOpenFileName(this,"选择导入文件",defpath);
                    }
                    if(filepath.isEmpty())
                        return;
                    if(!QFileInfo(filepath).isFile() || !hasFilePermission(filepath,QIODevice::ReadOnly))
                    {
                        emit errorChanged("访问文件"+filepath+"失败");
                        return;
                    }
                    medialist = nullptr;
                    if(QFileInfo(listpath).isFile() && !QFile::remove(listpath))
                    {
                        emit errorChanged("删除"+listpath+"失败");
                        this->initList();
                        return;
                    }
                    QByteArray ba = readfile(filepath);
                    writefile(ba,listpath);
                    this->initList();
                    this->loadMediaList();
                    dlg->close();
                    settingbutton->click();
                }
            }
        });
        if(stayontopaction->isChecked())
            staysOnTop(dlg);
        fixSize(dlg);
        dlg->setFocus();
        dlg->exec();
        settings->sync();
    });
    QObject::connect(pausebutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        if(playerwidget->state() == PlayerWidget::State::PlayingState)
        {
            playerwidget->pause();
        }
        else
        {
            playerwidget->play();
        }
    });
    QObject::connect(forwardbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        if(slider->isEnabled())
            slider->setValue(slider->value()+1000*10);
    });
    QObject::connect(backwardbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        if(slider->isEnabled())
            slider->setValue(slider->value()-1000*10);
    });
    QObject::connect(fullscreenbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
#if (QT_VERSION > QT_VERSION_CHECK(6,5,0)) && (QT_VERSION < QT_VERSION_CHECK(6,7,0))
        playerwidget->lock();
        if(playerwidget->state()==PlayerWidget::PlayingState)
        {
            playerwidget->pause();
            paused = true;
        }
#endif

        if(this->isFullScreen())
        {
            if(ismax == true)
                this->showMaximized();
            else
                this->showNormal();
#if (QT_VERSION > QT_VERSION_CHECK(6,5,0)) && (QT_VERSION < QT_VERSION_CHECK(6,7,0))
            while(this->isFullScreen())
            {
                sleep(100);
            }
#endif
        }
        else
        {
            ismax = this->isMaximized();
            this->showFullScreen();
#if (QT_VERSION > QT_VERSION_CHECK(6,5,0)) && (QT_VERSION < QT_VERSION_CHECK(6,7,0))
            while(!this->isFullScreen())
            {
                sleep(100);
            }
#endif
        }

#if (QT_VERSION > QT_VERSION_CHECK(6,5,0)) && (QT_VERSION < QT_VERSION_CHECK(6,7,0))
            playerwidget->unlock();
            if(paused == true)
            {
                paused == false;
                playerwidget->play();
            }
#endif
    });
    QObject::connect(volumebutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        if(volumedlg->isHidden())
        {
            volumedlg->move(this->x()+controlwidget->x()+volumebutton->x()+volumebutton->width()/2-volumedlg->width()/2,this->y()+controlwidget->y()+volumebutton->y()-volumedlg->height());
            if(volumedlg->x()+volumedlg->width() > screenwidth())
            {
                volumedlg->move(volumedlg->x()-(volumedlg->x()+volumedlg->width()-screenwidth()),volumedlg->y());
            }
            volumedlg->show();
            volumedlg->raise();
            volumedlg->activateWindow();
        }
        else
        {
            volumedlg->hide();
        }
    });
    QObject::connect(aboutbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        QMenu* m = new QMenu(this);
        QPoint pos = controlwidget->mapToGlobal(aboutbutton->pos());
        QObject::connect(opendiraction,QOverload<bool>::of(&QAction::triggered),[=](){
            if(QFileInfo(playerwidget->filePath()).isFile())
            {
#ifdef Q_OS_WIN
    ShellExecuteW(NULL, L"open", L"explorer", QString("/select, \"%1\"").arg(playerwidget->filePath().replace("/","\\")).toStdWString().c_str(), NULL, SW_SHOW);
#else
#ifndef Q_OS_ANDROID
    QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(playerwidget->filePath()).absolutePath()));
#else
    Android::shareFile(playerwidget->filePath());
#endif
#endif
            }
        });
        m->addActions(QList<QAction*>() << aboutaction << opendiraction << stayontopaction << saveframeaction);
        saveframeaction->setEnabled(playerwidget->videoFrame().isValid());
        opendiraction->setEnabled(QFileInfo(playerwidget->filePath()).isFile());
        aboutaction->setEnabled(opendiraction->isEnabled());
        m->show();
        m->move(pos.x()+aboutbutton->width()-m->width(),pos.y()-m->height()-5);
        m->hide();
        m->exec();
        saveframeaction->setEnabled(true);
        opendiraction->setEnabled(true);
        aboutaction->setEnabled(true);
        opendiraction->disconnect();
    });
    QObject::connect(aboutaction,QOverload<bool>::of(&QAction::triggered),[=](){
        if(playerwidget->filePath() != "")
        {
#ifndef Q_OS_ANDROID
            if(!aboutdialog->isHidden())
                aboutdialog->close();
#endif
            this->showAboutDialog();
        }
    });
    QObject::connect(stayontopaction,QOverload<bool>::of(&QAction::triggered),[=](bool check){
        if(stayontopaction->isChecked())
        {
            staysOnTop(this);
        }
        else
        {
            staysNotOnTop(this);
        }
        settings->setValue("staysOnTop",toString(stayontopaction->isChecked()));
    });
    QObject::connect(saveframeaction,QOverload<bool>::of(&QAction::triggered),[=](){
        QVideoFrame f = playerwidget->videoFrame();
        if(f.isValid())
        {
            QImage image = frameToImage(f);
            if(!image.isNull())
            {
                if(!settings->contains("filedialog"))
                {
                    settings->setValue("filedialog","default");
                }

                QString mode = settings->value("filedialog").toString();
                if(mode != "default" && mode != "qfiledialog" && mode != "myfiledialog")
                {
                    mode = "default";
                    settings->setValue("filedialog","default");
                }
                if(mode == "default")
                {
        #ifdef Q_OS_ANDROID
                    mode = "myfiledialog";
        #else
                    mode = "qfiledialog";
        #endif
                }

                QString path = settings->value("savepath").toString();
                if(path == "default" || !QFileInfo(path).isDir())
                {
        #ifdef Q_OS_ANDROID
                    if(QFileInfo("/sdcard/Download").isDir())
                        path = "/sdcard/Download";
                    else if(QFileInfo("/sdcard/Picture").isDir())
                        path = "/sdcard/Picture";
                    else if(QFileInfo("/sdcard/Document").isDir())
                        path = "/sdcard/Document";
                    else
                        path = "/sdcard";
        #else
                    path = QStandardPaths::writableLocation(QStandardPaths::DownloadLocation);
        #endif
                }

                QString ret = "";
                if(mode == "qfiledialog")
                {
                    QStringList list = toStringList(QImageWriter::supportedImageFormats());
                    QString filter;
                    int pngIndex = list.indexOf("png");
                    if (pngIndex != -1)
                    {
                        list.move(pngIndex, 0);
                    }
                    for(QString s : list)
                    {
                        filter = filter + "*." + s + ";;";
                    }
                    filter.chop(1);
                    QFileDialog* dlg = new QFileDialog(this);
                    ret = dlg->getSaveFileName(this,"保存",path+"/frame_"+QDateTime::currentDateTime().toString("yyyyMMddHHmmss"),filter);
        #ifdef Q_OS_ANDROID
                    ret = Android::getRealPathFromUri(ret);
        #endif
                }
                else if(mode == "myfiledialog")
                {
                    MyFileDialog* dlg = new MyFileDialog();
#ifdef Q_OS_ANDROID
                    dlg->fileSystemModel()->registerIcons();
#endif
                    ret = dlg->getExistingDirectory(this,"打开",path);
                }

                if(QFileInfo(ret).isDir())
                {
                    ret = ret + "/frame_" + QDateTime::currentDateTime().toString("yyyyMMddHHmmss") + ".png";
                }
                if(hasFilePermission(ret,QIODevice::WriteOnly))
                {
                    image.save(ret);
                    ret = QFileInfo(ret).absoluteDir().path();
                    settings->setValue("savepath",ret);
                }
                else if(!ret.isEmpty())
                {
                    emit errorChanged("保存"+ret+"失败");
                }
            }
        }
    });
    QObject::connect(modebutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        QPoint pos = controlwidget->mapToGlobal(modebutton->pos());
        QMenu* m = new QMenu(this);
        m->addActions(QList<QAction*>() << singleaction << repeataction << randomaction);
        m->show();
        m->exec(QPoint(pos.x()+modebutton->width()/2-m->width()/2,pos.y()-m->height()-5));
    });
    QObject::connect(singleaction,QOverload<bool>::of(&QAction::triggered),[=](){
        if(darkmode || playing)
        {
            modebutton->setIcon(QIcon(":/icon/single_white.png"));
        }
        else
        {
            modebutton->setIcon(QIcon(":/icon/single_black.png"));
        }
        playmode = PlaySingle;
        settings->setValue("mode","single");
    });
    QObject::connect(repeataction,QOverload<bool>::of(&QAction::triggered),[=](){
        if(darkmode || playing)
        {
            modebutton->setIcon(QIcon(":/icon/repeat_white.png"));
        }
        else
        {
            modebutton->setIcon(QIcon(":/icon/repeat_black.png"));
        }
        playmode = PlayRepeat;
        settings->setValue("mode","repeat");
    });
    QObject::connect(randomaction,QOverload<bool>::of(&QAction::triggered),[=](){
        if(darkmode || playing)
        {
            modebutton->setIcon(QIcon(":/icon/random_white.png"));
        }
        else
        {
            modebutton->setIcon(QIcon(":/icon/random_black.png"));
        }
        playmode = PlayRandom;
        settings->setValue("mode","random");
    });
    QObject::connect(this,QOverload<bool>::of(&Widget::systemThemeChanged),[=](){
        this->checkDarkMode();
    });
    QTimer::singleShot(0,[=](){
        taskbar->setState(MyTaskBarProgress::NoProgress);
        taskbar->setRange(0,100);
        taskbar->setValue(100);
        setDarkTitleBar(this->effectiveWinId(),darkmode);
        this->readSettings();
        if(QApplication::arguments().count() > 1)
        {
            //QMessageBox::critical(this,"",QApplication::arguments().join(";")+toString(QFileInfo(QApplication::arguments().at(1)).isFile()));
            int i = 1;
            while(i < QApplication::arguments().count() && !QFileInfo(QApplication::arguments().at(i)).isFile())
            {
                i++;
            }
            if(QFileInfo(QApplication::arguments().at(i)).isFile())
                this->playMedia(QApplication::arguments().at(i));
        }
//        auto mb = QMessageBox(QMessageBox::Information,"title","text",QMessageBox::NoButton);
//        WId w = mb.winId();
//        mb.addButton("确定",QMessageBox::AcceptRole);
//        QTimer::singleShot(2000,[=](){
//            QWidget* widget = QWidget::find(w);
//            if(widget)
//                widget->hide();
//        });
//        mb.exec();
    });
#ifdef Q_OS_ANDROID
    if(!Android::registerJNINativeMethod("onConfigurationChangedmirror","(Landroid/content/res/Configuration;)V",(void*)androidConfigurationChangedSender))
    {
        QString msg;
        msg = msg + "注册native方法失败" + "\n";
        msg = msg + "Activity 名称: " + javaPackage + "\n";
        msg = msg + "方法名称: " + "onConfigurationChangedmirror" + "\n";
        msg = msg + "参数: " + "(Landroid/content/res/Configuration;)V" + "\n";
        msg = msg + "接收函数: " + toAddress((void*)androidConfigurationChangedSender);
        emit errorChanged(msg);
    }
#endif
}
Widget::~Widget()
{
}
void Widget::refreshUI()
{
    mainwidget->resize(this->size());
    openbutton->resize(mainwidget->width()*0.15,mainwidget->height()*0.1);
    settingbutton->resize(openbutton->size());
    settingbutton->move(openbutton->x()+openbutton->width()+5,openbutton->y());
    playerwidget->resize(this->size());
    controlwidget->resize(this->width(),controlwidget->height());
    controlwidget->move(0,this->height()-controlwidget->height());

    iconlabel->resize(controlwidget->height()-20,controlwidget->height()-20);
    iconlabel->move(10,10);
    namelabel->resize(iconlabel->width()*1.5,iconlabel->height());
    namelabel->move(iconlabel->x()+iconlabel->width(),iconlabel->y());
    if(namelabel->x()+namelabel->width() > controlwidget->width()/5*2 || namelabel->width() <= namelabel->height()/2)
        namelabel->hide();
    else if(!iconlabel->isHidden())
        namelabel->show();
    timelabel->resize(60,30);
    timelabel->move(controlwidget->x()+controlwidget->width()-timelabel->width()-10,controlwidget->y()-timelabel->height());
    slider->resize(controlwidget->width()-30-timelabel->width(),30);
    slider->move(controlwidget->x()+10,timelabel->y());

    mediawidget->move(openbutton->x(),openbutton->y()+openbutton->height()+10);
    mediawidget->resize(mainwidget->width()-2*mediawidget->x(),slider->y()-openbutton->height()-openbutton->y()-20);

    int x;
    if(iconlabel->isHidden())
        x = 0;
    else if(namelabel->isHidden())
        x = iconlabel->x()+iconlabel->width();
    else
        x = namelabel->x()+namelabel->width();
    if(controlwidget->width()/2-namelabel->x()-namelabel->width()-pausebutton->width()/2-backwardbutton->width()-10 >= 10)
        pausebutton->move(controlwidget->width()/2-pausebutton->width()/2,controlwidget->height()/2-pausebutton->height()/2);
    else
        pausebutton->move(controlwidget->width()/2-x/2-pausebutton->width()/2+x,controlwidget->height()/2-pausebutton->height()/2);
    forwardbutton->resize(pausebutton->size());
    backwardbutton->resize(pausebutton->size());
#ifdef Q_Device_Mobile
    forwardbutton->move(pausebutton->x()+pausebutton->width()+5,pausebutton->y());
    backwardbutton->move(pausebutton->x()-backwardbutton->width()-5,pausebutton->y());
#else
    forwardbutton->move(pausebutton->x()+pausebutton->width()+10,pausebutton->y());
    backwardbutton->move(pausebutton->x()-backwardbutton->width()-10,pausebutton->y());
#endif

    aboutbutton->move(controlwidget->width()-aboutbutton->width()-5,controlwidget->height()/2-aboutbutton->height()/2);
    fullscreenbutton->move(aboutbutton->x()-fullscreenbutton->width()-5,aboutbutton->y());
    volumebutton->move(fullscreenbutton->x()-volumebutton->width()-5,aboutbutton->y());
    modebutton->move(volumebutton->x()-modebutton->width()-5,aboutbutton->y());

    if(modebutton->x() <= forwardbutton->x()+forwardbutton->width()+5)
    {
        int delta = forwardbutton->x()+forwardbutton->width()+5-modebutton->x();
        backwardbutton->move(backwardbutton->x()-delta,backwardbutton->y());
        pausebutton->move(pausebutton->x()-delta,pausebutton->y());
        forwardbutton->move(forwardbutton->x()-delta,forwardbutton->y());
        if(backwardbutton->x() <= namelabel->x()+namelabel->width()+10)
        {
            delta = namelabel->width()+namelabel->x()+10-backwardbutton->x();
            namelabel->resize(namelabel->width()-delta,namelabel->height());
        }
    }
    if(namelabel->x()+namelabel->width() > controlwidget->width()/5*2  || namelabel->width() <= namelabel->height()/2)
        namelabel->hide();
    else if(!iconlabel->isHidden())
        namelabel->show();

    if(backwardbutton->x() < iconlabel->x()+iconlabel->width()+5)
    {
        iconlabel->resize(iconlabel->width()-(iconlabel->x()+iconlabel->width()+5-backwardbutton->x()),iconlabel->height());
    }

    area->setGeometry(0,0,mediawidget->width(),mediawidget->height());
    //int h = widget->height();
    widget->resize(mediawidget->size());
    //widget->resize(widget->width(),h);
    widget->move(0,0);
    int i = 0;
    while(i < widgetlist.count())
    {
        MediaWidget* w = qobject_cast<MediaWidget*>(widgetlist.at(i));
        w->resize(mediawidget->width()-15,w->height());
        widget->resize(w->width(),w->y()+w->height());
        i++;
    }
}
bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonRelease)
    {
        if(!volumedlg->isHidden() && watched != volumedlg && watched != volumeslider)
            volumedlg->hide();
    }

    if(watched == this)
    {
        if(event->type() == QEvent::Resize)
        {
            this->refreshUI();
            if(!volumedlg->isHidden())
                volumedlg->close();
            if(!aboutdialog->isHidden())
                aboutdialog->resize(this->width()-20,300);
                //aboutdialog->move(this->x()+this->width()/2-aboutdialog->width()/2,this->y()+this->height()/2-aboutdialog->height()/2);
        }
        else if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if(keyEvent->key() == Qt::Key_Back || keyEvent->key() == Qt::Key_Escape)
            {
                if(!aboutdialog->isHidden())
                {
                    return false;
                }
                else if(this->isFullScreen())
                {
                    fullscreenbutton->click();
                }
                else if(playing)
                {
                    return false;
                    //this->hidePlayerWidget();
                    //this->clearFocus();
                }
                else
                {
                    playerwidget->stop();
                    this->close();
                    QApplication::exit();
                }
            }
            return true;
        }
        else if(event->type() == QEvent::KeyRelease)
        {
            if(playing)
            {
                this->hidePlayerWidget();
                this->clearFocus();
                return true;
            }
        }
        else if(event->type() == QEvent::Close)
        {
            if(!volumedlg->isHidden())
                volumedlg->close();
            settings->setValue("x",QString::number(this->x()));
            settings->setValue("y",QString::number(this->y()));
            if(this->isMaximized() || this->isFullScreen())
            {
                settings->setValue("width",QString::number(-1));
                settings->setValue("height",QString::number(-1));
            }
            else
            {
                settings->setValue("width",QString::number(this->width()));
                settings->setValue("height",QString::number(this->height()));
            }
        }
        else if(event->type() == QEvent::Move)
        {
            if(!volumedlg->isHidden())
                volumedlg->close();
        }
        else if(event->type() == QEvent::ThemeChange)
        {
            if(oldThemeIsDark != isSystemDarkMode())
            {
                oldThemeIsDark = !oldThemeIsDark;
                emit systemThemeChanged(oldThemeIsDark);
            }
        }
        else if(event->type() == QEvent::DragEnter)
        {
            QDragEnterEvent* dragEnterEvent = static_cast<QDragEnterEvent*>(event);
            dragEnterEvent->accept();
        }
        else if(event->type() == QEvent::Drop)
        {
            QDropEvent* dropEvent = static_cast<QDropEvent*>(event);
            if(!dropEvent->mimeData()->urls().isEmpty() && dropEvent->mimeData()->hasFormat("text/uri-list"))
            {
                this->playMedia(dropEvent->mimeData()->urls().first().toLocalFile());
            }
            dropEvent->accept();
        }
    }
    else if(watched == namelabel || watched == iconlabel)
    {
        if(event->type() == QEvent::MouseButtonRelease)
        {
            QLabel* label = qobject_cast<QLabel*>(watched);
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if(label->rect().contains(mouseEvent->pos()) && playerwidget->filePath() != "")
            {
                this->showPlayerWidget();
            }
        }
    }
    else if(qobject_cast<QSlider*>(watched) != nullptr)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QSlider* s = qobject_cast<QSlider*>(watched);
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if(s->isEnabled() && mouseEvent->button() != Qt::RightButton)
            {
                s->setValue(s->minimum()+float(mouseEvent->x())/float(s->width())*float(s->maximum()-s->minimum()));
                if(watched == slider)
                {
                    if(playerwidget->state() == PlayerWidget::PlayingState)
                    {
                        paused = true;
                        playerwidget->pause();
                    }
                    playerwidget->setVolume(0);
#if (QT_VERSION > QT_VERSION_CHECK(6,5,0)) && (QT_VERSION < QT_VERSION_CHECK(6,7,0))
                    playerwidget->lock();
#endif
                }
            }
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if(watched == slider && mouseEvent->button() != Qt::RightButton)
            {
                if(paused == true)
                {
                    paused = false;
                    playerwidget->mediaPlayer()->play();
                }
                playerwidget->setVolume(volumeslider->value());
#if (QT_VERSION > QT_VERSION_CHECK(6,5,0)) && (QT_VERSION < QT_VERSION_CHECK(6,7,0))
                sleep(500);
                playerwidget->unlock();
#endif
            }
        }
        else if(event->type() == QEvent::FocusIn)
        {
//            if(watched == slider)
//                pausebutton->setFocus();
        }
    }
    else if(watched == controlwidget)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            QPoint point = mouseEvent->pos();
#ifdef Q_Device_Mobile
            this->setMouseTracking(true);
            controlwidget->setMouseTracking(true);
#endif
            startpoint = point;
        }
        else if(event->type() == QEvent::MouseMove)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            QPoint point = mouseEvent->pos();
            if(playing == false && startpoint != QPoint(-1,-1) && !controlwidget->rect().contains(point) && point.y()-startpoint.y() <= -100 && playerwidget->filePath() != "")
            {
                startpoint = QPoint(-1,-1);
                this->showPlayerWidget();
            }
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            QPoint point = mouseEvent->pos();
#ifdef Q_Device_Mobile
            this->setMouseTracking(false);
            controlwidget->setMouseTracking(false);
#endif
            startpoint = QPoint(-1,-1);
            pausebutton->setFocus();
        }
        else if(event->type() == QEvent::MouseButtonDblClick)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(!playing && mouseEvent->button() == Qt::LeftButton && playerwidget->filePath() != "")
                this->showPlayerWidget();
        }
    }
    else if(watched == playerwidget)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            QPoint point = mouseEvent->pos();
#ifdef Q_Device_Mobile
            playerwidget->setMouseTracking(true);
#endif
            startpoint = point;
            starttime = QTime::currentTime();
        }
        else if(event->type() == QEvent::MouseMove)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            QPoint point = mouseEvent->pos();
            if(!this->isHidden() && startpoint != QPoint(-1,-1) && point.y()-startpoint.y() >= 100)
            {
                startpoint = QPoint(-1,-1);
                this->hidePlayerWidget();
            }
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            QPoint point = mouseEvent->pos();
            int interval = -1;
            if(starttime.isValid())
            {
                interval = starttime.msecsTo(QTime::currentTime());
            }
#ifdef Q_Device_Mobile
            this->setMouseTracking(false);
#endif
            if(point == startpoint && interval <= 500 && mouseEvent->button() == Qt::LeftButton)
            {
                if(controlwidget->isHidden())
                {
                    controlwidget->show();
                    timelabel->show();
                    slider->show();
                    //slider->setFocus();
                    pausebutton->setFocus();
                }
                else
                {
                    controlwidget->hide();
                    timelabel->hide();
                    slider->hide();
                    playerwidget->setFocus();
                }
            }
            startpoint = QPoint(-1,-1);
            starttime = QTime();
        }
        else if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if(keyEvent->key() == Qt::Key_Space)
            {
                pausebutton->click();
            }
            else if(keyEvent->key() == Qt::Key_Left || keyEvent->key() == Qt::Key_Right)
            {
                int direction = -1;
                if(keyEvent->key() == Qt::Key_Right)
                    direction = 1;
                slider->setValue(slider->value()+direction*slider->singleStep());
            }
            return true;
        }
        else if(event->type() == QEvent::MouseButtonDblClick)
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if(playing)
            {
                int direction = 1;
                if(mouseEvent->pos().x() < playerwidget->width()/2)
                    direction = -1;
                slider->setValue(slider->value()+direction*slider->singleStep());
                if(controlwidget->isHidden())
                {
                    controlwidget->show();
                    slider->show();
                    timelabel->show();
                }
                else
                {
                    controlwidget->hide();
                    slider->hide();
                    timelabel->hide();
                }
            }
        }
    }
    else if(watched == aboutdialog)
    {
        if(event->type() == QEvent::KeyPress)
        {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            if(keyEvent->key() == Qt::Key_Back || keyEvent->key() == Qt::Key_Escape)
            {
                aboutdialog->close();
                return true;
            }
        }
        else if(event->type() == QEvent::Resize)
        {
            filenamelabel1->move(10,10);
            filenamelabel2->move(filenamelabel1->x()+filenamelabel1->width()+5,filenamelabel1->y());
            filenamelabel2->resize(aboutdialog->width()-filenamelabel2->x()-5,filenamelabel1->height());

            filepathlabel1->move(filenamelabel1->x(),filenamelabel1->y()+filenamelabel1->height()+5);
            filepathlabel2->move(filepathlabel1->x()+filepathlabel1->width()+5,filepathlabel1->y());
            filepathlabel2->resize(aboutdialog->width()-filepathlabel2->x()-5,filepathlabel1->height());

            widthlabel1->move(filepathlabel1->x(),filepathlabel1->y()+filepathlabel1->height()+5);
            widthlabel2->move(widthlabel1->x()+widthlabel1->width()+5,widthlabel1->y());
            widthlabel2->resize(aboutdialog->width()-widthlabel2->x()-5,widthlabel1->height());

            heightlabel1->move(widthlabel1->x(),widthlabel1->y()+widthlabel1->height()+5);
            heightlabel2->move(heightlabel1->x()+heightlabel1->width()+5,heightlabel1->y());
            heightlabel2->resize(aboutdialog->width()-heightlabel2->x()-5,heightlabel1->height());

            existlabel1->move(heightlabel1->x(),heightlabel1->y()+heightlabel1->height()+5);
            existlabel2->move(existlabel1->x()+existlabel1->width()+5,existlabel1->y());
            existlabel2->resize(aboutdialog->width()-existlabel2->x()-5,existlabel1->height());

            readablelabel1->move(existlabel1->x(),existlabel1->height()+existlabel1->y()+5);
            readablelabel2->move(readablelabel1->x()+readablelabel1->width()+5,readablelabel1->y());
            readablelabel2->resize(aboutdialog->width()-readablelabel2->x()-5,readablelabel1->height());

            durationlabel1->move(readablelabel1->x(),readablelabel1->height()+readablelabel1->y()+5);
            durationlabel2->move(durationlabel1->x()+durationlabel1->width()+5,durationlabel1->y());
            durationlabel2->resize(aboutdialog->width()-durationlabel2->x()-5,durationlabel1->height());
        }
    }
    else if(watched == filepathlabel2)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QLabel* label = qobject_cast<QLabel*>(watched);
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if(label->rect().contains(mouseEvent->pos()))
            {
                QMenu* m = new QMenu(this);
#ifdef Q_Device_Desktop
                m->addActions(QList<QAction*>() << copyaction << opendiraction);
#else
                m->addActions(QList<QAction*>() << copyaction);
#endif
                QObject::connect(copyaction,QOverload<bool>::of(&QAction::triggered),[=](){
                    QGuiApplication::clipboard()->setText(label->text());
                });
                QObject::connect(opendiraction,QOverload<bool>::of(&QAction::triggered),[=](){
                    if(QFileInfo(label->text()).isFile())
                    {
#ifdef Q_OS_WIN
            ShellExecuteW(NULL, L"open", L"explorer", QString("/select, \"%1\"").arg(label->text().replace("/","\\")).toStdWString().c_str(), NULL, SW_SHOW);
#else
            QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(label->text()).absolutePath()));
#endif
                    }
                });
                m->exec(QCursor::pos());
                copyaction->disconnect();
                opendiraction->disconnect();
            }
        }
    }
    else if(watched == filenamelabel2 || watched == widthlabel2 || watched == heightlabel2 || watched == durationlabel2)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QLabel* label = qobject_cast<QLabel*>(watched);
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            if(label->rect().contains(mouseEvent->pos()))
            {
                QMenu* m = new QMenu(this);
                m->addActions(QList<QAction*>() << copyaction);
                QObject::connect(copyaction,QOverload<bool>::of(&QAction::triggered),[=](){
                    QGuiApplication::clipboard()->setText(label->text());
                });
                m->exec(QCursor::pos());
                copyaction->disconnect();
            }
        }
    }
    return QObject::eventFilter(watched,event);
}
bool Widget::playMedia(QString filepath)
{
    taskbar->setState(MyTaskBarProgress::Busy);
    taskbar->show();
    playerwidget->pause();
    QString suffix = QFileInfo(filepath).suffix();
    QPixmap p;
    if((toStringList(QImageReader::supportedImageFormats()).contains(suffix) || QList<QString>({"psd","psb"}).contains(suffix)) && p.loadFromData(readfile(filepath)))
    {
        p = p.scaled(this->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        taskbar->setState(MyTaskBarProgress::NoProgress);
        taskbar->hide();
        showPixmapDialog(p,this,QFileInfo(filepath).fileName());
        return true;
    }
    if(playerwidget->setFilePath(filepath))
    {
        playerwidget->stop();
        iconlabel->clear();
        if(darkmode)
        {
            QColor color = QColor(100,100,100);
            iconlabel->setStyleSheet("background-color:"+color.name());
        }
        else
        {
            iconlabel->setStyleSheet("background-color:white");
        }
        if(playerwidget->play())
        {
            QString abs = QFileInfo(filepath).absoluteFilePath();
            QString path = filepath;
            if(!abs.isEmpty())
                path = abs;

            qDebug() << "vaild media";
            this->setWindowTitle(QFileInfo(filepath).fileName());
            namelabel->setText(this->windowTitle());
            namelabel->setToolTip(namelabel->text());
            slider->setEnabled(true);
            pausebutton->setFocus();

            int i = 1;
            int index = -1;
            while(medialist->contains(QString::number(i)) && index == -1)
            {
                if(medialist->value(QString::number(i)).toString() == path)
                    index = i;
                i++;
            }
            if(index == -1)
            {
                i = medialist->allKeys().count();
                while(medialist->contains(QString::number(i)))
                {
                    medialist->setValue(QString::number(i+1),medialist->value(QString::number(i)).toString());
                    i = i - 1;
                }
                medialist->setValue(QString::number(1),path);
            }
            else
            {
                i = index - 1;
                while(medialist->contains(QString::number(i)))
                {
                    medialist->setValue(QString::number(i+1),medialist->value(QString::number(i)).toString());
                    i = i - 1;
                }
                medialist->setValue(QString::number(1),path);
            }
            medialist->sync();
            this->loadMediaList();
            QStringList videofilelist = {"mp4","mkv","flv","mov"};
            if(!playing && videofilelist.contains(QFileInfo(path).suffix()))
            {
                this->showPlayerWidget();
            }
            taskbar->setState(MyTaskBarProgress::NoProgress);
            taskbar->hide();
            return true;
        }
        else
        {
            qDebug() << "invaild media";
            taskbar->setState(MyTaskBarProgress::NoProgress);
            taskbar->hide();
            this->setWindowTitle(title);
            namelabel->setText("");
            namelabel->setToolTip(namelabel->text());
            slider->setEnabled(false);
            QString msg = "<br>媒体播放失败\n";
            msg = msg + "<br>文件路径:" + filepath + "\n";
            msg = msg + "<br>错误类型:" + toString(playerwidget->errorType()) + "\n";
            msg = msg + "<br>详细信息:" + playerwidget->errorString() + "\n";
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
            msg = msg + "<br>若该媒体为正常，请检查解码器是否安装\n<br>下载解码器:" + toLinkedString("LAVFilters","https://github.com/Nevcairiel/LAVFilters/releases");
#endif

            emit errorChanged(msg);
            //QMessageBox::critical(this,"错误",msg,"确定");
            return false;
        }
    }
    else
    {
        taskbar->setState(MyTaskBarProgress::NoProgress);
        taskbar->hide();
        playerwidget->play();
        QString msg;
        if(!QFileInfo(filepath).isFile())
            msg = "文件" + filepath + "不存在";
        else
            msg = "文件" + filepath + "不可读";
        emit errorChanged(msg);
        return false;
    }
}
void Widget::showPlayerWidget()
{
    moving = true;
#if (QT_VERSION > QT_VERSION_CHECK(6,5,0)) && (QT_VERSION < QT_VERSION_CHECK(6,7,0))
    playerwidget->lock();
#endif
    int s1 = int(floor(double(controlwidget_color.red()-0)/10.0));
    int s2 = int(floor(double(controlwidget_color.green()-0)/10.0));
    int s3 = int(floor(double(controlwidget_color.blue()-0)/10.0));
    int s4 = int(floor(double(controlwidget_color.alpha()-100)/10.0));
    QColor color = controlwidget_color;

    mainwidget->hide();
    playerwidget->show();
    namelabel->hide();
    iconlabel->hide();
    if(!isBool(settings->value("showSmoothly").toString()))
    {
        settings->setValue("showSmoothly","true");
    }
    if(toBool(settings->value("showSmoothly").toString()))
    {
        QEventLoop* loop = new QEventLoop(this);
        playerwidget->move(0,mainwidget->height());
        while(playerwidget->y() > 0)
        {
            playerwidget->move(0,playerwidget->y()-float(mainwidget->height())/10.0);
            color = QColor(color.red()-s1,color.green()-s2,color.blue()-s3,color.alpha()-s4);
//            QPalette p;
//            p.setColor(QPalette::Window,controlwidget_color);
//            p.setColor(QPalette::Button,controlwidget_color);
//            controlwidget->setPalette(p);
//            controlwidget->setAutoFillBackground(true);
            controlwidget->setStyleSheet("background-color:rgba("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+","+QString::number(color.alpha())+");");
            QTimer::singleShot(5,[=](){
                loop->quit();
            });
            loop->exec();
        }
    }
    controlwidget->setStyleSheet("background-color:rgba(0,0,0,100);");

    playing = true;
    this->checkDarkMode();
    this->refreshUI();
    Android::setKeepScreenOn(true);

    loop = nullptr;
    playerwidget->move(0,0);
    moving = false;
#if (QT_VERSION > QT_VERSION_CHECK(6,5,0)) && (QT_VERSION < QT_VERSION_CHECK(6,7,0))
    playerwidget->unlock();
#endif
}
void Widget::hidePlayerWidget()
{
    moving = true;
#if (QT_VERSION > QT_VERSION_CHECK(6,5,0)) && (QT_VERSION < QT_VERSION_CHECK(6,7,0))
    playerwidget->lock();
#endif

    controlwidget->show();
    slider->show();
    timelabel->show();
    int s1 = int(floor(double(controlwidget_color.red()-0)/10.0));
    int s2 = int(floor(double(controlwidget_color.green()-0)/10.0));
    int s3 = int(floor(double(controlwidget_color.blue()-0)/10.0));
    int s4 = int(floor(double(controlwidget_color.alpha()-100)/10.0));
    QColor color = QColor(0,0,0,100);
    playing = false;

    if(!isBool(settings->value("showSmoothly").toString()))
    {
        settings->setValue("showSmoothly","true");
    }
    if(toBool(settings->value("showSmoothly").toString()))
    {
        QEventLoop* loop = new QEventLoop(this);
        while(playerwidget->y() < mainwidget->height())
        {
            playerwidget->move(0,playerwidget->y()+float(mainwidget->height())/10.0);
            color = QColor(color.red()+s1,color.green()+s2,color.blue()+s3,color.alpha()+s4);
            QPalette p;
            p.setColor(QPalette::Window,color);
            p.setColor(QPalette::Button,color);
            controlwidget->setAutoFillBackground(true);
            controlwidget->setPalette(p);
            controlwidget->setStyleSheet("");
            //controlwidget->setStyleSheet("background-color:rgba("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+","+QString::number(color.alpha())+");");
            QTimer::singleShot(5,[=](){
                loop->quit();
            });
            loop->exec();
        }
        loop = nullptr;
    }
    color = QColor(0,0,0,100);
    QPalette p;
    p.setColor(QPalette::Window,color);
    p.setColor(QPalette::Button,color);
    controlwidget->setPalette(p);
    controlwidget->setStyleSheet("");

    this->checkDarkMode();
    namelabel->show();
    iconlabel->show();
    this->refreshUI();
    Android::setKeepScreenOn(false);

    playerwidget->move(0,mainwidget->height());
    playerwidget->hide();
    mainwidget->show();
    playerwidget->move(0,0);
    pausebutton->setFocus();

    moving = false;
#if (QT_VERSION > QT_VERSION_CHECK(6,5,0))
    playerwidget->unlock();
#endif
}
void Widget::loadMediaList()
{
    if(!widgetlist.isEmpty())
    {
        int i = 0;
        while(i < widgetlist.count())
        {
            MediaWidget* w = qobject_cast<MediaWidget*>(widgetlist.at(i));
            w->disconnect();
            w->close();
            i++;
        }
        widgetlist.clear();
    }
    int i = 1;
    while(medialist->contains(QString::number(i)))
    {
        MediaWidget* w = new MediaWidget(widget);
        w->resize(widget->width()-15,50);
        w->move(0,(i-1)*50);
        w->setFilePath(medialist->value(QString::number(i)).toString());
        if(darkmode)
        {
            w->setMenuButtonIcon(QIcon(":/icon/more_white.png"));
        }
        else
        {
            w->setMenuButtonIcon(QIcon(":/icon/more_black.png"));
        }
        w->show();
        widgetlist << w;
        widget->resize(widget->width(),w->y()+w->height());
        QObject::connect(w,QOverload<>::of(&MediaWidget::play),[=](){
            this->playMedia(w->filePath());
        });
        QObject::connect(w,QOverload<>::of(&MediaWidget::removeFromList),[=](){
            this->removeMediaFromList(w->filePath());
            this->loadMediaList();
        });
        QObject::connect(w,QOverload<>::of(&MediaWidget::deleteMedia),[=](){
            auto box = QMessageBox(QMessageBox::Warning,"提示","是否删除"+w->filePath()+"？",QMessageBox::NoButton);
            box.addButton("确定",QMessageBox::AcceptRole);
            box.setDefaultButton(box.addButton("手滑了",QMessageBox::RejectRole));
            box.exec();
            if(box.result() == QMessageBox::AcceptRole)
            {
                QString filePath = w->filePath();
                this->setWindowTitle(title);
                namelabel->setText("");
                namelabel->setToolTip(namelabel->text());
                iconlabel->clear();
                slider->setValue(0);
                slider->setEnabled(false);
                timelabel->setText("");
                playerwidget->clear();
                this->removeMediaFromList(w->filePath());
                this->loadMediaList();
                if(!QFile::remove(filePath))
                {
                    emit errorChanged("删除"+filePath+"失败");
                }
            }
        });
        QObject::connect(w,QOverload<>::of(&MediaWidget::about),[=](){
#ifndef Q_OS_ANDROID
            if(!aboutdialog->isHidden())
                aboutdialog->close();
#endif
            qDebug() << "test";
            this->showAboutDialog(w->filePath());
        });
        QObject::connect(w,QOverload<>::of(&MediaWidget::opendir),[=](){
#ifdef Q_Device_Desktop
#ifdef Q_OS_WIN
            ShellExecuteW(NULL, L"open", L"explorer", QString("/select, \"%1\"").arg(w->filePath().replace("/","\\")).toStdWString().c_str(), NULL, SW_SHOW);
#else
            QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(w->filePath()).absolutePath()));
#endif
#else
#ifdef Q_OS_ANDROID
            Android::shareFile(QFileInfo(w->filePath()).absoluteFilePath());
#endif
#endif
        });
        i++;
    }
    area->setGeometry(0,0,mediawidget->width(),mediawidget->height());
}
void Widget::removeMediaFromList(QString path)
{
    QString abs = QFileInfo(path).absoluteFilePath();
    if(!abs.isEmpty())
        path = abs;
    int i = 1;
    int index = -1;
    while(medialist->contains(QString::number(i)) && index == -1)
    {
        if(medialist->value(QString::number(i)).toString() == path)
            index = i;
        i++;
    }
    i = index;
    while(medialist->contains(QString::number(i+1)))
    {
        medialist->setValue(QString::number(i),medialist->value(QString::number(i+1)).toString());
        i++;
    }
    medialist->remove(QString::number(i));
}
void Widget::showAboutDialog(QString filepath)
{

#ifndef Q_OS_ANDROID
    aboutdialog->resize(this->width(),300);
    //aboutdialog->setWindowFlag(Qt::FramelessWindowHint);
    if(filepath == "" || QFileInfo(filepath).absoluteFilePath() == playerwidget->filePath())
    {
        filepath = playerwidget->filePath();
        if(playerwidget->hasVideo())
        {
            widthlabel2->setText(QString::number(playerwidget->videoFrame().width()));
            heightlabel2->setText(QString::number(playerwidget->videoFrame().height()));
        }
        int sec = floor(double(playerwidget->duration())/1000);
        int min = floor(double(sec)/60);
        sec = sec - 60 * min;
        QString str = "";
        if(min < 10)
            str = str + "0";
        str = str + QString::number(min) + ":";
        if(sec < 10)
            str = str + "0";
        str = str + QString::number(sec);
        durationlabel2->setText(str);
    }
    else
    {
        filepath = QFileInfo(filepath).absoluteFilePath();
        PlayerWidget* widget = new PlayerWidget(this);
        widget->setVolume(0);
        widget->hide();
        QObject::connect(widget,QOverload<QVideoFrame>::of(&PlayerWidget::videoFrameChanged),[=](QVideoFrame frame){
            if(frame.isValid())
            {
                widthlabel2->setText(QString::number(frame.width()));
                heightlabel2->setText(QString::number(frame.height()));
                widget->disconnect(widget,SIGNAL(videoFrameChanged(QVideoFrame)),0,0);
                if(playerwidget->duration() != 0)
                {
                    qDebug() << "1";
                    widget->stop();
                    widget->close();
                }
            }
        });
        QObject::connect(widget,QOverload<int>::of(&PlayerWidget::durationChanged),[=](){
            if(widget->duration() != 0)
            {
                int sec = floor(double(widget->duration())/1000);
                int min = floor(double(sec)/60);
                sec = sec - 60 * min;
                QString str = "";
                if(min < 10)
                    str = str + "0";
                str = str + QString::number(min) + ":";
                if(sec < 10)
                    str = str + "0";
                str = str + QString::number(sec);
                durationlabel2->setText(str);
                widget->disconnect(widget,SIGNAL(durationChanged(int)),0,0);
                if(widget->videoFrame().isValid())
                {
                    qDebug() << "2";
                    widget->stop();
                    widget->close();
                }
            }
        });
        if(!widget->setFilePath(filepath) || !widget->play())
        {
            widthlabel2->setText("播放失败: "+widget->errorString());
            heightlabel2->setText("播放失败: "+widget->errorString());
            durationlabel2->setText("播放失败: "+widget->errorString());
            widget->close();
        }
    }
    filenamelabel2->setText(QFileInfo(filepath).fileName());
    filepathlabel2->setText(filepath);
    if(QFile::exists(filepath))
        existlabel2->setText("是");
    else
        existlabel2->setText("否");
    if(hasFilePermission(filepath,QIODevice::ReadOnly))
        readablelabel2->setText("是");
    else
        readablelabel2->setText("否");
    filepathlabel2->setToolTip(filepathlabel2->text());
    aboutdialog->show();
    this->checkDarkMode();
    //this->setEnabled(false);
    //fixNoSize(aboutdialog,0);
#else

    QMessageBox* box = new QMessageBox(this);
        message = "";
        //QEventLoop* loop = new QEventLoop(this);
        filepath = QFileInfo(filepath).absoluteFilePath();
        message = message + "文件名 " + QFileInfo(filepath).fileName() + "\n";
        message = message + "文件路径 " + filepath + "\n";
        if(QFileInfo(filepath).isFile())
            message = message + "是否存在 " + "是" + "\n";
        else
            message = message + "是否存在 " + "否" + "\n";
        if(hasFilePermission(filepath,QIODevice::ReadOnly))
            message = message + "是否可读 " + "是" + "\n";
        else
            message = message + "是否可读 " + "否" + "\n";
        if(filepath == "" || QFileInfo(filepath).absoluteFilePath() == playerwidget->filePath())
        {
            int sec = floor(double(playerwidget->duration())/1000);
            int min = floor(double(sec)/60);
            sec = sec - 60 * min;
            QString str = "";
            if(min < 10)
                str = str + "0";
            str = str + QString::number(min) + ":";
            if(sec < 10)
                str = str + "0";
            str = str + QString::number(sec);
            message = message + "帧宽度 " + QString::number(playerwidget->videoFrame().width()) + "\n";
            message = message + "帧高度 " + QString::number(playerwidget->videoFrame().height()) + "\n";
            message = message + "时长 " + str + "\n";
        }
        else
        {
            filepath = QFileInfo(filepath).absoluteFilePath();
            PlayerWidget* widget = new PlayerWidget(this);
            widget->setVolume(0);
            widget->hide();
            QObject::connect(widget,QOverload<QVideoFrame>::of(&PlayerWidget::videoFrameChanged),[=](QVideoFrame frame){
                if(frame.isValid())
                {
                    message = message + "帧宽度 " + QString::number(frame.width()) + "\n";
                    message = message + "帧高度 " + QString::number(frame.height()) + "\n";
                    box->setText(message);
                    box->close();
                    box->exec();
                    widget->disconnect(widget,SIGNAL(videoFrameChanged(QVideoFrame)),0,0);
                    if(playerwidget->duration() != 0)
                    {
                        widget->stop();
                        widget->close();
                    }
                }
            });
            QObject::connect(widget,QOverload<int>::of(&PlayerWidget::durationChanged),[=](){
                if(widget->duration() != 0)
                {
                    int sec = floor(double(widget->duration())/1000);
                    int min = floor(double(sec)/60);
                    sec = sec - 60 * min;
                    QString str = "";
                    if(min < 10)
                        str = str + "0";
                    str = str + QString::number(min) + ":";
                    if(sec < 10)
                        str = str + "0";
                    str = str + QString::number(sec);
                    message = message + "时长 " + str + "\n";
                    box->setText(message);
                    box->close();
                    box->exec();
                    widget->disconnect(widget,SIGNAL(durationChanged(int)),0,0);
                    if(widget->videoFrame().isValid())
                    {
                        widget->stop();
                        widget->close();
                    }
                }
            });
            if(!widget->setFilePath(filepath) || !widget->play())
            {
                message = message + "帧宽度 " + "播放失败: "+ widget->errorString() + "\n";
                message = message + "帧高度 " + "播放失败: "+ widget->errorString() + "\n";
                message = message + "时长 " + "播放失败: "+ widget->errorString() + "\n";
                widget->close();
            }
            else
            {
            }
        }
        box->setText(message);
        box->show();
    #endif

}
void Widget::checkDarkMode()
{
    if(!settings->allKeys().contains("appTheme"))
    {
        settings->setValue("appTheme","system");
    }
    QString value = settings->value("appTheme").toString();
    if(value == "system")
    {
        darkmode = isSystemDarkMode();
        this->setDarkMode(darkmode);
    }
    else if(value == "light")
    {
        darkmode = false;
        this->setDarkMode(false);
    }
    else if(value == "dark")
    {
        darkmode = true;
        this->setDarkMode(true);
    }
    else
    {
        settings->setValue("appTheme","system");
        darkmode = isSystemDarkMode();
        this->setDarkMode(darkmode);
    }
}
void Widget::setDarkMode(bool on)
{
    setDarkTitleBar(this->winId(),on);
    setApplicationDarkMode(on,this);
    if(hasPixmap(iconlabel))
    {
        iconlabel->setStyleSheet("");
    }
    else if(darkmode)
    {
        QColor color = QColor(100,100,100);
        iconlabel->setStyleSheet("background-color:"+color.name());
    }
    else
    {
        iconlabel->setStyleSheet("background-color:white");
    }
    if(on || playing)
    {
        if(playing)
        {
            QPalette p;
            p.setColor(QPalette::Window,QColor(0,0,0,100));
            p.setColor(QPalette::Button,QColor(0,0,0,100));
            controlwidget->setAutoFillBackground(true);
            controlwidget->setPalette(p);
            //controlwidget->setStyleSheet("background-color:rgba("+QString::number(0)+","+QString::number(0)+","+QString::number(0)+","+QString::number(100)+");");
            timelabel->setStyleSheet("color:rgba(255,255,255,255);background-color:rgba(0,0,0,100);");
        }
        else
        {
            controlwidget_color = QColor(65,65,65,255);
            QPalette p;
            p.setColor(QPalette::Window,controlwidget_color);
            p.setColor(QPalette::Button,controlwidget_color);
            controlwidget->setAutoFillBackground(true);
            controlwidget->setPalette(p);
            //controlwidget->setStyleSheet("background-color:rgba("+QString::number(controlwidget_color.red())+","+QString::number(controlwidget_color.green())+","+QString::number(controlwidget_color.blue())+","+QString::number(controlwidget_color.alpha())+");");
            timelabel->setStyleSheet("color:rgba(255,255,255,255);");
        }
        if(playerwidget->state() == PlayerWidget::PlayingState)
            pausebutton->setIcon(QIcon(":/icon/pause_white"));
        else
            pausebutton->setIcon(QIcon(":/icon/play_white.png"));
        forwardbutton->setIcon(QIcon(":/icon/forward_white.png"));
        backwardbutton->setIcon(QIcon(":/icon/backward_white.png"));
        aboutbutton->setIcon(QIcon(":/icon/more_white.png"));
        fullscreenbutton->setIcon(QIcon(":/icon/fullscreen_white.png"));
        volumebutton->setIcon(QIcon(":/icon/volume_white.png"));
        if(playmode == Widget::PlayRandom)
        {
            modebutton->setIcon(QIcon(":/icon/random_white.png"));
        }
        else if(playmode == Widget::PlayRepeat)
        {
            modebutton->setIcon(QIcon(":/icon/repeat_white.png"));
        }
        else
        {
            modebutton->setIcon(QIcon(":/icon/single_white.png"));
        }
    }
    else
    {
        controlwidget_color = QColor(230,230,230,255);
        QPalette p;
        p.setColor(QPalette::Window,controlwidget_color);
        p.setColor(QPalette::Button,controlwidget_color);
        controlwidget->setAutoFillBackground(true);
        controlwidget->setPalette(p);
        //controlwidget->setStyleSheet("background-color:rgba("+QString::number(controlwidget_color.red())+","+QString::number(controlwidget_color.green())+","+QString::number(controlwidget_color.blue())+","+QString::number(controlwidget_color.alpha())+");");
        timelabel->setStyleSheet("color:rgba(0,0,0,255);");
        if(playerwidget->state() == PlayerWidget::PlayingState)
            pausebutton->setIcon(QIcon(":/icon/pause_black"));
        else
            pausebutton->setIcon(QIcon(":/icon/play_black.png"));
        fullscreenbutton->setIcon(QIcon(":/icon/fullscreen_black.png"));
        forwardbutton->setIcon(QIcon(":/icon/forward_black.png"));
        backwardbutton->setIcon(QIcon(":/icon/backward_black.png"));
        aboutbutton->setIcon(QIcon(":/icon/more_black.png"));
        volumebutton->setIcon(QIcon(":/icon/volume_black.png"));
        if(playmode == Widget::PlayRandom)
        {
            modebutton->setIcon(QIcon(":/icon/random_black.png"));
        }
        else if(playmode == Widget::PlayRepeat)
        {
            modebutton->setIcon(QIcon(":/icon/repeat_black.png"));
        }
        else
        {
            modebutton->setIcon(QIcon(":/icon/single_black.png"));
        }
    }
    if(on)
    {
        int i = 0;
        while(i < widgetlist.count())
        {
            MediaWidget* w = qobject_cast<MediaWidget*>(widgetlist.at(i));
            w->setMenuButtonIcon(QIcon(":/icon/more_white.png"));
            i++;
        }
        singleaction->setIcon(QIcon(":/icon/single_white.png"));
        repeataction->setIcon(QIcon(":/icon/repeat_white.png"));
        randomaction->setIcon(QIcon(":/icon/random_white.png"));
    }
    else
    {
        int i = 0;
        while(i < widgetlist.count())
        {
            MediaWidget* w = qobject_cast<MediaWidget*>(widgetlist.at(i));
            w->setMenuButtonIcon(QIcon(":/icon/more_black.png"));
            i++;
        }
        singleaction->setIcon(QIcon(":/icon/single_black.png"));
        repeataction->setIcon(QIcon(":/icon/repeat_black.png"));
        randomaction->setIcon(QIcon(":/icon/random_black.png"));
    }
}
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
bool Widget::nativeEvent(const QByteArray &eventType, void *message,qintptr* result) {
#else
bool Widget::nativeEvent(const QByteArray &eventType, void *message,long* result) {
#endif
#ifdef Q_OS_WIN
    //qDebug() << eventType;
    MSG* msg = static_cast<MSG*>(message);
    if(msg->message == 563 && Windows::isAdmin())
    {
         Windows::processNativeDropEvent(msg);
    }
#if (QT_VERSION < QT_VERSION_CHECK(6,5,0))
    if(msg->message == 15 && oldThemeIsDark != isSystemDarkMode())
    {
        oldThemeIsDark = !oldThemeIsDark;
        emit systemThemeChanged(oldThemeIsDark);
    }
#endif
#endif
    return false;
}
Widget* Widget::getCurrentWindow()
{
    QList<QWidget*> list;
    QList<QWidget*> widgets = qApp->topLevelWidgets();
    for(QWidget* widget : widgets)
    {
        if(QString(widget->metaObject()->className()) == "Widget" && !list.contains(widget))
        {
            list << widget;
        }
    }

    if(list.count() == 1)
    {
        return (Widget*)list.at(0);
    }
    else if(list.count() > 1)
    {
        qDebug() << list.count();
        QList<int> childrenCountList;
        for(QWidget* widget : list)
        {
            childrenCountList << allChildren(widget).count();
        }
        int index = getMaxIntIndex(childrenCountList);
        return (Widget*)list.at(index);
    }
    return nullptr;
}
