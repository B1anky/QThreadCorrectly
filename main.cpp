#include "worker.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>

void setupConnections(QThread* thread, Worker* worker, QCheckBox* checkbox, QPushButton* button){
    QObject::connect(button, &QPushButton::clicked, checkbox, [=](){
        if(checkbox->isChecked() && !thread->isRunning()){
            thread->start();
        }else{
            qDebug() << "Program should be stalling";
            worker->work();
        }
    }, Qt::DirectConnection);
}

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

    setupConnections(thread1, worker1, threadedCheckBox, sortButton1);
    setupConnections(thread2, worker2, threadedCheckBox, sortButton2);

    return a.exec();
}
