#include "hfwidget.h"
#include "ui_hfwidget.h"

HFWidget::HFWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HFWidget)
{
    ui->setupUi(this);
}

HFWidget::~HFWidget()
{
    delete ui;
}
