#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>

class mythread : public QThread
{
    Q_OBJECT
public:
    explicit mythread(QObject *parent = nullptr);
protected:
    void run() override;

signals:
    void updateWindow();
};


#endif // MYTHREAD_H
