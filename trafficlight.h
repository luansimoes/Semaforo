#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <QWidget>
#include <QState>
#include "lightwidget.h"
#include "trafficlightwidget.h"

class TrafficLight : public QWidget
{
    Q_OBJECT

public:
    TrafficLight(QWidget *parent = nullptr);
    ~TrafficLight(){}

    QState *createLightState(LightWidget *light, QWidget *main, QState *parent = nullptr);


    TrafficLightWidget *widget();
    QStateMachine *rMachine(){return machine;}

    void setInitialState();

private:
    TrafficLightWidget *m_widget;
    QStateMachine *machine;

public slots:
    void setRedState();
    void setGreenState();
    void setYellowState();
};

#endif // TRAFFICLIGHT_H
