#include "settingwidget.h"

SettingWidget::SettingWidget(QWidget *parent)
    : QWidget{parent}
{
    area = new QScrollArea(this);
    mainwidget = new QWidget(this);
    mainwidget->resize(this->width()-20,(widgetlist.count()+1)*h);
    area->setWidget(mainwidget);
    area->setGeometry(0,0,this->width(),this->height());
    area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    QScroller::grabGesture(area->viewport(),QScroller::TouchGesture);
    mainwidget->show();
    this->installEventFilter(this);
}
bool SettingWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this)
    {
        if(event->type() == QEvent::Resize)
        {
            this->refreshUI();
        }
    }
    else if(widgetlist.contains((QWidget*)watched) && (QWidget*)watched != nullptr)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent* e = static_cast<QMouseEvent*>(event);
            if(e->button() == Qt::LeftButton)
            {
                time = QTime::currentTime();
                p1 = e->pos();
            }
        }
        else if(event->type() == QEvent::MouseButtonRelease)
        {
            QMouseEvent* e = static_cast<QMouseEvent*>(event);
            if(e->button() == Qt::LeftButton)
            {
                int interval = -1;
                if(time.isValid() && !p1.isNull())
                {
                    interval = time.msecsTo(QTime::currentTime());
                    if(e->pos() == p1)
                    {
                        int index = widgetlist.indexOf((QWidget*)watched);
                        QString key = keylist.at(index);
                        emit itemClicked(index,key);
                    }
                }
                time = QTime();
                p1 = QPoint();
            }
        }
    }
    return QWidget::eventFilter(watched,event);
}
void SettingWidget::refreshUI()
{
    mainwidget->resize(this->width()-20,(widgetlist.count()+1)*h);
    area->setGeometry(0,0,this->width(),this->height());
    for(int i = 0;i < widgetlist.count();i++)
    {
        QWidget* w = widgetlist.at(i);
        QLabel* namelabel = namelabellist.at(i);
        QPushButton* pushbutton = pushbuttonlist.at(i);
        QComboBox* combobox = comboboxlist.at(i);
        QRadioButton* radiobutton = radiobuttonlist.at(i);
        int delta = mainwidget->width() - w->width();
        w->resize(mainwidget->width(),w->height());
        namelabel->resize(namelabel->width()+delta,namelabel->height());
        pushbutton->move(pushbutton->x()+delta,pushbutton->y());
        combobox->move(combobox->x()+delta,combobox->y());
        radiobutton->move(radiobutton->x()+delta,radiobutton->y());
    }
}
bool SettingWidget::addItem(QString key, QString name, Mode mode, QVariant content, QVariant defaultValue,QVariant icon, QString tooltip)
{
    if(!key.isEmpty() && !keylist.contains(key) && !name.isEmpty() && mode != InVaild)
    {
        QStringList combobox_items;
        QString button_text;
        QPixmap pix;
        if(content.canConvert<QStringList>())
            combobox_items = content.value<QStringList>();
        if(content.canConvert<QString>())
            button_text = content.value<QString>();
        if(icon.canConvert<QPixmap>())
            pix = icon.value<QPixmap>();
        else if(icon.canConvert<QImage>())
            pix = QPixmap::fromImage(icon.value<QImage>());
        else if(icon.canConvert<QIcon>())
            pix = icon.value<QIcon>().pixmap(256,256);

        QWidget* w = new QWidget(mainwidget);
        QLabel* iconlabel = new QLabel(w);
        QLabel* namelabel = new QLabel(w);
        QPushButton* pushbutton = new QPushButton(w);
        QComboBox* combobox = new QComboBox(w);
        QRadioButton* radiobutton = new QRadioButton(w);

        mainwidget->resize(this->width()-20,(widgetlist.count()+1)*h);
        w->resize(mainwidget->width(),h);
        w->move(0,widgetlist.count()*h);
        iconlabel->setAlignment(Qt::AlignCenter);
        namelabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        namelabel->setToolTip(tooltip);
        namelabel->setOpenExternalLinks(true);

        QSize s1 = QSize((h-10.0)/3.0*5.0,h-10);
        if(mode == RadioButton)
        {
            s1.setWidth(s1.height());
        }
        else if(mode == ComboBox || mode == PushButton)
        {
            int w1 = 0;
            if(mode == ComboBox)
            {
                w1 = nativeLabelSize(combobox_items.at(getLongestStringIndex(combobox_items))).width();
            }
            else
            {
                w1 = nativeLabelSize(button_text).width();
            }
            if(w1 > w->width()/2.0)
                s1.setWidth(w->width()/2);
            else if(w1 > s1.width())
                s1.setWidth(w1);
        }
        if(mode == PushButton)
        {
            pushbutton->resize(s1);
            pushbutton->move(w->width()-5-pushbutton->width(),w->height()/2.0-pushbutton->height()/2.0);
        }
        else if(mode == ComboBox)
        {
            combobox->resize(s1);
            combobox->move(w->width()-5-combobox->width(),w->height()/2.0-combobox->height()/2.0);
        }
        else if(mode == RadioButton)
        {
            radiobutton->resize(s1);
            radiobutton->move(w->width()-5-radiobutton->width(),w->height()/2.0-radiobutton->height()/2.0);
        }

        QSize s2 = QSize(h-10,h-10);
        if(pix.isNull())
        {
            iconlabel->hide();
            namelabel->resize(w->width()/2-5,h-10);
            namelabel->move(5,5);
        }
        else
        {
            iconlabel->resize(s2);
            iconlabel->move(5,5);
            namelabel->resize(w->width()/2-iconlabel->x()-iconlabel->width(),iconlabel->width());
            namelabel->move(iconlabel->width()+iconlabel->x(),iconlabel->y());
            QPixmap p = pix.scaled(iconlabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
            iconlabel->setPixmap(p);
        }

        namelabel->setText(name);
        pushbutton->setText(button_text);
        combobox->addItems(combobox_items);
        pushbutton->hide();
        combobox->hide();
        radiobutton->hide();
        if(mode == PushButton)
            pushbutton->show();
        else if(mode == ComboBox)
            combobox->show();
        else if(mode == RadioButton)
            radiobutton->show();
        w->installEventFilter(this);
        w->show();

        if(mode == ComboBox)
        {
            if(defaultValue.canConvert<int>())
                combobox->setCurrentIndex(defaultValue.value<int>());
            else if(defaultValue.canConvert<QString>())
                combobox->setCurrentText(defaultValue.value<QString>());
        }
        else if(mode == RadioButton)
        {
            if(defaultValue.canConvert<bool>())
                radiobutton->setChecked(defaultValue.value<bool>());
        }

        QObject::connect(pushbutton,QOverload<bool>::of(&QPushButton::clicked),[=](){
            emit pushButtonClicked(pushbuttonlist.indexOf(pushbutton),key);
        });
        QObject::connect(combobox,QOverload<int>::of(&QComboBox::currentIndexChanged),[=](int index){
            emit comboBoxChanged(comboboxlist.indexOf(combobox),key,index,combobox->currentText());
        });
        QObject::connect(radiobutton,QOverload<bool>::of(&QRadioButton::clicked),[=](){
            emit radioButtonClicked(radiobuttonlist.indexOf(radiobutton),key,radiobutton->isChecked());
        });

        widgetlist.append(w);
        keylist.append(key);
        namelist.append(name);
        modelist.append(mode);
        pushbuttonlist.append(pushbutton);
        comboboxlist.append(combobox);
        radiobuttonlist.append(radiobutton);
        namelabellist.append(namelabel);
        iconlabellist.append(iconlabel);
        iconlist.append(pix);
        return true;
    }
    else
    {
        return false;
    }
}
bool SettingWidget::setItemHeight(int height)
{
    if(height > 0)
    {
        if(height == h)
            return true;

        for(int i = 0;i < widgetlist.count();i++)
        {
            QWidget* w = widgetlist.at(i);
            QLabel* iconlabel = iconlabellist.at(i);
            QLabel* namelabel = namelabellist.at(i);
            QPushButton* pushbutton = pushbuttonlist.at(i);
            QComboBox* combobox = comboboxlist.at(i);
            QRadioButton* radiobutton = radiobuttonlist.at(i);
            Mode mode = modelist.at(i);
            QPixmap icon = iconlist.at(i);
            //int delta = height - h;
            w->resize(mainwidget->width(),height);
            w->move(0,height*i);

            QSize s1 = QSize((height-10.0)/3.0*5.0,height-10);
            if(mode == RadioButton)
            {
                s1.setWidth(s1.height());
            }
            else if(mode == ComboBox || mode == PushButton)
            {
                int w1 = 0;
                if(mode == ComboBox)
                {
                    w1 = combobox->width();
                }
                else
                {
                    w1 = pushbutton->width();
                }
                if(w1 > w->width()/2.0)
                    s1.setWidth(w->width()/2);
                else if(w1 > s1.width())
                    s1.setWidth(w1);
            }
            if(mode == PushButton)
            {
                pushbutton->resize(s1);
                pushbutton->move(w->width()-5-pushbutton->width(),w->height()/2.0-pushbutton->height()/2.0);
            }
            else if(mode == ComboBox)
            {
                combobox->resize(s1);
                combobox->move(w->width()-5-combobox->width(),w->height()/2.0-combobox->height()/2.0);
            }
            else if(mode == RadioButton)
            {
                radiobutton->resize(s1);
                radiobutton->move(w->width()-5-radiobutton->width(),w->height()/2.0-radiobutton->height()/2.0);
            }

            QSize s2 = QSize(height-10,height-10);
            if(icon.isNull())
            {
                iconlabel->hide();
                namelabel->resize(w->width()/2-5,height-10);
                namelabel->move(5,5);
            }
            else
            {
                iconlabel->resize(s2);
                iconlabel->move(5,5);
                namelabel->resize(w->width()/2-iconlabel->x()-iconlabel->width(),iconlabel->width());
                namelabel->move(iconlabel->width()+iconlabel->x(),iconlabel->y());
                QPixmap p = icon.scaled(iconlabel->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
                iconlabel->setPixmap(p);
            }
        }
        h = height;
        return true;
    }
    else
    {
        return false;
    }
}
SettingWidget::Mode SettingWidget::mode(int index)
{
    if(index < modelist.count())
        return modelist.at(index);
    else
        return InVaild;
}
bool SettingWidget::setItemEnabled(int index, bool on)
{
    if(index < widgetlist.count())
    {
        QPushButton* pushbutton = pushbuttonlist.at(index);
        QComboBox* combobox = comboboxlist.at(index);
        QRadioButton* radiobutton = radiobuttonlist.at(index);
        pushbutton->setEnabled(on);
        combobox->setEnabled(on);
        radiobutton->setEnabled(on);
        return true;
    }
    else
    {
        return false;
    }
}
bool SettingWidget::isItemEnabled(int index)
{
    if(index < widgetlist.count())
    {
        QPushButton* pushbutton = pushbuttonlist.at(index);
        return pushbutton->isEnabled();
    }
    else
    {
        return false;
    }
}
QPushButton* SettingWidget::pushButton(int index)
{
    if(index >= 0 && index < pushbuttonlist.count())
    {
        return pushbuttonlist.at(index);
    }
    else
    {
        return nullptr;
    }
}
QComboBox* SettingWidget::comboBox(int index)
{
    if(index >= 0 && index < comboboxlist.count())
    {
        return comboboxlist.at(index);
    }
    else
    {
        return nullptr;
    }
}
QRadioButton* SettingWidget::radioButton(int index)
{
    if(index >= 0 && index < radiobuttonlist.count())
    {
        return radiobuttonlist.at(index);
    }
    else
    {
        return nullptr;
    }
}
