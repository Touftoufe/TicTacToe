#include "invisible_button.h"

invisible_button_c::invisible_button_c(QWidget *parent):QPushButton(parent)
{
    setAttribute(Qt::WA_Hover);
    m_sel = std::unique_ptr<QFrame>(new QFrame(parent));
    m_sel->setObjectName("m_sel");
    m_sel->setEnabled(true);
    m_sel->setGeometry(QRect(0, 0, 91, 71));
    m_sel->setStyleSheet(QString::fromUtf8(".QFrame {background: transparent; border-image: url(:/img/select.png) 0 0 0 0 stretch stretch;}"));
    m_sel->setFrameShape(QFrame::StyledPanel);
    m_sel->setFrameShadow(QFrame::Raised);
    m_sel->setHidden(true);
}

bool invisible_button_c::event(QEvent * e)
{
    switch(e->type())
    {
//    case QEvent::FocusIn:
    case QEvent::HoverEnter:
        m_sel->setHidden(false);
        return true;
        break;
//    case QEvent::FocusOut:
    case QEvent::HoverLeave:
        m_sel->setHidden(true);
        return true;
        break;
    case QEvent::Move:
        m_sel->setGeometry(QRect(geometry().x() + geometry().width(), geometry().y(), geometry().height() * 91/71, geometry().height()));
        break;
    default:
        break;
    }
    return QWidget::event(e);
}
