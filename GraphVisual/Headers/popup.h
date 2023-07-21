#ifndef POPUP_H
#define POPUP_H

#include <QAbstractButton>
#include <QDialog>

namespace Ui {
class Popup;
}

class Popup : public QDialog {
    Q_OBJECT

public:
    explicit Popup(QWidget *parent = 0);
    ~Popup();

    QString getNodeName();

private:
    Ui::Popup *ui;
};

#endif // POPUP_H
