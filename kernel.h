#ifndef KERNEL_H
#define KERNEL_H

#include <QObject>
#include <QtScript/QScriptValue>
#include "trafficlight.h"

#include <QtLua/ValueBase>

class KernelPrivate;

class Kernel : public QObject
{
    Q_OBJECT
public:
    explicit Kernel();
    virtual ~Kernel();
    QtLua::ValueBase::List execute(TrafficLight *tl, const QString &script);
    void stop();

    enum MessageType {
        InfoMessage,
        WarningMessage,
        ErrorMessage
    };

Q_SIGNALS:
    void executionFinished();
    void message(const QString &message, Kernel::MessageType type);

private Q_SLOTS:
    void processMessage(const QString &message,Kernel::MessageType type);

private:
    const QScopedPointer<KernelPrivate> d;


};

#endif // KERNEL_H
