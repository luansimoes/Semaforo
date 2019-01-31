#include "linenumberarea.h"

LineNumberArea::LineNumberArea(ScriptEditor *editor) : QWidget(editor)
{
    m_codeEditor = editor;
}

QSize LineNumberArea::sizeHint() const{
    return QSize(m_codeEditor->lineNumberAreaWidth(), 0);
}

void LineNumberArea::paintEvent(QPaintEvent *event){
    m_codeEditor->lineNumberAreaPaintEvent(event);
}
