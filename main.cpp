#include "worker.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    QWidget*     widget  = new QWidget;
    QHBoxLayout* hLayout = new QHBoxLayout;

    QCheckBox*   threadedCheckBox = new QCheckBox("Threaded");
    QPushButton* sortButton1      = new QPushButton("Sort some numbers");
    QPushButton* sortButton2      = new QPushButton("Sort some numbers");

    widget->setLayout(hLayout);
    hLayout->addWidget(threadedCheckBox);
    hLayout->addWidget(sortButton1);
    hLayout->addWidget(sortButton2);

    widget->show();

    QThread* thread1 = new QThread;
    Worker* worker1 = new Worker;
    worker1->setup(thread1, "1");
    worker1->moveToThread(thread1);

    QThread* thread2 = new QThread;
    Worker* worker2 = new Worker;
    worker2->setup(thread2, "2");
    worker2->moveToThread(thread2);

    qDebug() << thread1->idealThreadCount();

    QObject::connect(sortButton1, &QPushButton::clicked, threadedCheckBox, [=](){
        if(threadedCheckBox->isChecked() && !thread1->isRunning()){
            thread1->start();
        }else{
            qDebug() << "Program should be stalling";
            worker1->work();
        }
    }, Qt::DirectConnection);

    QObject::connect(sortButton2, &QPushButton::clicked, threadedCheckBox, [=](){
        if(threadedCheckBox->isChecked() && !thread2->isRunning()){
            thread2->start();
        }else{
            qDebug() << "Program should be stalling";
            worker2->work();
        }
    }, Qt::DirectConnection);

    return a.exec();
}


