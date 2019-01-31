#include "trafficlightwidgetwrapper.h"
#include "trafficlight.h"

TrafficLightWidgetWrapper::TrafficLightWidgetWrapper(TrafficLight *tl, LuaScriptEngine *engine) :
    m_widget(tl), m_engine(engine)
{
    connect(this, SIGNAL(turnRed()), m_widget, SLOT(&TrafficLight::setRedState));
    connect(this, SIGNAL(turnYellow()), m_widget, SLOT(&TrafficLight::setYellowState));
    connect(this, SIGNAL(turnGreen()), m_widget, SLOT(&TrafficLight::setGreenState));
}


LuaScriptEngine *TrafficLightWidgetWrapper::engine() const{
    return m_engine;
}

void TrafficLightWidgetWrapper::red(){
    emit turnRed();
}

void TrafficLightWidgetWrapper::yellow(){
    emit turnYellow();
}

void TrafficLightWidgetWrapper::green(){
    emit turnGreen();
}
