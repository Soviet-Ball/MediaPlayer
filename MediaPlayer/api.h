#ifndef API_H
#define API_H

#define Core_Private_Enabled
#define Gui_Private_Enabled
#define Network_Enabled
#define Multimedia_And_Widgets_Enabled
#define Multimedia_Private_Enabled
#define Android_Activity_Enabled
#define Concurrent_Enabled
//#define Win_Extra_Enabled
#define Load_Windows_LIBS
//#define Webview_Enabled
#define Use_Plaform_Namespace

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <iomanip>
//using namespace std;
//#include <graphics.h>

#include <QObject>
#include <QApplication>
//#include <QApplicationPrivate>
#include <QCoreApplication>
#include <QGuiApplication>

#include <QMainWindow>
#include <QWidget>
#include <QDialog>
#include <QWindow>

#include <QEvent>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QTouchEvent>
#include <QFocusEvent>
#include <QDrag>
#include <QDragEnterEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QFileOpenEvent>

#include <QString>
#include <QStringList>
#include <QSet>
#include <QUrl>
#include <QByteArray>
#include <QDesktopServices>
#include <QProcess>
#include <QTime>
#include <QTimer>
#include <QDebug>
#include <QMutex>
#include <QWaitCondition>
#include <QStack>
#include <QStandardPaths>
#include <QSysInfo>
#include <QFont>
#include <QRegularExpression>
#include <QMimeData>
#include <QSettings>
#include <QFuture>
#include <QStyle>
#include <QStyleFactory>
#include <QCursor>
#include <QThread>
#include <QRegularExpression>
#include <QValidator>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QClipboard>

//#include <QtVirtualKeyboard/QtVirtualKeyboard>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QFileDialog>
#include <QProgressBar>
#include <QCheckBox>
#include <QComboBox>
#include <QTreeView>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QSlider>
#include <QScroller>
#include <QScrollArea>
#include <QScrollBar>
#include <QScrollerProperties>
#include <QListView>
#include <QList>
#include <QRadioButton>
#include <QMessageBox>
#include <QScreen>
#include <QSystemTrayIcon>
#include <QStandardItem>
#include <QColorDialog>
#include <QSpinBox>
#include <QFileIconProvider>

#include <QImage>
#include <QImageIOHandler>
#include <QImageReader>
#include <QPixmap>
#include <QBitmap>
#include <QRect>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPalette>
#include <QStyleHints>
#include <QOperatingSystemVersion>
#include <QLocale>
//#include <qnativeinterface.h>

#ifdef Q_OS_WIN
#ifdef Webview_Enabled
#if defined(_MSC_VER)
#include <QtWebView>
#include <QtWebView/QtWebView>
#include <qwebview_global.h>
//#include <winrt/Windows.UI.ViewManagement.h>
#if (QT_VERSION >= QT_VERSION_CHECK(6,5,0))
#include <QWebEngineView>
#endif
#endif
#endif
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
#ifdef Win_Extra_Enabled
#include <QtWinExtras>
#include <QtWin>
#include <qwinfunctions.h>
#endif
#endif
#if (QT_VERSION > QT_VERSION_CHECK(6,0,0))
#ifdef Core_Private_Enabled
#endif
#endif
#include <Windows.h>
#include <processthreadsapi.h>
#include <qt_windows.h>
#include <tlhelp32.h>
#include <string.h>
#include <shellapi.h>
#include <ShlObj.h>
#include <Ole2.h>
#include <commdlg.h>
#include <dwmapi.h>
#include <Psapi.h>
#include <fcntl.h>
#include <io.h>
#ifdef Load_Windows_LIBS
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "DbgHelp.lib")
#endif
#endif

#ifdef Q_OS_ANDROID
#ifdef Core_Private_Enabled
#include <android/bitmap.h>
#include <QtCore/private/qandroidextras_p.h>
#include <QJniObject>
#include <QJniEnvironment>
//#include <QPermissions>
#endif
#endif

#ifdef Core_Private_Enabled
#ifdef Network_Enabled
#include <QSslSocket>
#endif
#endif

#ifdef Concurrent_Enabled
#include <QtConcurrent>
#endif

#ifdef Core_Private_Enabled
#if(QT_VERSION>=QT_VERSION_CHECK(6,7,0))
#include "QtCore/private/qzipreader_p.h"
#include "QtCore/private/qzipwriter_p.h"
#endif
#endif
#ifdef Gui_Private_Enabled
#if(QT_VERSION<QT_VERSION_CHECK(6,7,0))
#include "QtGui/private/qzipreader_p.h"
#include "QtGui/private/qzipwriter_p.h"
#endif
#endif

#ifdef Network_Enabled
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#endif

#ifdef Multimedia_And_Widgets_Enabled
//#include <QVideoProbe>
#include <QImageWriter>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaMetaData>
#include <QVideoFrame>
#include <QGraphicsVideoItem>
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
#include <QAbstractVideoSurface>
#include <QAudioRecorder>
#include <QAudioEncoderSettings>
#include <QVideoEncoderSettings>
#endif
#endif

#ifdef Q_OS_WIN
//Windows
#define Q_Device_Desktop
#else
#ifdef Q_OS_LINUX
#ifdef Q_OS_ANDROID
//Android
#define Q_Device_Mobile
#else
//Linix Desktop
#define Q_Device_Desktop
#endif
#else
#ifdef Q_OS_UNIX
#ifdef Q_OS_MAC
//Macos
#define Q_Device_Desktop
#else
#ifdef Q_OS_IOS
//ios
#define Q_Device_Mobile
#else
//unix unknown
#define Q_Device_Unknown
#endif
#endif
#else
//Unknown
#define Q_Device_Unknown
#endif
#endif
#endif

#ifdef Q_Device_Unknown
#define Q_Device_Desktop
#endif

