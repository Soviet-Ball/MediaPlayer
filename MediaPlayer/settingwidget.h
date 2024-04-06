#ifndef SETTINGWIDGET_H
#define SETTINGWIDGET_H

#include <QWidget>
#include "api.h"

class SettingWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingWidget(QWidget *parent = nullptr);
    enum Mode
    {
        PushButton,
        ComboBox,
        RadioButton,
        InVaild
    };
    bool eventFilter(QObject *watched, QEvent *event);
    bool addItem(QString key,QString name,Mode mode,QVariant content = QVariant(),QVariant defaultValue = QVariant(),QVariant icon = QVariant(),QString tooltip = QString());
    bool setItemHeight(int height);
    int itemHeight() {return h;}
    QStringList allkeys() {return keylist;}
    Mode mode(int index);
    Mode mode(QString key) {return mode(keylist.indexOf(key));}
    QPushButton* pushButton(int index);
    QPushButton* pushButton(QString key) {return pushButton(keylist.indexOf(key));}
    QComboBox* comboBox(int index);
    QComboBox* comboBox(QString key) {return comboBox(keylist.indexOf(key));}
    QRadioButton* radioButton(int index);
    QRadioButton* radioButton(QString key) {return radioButton(keylist.indexOf(key));}
    bool setItemEnabled(int index,bool on);
    bool setItemEnabled(QString key,bool on) {return setItemEnabled(keylist.indexOf(key),on);}
    bool isItemEnabled(int index);
    bool isItemEnabled(QString key) {return isItemEnabled(keylist.indexOf(key));}
signals:
    void itemClicked(int index,QString key);
    void pushButtonClicked(int index,QString key);
    void radioButtonClicked(int index,QString key,bool check);
    void comboBoxChanged(int index,QString key,int currentIndex,QString currentText);
private slots:
    void refreshUI();
private:
    QTime time;
    QPoint p1;
    int h = 40;

    QScrollArea* area;
    QWidget* mainwidget;
    QList<QString> keylist;
    QList<QString> namelist;
    QList<Mode> modelist;
    QList<QVariant> valuelist;
    QList<QWidget*> widgetlist;
    QList<QLabel*> iconlabellist;
    QList<QLabel*> namelabellist;
    QList<QPushButton*> pushbuttonlist;
    QList<QComboBox*> comboboxlist;
    QList<QRadioButton*> radiobuttonlist;
    QList<QPixmap> iconlist;
};

#endif // SETTINGWIDGET_H
