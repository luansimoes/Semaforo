#include "luascriptengine.h"
#include "lua.h"

#include <QDebug>





LuaScriptEngine::LuaScriptEngine(QObject *parent): l(new QtLua::State())
{
    this->setParent(parent);

}

LuaScriptEngine::~LuaScriptEngine() {
    if(l) l->deleteLater();
}

void LuaScriptEngine::printError(const QString &variableName, const QString &reason) {
    qDebug()<<"Error: can't get ["<<variableName<<"]. "<<reason;
}

void LuaScriptEngine::newQObject(QObject *object, const QString &name){
    (*l)[name] = QtLua::Value(l, object);
}

QtLua::Value LuaScriptEngine::getObject(const QString &name){
    return l->at(name);
}

QtLua::ValueBase::List LuaScriptEngine::evaluate(const QString &statements){
    return l->exec_statements(statements);
}

bool LuaScriptEngine::isEvaluating(){

    return false;
}

void LuaScriptEngine::abortEvaluation(){

}

void LuaScriptEngine::collectGarbage(){
    l->gc_collect();
}




