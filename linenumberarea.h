#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
#include "scripteditor.h"

class LineNumberArea : public QWidget
{
    Q_OBJECT
public:
    explicit LineNumberArea(ScriptEditor *editor);
    QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    ScriptEditor *m_codeEditor;
};

#endif // LINENUMBERAREA_H
