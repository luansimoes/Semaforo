#ifndef LUASCRIPTENGINE_H
#define LUASCRIPTENGINE_H

#include <QString>
#include <QObject>
#include <QtLua/State>
#include <QtLua/Value>
#include <QtLua/ValueBase>



class LuaScriptEngine : public QObject
{
public:
    explicit LuaScriptEngine(QObject *parent=nullptr);
    virtual ~LuaScriptEngine();
    void printError(const QString& variableName, const QString& reason);


    void newQObject(QObject *object, const QString &name);
    QtLua::Value getObject(const QString &name);

    bool isEvaluating();
    void abortEvaluation();
    void collectGarbage();
    void pushContext(){}
    QtLua::ValueBase::List evaluate(const QString &statements);


private:
    QtLua::State *l;
};

#endif // LUASCRIPTENGINE_H
