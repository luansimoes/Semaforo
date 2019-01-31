#ifndef LIGHTWIDGET_H
#define LIGHTWIDGET_H

#include <QWidget>


class LightWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool on READ isOn WRITE setOn)

public:
    explicit LightWidget(const QColor &color, QWidget *parent = nullptr);

    bool isOn() const
        { return m_on; }
    void setOn(bool on)
    {
        if (on == m_on)
            return;
        m_on = on;
        update();
    }

signals:

public slots:
    void turnOff() { setOn(false); }
    void turnOn() { setOn(true); }

protected:
    virtual void paintEvent(QPaintEvent *) override;


private:
    QColor m_color;
    bool m_on;
};

#endif // LIGHTWIDGET_H
