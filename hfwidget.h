#ifndef HFWIDGET_H
#define HFWIDGET_H

#include <QWidget>

namespace Ui {
class HFWidget;
}

class HFWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HFWidget(QWidget *parent = nullptr);
    ~HFWidget();

private:
    Ui::HFWidget *ui;
};

#endif // HFWIDGET_H
