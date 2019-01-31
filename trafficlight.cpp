#include <QtWidgets>
#include "mainwindow.h"
#include "kernel.h"
#include "QDebug"


TrafficLight::TrafficLight(QWidget *parent)
        : QWidget(parent)
    {
        QVBoxLayout *vbox = new QVBoxLayout(this);
        m_widget = new TrafficLightWidget();
        vbox->addWidget(m_widget);
        vbox->setMargin(0);

        setInitialState();



        /*machine = new QStateMachine(this);
        QState *red = createLightState(m_widget->redLight(), parent);
        red->setObjectName("red");
        QState *yellow = createLightState(m_widget->yellowLight(), parent);
        yellow->setObjectName("yellow");
        red->addTransition(red, SIGNAL(finished()), yellow);
        QState *green = createLightState(m_widget->greenLight(), parent);
        green->setObjectName("green");
        yellow->addTransition(yellow, SIGNAL(finished()), green);
        green->addTransition(green, SIGNAL(finished()), yellow);
        yellow->addTransition(yellow, SIGNAL(finished()), red);

        machine->addState(red);
        machine->addState(yellow);
        machine->addState(green);
        machine->setInitialState(red);
        machine->start();*/
    }



void TrafficLight::setInitialState(){
    setRedState();
}

QState *TrafficLight::createLightState(LightWidget *light, QWidget *main, QState *parent)
{

    MainWindow *mw = dynamic_cast<MainWindow*>(main);
    QState *lightState = new QState(parent);
    QState *waiting = new QState(lightState);
    QObject::connect(waiting, SIGNAL(entered()), light, SLOT(turnOn()));
    QObject::connect(waiting, SIGNAL(exited()), light, SLOT(turnOff()));
    QFinalState *done = new QFinalState(lightState);
    waiting->addTransition(mw->kernel(), SIGNAL(executionFinished()), done);
    lightState->setInitialState(waiting);
    return lightState;
}

void TrafficLight::setRedState(){
    m_widget->redLight()->turnOn();
    m_widget->greenLight()->turnOff();
    m_widget->yellowLight()->turnOff();
}

void TrafficLight::setGreenState(){
    m_widget->redLight()->turnOff();
    m_widget->greenLight()->turnOn();
    m_widget->yellowLight()->turnOff();
}

void TrafficLight::setYellowState(){
    m_widget->redLight()->turnOff();
    m_widget->greenLight()->turnOff();
    m_widget->yellowLight()->turnOn();
}
