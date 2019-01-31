#include "lightwidget.h"
#include <QPainter>

LightWidget::LightWidget(const QColor &color, QWidget *parent)
    : QWidget(parent), m_color(color), m_on(false)
{}

void LightWidget::paintEvent(QPaintEvent *)
{
    if (!m_on)
        return;
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(m_color);
    painter.drawEllipse(0, 0, height(), height());
}
