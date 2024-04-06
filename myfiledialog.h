#ifndef MYFILEDIALOG_H
#define MYFILEDIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include <QFileDialog>
#include "api.h"

#define Icon_Prepared

class MyFileSystemModel: public QFileSystemModel
{
public:
    explicit MyFileSystemModel(QObject *parent = nullptr) : QFileSystemModel(parent) {}
    ~MyFileSystemModel() {}
    QIcon dirIcon() {return diricon;}
    QList<QIcon> fileIcons() {return iconlist;}
    QList<QString> fileTypes() {return formatlist;}
    void setUseFileIconProvider(bool on) {provider_using = on;}
    bool useFileIconProvider() {return provider_using;}
    bool setFileIcon(QString suffix,QIcon icon)
    {
        if(suffix.contains("."))
        {
            suffix = suffix.right(suffix.length()-suffix.lastIndexOf(".")-1);
        }
        if(!suffix.isEmpty() && !icon.isNull())
        {
            formatlist << suffix;
            iconlist << icon;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool setDirIcon(QIcon icon)
    {
        if(!icon.isNull())
        {
            diricon = icon;
            return true;
        }
        else
        {
            return false;
        }
    }
    void clear()
    {
        formatlist = QList<QString>();
        iconlist = QList<QIcon>();
    }
    void setAlwaysUseFileProvider(bool on) {provider_top = on;}
    bool alwaysUseFileProvider() {return provider_top;}
    static bool multimedia_available()
    {
#if QT_MULTIMEDIA_LIB && QT_MULTIMEDIAWIDGETS_LIB
        return true;
#else
        return false;
#endif
    }
#ifdef Icon_Prepared
    void registerIcons()
    {
        QString resource_path = ":/icon/fileicons";
        QFileInfoList list = getFileList(resource_path);
        QStringList audiofilelist = {"mp3","flac","ogg","m4a","wav"};
        QStringList videofilelist = {"mp4","mkv","flv","mov"};
        QStringList imagefilelist = toStringList(QImageWriter::supportedImageFormats());
        QStringList photoshopfilelist = {"psd","psb"};
        for(int i = 0;i < list.count();i++)
        {
            QFileInfo info = list.at(i);
            QString filePath = info.filePath();
            QString type = filePath.left(filePath.indexOf("."));
            type = type.remove(0,QString(resource_path+"/").length());
            if(audiofilelist.contains(type))
            {
                for(QString s : audiofilelist)
                {
                    this->setFileIcon(s,QIcon(filePath));
                }
            }
            else if(videofilelist.contains(type))
            {
                for(QString s : videofilelist)
                {
                    this->setFileIcon(s,QIcon(filePath));
                }
            }
            else if(imagefilelist.contains(type))
            {
                for(QString s : imagefilelist)
                {
                    this->setFileIcon(s,QIcon(filePath));
                }
            }
            else if(photoshopfilelist.contains(type))
            {
                for(QString s : photoshopfilelist)
                {
                    this->setFileIcon(s,QIcon(filePath));
                }
            }
            else
            {
                this->setFileIcon(type,QIcon(filePath));
            }
        }
        QString diriconpath = ":/icon/folder.ico";
        this->setDirIcon(QIcon(diriconpath));
    }
#endif
private:
    bool provider_top = false;
#ifdef Q_OS_WIN
    bool provider_using = false;
#else
    bool provider_using = true;
#endif
    bool load_image_icon = false;
    //bool load_video_icon = false;
    QList<QString> formatlist;
    QList<QIcon> iconlist;
    QIcon diricon;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {
        if(index.isValid() && role == Qt::DecorationRole && index.column() == 0)
        {
            QFileInfo info = MyFileSystemModel::fileInfo(index);
            if(provider_top)
            {
                return QFileIconProvider().icon(info);
            }
            else if(info.isDir())
            {
                if(!diricon.isNull())
                {
                    return diricon;
                }
                else if(provider_using)
                {
                    return QFileIconProvider().icon(info);
                }
            }
            else if(info.isFile())
            {
                QIcon ret;
                QString suffix = info.suffix();
                suffix = suffix.toLower();
                int current = 0;
                if(load_image_icon && QImageReader::supportedImageFormats().contains(suffix.toLatin1()) && hasFilePermission(info.filePath(),QIODevice::ReadOnly))
                {
#ifndef QTCONCURRENT_RUNBASE_H
                    QByteArray content = readfile(info.filePath());
                    QPixmap p;
                    if(p.loadFromData(content))
                    {
                        return QIcon(p);
                    }
#else
                    QFuture r = QtConcurrent::run([info](){
                        QByteArray content = readfile(info.filePath());
                        QPixmap p;
                        if(p.loadFromData(content))
                        {
                            return QIcon(p);
                        }
                    });
                    r.waitForFinished();
                    ret = r.result();
                    if(!ret.isNull())
                        return ret;
#endif
                }
                while(current < formatlist.count() && current < iconlist.count() && ret.isNull())
                {
                    if(suffix == formatlist.at(current))
                    {
                        ret = iconlist.at(current);
                    }
                    current++;
                }
                if(!ret.isNull())
                {
                    return ret;
                }
                else if(provider_using)
                {
                    return QFileIconProvider().icon(info);
                }
            }
        }
        return QFileSystemModel::data(index,role);
    }
};

class MyFileDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MyFileDialog(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent* k);
    void resizeEvent(QResizeEvent* r);
    bool eventFilter(QObject* watched, QEvent* event);
    ~MyFileDialog();
    QString getOpenFileName(QWidget *parent = nullptr, const QString &caption = QString(),const QString &dir = QString());
    QString getExistingDirectory(QWidget *parent = nullptr, const QString &caption = QString(),const QString &dir = QString());
    bool load(QString path);
    MyFileSystemModel* fileSystemModel() {return m_fileSystemModel;}
    void setNeedDoubleClick(bool on) {need_double_click = on;}
    bool needDoubleClick() {return need_double_click;}
private slots:
    void listView_clicked(const QModelIndex &index);
private:
    MyFileSystemModel *m_fileSystemModel;
    QString m_currentPath;
    QString m_selectedFile;
    QString m_selectedPath;
    QLineEdit* pathEdit;
    QListView* listView;
    bool DirectoryMode;
    bool need_double_click;
    QPushButton* commitbutton;
    QPushButton* backbutton;
    QComboBox* pathbox;
};

#endif // MYFILEDIALOG_H
