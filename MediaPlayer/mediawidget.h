#ifndef MEDIAWIDGET_H
#define MEDIAWIDGET_H

#include <QWidget>
#include "api.h"

class MediaWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MediaWidget(QWidget *parent = nullptr);
    ~MediaWidget();
    void showMenu(QPoint pos = QCursor::pos());
    void refreshUI();
    void setFilePath(QString p);
    QString filePath();
    bool eventFilter(QObject *watched, QEvent *event);
    bool setLongPressTime(int i);
    int longPressTime();
    bool setMenuButtonIcon(QIcon icon);
signals:
    void deleteMedia();
    void removeFromList();
    void about();
    void opendir();
    void play();
private:
    int press = 500;
    bool hasmenu = false;
    QTime starttime;
    QString filepath = "";
    QPoint p1 = QPoint(-1,-1);
    QLabel* iconlabel;
    QLabel* namelabel;
    QPushButton* playbutton;
    QPushButton* menubutton;
    QAction* deleteaction;
    QAction* removeaction;
    QAction* aboutaction;
    QAction* opendiraction;
    QAction* playaction;
};

#endif // MEDIAWIDGET_H
