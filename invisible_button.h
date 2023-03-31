#ifndef INVISIBLE_BUTTON_C_H
#define INVISIBLE_BUTTON_C_H

#include <iostream>
#include <memory>
#include <QPushButton>
#include <QFrame>
#include <QEvent>

class invisible_button_c : public QPushButton
{
    Q_OBJECT
public:
    explicit invisible_button_c(QWidget *parent = nullptr);

protected:
    virtual bool event(QEvent * e) override;
    QFrame* m_sel;
};

#endif // INVISIBLE_BUTTON_C_H
