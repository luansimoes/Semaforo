#ifndef TRAFFICLIGHTWIDGETWRAPPER_H
#define TRAFFICLIGHTWIDGETWRAPPER_H

#include <QObject>
#include <QSharedPointer>
#include <trafficlight.h>
#include <luascriptengine.h>
#include "kernel.h"

class TrafficLightWidgetWrapper : public QObject
{
    Q_OBJECT
public:
    explicit TrafficLightWidgetWrapper(TrafficLight *tl, LuaScriptEngine *engine);
    virtual ~TrafficLightWidgetWrapper(){}

    LuaScriptEngine* engine() const;

Q_SIGNALS:
    void message(const QString &messageString, Kernel::MessageType type) const;
    void turnRed();
    void turnYellow();
    void turnGreen();

private:
    Q_DISABLE_COPY(TrafficLightWidgetWrapper)
    const TrafficLight *m_widget;
    LuaScriptEngine *m_engine;

public slots:
    void red();
    void yellow();
    void green();
};

#endif // TRAFFICLIGHTWIDGETWRAPPER_H
