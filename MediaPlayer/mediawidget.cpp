#include "mediawidget.h"
MediaWidget::MediaWidget(QWidget *parent) :
    QWidget(parent)
{
    iconlabel = new QLabel(this);
    namelabel = new QLabel(this);
    playbutton = new QPushButton(this);
    menubutton = new QPushButton(this);

    playaction = new QAction;
    deleteaction = new QAction;
    removeaction = new QAction;
    aboutaction = new QAction;
    opendiraction = new QAction;
    playaction->setText("播放");
    deleteaction->setText("删除文件");
    removeaction->setText("从列表移除");
    aboutaction->setText("属性");
#ifdef Q_Device_Desktop
    opendiraction->setText("打开文件夹");
#else
    opendiraction->setText("分享");
#endif

    playbutton->setIcon(this->style()->standardIcon(QStyle::SP_MediaPlay));
    playbutton->hide();
    //this->style()->standardIcon(QStyle::SP_MediaPlay).pixmap(100,100).save("play.png");
    iconlabel->setAlignment(Qt::AlignCenter);
    namelabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    //iconlabel->setStyleSheet("background-color:white;");
    //this->setStyleSheet("color:yellow;");
    this->refreshUI();

    this->installEventFilter(this);

    QObject::connect(playbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        emit play();
    });
    QObject::connect(menubutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
        this->showMenu(QPoint(this->mapToGlobal(menubutton->pos()).x(),this->mapToGlobal(menubutton->pos()).y()+menubutton->height()));
    });
    QObject::connect(playaction,QOverload<bool>::of(&QAction::triggered),[=](){
        emit play();
    });
    QObject::connect(aboutaction,QOverload<bool>::of(&QAction::triggered),[=](){
        emit about();
    });
    QObject::connect(deleteaction,QOverload<bool>::of(&QAction::triggered),[=](){
        emit deleteMedia();
    });
    QObject::connect(removeaction,QOverload<bool>::of(&QAction::triggered),[=](){
        emit removeFromList();
    });
    QObject::connect(opendiraction,QOverload<bool>::of(&QAction::triggered),[=](){
        emit opendir();
    });
}
MediaWidget::~MediaWidget()
{
}
void MediaWidget::refreshUI()
{
    menubutton->resize(this->height()-10,this->height()-10);
    menubutton->move(this->width()-menubutton->width()-5,5);
    iconlabel->resize((this->height()-10)/9.0*16.0,this->height()-10);
    iconlabel->move(5,5);
    namelabel->resize(menubutton->x()-iconlabel->x()-iconlabel->width()-10,this->height()-10);
    namelabel->move(iconlabel->x()+iconlabel->width()+5,iconlabel->y());
    QPixmap p;
    p.loadFromData(readfile(":/icon/appicon.ico"));
    p = p.scaled(iconlabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    iconlabel->setPixmap(p);
    /*
    namelabel->resize(iconlabel->height()*5,iconlabel->height());
    namelabel->move(iconlabel->x()+iconlabel->width()+5,iconlabel->y());
    if(menubutton->x()-namelabel->x()-namelabel->width() < 40)
        namelabel->resize(namelabel->width()+menubutton->x()-namelabel->x()-namelabel->width()-40,namelabel->height());
    playbutton->resize(menubutton->size());
    //playbutton->setIconSize(playbutton->size());
    playbutton->move(namelabel->x()+namelabel->width()+(menubutton->x()-namelabel->x()-namelabel->width())/2-playbutton->width()/2,menubutton->y());
    */
}
void MediaWidget::showMenu(QPoint pos)
{
    QMenu* m = new QMenu();
    m->addActions(QList<QAction*>() << playaction << aboutaction << removeaction << deleteaction << opendiraction);
//#ifdef Q_Device_Mobile
//#else
//    m->addAction(opendiraction);
//#endif
    hasmenu = true;
    m->exec(pos);
}
void MediaWidget::setFilePath(QString p)
{
    filepath = p;
    namelabel->setText(QFileInfo(filepath).fileName());
    namelabel->setToolTip(namelabel->text());
}
QString MediaWidget::filePath()
{
    return filepath;
}
bool MediaWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Resize)
        {
            this->refreshUI();
        }
        else if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            starttime = QTime::currentTime();
            if(mouseEvent->button() != Qt::RightButton)
            {
                p1 = QCursor::pos();
                /*
                QTimer::singleShot(press,[=](){
                    if(p1 != QPoint(-1,-1) && p1 == QCursor::pos())
                    {
                        this->showMenu();
                    }
                });
                */
            }
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            int interval = -1;
            if(starttime.isValid())
                interval = starttime.msecsTo(QTime::currentTime());
            if(mouseEvent->button() == Qt::RightButton)
            {
                this->showMenu();
            }
            else if(!hasmenu && p1 == QCursor::pos() && mouseEvent->button() == Qt::LeftButton && interval <= 500)
            {
                emit play();
            }
            else if(!hasmenu && p1 == QCursor::pos() && mouseEvent->button() == Qt::MiddleButton)
            {
                emit removeFromList();
            }
            else if(hasmenu)
            {
                hasmenu = false;
            }
            p1 = QPoint(-1,-1);
            starttime = QTime();
        }
    }
    return QObject::eventFilter(watched,event);
}
bool MediaWidget::setLongPressTime(int i)
{
    if(i > 0)
    {
        press = i;
        return true;
    }
    else
    {
        return false;
    }
}
int MediaWidget::longPressTime()
{
    return press;
}
bool MediaWidget::setMenuButtonIcon(QIcon icon)
{
    if(!icon.isNull())
    {
        menubutton->setIcon(icon);
        return true;
    }
    else
    {
        return false;
    }
}
