#include "consolemodule.h"

ConsoleModule::ConsoleModule(QObject *parent) : QObject(parent)
{

}

ConsoleModule::~ConsoleModule()
{
}

QList< QPair< Kernel::MessageType, QString > > ConsoleModule::backlog() const
{
    return m_backlog;
}

void ConsoleModule::clear()
{
    m_backlog.clear();
}

void ConsoleModule::log(const QString& messageString)
{
    m_backlog.append(qMakePair<Kernel::MessageType, QString>(Kernel::InfoMessage, messageString));
    emit(message(messageString, Kernel::InfoMessage));
}

void ConsoleModule::debug(const QString& messageString)
{
    m_backlog.append(qMakePair<Kernel::MessageType, QString>(Kernel::WarningMessage, messageString));
    emit(message(messageString, Kernel::WarningMessage));
}

void ConsoleModule::error(const QString& messageString)
{
    m_backlog.append(qMakePair<Kernel::MessageType, QString>(Kernel::ErrorMessage, messageString));
    emit(message(messageString, Kernel::ErrorMessage));
}
