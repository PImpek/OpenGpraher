#ifndef AXESOPTIONS_H
#define AXESOPTIONS_H

#include <QWidget>
#include "Data/graphopts.h"

namespace Ui {
class AxesOptions;
}

class AxesOptions : public QWidget
{
    Q_OBJECT
    
public:
    explicit AxesOptions(QWidget *parent = 0);
    ~AxesOptions();
    
    void setAxes(Axes *ax);

private:
    Ui::AxesOptions *ui;
    Axes *axes;

    void refreshList();
};

#endif // AXESOPTIONS_H
