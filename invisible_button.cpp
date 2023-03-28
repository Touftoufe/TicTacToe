#include "invisible_button.h"

invisible_button_c::invisible_button_c(QWidget *parent):QPushButton(parent), m_sel(nullptr)
{
    setAttribute(Qt::WA_Hover);
}

void invisible_button_c::set_selector(QWidget* sel)
{
    m_sel = sel;
}

bool invisible_button_c::event(QEvent * e)
{
    switch(e->type())
    {
    case QEvent::HoverEnter:
        if(m_sel) m_sel->setHidden(false);
        return true;
        break;
    case QEvent::HoverLeave:
        if(m_sel) m_sel->setHidden(true);
        return true;
        break;
    default:
        break;
    }
    return QWidget::event(e);
}
