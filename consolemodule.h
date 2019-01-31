#ifndef CONSOLEMODULE_H
#define CONSOLEMODULE_H

#include <QObject>
#include "kernel.h"

class ConsoleModule : public QObject
{
    Q_OBJECT
public:
    explicit ConsoleModule(QObject *parent = nullptr);
    ~ConsoleModule();

    void clear();
    QList< QPair<Kernel::MessageType, QString> > backlog() const;

public Q_SLOTS:
    Q_INVOKABLE void log(const QString &message);
    Q_INVOKABLE void debug(const QString &message);
    Q_INVOKABLE void error(const QString &message);

Q_SIGNALS:
    void message(const QString &message, Kernel::MessageType type);

private:
    QList< QPair<Kernel::MessageType, QString> > m_backlog;


};

#endif // CONSOLEMODULE_H
