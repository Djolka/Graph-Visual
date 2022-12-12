#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>

class MyTextEdit : public QTextEdit {
    Q_OBJECT
public:
    MyTextEdit(QWidget *parent = 0) : QTextEdit(parent) {}

protected:
    void keyPressEvent(QKeyEvent *e) override;
};

#endif // MYTEXTEDIT_H