//1.基本函数
static int Abs(int num)//绝对值
{
    if(num >= 0)
        return num;
    else
        return -num;
}
static float Abs(float num)
{
    if(num >= 0)
        return num;
    else
        return -num;
}
static int Max(int a,int b)//取大
{
    if(a > b)
        return a;
    else
        return b;
}
static float Max(float a,float b)
{
    if(a > b)
        return a;
    else
        return b;
}
static int Mini(int a,int b)//取小
{
    if(a < b)
        return a;
    else
        return b;
}
static float Mini(float a,float b)
{
    if(a < b)
        return a;
    else
        return b;
}
static bool isint(QString str)
{
    bool ok;
    str.toInt(&ok);
    return ok;
}
static bool isfloat(QString str)
{
    bool ok;
    str.toFloat(&ok);
    return ok;
}
static bool isDouble(QString str)
{
    bool ok;
    str.toDouble(&ok);
    return ok;
}
static QString getlastPath(QString path)
{
    QString ret = path.replace("\\","/");

    if(ret.indexOf("/") != ret.lastIndexOf("/"))//2个或以上
    {
        if(ret.endsWith("/"))
            ret.chop(1);

        while(!ret.endsWith("/"))
        {
            ret.chop(1);
        }
        if(ret != "/")
            ret.chop(1);
    }
    else if(ret.contains("/"))
    {
        if(!ret.endsWith("/"))
        {
            while(!ret.endsWith("/"))
                ret.chop(1);
            if(ret != "/")
                ret.chop(1);
        }
        else if(ret != "/")
        {
            ret.chop(1);
        }
    }

    return ret;
}
static double distance(QPoint p1,QPoint p2)
{
    if(p1.x() == p2.x())
    {
        return double(Abs(p1.y()-p2.y()));
    }
    else if(p1.y() == p2.y())
    {
        return double(Abs(p1.x()-p2.x()));
    }
    else
    {
        return double(sqrt(double(Abs(p1.x()-p2.x())*Abs(p1.x()-p2.x())+Abs(p1.y()-p2.y())*Abs(p1.y()-p2.y()))));
    }
}
static QPoint midPoint(QPoint p1,QPoint p2)
{
    return QPoint((p1.x()+p2.x())/2,(p1.y()+p2.y())/2);
}
static QString runCommand(QString cmd)
{
    FILE *fp;
    char buffer[1024];
#ifdef Q_OS_WIN
    fp = _popen(cmd.toLocal8Bit().data(), "r");
#else
    fp = popen(cmd.toLocal8Bit().data(), "r");
#endif
    if (fp == NULL)
    {
        return "";
    }

    while(fgets(buffer, sizeof(buffer), fp) != NULL)
    {

    }
#ifdef Q_OS_WIN
    _pclose(fp);
#else
    pclose(fp);
#endif
    QString ret = QString(buffer);
    if(ret.endsWith("\n"))
        ret = ret.left(ret.length()-QString("\n").length());
    if(ret.endsWith("\r"))
        ret = ret.left(ret.length()-QString("\r").length());
    return ret;
}
static double setPrecision(double num,int p)
{
    return round(num*10*p)/(10*p);
}
static int getContainStringTimes(QString parent,QString s)
{
    int count = 0;
    int index = parent.indexOf(s);
    while(index != -1)
    {
        parent.remove(index,s.length());
        count++;
        index = parent.indexOf(s);
    }
    return count;
}
static int screenwidth()//屏幕高度
{
    return QGuiApplication::primaryScreen()->availableVirtualGeometry().width();
}
static int screenheight()//屏幕宽度
{
    return QGuiApplication::primaryScreen()->availableVirtualGeometry().height();
}
static QSize screensize()//屏幕大小
{
    return QGuiApplication::primaryScreen()->availableVirtualGeometry().size();
}
static void wait(int time,int mode = 0)//使应用程序暂停执行一段时间
{
    if(mode == 0)
    {
        QMutex mutex;
        QWaitCondition waitCondition;
        mutex.lock();
        waitCondition.wait(&mutex, time);
        mutex.unlock();
    }
    else
    {
        QCoreApplication::processEvents(QEventLoop::AllEvents,time);
    }
}
static QStringList findTextFiles(const QString& path, const QString& keyword)
{
    QDir dir(path);
    QStringList filters;
    filters << "*.txt" << "*.log" << "*.ini" << "*.cmd" << "*.bat";  // 只搜索文本文件
    dir.setNameFilters(filters);

    QStringList fileList;
    QRegularExpression regex(keyword, QRegularExpression::CaseInsensitiveOption);

    // 递归遍历目录下的所有文件
    foreach (const QString& file, dir.entryList(QDir::Files | QDir::NoSymLinks)) {
        QFile f(dir.filePath(file));
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&f);
            while (!in.atEnd()) {
                QString line = in.readLine();
                if (regex.match(line).hasMatch()) {
                    fileList.append(dir.filePath(file));
                    break;
                }
            }
        }
    }

    // 递归遍历子目录
    foreach (const QString& subdir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QStringList subFiles = findTextFiles(dir.filePath(subdir), keyword);
        fileList.append(subFiles);
    }

    return fileList;
}
static QStringList findFiles(const QString& path, const QString& keyword, const QString& suffix = "")
{
    QDir dir(path);
    QStringList filters;
    if (!suffix.isEmpty()) {
        filters << "*." + suffix;
    }
    dir.setNameFilters(filters);

    QStringList fileList;

    // 递归遍历目录下的所有文件
    foreach (const QString& file, dir.entryList(QDir::Files | QDir::NoSymLinks)) {
        if (file.contains(keyword, Qt::CaseInsensitive)) {
            fileList.append(dir.filePath(file));
        }
    }

    // 递归遍历子目录
    foreach (const QString& subdir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        QStringList subFiles = findFiles(dir.filePath(subdir), keyword, suffix);
        fileList.append(subFiles);
    }

    return fileList;
}
static int getFilesNumber(QString path,QString type = "")
{
    QDir *dir=new QDir(path);
    QStringList filter;
    if(type != "")
    {
        filter << "*." + type;
        dir->setNameFilters(filter);
    }
    QList<QFileInfo> *fileInfo = new QList<QFileInfo>(dir->entryInfoList(filter));
    int count = fileInfo->count();
    if(type == "")
        count = count - 2;
    return count;
}
static QFileInfoList getFileList(QString path)
{
    QDir dir(path);
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i != folder_list.size(); i++)
    {
         QString name = folder_list.at(i).absoluteFilePath();
         QFileInfoList child_file_list = getFileList(name);
         file_list.append(child_file_list);
    }

    return file_list;
}
static bool hasFilePermission(QString filepath,QIODevice::OpenModeFlag device = QIODevice::ReadWrite)//检查文件访问权限
{
    bool check = true;
    if(filepath != "")
    {
        QFile* file = new QFile(filepath);
        if(!file->exists())
            check = false;
        if(file->open(device))
        {
            file->close();
            delete file;
            if(!check)
                QFile::remove(filepath);
            return true;
        }
        else
        {
            delete file;
            return false;
        }
    }
    else
    {
        return false;
    }
}
static bool hasPathPermission(QString path,QIODevice::OpenModeFlag device = QIODevice::ReadWrite)//检查文件访问权限
{
    if(path != "" && QFileInfo(path).isDir())
    {
        path.replace("\\","/");
        if(!path.endsWith("/"))
            path = path + "/";
        path = path + "my_app_textfile.txt";
        return hasFilePermission(path,device);
    }
    else if(QFileInfo(path).isFile())
    {
        return hasFilePermission(path,device);
    }
    else
    {
        return false;
    }
}
static bool staysOnTop(QObject* obj)
{
    QWidget* w = static_cast<QWidget*>(obj);
    if(w)
    {
#ifdef Q_OS_WIN
        SetWindowPos(HWND(w->winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
#else
        if(w->isHidden())
        {
            w->setWindowFlags(w->windowFlags() | Qt::WindowStaysOnTopHint);
        }
        else
        {
            QWindow* pWin = w->windowHandle();
            pWin->setFlags(w->windowFlags() | Qt::WindowStaysOnTopHint);
        }
#endif
        return true;
    }
    else
    {
        return false;
    }
}
static bool staysNotOnTop(QObject* obj)
{
    QWidget* w = static_cast<QWidget*>(obj);
    if(w)
    {
#ifdef Q_OS_WIN
        SetWindowPos(HWND(w->winId()), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
#else
        if(w->isHidden())
        {
            w->setWindowFlag(Qt::Window);
        }
        else
        {
            QWindow* pWin = w->windowHandle();
            pWin->setFlags(Qt::Window);
        }
#endif
        return true;
    }
    else
    {
        return false;
    }
}
static bool fixSize(QObject* obj)
{
    QWidget* w = static_cast<QWidget*>(obj);
    if(w)
    {
        if(w->isHidden())
        {
            w->setMaximumSize(w->size());
            w->setMinimumSize(w->size());
        }
        else
        {
            QWindow* pWin = w->windowHandle();
            pWin->setMaximumSize(w->size());
            pWin->setMinimumSize(w->size());
        }
        return true;
    }
    else
    {
        return false;
    }
}
static bool fixNoSize(QObject* obj)
{
    QWidget* w = static_cast<QWidget*>(obj);
    if(w)
    {
        if(w->isHidden())
        {
            w->setMaximumSize(16777215,16777215);
            w->setMinimumSize(0,0);
        }
        else
        {
            QWindow* pWin = w->windowHandle();
            pWin->setMaximumSize(QSize(16777215,16777215));
            pWin->setMinimumSize(QSize(0,0));
        }
        return true;
    }
    else
    {
        return false;
    }
}
static bool setMaximizeButton(QObject* obj,bool check)
{
    QWidget* w = static_cast<QWidget*>(obj);
    if(w)
    {
        if(w->isHidden())
        {
            w->setWindowFlag(Qt::WindowMaximizeButtonHint,check);
        }
        else
        {
            QWindow* pWin = w->windowHandle();
            pWin->setFlag(Qt::WindowMaximizeButtonHint,check);
        }
        return true;
    }
    else
    {
        return false;
    }
}
static bool setCloseButton(QObject* obj,bool check)
{
    QWidget* w = static_cast<QWidget*>(obj);
    if(w)
    {
        if(w->isHidden())
        {
            w->setWindowFlag(Qt::WindowCloseButtonHint,check);
        }
        else
        {
            QWindow* pWin = w->windowHandle();
            pWin->setFlag(Qt::WindowCloseButtonHint,check);
        }
        return true;
    }
    else
    {
        return false;
    }
}
static QString readtextfile(QString path)
{
    if(path != "")
    {
        QFile* file = new QFile(path);
        if(file->open(QIODevice::ReadOnly | QIODevice::Text) || file->open(QIODevice::ReadWrite | QIODevice::Text))
        {
            QString content = QString::fromLocal8Bit(file->readAll());
            file->close();
            delete file;
            return content;
        }
        else
        {
            return QString();
        }
    }
    else
    {
        return QString();
    }
}
static QByteArray readfile(QString path)
{
    if(path != "")
    {
        QFile* file = new QFile(path);
        if(file->open(QIODevice::ReadOnly) || file->open(QIODevice::ReadWrite))
        {
            QByteArray content = file->readAll();
            file->close();
            delete file;
            return content;
        }
        else
        {
            return QByteArray();
        }
    }
    else
    {
        return QByteArray();
    }
}
static bool writetextfile(QString text,QString path)
{
    QFile* file = new QFile(path);
    if(file->open(QIODevice::WriteOnly) || file->open(QIODevice::ReadWrite))
    {
        file->write(text.toLatin1());
        file->close();
        return true;
    }
    else
    {
        return false;
    }
}
static bool writefile(QByteArray ba,QString path)
{
    QFile file(path);
    if(file.open(QIODevice::WriteOnly) || file.open(QIODevice::ReadWrite))
    {
        file.write(ba);
        file.close();
        return true;
    }
    else
    {
        return false;
    }
}
static bool writetextfileappend(QString text,QString path)
{
    QFile* file = new QFile(path);
    if(file->open(QIODevice::WriteOnly | QIODevice::Append) || file->open(QIODevice::ReadWrite | QIODevice::Append))
    {
        file->write(text.toLatin1());
        file->close();
        return true;
    }
    else
    {
        return false;
    }
}
static bool copyfile(QString path1,QString path2)
{
    if(QFile::exists(path1) && hasFilePermission(path1,QIODevice::ReadOnly) && hasFilePermission(path2,QIODevice::WriteOnly))
    {
        QByteArray ba = readfile(path1);
        writefile(ba,path2);
        ba = "";
        return QFile::exists(path2);
    }
    else
    {
        return false;
    }
}
static bool zipReader(QString zip,QString path)//解压zip
{
#ifdef Gui_Private_Enabled
    if(!QFileInfo(path).isDir())
        QDir().mkpath(path);
    if(QFileInfo(path).isDir() && hasFilePermission(zip,QIODevice::ReadOnly) && hasPathPermission(path))
    {
        path = path.replace("\\","/");
        if(path.endsWith("/"))
            path.chop(1);


        QZipReader reader(zip);
        //qDebug() << reader.fileInfoList().size();
        reader.extractAll(path);
        for(int i = 0; i < reader.fileInfoList().size(); i++)
        {
            QString filepath = path + "/" + reader.fileInfoList().at(i).filePath;
            //qDebug() << filepath;
            QString tmp = filepath;
            while(!tmp.endsWith("/"))
                tmp.chop(1);
            if(!QFileInfo(tmp).isDir() || !QDir(tmp).exists())
                QDir().mkpath(tmp);

            QFile* file = new QFile(filepath);
            file->open(QIODevice::WriteOnly);
            file->write(reader.fileData(QString::fromLocal8Bit(reader.fileInfoList().at(i).filePath.toUtf8())));
            file->close();
            delete file;
        }
        reader.close();
    }
    else
    {
        qDebug() << QFileInfo(path).isDir();
        qDebug() << hasFilePermission(zip,QIODevice::ReadOnly);
        qDebug() << hasPathPermission(path);
        return false;
    }
#else
    return false;
#endif
}
static bool zipWriter(QString zip,QString path)//压缩zip
{
#ifdef Gui_Private_Enabled
    if(QFileInfo(path).isDir() && hasFilePermission(zip,QIODevice::WriteOnly) && hasPathPermission(path))
    {
        QFileInfoList list = getFileList(path);
        path.replace("\\","/");
        if(path.endsWith("/"))
            path.chop(1);
        if(path.contains("/"))
            while(!path.endsWith("/"))
                path.chop(1);
        else
            path = path + "/";
        QZipWriter writer(zip);
        for(int i = 0; i < list.size(); i++)
        {
            QString filepath = list.at(i).absoluteFilePath().replace("\\","/");
            QFile* file = new QFile(filepath);
            filepath = filepath.remove(0,path.length());

            QString tmp = filepath;
            QStringList DirectoryList;
            while(!tmp.endsWith("/"))
                tmp.chop(1);
            while(tmp != "")
            {
                if(tmp.endsWith("/"))
                    DirectoryList << tmp;
                tmp.chop(1);
            }
            for(int i = DirectoryList.size()-1; i >= 0; i = i - 1)
            {
                //qDebug() << DirectoryList.at(i);
                writer.addDirectory(DirectoryList.at(i));
            }

            if(file->open(QIODevice::ReadOnly))
            {
                writer.addFile(filepath,file->readAll());
                file->close();
                delete file;
            }
            else
            {
                qDebug() << "fail to read file:" << filepath;
            }
        }
        writer.close();
        return true;
    }
    else
    {
        return false;
    }
#else
    return false;
#endif
}
#ifndef QVIDEOFRAME_H
typedef int QVideoFrame;
#endif
static QImage frameToImage(QVideoFrame f)
{
#ifdef QVIDEOFRAME_H
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
            return f.toImage();
#else
#if defined(Multimedia_Private_Enabled) && defined(QVIDEOFRAME_P_H)
            QImage image = qt_imageFromVideoFrame(f);
#else
            QImage image;
            f.map(QAbstractVideoBuffer::ReadOnly);
            QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(f.pixelFormat());
            if(imageFormat != QImage::Format_Invalid)
            {
                image = QImage(f.bits(),f.width(),f.height(),f.bytesPerLine(),imageFormat);
            }
            else
            {
                int nbytes = f.mappedBytes();
                image = QImage::fromData(f.bits(), nbytes);
            }
            f.unmap();
#endif
#ifdef Q_OS_WIN
            image = image.mirrored();
#endif
            return image;
#endif
#else
    return QImage();
#endif
}
static QSize nativeLabelSize(QString text,Qt::Alignment align = Qt::AlignLeft | Qt::AlignTop)
{
    QWidget* widget = new QWidget(nullptr);
    QLabel* label = new QLabel(widget);
    widget->hide();
    label->setText(text);
    label->setAlignment(align);
    label->show();
    QSize size = label->size();
    label->close();
    widget->close();
    return size;
}
static QSize nativeLabelSize(QLabel* label)
{
    return nativeLabelSize(label->text(),label->alignment());
}
static QObjectList allChildren(QObject* object)
{
    QObjectList list = object->children();
    int old = 0;
    while(list.count() != old)
    {
        old = list.count();
        for(int i = 0;i < list.count();i++)
        {
            QObject* obj = list.at(i);
            for(int j = 0;j < obj->children().count();j++)
            {
                if(!list.contains(obj->children().at(j)))
                    list << obj->children().at(j);
            }
        }
    }
    return list;
}
static QList<int> standardPrimeNumberList()
{
    return QList<int>({1,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,487,491,499,503,509,521,523,541,547,557,563,569,571,577,587,593,599,601,607,613,617,619,631,641,643,647,653,659,661,673,677,683,691,701,709,719,727,733,739,743,751,757,761,769,773,787,797,809,811,821,823,827,829,839,853,857,859,863,877,881,883,887,907,911,919,929,937,941,947,953,967,971,977,983,991,997,1009,1013,1019,1021,1031,1033,1039,1049,1051,1061,1063,1069,1087,1091,1093,1097,1103,1109,1117,1123,1129,1151,1153,1163,1171,1181,1187,1193,1201,1213,1217,1223,1229,1231,1237,1249,1259,1277,1279,1283,1289,1291,1297,1301,1303,1307,1319,1321,1327,1361,1367,1373,1381,1399,1409,1423,1427,1429,1433,1439,1447,1451,1453,1459,1471,1481,1483,1487,1489,1493,1499,1511,1523,1531,1543,1549,1553,1559,1567,1571,1579,1583,1597,1601,1607,1609,1613,1619,1621,1627,1637,1657,1663,1667,1669,1693,1697,1699,1709,1721,1723,1733,1741,1747,1753,1759,1777,1783,1787,1789,1801,1811,1823,1831,1847,1861,1867,1871,1873,1877,1879,1889,1901,1907,1913,1931,1933,1949,1951,1973,1979,1987,1993,1997,1999,2003,2011,2017,2027,2029,2039,2053,2063,2069,2081,2083,2087,2089,2099,2111,2113,2129,2131,2137,2141,2143,2153,2161,2179,2203,2207,2213,2221,2237,2239,2243,2251,2267,2269,2273,2281,2287,2293,2297,2309,2311,2333,2339,2341,2347,2351,2357,2371,2377,2381,2383,2389,2393,2399,2411,2417,2423,2437,2441,2447,2459,2467,2473,2477,2503,2521,2531,2539,2543,2549,2551,2557,2579,2591,2593,2609,2617,2621,2633,2647,2657,2659,2663,2671,2677,2683,2687,2689,2693,2699,2707,2711,2713,2719,2729,2731,2741,2749,2753,2767,2777,2789,2791,2797,2801,2803,2819,2833,2837,2843,2851,2857,2861,2879,2887,2897,2903,2909,2917,2927,2939,2953,2957,2963,2969,2971,2999,3001,3011,3019,3023,3037,3041,3049,3061,3067,3079,3083,3089,3109,3119,3121,3137,3163,3167,3169,3181,3187,3191,3203,3209,3217,3221,3229,3251,3253,3257,3259,3271,3299,3301,3307,3313,3319,3323,3329,3331,3343,3347,3359,3361,3371,3373,3389,3391,3407,3413,3433,3449,3457,3461,3463,3467,3469,3491,3499,3511,3517,3527,3529,3533,3539,3541,3547,3557,3559,3571,3581,3583,3593,3607,3613,3617,3623,3631,3637,3643,3659,3671,3673,3677,3691,3697,3701,3709,3719,3727,3733,3739,3761,3767,3769,3779,3793,3797,3803,3821,3823,3833,3847,3851,3853,3863,3877,3881,3889,3907,3911,3917,3919,3923,3929,3931,3943,3947,3967,3989,4001,4003,4007,4013,4019,4021,4027,4049,4051,4057,4073,4079,4091,4093,4099,4111,4127,4129,4133,4139,4153,4157,4159,4177,4201,4211,4217,4219,4229,4231,4241,4243,4253,4259,4261,4271,4273,4283,4289,4297,4327,4337,4339,4349,4357,4363,4373,4391,4397,4409,4421,4423,4441,4447,4451,4457,4463,4481,4483,4493,4507,4513,4517,4519,4523,4547,4549,4561,4567,4583,4591,4597,4603,4621,4637,4639,4643,4649,4651,4657,4663,4673,4679,4691,4703,4721,4723,4729,4733,4751,4759,4783,4787,4789,4793,4799,4801,4813,4817,4831,4861,4871,4877,4889,4903,4909,4919,4931,4933,4937,4943,4951,4957,4967,4969,4973,4987,4993,4999,5003,5009,5011,5021,5023,5039,5051,5059,5077,5081,5087,5099,5101,5107,5113,5119,5147,5153,5167,5171,5179,5189,5197,5209,5227,5231,5233,5237,5261,5273,5279,5281,5297,5303,5309,5323,5333,5347,5351,5381,5387,5393,5399,5407,5413,5417,5419,5431,5437,5441,5443,5449,5471,5477,5479,5483,5501,5503,5507,5519,5521,5527,5531,5557,5563,5569,5573,5581,5591,5623,5639,5641,5647,5651,5653,5657,5659,5669,5683,5689,5693,5701,5711,5717,5737,5741,5743,5749,5779,5783,5791,5801,5807,5813,5821,5827,5839,5843,5849,5851,5857,5861,5867,5869,5879,5881,5897,5903,5923,5927,5939,5953,5981,5987,6007,6011,6029,6037,6043,6047,6053,6067,6073,6079,6089,6091,6101,6113,6121,6131,6133,6143,6151,6163,6173,6197,6199,6203,6211,6217,6221,6229,6247,6257,6263,6269,6271,6277,6287,6299,6301,6311,6317,6323,6329,6337,6343,6353,6359,6361,6367,6373,6379,6389,6397,6421,6427,6449,6451,6469,6473,6481,6491,6521,6529,6547,6551,6553,6563,6569,6571,6577,6581,6599,6607,6619,6637,6653,6659,6661,6673,6679,6689,6691,6701,6703,6709,6719,6733,6737,6761,6763,6779,6781,6791,6793,6803,6823,6827,6829,6833,6841,6857,6863,6869,6871,6883,6899,6907,6911,6917,6947,6949,6959,6961,6967,6971,6977,6983,6991,6997,7001,7013,7019,7027,7039,7043,7057,7069,7079,7103,7109,7121,7127,7129,7151,7159,7177,7187,7193,7207,7211,7213,7219,7229,7237,7243,7247,7253,7283,7297,7307,7309,7321,7331,7333,7349,7351,7369,7393,7411,7417,7433,7451,7457,7459,7477,7481,7487,7489,7499,7507,7517,7523,7529,7537,7541,7547,7549,7559,7561,7573,7577,7583,7589,7591,7603,7607,7621,7639,7643,7649,7669,7673,7681,7687,7691,7699,7703,7717,7723,7727,7741,7753,7757,7759,7789,7793,7817,7823,7829,7841,7853,7867,7873,7877,7879,7883,7901,7907,7919,7927,7933,7937,7949,7951,7963,7993,8009,8011,8017,8039,8053,8059,8069,8081,8087,8089,8093,8101,8111,8117,8123,8147,8161,8167,8171,8179,8191,8209,8219,8221,8231,8233,8237,8243,8263,8269,8273,8287,8291,8293,8297,8311,8317,8329,8353,8363,8369,8377,8387,8389,8419,8423,8429,8431,8443,8447,8461,8467,8501,8513,8521,8527,8537,8539,8543,8563,8573,8581,8597,8599,8609,8623,8627,8629,8641,8647,8663,8669,8677,8681,8689,8693,8699,8707,8713,8719,8731,8737,8741,8747,8753,8761,8779,8783,8803,8807,8819,8821,8831,8837,8839,8849,8861,8863,8867,8887,8893,8923,8929,8933,8941,8951,8963,8969,8971,8999,9001,9007,9011,9013,9029,9041,9043,9049,9059,9067,9091,9103,9109,9127,9133,9137,9151,9157,9161,9173,9181,9187,9199,9203,9209,9221,9227,9239,9241,9257,9277,9281,9283,9293,9311,9319,9323,9337,9341,9343,9349,9371,9377,9391,9397,9403,9413,9419,9421,9431,9433,9437,9439,9461,9463,9467,9473,9479,9491,9497,9511,9521,9533,9539,9547,9551,9587,9601,9613,9619,9623,9629,9631,9643,9649,9661,9677,9679,9689,9697,9719,9721,9733,9739,9743,9749,9767,9769,9781,9787,9791,9803,9811,9817,9829,9833,9839,9851,9857,9859,9871,9883,9887,9901,9907,9923,9929,9931,9941,9949,9967,9973});
}
static bool isPrimeNumber(int num)
{
    if(num != num)
        return false;
    if(num <= 0)
        return false;
    if(QList<int>({1,2,3,5,7,11,13}).contains(num))
        return true;
    QString str = QString::number(num);
    int end = str.right(1).toInt();
    if(end == 2 || end == 4 || end == 5 || end == 6 || end == 8 || end == 0)
        return false;
    else if(num%3 == 0 || num%7 == 0 || num%11 == 0)
        return false;

    if(standardPrimeNumberList().contains(num))
        return true;

    bool ret = true;
    int current = 13;
    double half = double(num)/2.0;
    while(ret && double(current) < half && current < num && current <= 2147483647)
    {
        int end1 = QString::number(current).right(1).toInt();
        if(end1 != 0 && end1 != 2 && end1 != 4 && end1 != 5 && end1 != 6 && end1 != 8)
        {
            ret = (num%current != 0);
        }
        current++;
    }
    return ret;
}
static QString getNextWord(QString w)
{
    if(w == "A")
        return "B";
    if(w == "B")
        return "C";
    if(w == "C")
        return "D";
    if(w == "D")
        return "E";
    if(w == "E")
        return "F";
    if(w == "F")
        return "G";
    if(w == "G")
        return "H";
    if(w == "H")
        return "I";
    if(w == "I")
        return "J";
    if(w == "J")
        return "K";
    if(w == "K")
        return "L";
    if(w == "L")
        return "M";
    if(w == "M")
        return "N";
    if(w == "N")
        return "O";
    if(w == "O")
        return "P";
    if(w == "P")
        return "Q";
    if(w == "Q")
        return "R";
    if(w == "R")
        return "S";
    if(w == "S")
        return "T";
    if(w == "T")
        return "U";
    if(w == "U")
        return "V";
    if(w == "V")
        return "W";
    if(w == "W")
        return "X";
    if(w == "X")
        return "Y";
    if(w == "Y")
        return "Z";
    if(w == "Z")
        return "";
    if(w == "a")
        return "b";
    if(w == "b")
        return "c";
    if(w == "c")
        return "d";
    if(w == "d")
        return "e";
    if(w == "e")
        return "f";
    if(w == "f")
        return "g";
    if(w == "g")
        return "h";
    if(w == "h")
        return "i";
    if(w == "i")
        return "j";
    if(w == "j")
        return "k";
    if(w == "k")
        return "l";
    if(w == "l")
        return "m";
    if(w == "m")
        return "n";
    if(w == "n")
        return "o";
    if(w == "o")
        return "p";
    if(w == "p")
        return "q";
    if(w == "q")
        return "r";
    if(w == "r")
        return "s";
    if(w == "s")
        return "t";
    if(w == "t")
        return "u";
    if(w == "u")
        return "v";
    if(w == "v")
        return "w";
    if(w == "w")
        return "x";
    if(w == "x")
        return "y";
    if(w == "y")
        return "z";
    if(w == "z")
        return "";
    return "";
}
static int getLongestStringIndex(QStringList list)
{
    int index = 0;
    int maxlength = -1;
    int result = -1;
    while(index < list.count())
    {
        int currentlength = list.at(index).length();
        if(currentlength > maxlength)
        {
            maxlength = currentlength;
            result = index;
        }
        index++;
    }
    return result;
}
static QStringList toStringList(QList<QByteArray> list)
{
    QStringList ret;
    for(QByteArray byte : list)
    {
        ret << QString(byte);
    }
    return ret;
}
static QString toString(bool b)
{
    if(b == true)
        return QString("true");
    else
        return QString("false");
}
static bool isBool(QString s)
{
    if(s == "true" || s == "false")
        return true;
    else
        return false;
}
static bool toBool(QString s)
{
    if(s == "true")
        return true;
    else if(s == "false")
        return false;
    else
        return bool(s.toInt());
}

//Qt For Android 函数   依赖Qt模块:core-private
#define javaPackage "com/MyActivity/MainActivity"
#ifdef Use_Plaform_Namespace
namespace Android {
#endif
#ifndef Q_OS_ANDROID
typedef int QJniObject;
typedef int QJniEnvironment;
#endif
#if QT_VERSION_MAJOR == 5
typedef QAndroidJniObject QJniObject;
typedef QAndroidJniEnvironment QJniEnvironment;
#endif
static void showNativeToast(const QString &message,bool waitforfinished = false)//调用Android Toast
{
#ifdef Q_OS_ANDROID
    /*
    QJniObject javaToast = QJniObject::fromString(message);
    QJniObject::callStaticMethod<void>(javaPackage,
                                           "makeToast",
                                           "(Ljava/lang/String;)V",
                                           javaToast.object<jstring>());
                                           */
    QFuture<void> f = QNativeInterface::QAndroidApplication::runOnAndroidMainThread([message](){
        QJniObject context = QtAndroidPrivate::activity();
        QJniObject javaString = QJniObject::fromString(message);
        QJniObject toast = QJniObject::callStaticObjectMethod("android/widget/Toast", "makeText","(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;",context.object(),javaString.object<jstring>(),jint(0));
        toast.callMethod<void>("show");
    });
    if(waitforfinished)
    {
        f.waitForFinished();
    }
#else
    qDebug() << message;
#endif
}
static QString getPackageName()//获取应用的包名
{
    QString packageName = "";
#ifdef Q_OS_ANDROID
#ifdef Core_Private_Enabled
    QJniObject context = QtAndroidPrivate::context();
    QJniObject packageNameObject = context.callObjectMethod("getPackageName", "()Ljava/lang/String;");
    if (packageNameObject.isValid())
    {
         packageName = packageNameObject.toString();
    }
#else
    QString path = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation).replace("\\","/");
    if(path.endsWith("/"))
        path.chop(1);
    while(!path.endsWith("/"))
        path.chop(1);
    packageName = QDir(path).dirName();
#endif
#endif
    return packageName;
}
static int getSystemVersion()//获取Android系统的版本
{
    int androidSdkVersion = -1;
#ifdef Q_OS_ANDROID
    QJniObject context = QtAndroidPrivate::context();
    QJniObject sdkVersion = QJniObject::getStaticObjectField<jstring>("android/os/Build$VERSION", "RELEASE");
    if (sdkVersion.isValid())
    {
        androidSdkVersion = QJniObject::callStaticMethod<jint>("java/lang/Integer", "parseInt", "(Ljava/lang/String;)I", sdkVersion.object<jstring>());
    }
    if(androidSdkVersion == 0)
    {
        QJniEnvironment env;
        QJniObject sdkVersion = QJniObject::getStaticObjectField<jstring>("android/os/Build$VERSION", "RELEASE");
        if (sdkVersion.isValid())
        {
            std::string version = env->GetStringUTFChars(static_cast<jstring>(sdkVersion.object()), nullptr);
            androidSdkVersion = std::stoi(version);
        }
    }
#endif
    return androidSdkVersion;
}
static int getSdkVersion()//获取Android SDK版本
{
    int sdkversion = -1;
#ifdef Q_OS_ANDROID
    sdkversion = QJniObject::getStaticField<jint>("android.os.Build$VERSION", "SDK_INT");
#endif
    return sdkversion;
}
static int getTargetSdkVersion(QString packageName = getPackageName())
{
#ifdef Q_OS_ANDROID
    QJniObject packageManager = QJniObject(QtAndroidPrivate::activity()).callObjectMethod("getPackageManager", "()Landroid/content/pm/PackageManager;");
    QJniObject applicationInfo = packageManager.callObjectMethod("getApplicationInfo", "(Ljava/lang/String;I)Landroid/content/pm/ApplicationInfo;", QJniObject::fromString(packageName).object<jobject>(), 0);
    return applicationInfo.getField<jint>("targetSdkVersion");
#else
    return -1;
#endif
}
static QString getRealPathFromUri(const QUrl &url)//将Android文件uri转换为真实的文件路径
{
    QString path = "";

#ifdef Q_OS_ANDROID
    QJniObject jUrl = QJniObject::fromString(url.toString());
    QJniObject jContext = QtAndroidPrivate::context();
    QJniObject jContentResolver = jContext.callObjectMethod("getContentResolver", "()Landroid/content/ContentResolver;");
    QJniObject jUri = QJniObject::callStaticObjectMethod("android/net/Uri", "parse", "(Ljava/lang/String;)Landroid/net/Uri;", jUrl.object<jstring>());
    QJniObject jCursor = jContentResolver.callObjectMethod("query", "(Landroid/net/Uri;[Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;Ljava/lang/String;)Landroid/database/Cursor;", jUri.object<jobject>(), nullptr, nullptr, nullptr, nullptr);
    if (jCursor.isValid() && jCursor.callMethod<jboolean>("moveToFirst"))
    {
        QJniObject jColumnIndex = QJniObject::fromString("_data");
        jint columnIndex = jCursor.callMethod<jint>("getColumnIndexOrThrow", "(Ljava/lang/String;)I", jColumnIndex.object<jstring>());
        QJniObject jRealPath = jCursor.callObjectMethod("getString", "(I)Ljava/lang/String;", columnIndex);
        path = jRealPath.toString();
    }
    else
    {
        QJniObject jScheme = jUri.callObjectMethod("getScheme", "()Ljava/lang/String;");
        if (jScheme.isValid())
        {
            if(jScheme.toString() == "content" || jScheme.toString() == "file")
            {
                QJniObject jPath = jUri.callObjectMethod("getPath", "()Ljava/lang/String;");
                path = jPath.toString();
            }
        }
    }
    if(path.startsWith("primary:"))
    {
        path = path.remove(0,QString("primary:").length());
        path = "/sdcard/" + path;
        //path = "/storage/emulated/0/" + path;
    }
    else if(path.startsWith("/document/primary:"))
    {
        path = path.remove(0,QString("/document/primary:").length());
        path = "/sdcard/" + path;
        //path = "/storage/emulated/0/" + path;
    }
    else if(path.startsWith("/tree/primary:"))
    {
        path = path.remove(0,QString("/tree/primary:").length());
        path = "/sdcard/" + path;
        //path = "/storage/emulated/0/" + path;
    }
    return path;
#else
    return url.toString();
#endif

}
static void startIntent(QString IntentString,bool append = false,bool waitforfinished = false,bool usejni = false)
{
/*
android.settings.MANAGE_ALL_FILES_ACCESS_PERMISSION 所有文件权限
android.settings.action.MANAGE_OVERLAY_PERMISSION 悬浮窗
*/
#ifdef Q_OS_ANDROID
    QEventLoop* loop = new QEventLoop();
    //bool usejni = false;

    int a = 0;
    if(append == true)
        a = 1;

    if(IntentString.startsWith("ACTION_"))
    {
        IntentString = "android.settings." + IntentString.remove(0,QString("ACTION_").length());
    }
    if(IntentString == "android.settings.MANAGE_ALL_FILES_ACCESS_PERMISSION" && a == 1)
        IntentString = "android.settings.MANAGE_APP_ALL_FILES_ACCESS_PERMISSION";
    if(IntentString == "android.settings.MANAGE_APP_ALL_FILES_ACCESS_PERMISSION" && a == 0)
        IntentString = "android.settings.MANAGE_ALL_FILES_ACCESS_PERMISSION";

    QJniObject ACTION = QJniObject::fromString(IntentString);
#ifndef Android_Activity_Enabled
    QJniObject intent("android/content/Intent");
    //QJniObject ACTION = QJniObject::getStaticObjectField("android.provider.Settings", IntentString.toLatin1().data() , "Ljava/lang/String;");
    intent.callObjectMethod("setAction", "(Ljava/lang/String;)Landroid/content/Intent;", ACTION.object());
    if(a == 1)
    {
        QJniObject uri = QJniObject::callStaticObjectMethod("android/net/Uri", "parse", "(Ljava/lang/String;)Landroid/net/Uri;", QJniObject::fromString("package:" + AndroidPackageName()).object());
        intent.callObjectMethod("setData", "(Landroid/net/Uri;)Landroid/content/Intent;", uri.object());
    }

    if(waitforfinished == true)
    {
        auto callbackFunc = [loop](int requestCode, int resultCode, const QJniObject &data){
            loop->quit();
        };
        QtAndroidPrivate::startActivity(intent,0,callbackFunc);
        loop->exec();
    }
    else
    {
        QtAndroidPrivate::startActivity(intent,0);
    }
#else
    if(usejni == true)
    {
        QJniObject activity = QtAndroidPrivate::activity();
        QJniObject::callStaticMethod<void>(javaPackage,"startIntent","(Landroid/app/Activity;Ljava/lang/String;I)V",activity.object<jobject>(),ACTION.object<jstring>(),a);
    }
    else
    {
        QJniObject intent("android/content/Intent");
        intent.callObjectMethod("setAction", "(Ljava/lang/String;)Landroid/content/Intent;", ACTION.object());
        if(a == 1)
        {
            QJniObject uri = QJniObject::callStaticObjectMethod("android/net/Uri", "parse", "(Ljava/lang/String;)Landroid/net/Uri;", QJniObject::fromString("package:" + getPackageName()).object());
            intent.callObjectMethod("setData", "(Landroid/net/Uri;)Landroid/content/Intent;", uri.object());
        }

        if(waitforfinished == true)
        {
            auto callbackFunc = [loop](int requestCode, int resultCode, const QJniObject &data){
                loop->quit();
            };
            QtAndroidPrivate::startActivity(intent,0,callbackFunc);
            loop->exec();
        }
        else
        {
            QtAndroidPrivate::startActivity(intent,0);
        }
    }
#endif
#endif
}
static void shareFile(const QString &filePath)//分享文件
{
#ifdef Q_OS_ANDROID
    QJniObject javaFile = QJniObject::fromString(filePath);
    QJniObject intent("android/content/Intent");
    QJniObject action = QJniObject::getStaticObjectField("android/content/Intent", "ACTION_SEND", "Ljava/lang/String;");
    intent.callObjectMethod("setAction", "(Ljava/lang/String;)Landroid/content/Intent;", action.object<jstring>());

    QJniObject uri = QJniObject::callStaticObjectMethod("android/net/Uri", "parse", "(Ljava/lang/String;)Landroid/net/Uri;", javaFile.object<jstring>());
    QJniObject type = QJniObject::fromString("application/*");
    intent.callObjectMethod("setType", "(Ljava/lang/String;)Landroid/content/Intent;", type.object<jstring>());
    intent.callObjectMethod("putExtra", "(Ljava/lang/String;Landroid/os/Parcelable;)Landroid/content/Intent;", QJniObject::fromString("android.intent.extra.STREAM").object<jstring>(), uri.object<jobject>());

    QtAndroidPrivate::startActivity(intent, 0);
#else
    qDebug() << "File sharing is not available on non-Android device : shareFile(\"" + filePath + "\")";
#endif
}
static void setScreenOrientation(int orientation = -1)
{
#ifdef Q_OS_ANDROID
    QJniObject activity = QtAndroidPrivate::activity();
    if (activity.isValid())
    {
        if(orientation == Qt::LandscapeOrientation || orientation == 0)//横
        {
            activity.callMethod<void>("setRequestedOrientation", "(I)V", 0);
        }
        else if(orientation == Qt::PortraitOrientation || orientation == 1)//竖
        {
            activity.callMethod<void>("setRequestedOrientation", "(I)V", 1);
        }
        else if(orientation == Qt::PrimaryOrientation || orientation == -1)//自由
        {
            activity.callMethod<void>("setRequestedOrientation", "(I)V", 2);
        }
        else
        {
            activity.callMethod<void>("setRequestedOrientation", "(I)V", orientation);
        }
    }
#endif
}
static QString getModel()
{
#ifdef Q_OS_ANDROID
    QJniObject build = QJniObject::getStaticObjectField(
        "android/os/Build",
        "MODEL",
        "Ljava/lang/String;"
    );
    return build.toString();
#else
    return QString();
#endif
}
static QString getBrand()
{
#ifdef Q_OS_ANDROID
    QJniObject build = QJniObject::getStaticObjectField(
        "android/os/Build",
        "BRAND",
        "Ljava/lang/String;"
    );
    return build.toString();
#else
    return QString();
#endif
}
static bool checkPermission(QString permissionString)
{
#ifdef Q_OS_ANDROID
    QFuture<QtAndroidPrivate::PermissionResult> f = QtAndroidPrivate::checkPermission(permissionString);
    f.waitForFinished();
    return (f.result() == QtAndroidPrivate::PermissionResult::Authorized);
#else
    return false;
#endif
}
static bool requestPermission(QString permissionString)
{
#ifdef Q_OS_ANDROID
    QFuture<QtAndroidPrivate::PermissionResult> f = QtAndroidPrivate::requestPermission(permissionString);
    f.waitForFinished();
    return (f.result() == QtAndroidPrivate::PermissionResult::Authorized);
#else
    return false;
#endif
}
static bool hasStroagePermission()
{
#ifdef Q_OS_ANDROID
    if(!hasPathPermission("/sdcard") || !checkPermission("android.permission.WRITE_EXTERNAL_STORAGE"))
        return false;
    else
        return true;
#else
    return true;
#endif
}
static bool requestStroagePermission()
{
#ifdef Q_OS_ANDROID
    if(hasFilePermission("/sdcard",QIODevice::ReadWrite))
        return true;
    requestPermission("android.permission.READ_MEDIA_VIDEO");
    requestPermission("android.permission.READ_MEDIA_IMAGES");
    requestPermission("android.permission.READ_MEDIA_AUDIO");
    requestPermission("android.permission.READ_EXTERNAL_STORAGE");
    requestPermission("android.permission.WRITE_EXTERNAL_STORAGE");
    startIntent("android.settings.MANAGE_ALL_FILES_ACCESS_PERMISSION",true,true);
    return hasPathPermission("/sdcard");
#else
#ifdef Q_OS_WIN
    return hasPathPermission("C:/");
#else
    return true;
#endif
#endif
}
static bool saveMediaToAlbum(QString mediaFilePath)
{
#ifdef Q_OS_ANDROID
    if(QFile::exists(mediaFilePath))
    {
        QJniEnvironment env;
        QJniObject javaFilePath = QJniObject::fromString(mediaFilePath);
        jobjectArray javaFilePathArray = env->NewObjectArray(1, env->FindClass("java/lang/String"), nullptr);
        env->SetObjectArrayElement(javaFilePathArray, 0, javaFilePath.object<jstring>());

        QJniObject mediaScanner("android/media/MediaScannerConnection");
        mediaScanner.callStaticMethod<void>("android/media/MediaScannerConnection","scanFile", "(Landroid/content/Context;[Ljava/lang/String;[Ljava/lang/String;Landroid/media/MediaScannerConnection$OnScanCompletedListener;)V",
                                            QJniObject(QtAndroidPrivate::context()).object(),
                                            javaFilePathArray,
                                            nullptr, nullptr);
        return true;
    }
    else
    {
        return false;
    }
#else
    return false;
#endif
}
static QStringList getInstalledPackageList()
{
    QStringList list;
#ifdef Q_OS_ANDROID
    QJniObject context = QtAndroidPrivate::context();
    QJniObject packageManager = context.callObjectMethod("getPackageManager", "()Landroid/content/pm/PackageManager;");
    int flags = QJniObject::getStaticField<jint>("android/content/pm/PackageManager", "MATCH_UNINSTALLED_PACKAGES");
    QJniObject installedPackageInfoList = packageManager.callObjectMethod("getInstalledPackages", "(I)Ljava/util/List;", flags);
    jint packageCount = installedPackageInfoList.callMethod<jint>("size");
    for(jint i = 0; i < packageCount; ++i)
    {
        QJniObject packageInfo = installedPackageInfoList.callObjectMethod("get", "(I)Ljava/lang/Object;", i);
        QJniObject packageName = packageInfo.getObjectField("packageName", "Ljava/lang/String;");
        QString packageNameStr = packageName.toString();
        list << packageNameStr;
    }
#endif
    return list;
}
static bool startApplication(QString packageName,QString activityName = "")
{
    /*
    com.mojang.minecraftpe com.mojang.minecraftpe.MainActivity
    Minecraft PE package name and activity name for test
    */
#ifdef Q_OS_ANDROID
    QJniObject intent("android/content/Intent");
    if(intent.isValid() && packageName != "" && getInstalledPackageList().contains(packageName))
    {
        if(activityName == "")
        {
            QJniObject activity = QtAndroidPrivate::activity();
            QJniObject packageManager = activity.callObjectMethod("getPackageManager", "()Landroid/content/pm/PackageManager;");
            intent = packageManager.callObjectMethod("getLaunchIntentForPackage", "(Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString(packageName).object<jstring>());
        }
        else
        {
            intent.callObjectMethod("setAction", "(Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString("android.intent.action.MAIN").object<jstring>());
            intent.callObjectMethod("setClassName", "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString(packageName).object<jstring>(), QJniObject::fromString(activityName).object<jstring>());
            intent.callObjectMethod("putExtra", "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString(packageName).object<jstring>(), QJniObject::fromString(activityName).object<jstring>());
            intent.callObjectMethod("addCategory", "(Ljava/lang/String;)Landroid/content/Intent;", QJniObject::fromString("android.intent.category.LAUNCHER").object<jstring>());
            intent.callObjectMethod("setFlags", "(I)Landroid/content/Intent;", QJniObject::getStaticField<jint>("android/content/Intent", "FLAG_ACTIVITY_NEW_TASK"));
        }

        QEventLoop* loop = new QEventLoop();
        auto callbackFunc = [loop](int requestCode, int resultCode, const QJniObject &data){
            //qDebug() << requestCode << " " << resultCode << "\n" << data.toString() << " " << (data==QJniObject());
            loop->quit();
        };
        QtAndroidPrivate::startActivity(intent, 0, callbackFunc);
        loop->exec();
        return true;
    }
    else
    {
        return false;
    }
#else
    return false;
#endif
}
static bool setNotification(QString title,QString content,bool autocancel = true,bool ongoing = true)
{
#if defined(Q_OS_ANDROID) && defined(Android_Activity_Enabled)
    QJniObject activity = QtAndroidPrivate::activity();
    //QJniObject context = QtAndroidPrivate::context();
    //QJniObject context = QNativeInterface::QAndroidApplication::context();
    QJniObject::callStaticMethod<void>(javaPackage,
                                                  "setNotification",
                                                  "(Landroid/app/Activity;Ljava/lang/String;Ljava/lang/String;ZZ)V",
                                                  activity.object<jobject>(),
                                                  QJniObject::fromString(title).object<jstring>(),
                                                  QJniObject::fromString(content).object<jstring>(),
                                                  autocancel,
                                                  ongoing);
    return true;
#else
    return false;
#endif
}
static QJniObject createBitmap(int width,int height)
{
#ifdef Q_OS_ANDROID
    QJniObject config = QJniObject::getStaticObjectField("android/graphics/Bitmap$Config",
                                                                           "ARGB_8888",
                                                                           "Landroid/graphics/Bitmap$Config;");

    return QJniObject::callStaticObjectMethod("android/graphics/Bitmap",
                                                         "createBitmap",
                                                         "(IILandroid/graphics/Bitmap$Config;)Landroid/graphics/Bitmap;",
                                                         width, height, config.object());
#else
    return 0;
#endif
}
static QJniObject createBitmap(QSize size) {return createBitmap(size.width(),size.height());}
static bool isApplicationUsingDefaultIcon(QString packageName = getPackageName())
{
#ifdef Q_OS_ANDROID
    QJniObject packageManager = QJniObject(QtAndroidPrivate::activity()).callObjectMethod("getPackageManager", "()Landroid/content/pm/PackageManager;");
    QJniObject applicationInfo = packageManager.callObjectMethod("getApplicationInfo", "(Ljava/lang/String;I)Landroid/content/pm/ApplicationInfo;", QJniObject::fromString(packageName).object<jobject>(), 0);
    jint iconId = applicationInfo.getField<jint>("icon");
    return (iconId == 0);
#else
    return false;
#endif
}
static QJniObject drawableToAndroidBitmap(QJniObject drawable)
{
#ifdef Q_OS_ANDROID
    jint intrinsicWidth = drawable.callMethod<jint>("getIntrinsicWidth");
    jint intrinsicHeight = drawable.callMethod<jint>("getIntrinsicHeight");
    QJniObject bitmap = createBitmap(intrinsicWidth,intrinsicHeight);
    QJniObject canvas("android/graphics/Canvas", "(Landroid/graphics/Bitmap;)V", bitmap.object<jobject>());
    QJniObject boundsRect("android/graphics/Rect", "(IIII)V", 0, 0, intrinsicWidth, intrinsicHeight);
    drawable.callMethod<void>("setBounds", "(Landroid/graphics/Rect;)V", boundsRect.object());
    drawable.callMethod<void>("draw", "(Landroid/graphics/Canvas;)V", canvas.object());
    return bitmap;
#else
    return 0;
#endif
}
static QJniObject getApplicationDefaultIconObject()
{
#ifdef Q_OS_ANDROID
    jint iconId = QJniObject::getStaticField<jint>("android/R$drawable", "sym_def_app_icon");
    QJniObject drawable = QJniObject(QtAndroidPrivate::activity()).callObjectMethod("getResources", "()Landroid/content/res/Resources;").callObjectMethod("getDrawable", "(I)Landroid/graphics/drawable/Drawable;", iconId);
    return drawableToAndroidBitmap(drawable);
#else
    return 0;
#endif
}
static QJniObject getApplicationIconObject(QString packageName = getPackageName()) {
#ifdef Q_OS_ANDROID
    if(isApplicationUsingDefaultIcon(packageName))
    {
        return getApplicationDefaultIconObject();
    }
    else
    {
        QJniObject packageManager = QJniObject(QtAndroidPrivate::activity()).callObjectMethod("getPackageManager", "()Landroid/content/pm/PackageManager;");
        QJniObject applicationInfo = packageManager.callObjectMethod("getApplicationInfo", "(Ljava/lang/String;I)Landroid/content/pm/ApplicationInfo;", QJniObject::fromString(packageName).object<jobject>(), 0);
        QJniObject drawable = packageManager.callObjectMethod("getApplicationIcon","(Landroid/content/pm/ApplicationInfo;)Landroid/graphics/drawable/Drawable;",applicationInfo.object<jobject>());
        return drawableToAndroidBitmap(drawable);
    }
#else
    return 0;
#endif
}
static QImage toImage(const QJniObject &bitmap)
{
#ifdef Q_OS_ANDROID
    QJniEnvironment qenv;
    JNIEnv* env = qenv.jniEnv();
    AndroidBitmapInfo info;
    if (AndroidBitmap_getInfo(env, bitmap.object(), &info) != ANDROID_BITMAP_RESULT_SUCCESS)
        return QImage();

    QImage::Format format;
    switch (info.format) {
    case ANDROID_BITMAP_FORMAT_RGBA_8888:
        format = QImage::Format_RGBA8888;
        break;
    case ANDROID_BITMAP_FORMAT_RGB_565:
        format = QImage::Format_RGB16;
        break;
    case ANDROID_BITMAP_FORMAT_RGBA_4444:
        format = QImage::Format_ARGB4444_Premultiplied;
        break;
    case ANDROID_BITMAP_FORMAT_A_8:
        format = QImage::Format_Alpha8;
        break;
    default:
        return QImage();
    }

    void *pixels;
    if (AndroidBitmap_lockPixels(env, bitmap.object(), &pixels) != ANDROID_BITMAP_RESULT_SUCCESS)
        return QImage();

    QImage image(info.width, info.height, format);

    if (info.stride == uint32_t(image.bytesPerLine())) {
        memcpy((void*)image.constBits(), pixels, info.stride * info.height);
    } else {
        uchar *bmpPtr = static_cast<uchar *>(pixels);
        const unsigned width = std::min(info.width, (uint)image.width());
        const unsigned height = std::min(info.height, (uint)image.height());
        for (unsigned y = 0; y < height; y++, bmpPtr += info.stride)
            memcpy((void*)image.constScanLine(y), bmpPtr, width);
    }

    if (AndroidBitmap_unlockPixels(env, bitmap.object()) != ANDROID_BITMAP_RESULT_SUCCESS)
        return QImage();

    image.convertedTo(QImage::Format_RGBA8888);
    return image;
#else
    return QImage();
#endif
}
static QImage getApplicationIcon(QString packageName = getPackageName()) {return toImage(getApplicationIconObject(packageName));}
static QImage getApplicationDefaultIcon() {return toImage(getApplicationDefaultIconObject());}
static QJniObject toAndroidBitmap(const QImage &img)
{
#ifdef Q_OS_ANDROID
    QImage image = img.format() == QImage::Format_RGBA8888 ? img : img.convertToFormat(QImage::Format_RGBA8888);
    QJniObject bitmap = createBitmap(img.width(), img.height());
    QJniEnvironment qenv;
    JNIEnv* env = qenv.jniEnv();
    AndroidBitmapInfo info;
    if (AndroidBitmap_getInfo(env, bitmap.object(), &info) != ANDROID_BITMAP_RESULT_SUCCESS)
        return QJniObject();

    if (info.format!= ANDROID_BITMAP_FORMAT_RGBA_8888)
        return QJniObject();

    void *pixels;
    if (AndroidBitmap_lockPixels(env, bitmap.object(), &pixels) != ANDROID_BITMAP_RESULT_SUCCESS)
        return QJniObject();

    if (info.stride == uint32_t(image.bytesPerLine())) {
        memcpy(pixels, image.constBits(), info.stride * info.height);
    } else {
        uchar *bmpPtr = static_cast<uchar *>(pixels);
        const unsigned width = std::min(info.width, (uint)image.width());
        const unsigned height = std::min(info.height, (uint)image.height());
        for (unsigned y = 0; y < height; y++, bmpPtr += info.stride)
            memcpy(bmpPtr, image.constScanLine(y), width);
    }

    if (AndroidBitmap_unlockPixels(env, bitmap.object()) != ANDROID_BITMAP_RESULT_SUCCESS)
        return QJniObject();

    return bitmap;
#else
    return 0;
#endif
}
static bool registerJNINativeMethod(const char* name,const char* signature,void* callBackPointer)
{
#ifdef Q_OS_ANDROID
    static JNINativeMethod methods[] {
    { name, signature, callBackPointer}
    };
    const char* kClassName = javaPackage;
    QJniEnvironment qtEnv;
    jclass clazz;
    JNIEnv *EV = qtEnv.operator ->();
    if(EV->ExceptionCheck())
    {
        EV->ExceptionDescribe();
        EV->ExceptionClear();
    }
    clazz =EV->FindClass(kClassName);
    if(clazz != NULL)
    {
        int i = EV->RegisterNatives(clazz, methods, 1);
        if(i == JNI_OK)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
#else
    return false;
#endif
}
static void setKeepScreenOn(bool on)
{
#ifdef Q_OS_ANDROID
    QNativeInterface::QAndroidApplication::runOnAndroidMainThread([on](){
        QJniObject activity = QtAndroidPrivate::activity();
        QJniObject window = activity.callObjectMethod("getWindow", "()Landroid/view/Window;");
        jint flags = QJniObject::getStaticField<jint>("android/view/WindowManager$LayoutParams", "FLAG_KEEP_SCREEN_ON");
        if(on)
            window.callMethod<void>("addFlags", "(I)V", flags);
        else
            window.callMethod<void>("clearFlags", "(I)V", flags);
    });
#endif
}
#ifdef Use_Plaform_Namespace
}
#endif

//Qt For Windows 函数
#ifdef Use_Plaform_Namespace
namespace Windows {
#endif
static int getProcessAmount(QString name)
{
#ifdef Q_OS_WIN
    QProcess* process = new QProcess;
    process->start("tasklist" ,QStringList()<<"/FI"<<"imagename eq "+name);
    process->waitForFinished();
    QString outputStr = QString::fromLocal8Bit(process->readAllStandardOutput());
    return getContainStringTimes(outputStr,name);
#else
    return -1;
#endif
}
static int killExecute(const QString& exe)
{
#ifdef Q_OS_WIN
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hProcessSnap == INVALID_HANDLE_VALUE)
    {
        return -1;
    }
    pe32.dwSize = sizeof(PROCESSENTRY32);
    if (!Process32First(hProcessSnap, &pe32))
    {
        CloseHandle(hProcessSnap);
        return -1;
    }
    BOOL bRet = FALSE;
    DWORD dwPid = -1;
    while (Process32Next(hProcessSnap, &pe32))
    {
        int iLn = WideCharToMultiByte (CP_UTF8, 0, const_cast<LPWSTR> (pe32.szExeFile), static_cast< int>( sizeof(pe32.szExeFile)), NULL, 0, NULL, NULL);
        std:: string result (iLn, 0);
        WideCharToMultiByte (CP_UTF8, 0, pe32.szExeFile, static_cast< int>( sizeof(pe32.szExeFile)), const_cast<LPSTR> (result.c_str()), iLn, NULL, NULL);
        if(0 == strcmp(exe.toStdString().c_str(), result.c_str ()))
        {
            dwPid = pe32.th32ProcessID;
            bRet = TRUE;
            break;
        }
    }
    CloseHandle(hProcessSnap);
    //qDebug()<< "已终止进程,PID为" <<dwPid;
    HANDLE hProcess = NULL;
    hProcess = OpenProcess(PROCESS_TERMINATE,FALSE,dwPid);
    if (hProcess== NULL)
    {
        return -1;
    }
    DWORD ret = TerminateProcess(hProcess, 0);
    if(ret == 0)
    {
        return -1;
    }
    return static_cast<int>(dwPid);
#else
    return -1;
#endif
}
static void showTabTip()
{

#ifdef Q_OS_WIN
    bool ret = false;
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);
    char* windir = getenv("windir");
    char winroot = 'c';
    if (!windir || strcmp(windir, ""))
    {
        winroot = windir[0];
    }
    char tabtip[260];
    char tabtipworksp[260];
    qDebug() << osvi.dwMajorVersion;
    if (osvi.dwMajorVersion <= 5)
    {
        // XP
        sprintf(tabtip, "%c:\\Windows\\System32\\osk.exe ", winroot);
        sprintf(tabtipworksp, "%c:\\Windows\\System32", winroot);
        ret = QProcess::startDetached(tabtip, QStringList(), tabtipworksp);
    }
    else if (osvi.dwMajorVersion >= 6)
    {
        if (osvi.dwMinorVersion >= 2)
        {
            //qDebug() << "???";
            // win8, win8.1, Windows Server 2012
            PVOID OldValue;
            BOOL bRet = Wow64DisableWow64FsRedirection(&OldValue);
            ShellExecuteA(NULL, "open", "osk.exe", 0, 0, SW_SHOW);
            if (bRet)
            {
                Wow64RevertWow64FsRedirection(OldValue);
            }
            return;
        }
        // vista win7
        sprintf(tabtip, "%c:\\Program Files\\Common Files\\Microsoft Shared\\ink\\TabTip.exe ", winroot);
        sprintf(tabtipworksp, "%c:\\Program Files\\Common Files\\Microsoft Shared\\ink", winroot);
        ret = QProcess::startDetached(tabtip, QStringList(), tabtipworksp);
        if (!ret)
        {
            sprintf(tabtip, "%c:\\Program Files (x86)\\Common Files\\Microsoft Shared\\ink\\TabTip32.exe ", winroot);
            sprintf(tabtipworksp, "%c:\\Program Files (x86)\\Common Files\\Microsoft Shared\\ink", winroot);
            ret = QProcess::startDetached(tabtip, QStringList(), tabtipworksp);
            if (!ret)
            {
                HWND hTabTip = ::FindWindowA("IPTip_Main_Window", 0);
                if (hTabTip)
                {
                    ShowWindow(hTabTip, SW_NORMAL);
                    DWORD WM_DESKBAND_CLICKED = ::RegisterWindowMessage(L"TabletInputPanelDeskBandClicked");
                    ::PostMessage(hTabTip, WM_DESKBAND_CLICKED, 0, 0);
                }
                else
                {
                    sprintf(tabtip, "%c:\\Windows\\System32\\osk.exe ", winroot);
                    sprintf(tabtipworksp, "%c:\\Windows\\System32", winroot);
                    ret = QProcess::startDetached(tabtip, QStringList(), tabtipworksp);
                }
            }
        }
    }
#endif

}
static void setNativeDarkTitleBar(WId w,bool on = true)
{
#ifdef Q_OS_WIN
    BOOL value = TRUE;
    if(on == false)
        value = FALSE;
    ::DwmSetWindowAttribute(HWND(w),20,&value,sizeof(value));
#endif
}
static bool isAdmin()
{
#ifdef Q_OS_WIN
    return bool(IsUserAnAdmin());
#else
    return false;
#endif
}
static bool runAsAdmin(QString program = QApplication::applicationFilePath())
{
#ifdef Q_OS_WIN
    HINSTANCE hInstance = ShellExecute(NULL, L"runas", program.replace("/","\\").toStdWString().c_str(), NULL, NULL, SW_SHOWNORMAL);
    if(hInstance > (HINSTANCE)32)
    {
        return true;
    }
    else
    {
        return false;
    }
#else
    return false;
#endif
}
static bool setUACAcceptNativeDrops(QObject* object)
{
/*
 * from https://github.com/junbaibai0719/qt_uac_drag_demo/tree/main and https://www.zhihu.com/question/607474668
 * this fuction can be used to enable drag events for UAC applications, then you can process them in native event(563).
 */
#ifdef Q_OS_WIN
    QWidget* w = static_cast<QWidget*>(object);
    if(w)
    {
        bool hide = w->isHidden();
        w->show();
        void* user32 = LoadLibraryA("user32");
        FARPROC func = GetProcAddress((HMODULE)user32, "ChangeWindowMessageFilter");
        (*func)();
        user32 = LoadLibraryA("user32");
        func = GetProcAddress((HMODULE)user32, "ChangeWindowMessageFilter");
        (*func)();
        ChangeWindowMessageFilter(WM_DROPFILES, 1);
        ChangeWindowMessageFilterEx((HWND)w->effectiveWinId(), WM_DROPFILES, MSGFLT_ALLOW, NULL);
        ChangeWindowMessageFilterEx((HWND)w->effectiveWinId(), WM_COPYDATA, MSGFLT_ALLOW, NULL);
        ChangeWindowMessageFilterEx((HWND)w->effectiveWinId(), 0x0049, MSGFLT_ALLOW, NULL);
        DragAcceptFiles((HWND)w->effectiveWinId(), true);
        RevokeDragDrop((HWND)w->winId());
        if(hide)
        {
            w->hide();
        }
        return true;
    }
    else
    {
        return false;
    }
#else
    return false;
#endif
}
static bool setUACAcceptNativeDrops(WId winId)
{
#ifdef Q_OS_WIN
    return setUACAcceptNativeDrops(QWidget::find(winId));
#else
    return false;
#endif
}
#ifndef Q_OS_WIN
typedef int MSG;
#endif
static QStringList getStringListFromNativeDropEvent(MSG* msg)
{
/* from https://www.zhihu.com/question/607474668
 * this fuction can be used to process drop in native event
 */
#ifdef Q_OS_WIN
    if(msg->message == 563)
    {
        QStringList list;
        UINT file_num = DragQueryFile((HDROP) msg->wParam, 0xFFFFFFFF, NULL, 0);
        for(int i=0;i<file_num;i++)
        {
            UINT file_name_size = DragQueryFile((HDROP) msg->wParam, i, NULL, 0) + 1;
            LPWSTR fn = (LPWSTR)malloc(sizeof(WCHAR)*file_name_size);
            DragQueryFile((HDROP) msg->wParam, i, fn, file_name_size);
            QString filename = QString::fromStdWString(fn);
            free(fn);
            list << filename.replace("\\","/");
        }
        return list;
    }
    else
    {
        return QStringList();
    }
#else
    return QStringList();
#endif
}
static QList<QUrl> getUrlListFromNativeDropEvent(MSG* msg)
{
/* from https://www.zhihu.com/question/607474668
 * this fuction can be used to process drop in native event
 */
#ifdef Q_OS_WIN
    if(msg->message == 563)
    {
        QList<QUrl> list;
        UINT file_num = DragQueryFile((HDROP) msg->wParam, 0xFFFFFFFF, NULL, 0);
        for(int i=0;i<file_num;i++)
        {
            UINT file_name_size = DragQueryFile((HDROP) msg->wParam, i, NULL, 0) + 1;
            LPWSTR fn = (LPWSTR)malloc(sizeof(WCHAR)*file_name_size);
            DragQueryFile((HDROP) msg->wParam, i, fn, file_name_size);
            QString filename = QString::fromStdWString(fn);
            free(fn);
            list << QUrl::fromLocalFile(filename.replace("\\","/"));
        }
        return list;
    }
    else
    {
        return QList<QUrl>();
    }
#else
    return QList<QUrl>();
#endif
}
static bool processNativeDropEvent(MSG* msg,QObject* recieveObject = nullptr)
{
#ifdef Q_OS_WIN
    if(msg->message == 563)
    {
        QMimeData* data = new QMimeData;
        QObjectList list;
        QWidget* w;
        QPoint pos = QPoint(0,0);
        data->setUrls(getUrlListFromNativeDropEvent(msg));

        if(recieveObject)
        {
            list << recieveObject;
        }
        else
        {
            list << QWidget::find(WId(msg->hwnd));
            POINT nativePoint = msg->pt;
            MapWindowPoints(NULL,msg->hwnd,&nativePoint,1);
            w = static_cast<QWidget*>(list.at(0));
            if(w && w->rect().contains(QPoint(nativePoint.x,nativePoint.y)))
            {
                pos = QPoint(nativePoint.x,nativePoint.y);
                pos = w->mapToGlobal(pos);
                while(w->childAt(w->mapFromGlobal(pos)) && w->childAt(w->mapFromGlobal(pos)) != w && w->childAt(w->mapFromGlobal(pos))->acceptDrops())
                {
                    w = w->childAt(w->mapFromGlobal(pos));
                    list << QObjectList() << w;
                }
            }
        }

        for(int i = 0;i < list.size();i++)
        {
            QObject* object = list.at(i);
            QPoint p = pos;
            if(static_cast<QWidget*>(object))
            {
                p = static_cast<QWidget*>(object)->mapFromGlobal(pos);
            }
            QDragEnterEvent event1(p,Qt::DropAction::CopyAction,data,Qt::LeftButton,Qt::NoModifier);
            QDropEvent event2(p,Qt::DropAction::CopyAction,data,Qt::LeftButton,Qt::NoModifier,QEvent::Drop);
            QApplication::sendEvent(object,&event1);
            QApplication::sendEvent(object,&event2);
        }
        return true;
    }
    else
    {
        return false;
    }
#else
    return false;
#endif
}
static QStringList getDrivers()
{
    QStringList list;
#ifdef Q_OS_WIN
    QString disk = "A";
    while(disk != "")
    {
        if(QFileInfo(disk+":/").isDir())
            list << QString(disk+":/");
        disk = getNextWord(disk);
    }
#endif
    return list;
}
static bool hideFile(QString path)
{
#ifdef Q_OS_WIN
    return bool(SetFileAttributes(path.toStdWString().c_str(), FILE_ATTRIBUTE_HIDDEN));
#else
    return false;
#endif
}
#ifdef Use_Plaform_Namespace
}
#endif

//Qt Gui 函数
//单个按钮的信息提示框
static int messagebox(QWidget* w,QMessageBox::Icon icon,QString title,QString text)
{
    int ret = 0;
#ifdef Q_OS_WIN
    if(icon == QMessageBox::Information)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONINFORMATION);
    else if(icon == QMessageBox::Critical)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONERROR);
    else if(icon == QMessageBox::Question)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONQUESTION);
    else if(icon == QMessageBox::Warning)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONWARNING);
    else if(icon == QMessageBox::NoIcon)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1);
#else
#ifdef Q_OS_ANDROID
    if(icon == QMessageBox::NoIcon && title == "")
    {
        QMessageBox box;
        box.setText(text);
        box.exec();
    }
    else
    {
        auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
        dlg.addButton("确定", QMessageBox::AcceptRole);
        auto r = dlg.exec();
        if (r == QMessageBox::AcceptRole)
        {
            ret = 1;
            dlg.close();
        }
    }
#else
    auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
    dlg.addButton("确定", QMessageBox::AcceptRole);
    auto r = dlg.exec();
    if (r == QMessageBox::AcceptRole)
    {
        ret = 1;
        dlg.close();
    }
#endif
#endif
    return ret;
}
static int messagebox(QMainWindow* w,QMessageBox::Icon icon,QString title,QString text)
{
    int ret = 0;
#ifdef Q_OS_WIN
    if(icon == QMessageBox::Information)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONINFORMATION);
    else if(icon == QMessageBox::Critical)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONERROR);
    else if(icon == QMessageBox::Question)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONQUESTION);
    else if(icon == QMessageBox::Warning)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONWARNING);
    else if(icon == QMessageBox::NoIcon)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1);
