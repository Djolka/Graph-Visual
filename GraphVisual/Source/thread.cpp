#include "Headers/thread.h"

mythread::mythread(QObject *parent) : QThread(parent){

}

void mythread::run(){
   //QThread::run();
   emit updateWindow();
}
