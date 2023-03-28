#ifndef INVISIBLE_BUTTON_C_H
#define INVISIBLE_BUTTON_C_H

#include <iostream>
#include <QPushButton>
#include <QWidget>
#include <QEvent>

class invisible_button_c : public QPushButton
{
    Q_OBJECT
public:
    explicit invisible_button_c(QWidget *parent = nullptr);
    void set_selector(QWidget* sel);

protected:
    virtual bool event(QEvent * e) override;
    QWidget *m_sel;
};

#endif // INVISIBLE_BUTTON_C_H