#else
#ifdef Q_OS_ANDROID
    if(icon == QMessageBox::NoIcon && title == "")
    {
        QMessageBox box;
        box.setText(text);
        box.exec();
    }
    else
    {
        auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
        dlg.addButton("确定", QMessageBox::AcceptRole);
        auto r = dlg.exec();
        if (r == QMessageBox::AcceptRole)
        {
            ret = 1;
            dlg.close();
        }
    }
#else
    auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
    dlg.addButton("确定", QMessageBox::AcceptRole);
    auto r = dlg.exec();
    if (r == QMessageBox::AcceptRole)
    {
        ret = 1;
        dlg.close();
    }
#endif
#endif
    return ret;
}
static int messagebox(QDialog* w,QMessageBox::Icon icon,QString title,QString text)
{
    int ret = 0;
#ifdef Q_OS_WIN
    if(icon == QMessageBox::Information)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONINFORMATION);
    else if(icon == QMessageBox::Critical)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONERROR);
    else if(icon == QMessageBox::Question)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONQUESTION);
    else if(icon == QMessageBox::Warning)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONWARNING);
    else if(icon == QMessageBox::NoIcon)
        ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1);
#else
#ifdef Q_OS_ANDROID
    if(icon == QMessageBox::NoIcon && title == "")
    {
        QMessageBox box;
        box.setText(text);
        box.exec();
    }
    else
    {
        auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
        dlg.addButton("确定", QMessageBox::AcceptRole);
        auto r = dlg.exec();
        if (r == QMessageBox::AcceptRole)
        {
            ret = 1;
            dlg.close();
        }
    }
