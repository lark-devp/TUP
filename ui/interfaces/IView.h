#pragma once

#include <QWidget>


class IView : public QWidget
{
public:
     explicit IView(QWidget* parent = nullptr) : QWidget(parent) {}
    virtual ~IView() = default;


    virtual QWidget* getWidget() = 0;


    virtual void showView() { if(getWidget()) getWidget()->show(); }


    virtual void hideView() { if(getWidget()) getWidget()->hide(); }
};
