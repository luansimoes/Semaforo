#include "kernel.h"
#include <QDebug>
#include "luascriptengine.h"
#include "consolemodule.h"
#include "trafficlightwidgetwrapper.h"

#include <QtLua/Value>

class KernelPrivate {
public:
    KernelPrivate()
        : m_engine(nullptr)
    {
    }

    ~KernelPrivate()
    {
    }

    QtLua::Value registerGlobalObject(QObject *qobject, const QString &name);

    LuaScriptEngine *m_engine;
    ConsoleModule m_consoleModule;
};

QtLua::Value KernelPrivate::registerGlobalObject(QObject *qobject, const QString &name)
{
    if (!m_engine) {
        qDebug() << "No engine set, aborting global object creation.";
        return nullptr;
    }
    //newQObject() e globalObject()- criar
    m_engine->newQObject(qobject, name);

    return m_engine->getObject(name);
}

//BEGIN: Kernel
Kernel::Kernel()
    : d(new KernelPrivate)
{
    connect(&d->m_consoleModule, &ConsoleModule::message, this, &Kernel::processMessage);
}

Kernel::~Kernel(){}


QtLua::ValueBase::List Kernel::execute(TrafficLight *tl, const QString &script){

    if (!d->m_engine) {
        d->m_engine = new LuaScriptEngine(this);
    }

    // register meta types
    //qScriptRegisterSequenceMetaType<QList<GraphTheory::NodeWrapper*> >(d->m_engine);
    //qScriptRegisterSequenceMetaType<QList<GraphTheory::EdgeWrapper*> >(d->m_engine);
    //qRegisterMetaType<GraphTheory::NodeWrapper*>();
    //qRegisterMetaType<GraphTheory::EdgeWrapper*>();

    if (d->m_engine->isEvaluating()) {
        d->m_engine->abortEvaluation();
    }
    d->m_engine->collectGarbage();
    d->m_engine->pushContext();

    // add document
    TrafficLightWidgetWrapper tlWrapper(tl, d->m_engine);
    d->registerGlobalObject(&tlWrapper, "trafficLight");
    connect(&tlWrapper, &TrafficLightWidgetWrapper::message,
        this, &Kernel::processMessage);

    // set modules
    d->registerGlobalObject(&d->m_consoleModule,"Console");

    // set evaluation
    //d->m_engine->setProcessEventsInterval(100); //! TODO: Make that changeable.

    //QScriptValue result = d->m_engine->evaluate(script).toString();
    QtLua::ValueBase::List result = d->m_engine->evaluate(script);
    /*if (d->m_engine && d->m_engine->hasUncaughtException()) {
        emit message(result.toString(), WarningMessage);
        emit message(d->m_engine->uncaughtExceptionBacktrace().join("\n"), InfoMessage);
    }*/
    if (d->m_engine) {
        emit message(tr("@info status message after successful script execution", "<i>Execution Finished</i>"), InfoMessage);
        emit message(script, InfoMessage);
        d->m_engine->abortEvaluation();
    }
    // end processing messages
    disconnect(&tlWrapper, &TrafficLightWidgetWrapper::message, this, &Kernel::processMessage);

    emit executionFinished();
    //d->m_engine->globalObject().setProperty("Document", QScriptValue());

    return result;
}

void Kernel::stop(){
    d->m_engine->abortEvaluation();
}

void Kernel::processMessage(const QString &messageString, Kernel::MessageType type)
{
    emit message(messageString, type);
};