#else
    auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
    dlg.addButton("确定", QMessageBox::AcceptRole);
    auto r = dlg.exec();
    if (r == QMessageBox::AcceptRole)
    {
        ret = 1;
        dlg.close();
    }
#endif
#endif
    return ret;
}
static int messagebox(QMessageBox::Icon icon,QString title,QString text)
{
    int ret = 0;
#ifdef Q_OS_WIN
    if(icon == QMessageBox::Information)
        ret = MessageBox(NULL,text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONINFORMATION);
    else if(icon == QMessageBox::Critical)
        ret = MessageBox(NULL,text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONERROR);
    else if(icon == QMessageBox::Question)
        ret = MessageBox(NULL,text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONQUESTION);
    else if(icon == QMessageBox::Warning)
        ret = MessageBox(NULL,text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1|MB_ICONWARNING);
    else if(icon == QMessageBox::NoIcon)
        ret = MessageBox(NULL,text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OK|MB_DEFBUTTON1);
#else
#ifdef Q_OS_ANDROID
    if(icon == QMessageBox::NoIcon && title == "")
    {
        QMessageBox box;
        box.setText(text);
        box.exec();
    }
    else
    {
        auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
        dlg.addButton("确定", QMessageBox::AcceptRole);
        auto r = dlg.exec();
        if (r == QMessageBox::AcceptRole)
        {
            ret = 1;
            dlg.close();
        }
    }
#else
    auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
    dlg.addButton("确定", QMessageBox::AcceptRole);
    auto r = dlg.exec();
    if (r == QMessageBox::AcceptRole)
    {
        ret = 1;
        dlg.close();
    }
#endif
#endif
    return ret;
}

