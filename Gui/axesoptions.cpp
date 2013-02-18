#include "axesoptions.h"
#include "ui_axesoptions.h"

AxesOptions::AxesOptions(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AxesOptions)
{
    ui->setupUi(this);
    this->axes = nullptr;
}

AxesOptions::~AxesOptions()
{
    delete ui;
}

void AxesOptions::setAxes(Axes *ax)
{
    this->axes = ax;
    this->refreshList();
}

void AxesOptions::refreshList()
{
    if (this->axes == nullptr)
    {
        this->ui->listWidget->clear();
        return;
    }
    if (this->axes->size() != this->ui->listWidget->count())
    {
        this->ui->listWidget->clear();
        std::for_each(axes->begin(),axes->end(),[this](Axis *ax){

            auto item = new QListWidgetItem(std::get<2>((*ax)).c_str());
            item->setData(Qt::UserRole,QVariant::fromValue<void *>(ax));
            this->ui->listWidget->addItem(item);
        });
    } else {
        for(int i = 0 ; i < axes->size() ; i++)
        {
            if(axes->at(i) != this->ui->listWidget->item(i)->data(Qt::UserRole).value<void *>())
            {
                this->ui->listWidget->clear();
                this->refreshList();
                return;
            } else {
                auto item = this->ui->listWidget->item(i);
                auto axis = axes->at(i);
                item->setText(std::get<2>((*axis)).c_str());
            }
        }
    }
}
