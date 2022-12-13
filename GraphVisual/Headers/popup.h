#ifndef POPUP_H
#define POPUP_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
class Popup;
}

class Popup : public QDialog
{
    Q_OBJECT

public:
    explicit Popup(QWidget *parent = 0);
    ~Popup();

    QString getNodeName();

private:
    Ui::Popup *ui;
};

#endif // POPUP_H