//两个按钮的选择对话框
static int OkCancelBox(QWidget* w,QMessageBox::Icon icon,QString title,QString text,QString button1text = "",QString button2text = "")
{
    int ret = 0;
#ifdef Q_OS_WIN
    if(button1text == "" && button2text == "")
    {
        if(icon == QMessageBox::Information)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONINFORMATION);
        else if(icon == QMessageBox::Critical)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONERROR);
        else if(icon == QMessageBox::Question)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONQUESTION);
        else if(icon == QMessageBox::Warning)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONWARNING);
        else if(icon == QMessageBox::NoIcon)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1);
        if(ret == IDOK)
            ret = 1;
        else if(ret == IDCANCEL)
            ret = 2;
    }
    else
    {
        auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
        dlg.addButton(button1text, QMessageBox::AcceptRole);
        dlg.addButton(button2text, QMessageBox::RejectRole);
        auto r = dlg.exec();
        if (r == QMessageBox::AcceptRole)
        {
            ret = 1;
            dlg.close();
        }
        else if(r == QMessageBox::RejectRole)
        {
            ret = 2;
            dlg.close();
        }
    }
#else
    if(button1text == "" && button2text == "")
    {
        button1text = "确定";
        button2text = "取消";
    }
    auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
    dlg.addButton(button1text, QMessageBox::AcceptRole);
    dlg.addButton(button2text, QMessageBox::RejectRole);
    auto r = dlg.exec();
    if (r == QMessageBox::AcceptRole)
    {
        ret = 1;
        dlg.close();
    }
    else if(r == QMessageBox::RejectRole)
    {
        ret = 2;
        dlg.close();
    }
