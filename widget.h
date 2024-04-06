#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "api.h"
#include "playerwidget.h"
#include "myfiledialog.h"
#include "mediawidget.h"
#include "settingwidget.h"
#include "mytaskbarprogress.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    enum Mode
    {
        PlaySingle,
        PlayRandom,
        PlayRepeat
    };
    bool eventFilter(QObject *watched, QEvent *event);
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result);
#else
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
#endif
    bool playMedia(QString filepath);
    bool isPlaying();
    void showPlayerWidget();
    void hidePlayerWidget();
    void showAboutDialog(QString filepath = "");
    void loadMediaList();
    void removeMediaFromList(QString path);
    void checkDarkMode();
    void setDarkMode(bool on);
    static Widget* getCurrentWindow();

private slots:
    void refreshUI();
    void initSettings(bool clear = false);
    void initList(bool clear = false);
    void readSettings();

signals:
    void systemThemeChanged(bool on);
    void errorChanged(QString errorString);

private:
    PlayerWidget* playerwidget;
    QString message;
    QString title = "";
    QString settingpath;
    QSettings* settings = nullptr;
    QString listpath;
    QSettings* medialist = nullptr;
    QWidget* mainwidget;
    QWidget* controlwidget;
    QWidget* mediawidget;
    QDialog* aboutdialog;
    QLabel* iconlabel;
    QLabel* namelabel;
    QLabel* timelabel;
    QLabel* filenamelabel1;
    QLabel* filenamelabel2;
    QLabel* filepathlabel1;
    QLabel* filepathlabel2;
    QLabel* widthlabel1;
    QLabel* widthlabel2;
    QLabel* heightlabel1;
    QLabel* heightlabel2;
    QLabel* existlabel1;
    QLabel* existlabel2;
    QLabel* readablelabel1;
    QLabel* readablelabel2;
    QLabel* durationlabel1;
    QLabel* durationlabel2;
    QAction* copyaction;
    QAction* opendiraction;
    QAction* randomaction;
    QAction* singleaction;
    QAction* repeataction;
    QAction* aboutaction;
    QAction* saveframeaction;
    QAction* stayontopaction;
    QPushButton* openbutton;
    QPushButton* settingbutton;
    QPushButton* pausebutton;
    QPushButton* forwardbutton;
    QPushButton* backwardbutton;
    QPushButton* fullscreenbutton;
    QPushButton* aboutbutton;
    QPushButton* modebutton;
    QPushButton* volumebutton;
    QWidget* volumedlg;
    QSlider* volumeslider;
    QLabel* volumelabel;
    QSlider* slider;
    bool playing = false;
    bool lockslider = false;
    bool moving = false;
    bool ismax = false;
    bool paused = false;
    bool darkmode = false;
    bool oldThemeIsDark = false;
    QColor controlwidget_color = QColor(230,230,230,255);
    //QColor controlwidget_color = QColor(65,65,65,255);
    QPoint startpoint = QPoint(-1,-1);
    QTime starttime;
    QList<MediaWidget*> widgetlist;
    QWidget* widget;
    QScrollArea* area;
    QEventLoop* loop;
    Widget::Mode playmode = Widget::PlaySingle;
    MyTaskBarProgress* taskbar;
};
#endif // WIDGET_H