#endif
    return ret;
}
static int OkCancelBox(QMainWindow* w,QMessageBox::Icon icon,QString title,QString text,QString button1text = "",QString button2text = "")
{
    int ret = 0;
#ifdef Q_OS_WIN
    if(button1text == "" && button2text == "")
    {
        if(icon == QMessageBox::Information)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONINFORMATION);
        else if(icon == QMessageBox::Critical)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONERROR);
        else if(icon == QMessageBox::Question)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONQUESTION);
        else if(icon == QMessageBox::Warning)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONWARNING);
        else if(icon == QMessageBox::NoIcon)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1);
        if(ret == IDOK)
            ret = 1;
        else if(ret == IDCANCEL)
            ret = 2;
    }
    else
    {
        auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
        dlg.addButton(button1text, QMessageBox::AcceptRole);
        dlg.addButton(button2text, QMessageBox::RejectRole);
        auto r = dlg.exec();
        if (r == QMessageBox::AcceptRole)
        {
            ret = 1;
            dlg.close();
        }
        else if(r == QMessageBox::RejectRole)
        {
            ret = 2;
            dlg.close();
        }
    }
#else
    if(button1text == "" && button2text == "")
    {
        button1text = "确定";
        button2text = "取消";
    }
    auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
    dlg.addButton(button1text, QMessageBox::AcceptRole);
    dlg.addButton(button2text, QMessageBox::RejectRole);
    auto r = dlg.exec();
    if (r == QMessageBox::AcceptRole)
    {
        ret = 1;
        dlg.close();
    }
    else if(r == QMessageBox::RejectRole)
    {
        ret = 2;
        dlg.close();
    }
#endif
    return ret;
}
static int OkCancelBox(QDialog* w,QMessageBox::Icon icon,QString title,QString text,QString button1text = "",QString button2text = "")
{
    int ret = 0;
#ifdef Q_OS_WIN
    if(button1text == "" && button2text == "")
    {
        if(icon == QMessageBox::Information)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONINFORMATION);
        else if(icon == QMessageBox::Critical)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONERROR);
        else if(icon == QMessageBox::Question)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONQUESTION);
        else if(icon == QMessageBox::Warning)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1|MB_ICONWARNING);
        else if(icon == QMessageBox::NoIcon)
            ret = MessageBox(HWND(w->winId()),text.toStdWString().c_str(),title.toStdWString().c_str(),MB_OKCANCEL|MB_DEFBUTTON1);
        if(ret == IDOK)
            ret = 1;
        else if(ret == IDCANCEL)
            ret = 2;
    }
    else
    {
        auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
        dlg.addButton(button1text, QMessageBox::AcceptRole);
        dlg.addButton(button2text, QMessageBox::RejectRole);
        auto r = dlg.exec();
        if (r == QMessageBox::AcceptRole)
        {
            ret = 1;
            dlg.close();
        }
        else if(r == QMessageBox::RejectRole)
        {
            ret = 2;
            dlg.close();
        }
    }
#else
    if(button1text == "" && button2text == "")
    {
        button1text = "确定";
        button2text = "取消";
    }
    auto dlg = QMessageBox(icon,title,text,QMessageBox::NoButton);
    dlg.addButton(button1text, QMessageBox::AcceptRole);
    dlg.addButton(button2text, QMessageBox::RejectRole);
    auto r = dlg.exec();
    if (r == QMessageBox::AcceptRole)
    {
        ret = 1;
        dlg.close();
    }
    else if(r == QMessageBox::RejectRole)
    {
        ret = 2;
        dlg.close();
    }
#endif
    return ret;
}

static int EventMessageBox(QWidget* parent,QImage img,QString title,QString text,QString button1text,QString button2text = "",QString button3text = "",QString button4text = "",QString tip1 = "",QString tip2 = "",QString tip3 = "",QString tip4 = "")
{
    QDialog* dlg = new QDialog(parent);
    QLabel* titlelabel = new QLabel(dlg);
    QLabel* imagelabel = new QLabel(dlg);
    QLabel* textlabel = new QLabel(dlg);
    QPushButton* button1 = new QPushButton(dlg);
    QPushButton* button2 = new QPushButton(dlg);
    QPushButton* button3 = new QPushButton(dlg);
    QPushButton* button4 = new QPushButton(dlg);
    QLineEdit* edit = new QLineEdit(dlg);
    edit->setText("0");
    edit->hide();

#ifdef Q_Device_Desktop
    dlg->resize(400,300);
    dlg->setWindowFlags(Qt::FramelessWindowHint);
    dlg->setStyleSheet("background-color:black;border: 0.5px solid rgb(255, 255, 255);");
#else
    dlg->resize(screensize());
#endif


    titlelabel->resize(dlg->width(),30);
    titlelabel->move(0,0);
    titlelabel->setStyleSheet("color:white;background-color:black;");
    titlelabel->setAlignment(Qt::AlignCenter);
    titlelabel->setText(title);

    imagelabel->resize(dlg->width()-20,(dlg->width()-20)*(float(img.height())/float(img.width())));
    imagelabel->move(titlelabel->x()+10,titlelabel->y()+titlelabel->height()+10);
    imagelabel->setPixmap(QPixmap::fromImage(img).scaled(imagelabel->width(),imagelabel->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation));

    textlabel->resize(dlg->width(),60);
    textlabel->move(0,imagelabel->y()+imagelabel->height()+10);
    textlabel->setStyleSheet("color:white;background-color:black;");
    textlabel->setAlignment(Qt::AlignCenter);
    textlabel->setText(text);

    button1->resize(imagelabel->width(),30);
    button2->resize(button1->size());
    button3->resize(button1->size());
    button4->resize(button1->size());

    button1->move(imagelabel->x(),textlabel->y()+textlabel->height()+10);
    button2->move(button1->x(),button1->y()+button1->height()+10);
    button3->move(button2->x(),button2->y()+button2->height()+10);
    button4->move(button3->x(),button3->y()+button3->height()+10);

    button1->setStyleSheet("QPushButton{background-color:rgb(0,0,0);border: 0.5px solid rgb(255, 255, 255);color:rgb(255,255,255);}");
    button2->setStyleSheet(button1->styleSheet());
    button3->setStyleSheet(button1->styleSheet());
    button4->setStyleSheet(button1->styleSheet());

    button1->setText(button1text);
    button2->setText(button2text);
    button3->setText(button3text);
    button4->setText(button4text);

    button1->setToolTip(tip1);
    button2->setToolTip(tip2);
    button3->setToolTip(tip3);
    button4->setToolTip(tip4);
    dlg->setFixedHeight(button4->y()+button4->height()+10);

    QObject::connect(button1,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        edit->setText("1");
        dlg->close();
    });
    QObject::connect(button2,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        edit->setText("2");
        dlg->close();
    });
    QObject::connect(button3,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        edit->setText("3");
        dlg->close();
    });
    QObject::connect(button4,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        edit->setText("4");
        dlg->close();
    });

    if(button4text == "")
    {
        dlg->setFixedHeight(button4->y());
        button4->hide();
        button4->disconnect();
    }
    if(button3text == "")
    {
        dlg->setFixedHeight(button3->y());
        button3->hide();
        button3->disconnect();
    }
    if(button2text == "")
    {
        dlg->setFixedHeight(button2->y());
        button2->hide();
        button2->disconnect();
    }

    dlg->exec();
    return edit->text().toInt();
}
static WId processDialog(QWidget* parent = nullptr,QString title = " ")
{
    QDialog* dlg = new QDialog(parent);
    QComboBox* modebox = new QComboBox(dlg);
    QStringList mode;
    QLineEdit* commandEdit = new QLineEdit(dlg);
    QLineEdit* argumentEdit = new QLineEdit(dlg);
    QPushButton* runbutton = new QPushButton(dlg);
    QPushButton* closebutton = new QPushButton(dlg);
    QPushButton* killbutton = new QPushButton(dlg);
#ifdef Q_OS_LINUX
    QPushButton* rootbutton = new QPushButton(dlg);
#endif
    QLabel* l1 = new QLabel(dlg);
    QLabel* l2 = new QLabel(dlg);
    QLabel* l3 = new QLabel(dlg);
    QProcess* p = new QProcess(dlg);

    dlg->setWindowTitle(title);
#ifdef Q_Device_Mobile
    dlg->resize(screensize());
    //dlg->showFullScreen();
#else
    dlg->resize(430,170);
    fixSize(dlg);
#endif

    l1->resize(90,30);
    l2->resize(l1->size());
    l3->resize(l1->size());
    l1->move(10,10);
    l2->move(l1->x(),l1->y()+l1->height()+10);
    l3->move(l1->x(),l2->y()+l2->height()+10);
    l1->setText("mode:");
    l2->setText("command:");
    l3->setText("arguments:");
    l1->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    l2->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    l3->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

    modebox->move(l1->x()+l1->width()+10,l1->y());
    modebox->resize(dlg->width()-modebox->x()-10,l1->height());
    mode << "QProcess::execute(QString&)" << "system(char*)" << "QProcess::start(QString&,QStringList&)" << "QProcess::startDetached(QString&,QStringList&)";
    modebox->addItems(mode);

    commandEdit->move(l2->x()+l2->width()+10,l2->y());
    commandEdit->resize(modebox->size());

    argumentEdit->move(l3->x()+l3->width()+10,l3->y());
    argumentEdit->resize(commandEdit->size());

    closebutton->resize(50,30);
    closebutton->move(dlg->width()-closebutton->width()-10,l3->y()+l3->height()+10);
    closebutton->setText("取消");
    closebutton->setStyleSheet("QPushButton{background-color:rgb(255,255,255);border: 0.5px solid #DBDBDB;border-radius:5;color:rgb(0,0,0);}QPushButton:pressed{background-color:#D9D9D9;border: 0.5px solid #DBDBDB;}QPushButton:hover{background-color:#D9D9D9;border: 0.5px solid #DBDBDB;}");

    killbutton->resize(100,30);
    killbutton->move(closebutton->x()-killbutton->width()-10,closebutton->y());
    killbutton->setText("终止进程");
    killbutton->setStyleSheet(closebutton->styleSheet());

    runbutton->resize(closebutton->size());
    runbutton->move(killbutton->x()-runbutton->width()-10,killbutton->y());
    runbutton->setText("执行");
    runbutton->setStyleSheet("QPushButton{background-color:rgb(0,103,192);border: 0.5px solid rgb(0,103,192);border-radius:5;color:rgb(255,255,255);}QPushButton:pressed{background-color:#0A63A8;border: 0.5px solid #0A63A8;}QPushButton:hover{background-color:#0A63A8;border: 0.5px solid #0A63A8;}");

#ifdef Q_OS_LINUX
    rootbutton->move(runbutton->x(),runbutton->y()+runbutton->height()+10);
    rootbutton->resize(runbutton->width()+closebutton->width()+killbutton->width()+20,runbutton->height());
    rootbutton->setText("请求Root权限");
    rootbutton->setStyleSheet(closebutton->styleSheet());
#endif

    QObject::connect(closebutton,&QPushButton::clicked,[dlg](){
        dlg->close();
    });
    QObject::connect(modebox,QOverload<const QString &>::of(&QComboBox::currentTextChanged),[=](QString text)mutable{
        if(modebox->currentText() == "QProcess::execute(QString&)" || modebox->currentText() == "system(char*)")
        {
            argumentEdit->setEnabled(false);
        }
        else
        {
            argumentEdit->setEnabled(true);
        }
    });
    argumentEdit->setEnabled(false);
    QObject::connect(runbutton,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        if(modebox->currentText() == "QProcess::execute(QString&)" && commandEdit->text() != "")
            QProcess::execute(commandEdit->text());
        else if(modebox->currentText() == "system(char*)" && commandEdit->text() != "")
            system(QString(commandEdit->text()+" "+argumentEdit->text()).toLocal8Bit().data());
        else if(modebox->currentText() == "QProcess::start(QString&,QStringList&)" && commandEdit->text() != "")
            p->start(commandEdit->text(),QStringList() << argumentEdit->text());
        else if(modebox->currentText() == "QProcess::startDetached(QString&,QStringList&)" && commandEdit->text() != "")
            p->startDetached(commandEdit->text(),QStringList() << argumentEdit->text());
    });
    QObject::connect(killbutton,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        p->kill();
    });
#ifdef Q_OS_LINUX
    QObject::connect(rootbutton,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{QProcess::execute("su");
    });
#endif
    dlg->exec();
    return dlg->winId();
}
static WId playerDialog(QWidget* parent,QString path,QSize size = QSize(600,400))
{
#ifdef Multimedia_And_Widgets_Enabled
    QDialog* dlg = new QDialog(parent);
    QMediaPlayer* player = new QMediaPlayer(dlg);
    QVideoWidget* videowidget = new QVideoWidget(dlg);
    QAudioOutput* audiooutput = new QAudioOutput;
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
#endif

#ifdef Q_Device_Desktop
    dlg->resize(size);
    fixSize(dlg);
#else
    if(size.width() == 600 && size.height() == 400)
        dlg->resize(screensize());
    else
        dlg->resize(size);
#endif
    videowidget->resize(dlg->size());
    player->setVideoOutput(videowidget);

#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    if(hasFilePermission(path) == true)
    {
        player->setSource(QUrl::fromLocalFile(path));
        player->setAudioOutput(audiooutput);
    }
#else
    if(hasFilePermission(path) == true)
    {
        player->setMedia(QUrl::fromLocalFile(path));
    }
#endif

    //qDebug() << path << hasFilePermission(path);

    player->play();
    dlg->setWindowTitle(QFileInfo(path).fileName());
    dlg->exec();
    player->stop();
    return dlg->winId();
#else
    return parent->winId();
#endif
}
static WId fileDialog(QWidget* parent,QString title = " ")
{
    QDialog* w = new QDialog(parent);
    QWidget* dlg = new QWidget(w);
    dlg->setWindowTitle(title);
#ifdef Q_Device_Mobile
    w->resize(screensize());
    dlg->resize(screensize());
#else
    dlg->resize(500,600);
#endif

    QLabel* l1 = new QLabel(dlg);
    QLabel* l2 = new QLabel(dlg);
    QLabel* l3 = new QLabel(dlg);
    QLabel* l4 = new QLabel(dlg);
    QLabel* l5 = new QLabel(dlg);
    QLabel* l6 = new QLabel(dlg);
    QLabel* l7 = new QLabel(dlg);
    QLabel* l8 = new QLabel(dlg);
    QLabel* l9 = new QLabel(dlg);
    QLabel* l10 = new QLabel(dlg);
    QLabel* l11 = new QLabel(dlg);

    l1->setText("QFile file(");
    l2->setText(");");
    l3->setText("QIODevice::OpenModeFlag flag = ");
    l4->setText(";");
    l5->setText("bool check1 = file.exists();");
    l6->setText("bool check2 = file.open(flag);");
    l7->setText("QString content = file.readAll();");
    l8->setText("file.write(");
    l9->setText(");");
    l10->setText("file.close();");
    l11->setText("qDebug() << ");

    l1->setAlignment(Qt::AlignCenter);
    l2->setAlignment(Qt::AlignCenter);
    l3->setAlignment(Qt::AlignCenter);
    l4->setAlignment(Qt::AlignCenter);
    l5->setAlignment(Qt::AlignCenter);
    l6->setAlignment(Qt::AlignCenter);
    l7->setAlignment(Qt::AlignCenter);
    l8->setAlignment(Qt::AlignCenter);
    l9->setAlignment(Qt::AlignCenter);
    l10->setAlignment(Qt::AlignCenter);
    l11->setAlignment(Qt::AlignCenter);

    QComboBox* flagbox = new QComboBox(dlg);
    QComboBox* debugbox = new QComboBox(dlg);
    QStringList list1;
    QStringList list2;
    list1 << "QIODevice::ReadWrite" << "QIODevice::ReadOnly" << "QIODevice::WriteOnly";
    list2 << "check1" << "check2" << "content";
    flagbox->addItems(list1);
    debugbox->addItems(list2);

    QLineEdit* fileedit = new QLineEdit(dlg);
    QTextEdit* writeedit = new QTextEdit(dlg);
    QPushButton* browsebutton = new QPushButton(dlg);
    QPushButton* commitbutton = new QPushButton(dlg);
    QPushButton* cancelbutton = new QPushButton(dlg);
    QPushButton* clearbutton = new QPushButton(dlg);
    browsebutton->setIcon(QIcon(":/icon/folder.ico"));
    browsebutton->setStyleSheet("QPushButton{border:none;background:transparent;}");
    commitbutton->setText("确定");
    commitbutton->setStyleSheet("QPushButton{background-color:rgb(0,103,192);border: 0.5px solid rgb(0,103,192);border-radius:5;color:rgb(255,255,255);}QPushButton:pressed{background-color:#0A63A8;border: 0.5px solid #0A63A8;}QPushButton:hover{background-color:#0A63A8;border: 0.5px solid #0A63A8;}");
    cancelbutton->setText("取消");
    cancelbutton->setStyleSheet("QPushButton{background-color:rgb(255,255,255);border: 0.5px solid #DBDBDB;border-radius:5;color:rgb(0,0,0);}QPushButton:pressed{background-color:#D9D9D9;border: 0.5px solid #DBDBDB;}QPushButton:hover{background-color:#D9D9D9;border: 0.5px solid #DBDBDB;}");
    clearbutton->setText("clear");
    fileedit->setClearButtonEnabled(true);

    l1->move(10,10);
    l1->resize(80,30);
    l2->resize(l1->height(),l1->height());
    l2->move(dlg->width()-10-l2->width(),l1->y());
    browsebutton->resize(l1->height(),l1->height());
    browsebutton->move(l2->x()-10-browsebutton->width(),l1->y());
    fileedit->resize(browsebutton->x()-l1->x()-l1->width()-20,l1->height());
    fileedit->move(l1->x()+l1->width()+10,l1->y());

    l3->move(l1->x(),l1->y()+l1->height()+10);
    l3->resize(200,l1->height());
    l4->resize(15,25);
    l4->move(dlg->width()-10-l4->width(),l3->y());
    flagbox->move(l3->x()+l3->width()+10,l3->y());
    flagbox->resize(l4->x()-20-l3->x()-l3->width(),l1->height());

    l5->move(l1->x(),l3->y()+l3->height()+10);
    l5->resize(dlg->width()-20,l1->height());
    l6->move(l1->x(),l5->y()+l5->height()+10);
    l6->resize(l5->size());
    l7->move(l1->x(),l6->y()+l6->height()+10);
    l7->resize(l5->size());

    l8->resize(80,l1->height());
    l8->move(l7->x(),l7->y()+l7->height()+10);
    l9->resize(15,l1->height());
    l9->move(dlg->width()-10-l9->width(),l8->y()+l8->height()+10);
    writeedit->move(l8->x()+l8->width()+10,l8->y());
    writeedit->resize(l9->x()-l8->x()-l8->width()-20,l9->y()+l9->height()-l8->y());

    l10->move(l8->x(),l9->y()+l9->height()+10);
    l10->resize(l5->size());
    l11->move(l10->x(),l10->y()+l10->height()+10);
    l11->resize(100,l1->height());

    commitbutton->resize(50,30);
    cancelbutton->resize(commitbutton->size());
    cancelbutton->move(dlg->width()-10-cancelbutton->width(),l11->y());
    commitbutton->move(cancelbutton->x()-10-commitbutton->width(),cancelbutton->y());
    debugbox->move(l11->x()+l11->width()+10,l11->y());
    debugbox->resize(commitbutton->x()-l11->x()-l11->width()-20,l1->height());

    clearbutton->resize(l8->size());
    clearbutton->move(l8->x(),l8->y()+l8->height()+10);
    dlg->resize(dlg->width(),commitbutton->y()+commitbutton->height()+10);
#ifdef Q_Device_Mobile
    //QMessageBox::information(dlg,"",QString("screenheight:"+QString::number(screenheight())+"\ndlg.height():"+QString::number(dlg->height())));
    QScrollArea* s = new QScrollArea(w);
    s->setWidget(dlg);
    s->setGeometry(0,0,screenwidth(),screenheight());
    s->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScroller::grabGesture(s->viewport(),QScroller::LeftMouseButtonGesture);
#endif

    QObject::connect(browsebutton,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        QString path;
//#ifndef Q_OS_ANDROID
        dlg->hide();
        path = QFileDialog::getOpenFileName();
        QMessageBox::information(dlg,""," ");
        dlg->show();
//#else
//        MyFileDialog* dialog = new MyFileDialog(dlg);
//        path = dialog->getOpenFileName();
//#endif
        if(path != "")
            fileedit->setText(path);
    });
    QObject::connect(cancelbutton,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        dlg->close();
        w->close();
    });
    QObject::connect(debugbox,QOverload<const QString &>::of(&QComboBox::currentTextChanged),[=](QString text)mutable{

    });
    QObject::connect(clearbutton,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        writeedit->setText("");
    });
    QObject::connect(commitbutton,QOverload<bool>::of(&QPushButton::clicked),[=](bool check)mutable{
        if(fileedit->text() != "")
        {
            if(debugbox->currentText() == "check1")
            {
                bool check1 = QFile(fileedit->text()).exists();
                if(check1 == true)
                    messagebox(dlg,QMessageBox::NoIcon,"","check1 == true");
                else
                    messagebox(dlg,QMessageBox::NoIcon,"","check1 == false");
            }
            else if(debugbox->currentText() == "check2")
            {
                QIODevice::OpenModeFlag flag;
                if(flagbox->currentText() == "QIODevice::ReadWrite")
                    flag = QIODevice::ReadWrite;
                else if(flagbox->currentText() == "QIODevice::ReadOnly")
                    flag = QIODevice::ReadOnly;
                else if(flagbox->currentText() == "QIODevice::WriteOnly")
                    flag = QIODevice::WriteOnly;
                bool check2 = hasFilePermission(fileedit->text(),flag);
                if(check2 == true)
                    messagebox(dlg,QMessageBox::NoIcon,"","check2 == true");
                else
                    messagebox(dlg,QMessageBox::NoIcon,"","check2 == false");
            }
            else if(debugbox->currentText() == "content")
            {
                QString content = "";
                QFile file(fileedit->text());
                if(file.open(QIODevice::ReadOnly))
                {
                    content = file.readAll();
                    file.close();
                    file.deleteLater();
                    messagebox(dlg,QMessageBox::NoIcon,"",QString("content:\n"+content));
                }
                else
                {
                    messagebox(dlg,QMessageBox::NoIcon,"","fail to read file");
                }
            }
            if(writeedit->toPlainText() != "")
            {
                QFile file(fileedit->text());
                if(file.open(QIODevice::WriteOnly))
                {
                    file.write(writeedit->toPlainText().toLocal8Bit());
                    file.close();
                    file.deleteLater();
                }
                else
                {
                    messagebox(dlg,QMessageBox::NoIcon,"","fail to write file");
                }
            }
        }
    });
    w->exec();
    return w->winId();
}
static void showPixmapDialog(QPixmap pixmap,QObject* parent = nullptr,QString title = "")
{
    QDialog* dlg = new QDialog();

    QLabel* label = new QLabel(dlg);
    label->move(0,0);
    label->setPixmap(pixmap);
    if(!title.isEmpty())
    {
        dlg->setWindowTitle(title);
    }
    if(pixmap.isNull())
    {
        label->resize(100,100);
    }
    else
    {
        label->resize(pixmap.size());
    }
    dlg->resize(label->size());
    label->show();
    dlg->exec();
}
static QString lineEditDialog(QWidget* parent,QString text,QString title,QString placeholdertext = "",bool clearbutton = true)
{
    QDialog* dlg = new QDialog(parent);
    QLineEdit* edit = new QLineEdit(dlg);
    QPushButton* commitbutton = new QPushButton(dlg);
    QPushButton* cancelbutton = new QPushButton(dlg);

#ifdef Q_Device_Desktop
    dlg->resize(350,90);
    dlg->setWindowTitle(title);
#else
    dlg->resize(screensize());
#endif
    //setCloseButton(dlg,false,0);

    edit->resize(dlg->width()-20,30);
    edit->move(10,10);
    edit->setText(text);
    if(placeholdertext != "")
        edit->setPlaceholderText(placeholdertext);
    if(clearbutton == true)
        edit->setClearButtonEnabled(true);

    cancelbutton->resize(edit->height()/3*5,edit->height());
    commitbutton->resize(cancelbutton->size());
    cancelbutton->move(edit->x()+edit->width()-cancelbutton->width(),edit->y()+edit->height()+10);
    commitbutton->move(cancelbutton->x()-10-commitbutton->width(),cancelbutton->y());
    cancelbutton->setText("取消");
    commitbutton->setText("确定");

//    qDebug() << edit->width() << edit->height();
//    messagebox(parent,QMessageBox::NoIcon,"",QString::number(edit->width())+","+QString::number(edit->height()));

    QObject::connect(commitbutton,QOverload<bool>::of(&QPushButton::clicked),[=](bool check){
        if(edit->text() != "")
            dlg->close();
    });
    QObject::connect(cancelbutton,QOverload<bool>::of(&QPushButton::clicked),[=](bool check){
        edit->setText(text);
        dlg->close();
    });
    QObject::connect(edit,QOverload<>::of(&QLineEdit::returnPressed),[=](){
        commitbutton->click();
    });

    dlg->exec();
    return edit->text();
}

//调试
static QString GetDebugInfo(QWidget* w = nullptr)
{
    QString ret = "";

    ret = ret + "ApplicationFilePath" + ": " + QCoreApplication::applicationFilePath() + "\r\n";
    ret = ret + "ApplicationDirPath" + ": " + QCoreApplication::applicationDirPath() + "\r\n";
    ret = ret + "ApplicationCurrentPath" + ": " + QDir::currentPath() + "\r\n";
    ret = ret + "ApplicationName" + ": " + QCoreApplication::applicationName() + "\r\n";
    if(!QCoreApplication::applicationVersion().isEmpty())
        ret = ret + "ApplicationVersion" + ": " + QCoreApplication::applicationVersion() + "\r\n";
    else
        ret = ret + "ApplicationVersion" + ": " + "nullptr" + "\r\n";
    ret = ret + "ApplicationPid" + ": " + QString::number(QCoreApplication::applicationPid()) + "\r\n";
    ret = ret + "ApplicationArguments" + ": " + QCoreApplication::arguments().join(";") + "\r\n";
    if(w != nullptr)
    {
        ret = ret + "ApplicationWinId" + ": " + QString::number(w->winId()) + "\r\n";
#ifdef Q_OS_WIN
        TCHAR szBuffer[256];
        wsprintf(szBuffer, L"0x%08p", HWND(w->winId()));
        QString strHWND = QString::fromWCharArray(szBuffer);
        ret = ret + "ApplicationHWND" + ": " + strHWND + "\r\n";
#endif
    }

    ret = ret + "\r\n";
    ret = ret + "HomeDirPath" + ": " + QDir::homePath() + "\r\n";
    ret = ret + "HomeDirName" + ": " + QDir::home().dirName() + "\r\n";
    ret = ret + "TempDirName" + ": " + QDir::tempPath() + "\r\n";
    ret = ret + "DesktopLocation" + ": " + QStandardPaths::writableLocation(QStandardPaths::DesktopLocation) + "\r\n";
    ret = ret + "DownloadLocation" + ": " + QStandardPaths::writableLocation(QStandardPaths::DownloadLocation) + "\r\n";
    ret = ret + "DocumentsLocation" + ": " + QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "\r\n";
    ret = ret + "PicturesLocation" + ": " + QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + "\r\n";
    ret = ret + "MoviesLocation" + ": " + QStandardPaths::writableLocation(QStandardPaths::MoviesLocation) + "\r\n";
    ret = ret + "MusicLocation" + ": " + QStandardPaths::writableLocation(QStandardPaths::MusicLocation) + "\r\n";
    ret = ret + "GenericDataLocation" + ": " + QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + "\r\n";
    ret = ret + "GenericCacheLocation" + ": " + QStandardPaths::writableLocation(QStandardPaths::GenericCacheLocation) + "\r\n";
    ret = ret + "GenericConfigLocation" + ": " + QStandardPaths::writableLocation(QStandardPaths::GenericConfigLocation) + "\r\n";
    ret = ret + "ScreenWidth" + ": " + QString::number(screenwidth()) + "\r\n";
    ret = ret + "ScreenHeight" + ": " + QString::number(screenheight()) + "\r\n";

    ret = ret + "\r\n";
    ret = ret + "SystemProductName" + ": " + QSysInfo::prettyProductName() + "\r\n";
    ret = ret + "SystemProductType" + ": " + QSysInfo::productType() + "\r\n";
    ret = ret + "SystemProductVersion" + ": " + QSysInfo::productVersion() + "\r\n";
    ret = ret + "QtVersion" + ": " + QString(QT_VERSION_STR) + "\r\n";
#ifdef Core_Private_Enabled
#ifdef Network_Enabled
    if(QSslSocket::supportsSsl())
        ret = ret + "SupportOpenssl" + ": " + "true" + "\r\n";
    else
        ret = ret + "SupportOpenssl" + ": " + "false" + "\r\n";
#endif
#endif

//Android Debug
#ifdef Q_OS_ANDROID
#ifdef Core_Private_Enabled
    ret = ret + "\r\n";
    ret = ret + "AndroidPackageName" + ": " + Android::getPackageName() + "\r\n";
    ret = ret + "AndroidSystemVersion" + ": " + QString::number(Android::getSystemVersion()) + "\r\n";
    ret = ret + "AndroidSdkVersion" + ": " + QString::number(Android::getSdkVersion()) + "\r\n";
    ret = ret + "Brand" + ": " + Android::getBrand() + "\r\n";
    ret = ret + "Model" + ": " + Android::getModel() + "\r\n";
#endif
#endif

    return ret;
}
static WId showDebugInfo(QWidget* parent = nullptr,QString title = " ",bool check = true)
{
    QDialog* dlg = new QDialog(parent);
    QTextEdit* edit = new QTextEdit(dlg);

    dlg->setWindowTitle(title);
#ifdef Q_Device_Mobile
    dlg->resize(screensize());
#else
    dlg->resize(400,300);
    fixSize(dlg);
#endif

    edit->move(0,0);
    edit->resize(dlg->size());
    edit->setEnabled(check);
    edit->setText(GetDebugInfo(parent));
#ifdef Q_Device_Desktop
    QScroller::grabGesture(edit->viewport(),QScroller::TouchGesture);
#else
    QScroller::grabGesture(edit->viewport(),QScroller::LeftMouseButtonGesture);
#endif

    dlg->exec();
    return dlg->winId();
}

//图片处理
static QPixmap floodFill(QPixmap &pixmap, QPoint seedPoint, QColor newColor,int tolerance = 0)
{
    if(tolerance >= 0 && tolerance < 255)
    {
        QImage image = pixmap.toImage();
        QColor oldColor = image.pixelColor(seedPoint);
        if (oldColor == newColor && tolerance == 0)
        {
            return pixmap;
        }

        QStack<QPoint> stack;
        stack.push(seedPoint);

        while (!stack.isEmpty())
        {
            QPoint current = stack.pop();
            //if (image.valid(current) && image.pixelColor(current) == oldColor)
            if (image.valid(current) && Abs(image.pixelColor(current).red()-oldColor.red()) <= tolerance && Abs(image.pixelColor(current).green()-oldColor.green()) <= tolerance && Abs(image.pixelColor(current).blue()-oldColor.blue()) <= tolerance)
            {
                image.setPixelColor(current, newColor);
                stack.push(QPoint(current.x() + 1, current.y()));
                stack.push(QPoint(current.x() - 1, current.y()));
                stack.push(QPoint(current.x(), current.y() + 1));
                stack.push(QPoint(current.x(), current.y() - 1));
            }
        }
        pixmap = QPixmap::fromImage(image);
        image = QImage();
    }
    else if(tolerance == 255)
    {
        QPixmap p = pixmap;
        QPainter painter(&p);
        painter.fillRect(p.rect(),newColor);
        pixmap = p;
    }
    return pixmap;
}
static QImage floodFill(QImage &image, QPoint seedPoint, QColor newColor,int tolerance = 0)
{
    if(tolerance >= 0 && tolerance < 255)
    {
        QColor oldColor = image.pixelColor(seedPoint);
        if (oldColor == newColor && tolerance == 0)
        {
            return image;
        }

        QStack<QPoint> stack;
        stack.push(seedPoint);

        while (!stack.isEmpty())
        {
            QPoint current = stack.pop();
            //if (image.valid(current) && image.pixelColor(current) == oldColor)
            if (image.valid(current) && Abs(image.pixelColor(current).red()-oldColor.red()) <= tolerance && Abs(image.pixelColor(current).green()-oldColor.green()) <= tolerance && Abs(image.pixelColor(current).blue()-oldColor.blue()) <= tolerance)
            {
                image.setPixelColor(current, newColor);
                stack.push(QPoint(current.x() + 1, current.y()));
                stack.push(QPoint(current.x() - 1, current.y()));
                stack.push(QPoint(current.x(), current.y() + 1));
                stack.push(QPoint(current.x(), current.y() - 1));
            }
        }
    }
    else if(tolerance == 255)
    {
        QPixmap pixmap = QPixmap::fromImage(image);
        QPainter painter(&pixmap);
        painter.fillRect(pixmap.rect(),newColor);
        image = pixmap.toImage();
    }
    return image;
}
static QPixmap setOpacity(QPixmap &pixmap,int opacity)
{
    if(opacity < 255 && opacity >= 0 && !pixmap.isNull())
    {
        int x;
        int y;
        QImage image = pixmap.toImage();
        image = image.convertToFormat(QImage::Format_ARGB32);
        QColor color;
        for(x = 0;x <= image.width();x++)
        {
            for(y = 0;y <= image.height();y++)
            {
                if(image.valid(QPoint(x,y)) && image.pixelColor(x,y) != QColor(0,0,0,0))
                {
                    color = image.pixelColor(x,y);
                    image.setPixelColor(x,y,QColor(color.red(),color.green(),color.blue(),opacity));
                }
            }
        }
        color = QColor();
        x = NULL;
        y = NULL;
        pixmap = QPixmap::fromImage(image);
        image = QImage();
    }
    return pixmap;
}
static QImage setOpacity(QImage &image,int opacity)
{
    if(opacity < 255 && opacity >= 0 && !image.isNull())
    {
        int x;
        int y;
        image = image.convertToFormat(QImage::Format_ARGB32);
        QColor color;
        for(x = 0;x <= image.width();x++)
        {
            for(y = 0;y <= image.height();y++)
            {
                if(image.valid(QPoint(x,y)) && image.pixelColor(x,y) != QColor(0,0,0,0))
                {
                    color = image.pixelColor(x,y);
                    image.setPixelColor(x,y,QColor(color.red(),color.green(),color.blue(),opacity));
                }
            }
        }
        color = QColor();
        x = NULL;
        y = NULL;
    }
    return image;
}
static QPixmap replaceColor(QPixmap &pixmap,QColor oldColor,QColor newColor)
{
    if(!pixmap.isNull())
    {
        int x;
        int y;
        QImage image = pixmap.toImage();
        image = image.convertToFormat(QImage::Format_ARGB32);
        for(x = 0;x <= image.width();x++)
        {
            for(y = 0;y <= image.height();y++)
            {
                if(image.valid(QPoint(x,y)) && image.pixelColor(QPoint(x,y)) == oldColor)
                {
                    image.setPixelColor(x,y,newColor);
                }
            }
        }
        x = NULL;
        y = NULL;
        pixmap = QPixmap::fromImage(image);
        image = QImage();
    }
    return pixmap;
}
static QImage replaceColor(QImage &image,QColor oldColor,QColor newColor)
{
    if(!image.isNull())
    {
        int x;
        int y;
        image = image.convertToFormat(QImage::Format_ARGB32);
        for(x = 0;x <= image.width();x++)
        {
            for(y = 0;y <= image.height();y++)
            {
                if(image.valid(QPoint(x,y)) && image.pixelColor(QPoint(x,y)) == oldColor)
                {
                    image.setPixelColor(x,y,newColor);
                }
            }
        }
        x = NULL;
        y = NULL;
    }
    return image;
}
static QPixmap rectPixmap(int width,int height,QColor lineColor,int pensize,QColor fillColor = QColor(0,0,0,0),int round = -1)
{
    if(width > pensize && height > pensize && pensize > 0)
    {
        QPixmap pixmap(width+pensize,height+pensize);
        pixmap.fill(QColor(0,0,0,0));
        QPainter* painter = new QPainter(&pixmap);
        QPen pen;
        QBrush brush;
        if(fillColor != QColor(0,0,0,0))
        {
            brush.setColor(fillColor);
            brush.setStyle(Qt::SolidPattern);
            painter->setBrush(brush);
        }
        pen.setColor(lineColor);
        pen.setWidth(pensize);
        painter->setPen(pen);
        if(round > 0)
            painter->drawRoundedRect(QRect(pensize/2.0,pensize/2.0,width,height),round,round);
        else
            painter->drawRect(pensize/2.0,pensize/2.0,width,height);
        pen = QPen();
        brush = QBrush();
        delete painter;
        return pixmap;
    }
    else
    {
        return QPixmap();
    }
}
static QPixmap roundPixmap(int width,int height,QColor lineColor,int pensize,QColor fillColor = QColor(0,0,0,0))
{
    if(width > pensize && height > pensize && pensize > 0)
    {
        QPixmap pixmap(width+pensize,height+pensize);
        pixmap.fill(QColor(0,0,0,0));
        QPainter* painter = new QPainter(&pixmap);
        QPen pen;
        QBrush brush;
        if(fillColor != QColor(0,0,0,0))
        {
            brush.setColor(fillColor);
            brush.setStyle(Qt::SolidPattern);
            painter->setBrush(brush);
        }
        pen.setColor(lineColor);
        pen.setWidth(pensize);
        painter->setPen(pen);
        painter->drawEllipse(pensize/2.0,pensize/2.0,width,height);
        pen = QPen();
        brush = QBrush();
        delete painter;
        return pixmap;
    }
    else
    {
        return QPixmap();
    }
}
static QPixmap textPixmap(QString str,QColor textcolor = Qt::white,QColor backgroundcolor = Qt::transparent,QFont font = QFont())
{
    if(!str.isEmpty() && textcolor.isValid() && backgroundcolor.isValid())
    {
        QPixmap pixmap(nativeLabelSize(str));
        pixmap.fill(backgroundcolor);
        QPainter* painter = new QPainter(&pixmap);
        QPen pen;
        pen.setColor(textcolor);
        painter->setFont(font);
        painter->setPen(pen);
        painter->drawText(pixmap.rect(),str);
        return pixmap;
    }
    else
    {
        return QPixmap();
    }
}

//网络
#ifdef Network_Enabled
static bool sendTcpMessage(QHostAddress address,quint16 port,QString message)
{
    QTcpSocket* socket = new QTcpSocket();
    QEventLoop* loop = new QEventLoop();
    bool ret = false;
    QObject::connect(socket,QOverload<>::of(&QTcpSocket::connected),[socket,loop,&ret,message](){
        socket->write(message.toLatin1());
        ret = true;
        loop->quit();
    });
    QObject::connect(socket,QOverload<>::of(&QTcpSocket::disconnected),[socket,loop,&ret](){
        loop->quit();
    });
    socket->connectToHost(address,port);
    if(!ret)
        loop->exec();
    socket->disconnect();
    socket->disconnectFromHost();
    return ret;
}
#endif

//深色主题适配
static bool isSystemDarkMode()
{
#if(QT_VERSION>=QT_VERSION_CHECK(6,5,0))
    Qt::ColorScheme scheme = QGuiApplication::styleHints()->colorScheme();
    if(scheme != Qt::ColorScheme::Unknown)
        return bool(scheme==Qt::ColorScheme::Dark);
#endif
#if defined(Q_OS_ANDROID)
    QJniObject activity = QtAndroidPrivate::activity();
    if(activity.isValid())
    {
        QJniObject resources = activity.callObjectMethod("getResources", "()Landroid/content/res/Resources;");
        if (resources.isValid())
        {
            QJniObject configuration = resources.callObjectMethod("getConfiguration", "()Landroid/content/res/Configuration;");
            if (configuration.isValid())
            {
                jint uiMode = configuration.getField<jint>("uiMode");
                jint nightMode = QJniObject::getStaticField<jint>("android/content/res/Configuration", "UI_MODE_NIGHT_MASK");
                jint currentNightMode = uiMode & nightMode;
                if (currentNightMode == QJniObject::getStaticField<jint>("android/content/res/Configuration", "UI_MODE_NIGHT_YES"))
                {
                    return true;
                }
            }
        }
    }
    return false;
    /*
    if(activity.isValid())
    {
        int darkMode = QJniObject::callStaticMethod<jint>(
            javaPackage,
            "isDarkMode",
            "(Landroid/content/Context;)I",
            activity.object<jobject>()
        );
        if(darkMode == 1)
            return true;
        else
            return false;
    }
    else
    {
        return false;
    }
    */
#else
#if defined(Q_OS_WIN)
    QSettings* settings = new QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",QSettings::NativeFormat);
    if(settings->contains("AppsUseLightTheme") && settings->value("AppsUseLightTheme") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
#else
#if defined(Q_OS_MAC)
    return bool(runCommand("defaults read -g AppleInterfaceStyle")==QString("Dark"));
#else
    return false;
#endif
#endif
#endif

}
static void setDarkTitleBar(WId w,bool on = true)
{
#ifdef Q_OS_WIN
    Windows::setNativeDarkTitleBar(w,on);
#else
#endif
}
static void setApplicationDarkMode(bool on,QObject* mainWindow = qApp->topLevelWidgets().at(0),QList<QObject*> widgets = QList<QObject*>(),QList<QPalette> lightPalettes = QList<QPalette>(),QList<QPalette> darkPalettes = QList<QPalette>())
{
    const QString style = "Fusion";
#ifdef Q_OS_WIN
    QString native_style = "windowsvista";
#else
#ifdef Q_OS_ANDROID
    const QString native_style = "";
#else
    QString native_style = "";
#endif
#endif
//    for(QWidget* w : QApplication::topLevelWidgets())
//    {
//        setDarkTitleBar(w->winId(),on);
//    }
    QWidget* widget = static_cast<QWidget*>(mainWindow);
    if(on == true)
    {
        int j = 0;
        while(j < widgets.count() && j < darkPalettes.count())
        {
            QWidget* w = static_cast<QWidget*>(widgets.at(j));
            if(w)
            {
                w->setPalette(darkPalettes.at(j));
            }
            j++;
        }

        QObjectList list = allChildren(widget);
        for(int i = 0;i < list.count();i++)
        {
            QObject* obj = list.at(i);
            if(QString(obj->metaObject()->className()) == "QLineEdit" && static_cast<QLineEdit*>(obj) != nullptr)
            {
            }
            else if(static_cast<QWidget*>(obj) != nullptr && static_cast<QWidget*>(obj)->parent() == nullptr)
            {
                 setDarkTitleBar(static_cast<QWidget*>(obj)->winId(),on);
            }
            else if(QString(obj->metaObject()->className()) == "QComboBox" && static_cast<QComboBox*>(obj) != nullptr)
            {
                QPalette p3;
                p3.setColor(QPalette::Window,QColor(40,40,40));
                p3.setColor(QPalette::Button,QColor(40,40,40));
                p3.setColor(QPalette::Base,QColor(40,40,40));
                p3.setColor(QPalette::WindowText,Qt::white);
                p3.setColor(QPalette::ButtonText,Qt::white);
                static_cast<QComboBox*>(obj)->setPalette(p3);
                static_cast<QComboBox*>(obj)->update();
            }
        }
#if (QT_VERSION >= QT_VERSION_CHECK(6,5,0)) && defined(Q_OS_ANDROID)
        if(Android::getSystemVersion() >= 12 && isSystemDarkMode())
            return;
#endif
        if(QApplication::style() != QStyleFactory::create(style))
        {
            QApplication::setStyle(QStyleFactory::create(style));
        }
        if(widget != nullptr)
        {
            setDarkTitleBar(widget->winId(),on);
        }
#if (QT_VERSION >= QT_VERSION_CHECK(6,5,0)) && defined(Q_OS_WIN)
//        if(isSystemDarkMode())
//            return;
#endif
        QPalette p;
        p.setColor(QPalette::Window,QColor(40,40,40));
        p.setColor(QPalette::Button,QColor(40,40,40));
        p.setColor(QPalette::WindowText,Qt::white);
        p.setColor(QPalette::ButtonText,Qt::white);
        p.setColor(QPalette::Base,QColor(50,50,50));
        p.setColor(QPalette::Text,Qt::white);
        p.setColor(QPalette::PlaceholderText,QColor(160,160,160));
        p.setColor(QPalette::Disabled, QPalette::Window, QColor(68, 68, 68));
        QApplication::setPalette(p);
    }
    else
    {
        int j = 0;
        while(j < widgets.count() && j < lightPalettes.count())
        {
            QWidget* w = static_cast<QWidget*>(widgets.at(j));
            if(w)
            {
                w->setPalette(lightPalettes.at(j));
            }
            j++;
        }

        QObjectList list = allChildren(widget);
        for(int i = 0;i < list.count();i++)
        {
            QObject* obj = list.at(i);
            if(QString(obj->metaObject()->className()) == "QLineEdit" && static_cast<QLineEdit*>(obj) != nullptr)
            {
            }
            else if(static_cast<QWidget*>(obj) != nullptr && static_cast<QWidget*>(obj)->parent() == nullptr)
            {
                 setDarkTitleBar(static_cast<QWidget*>(obj)->winId(),on);
            }
            else if(QString(obj->metaObject()->className()) == "QComboBox" && static_cast<QComboBox*>(obj) != nullptr)
            {
                QPalette p3;
                p3.setColor(QPalette::Window,Qt::white);
                p3.setColor(QPalette::Button,Qt::white);
                p3.setColor(QPalette::Base,Qt::white);
                p3.setColor(QPalette::WindowText,Qt::black);
                p3.setColor(QPalette::ButtonText,Qt::black);
                static_cast<QComboBox*>(obj)->setPalette(p3);
                static_cast<QComboBox*>(obj)->update();
            }
        }
        if(QStyleFactory::keys().contains(native_style.toLatin1()) && QApplication::style() != QStyleFactory::create(native_style))
        {
            QApplication::setStyle(QStyleFactory::create(native_style));
        }
#if (QT_VERSION >= QT_VERSION_CHECK(6,5,0)) && defined(Q_OS_ANDROID)
        if(Android::getSystemVersion() >= 12 && !isSystemDarkMode())
            return;
#endif
#if (QT_VERSION >= QT_VERSION_CHECK(6,5,0)) && defined(Q_OS_WIN)
        //return;
#endif
        QPalette p;
        p.setColor(QPalette::Window,QColor(240,240,240));
        p.setColor(QPalette::Button,QColor(240,240,240));
        p.setColor(QPalette::WindowText,Qt::black);
        p.setColor(QPalette::ButtonText,Qt::black);
        p.setColor(QPalette::Base,Qt::white);
        p.setColor(QPalette::PlaceholderText,QColor(160,160,160));
        p.setColor(QPalette::Text,Qt::black);
        p.setColor(QPalette::Disabled, QPalette::Window, QColor(68, 68, 68));
        QApplication::setPalette(p);
    }
}

static QImage getApplicationIcon()
{
#ifdef Q_OS_ANDROID
    return Android::getApplicationIcon();
#else
    return QFileIconProvider().icon(QFileInfo(QApplication::applicationFilePath())).pixmap(256,256).toImage();
#endif
}

#endif // API_H
