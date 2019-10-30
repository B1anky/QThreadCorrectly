#include "workernetwork.h"

WorkerNetwork::WorkerNetwork(QWidget* parent) : QWidget(parent), m_workers(0){
    //Create base widgets
    m_mainHBoxLayout      = new QHBoxLayout;

    m_threadedCheckBox    = new QCheckBox("Threaded");
    m_addNewWorkersButton = new QPushButton("Add new worker");

    //Layout setup
    this->setLayout(m_mainHBoxLayout);
    m_mainHBoxLayout->addWidget(m_threadedCheckBox);
    m_mainHBoxLayout->addWidget(m_addNewWorkersButton);

    //Connection makes a new array
    QObject::connect(m_addNewWorkersButton, &QPushButton::clicked, this, &WorkerNetwork::createNewWorker, Qt::DirectConnection);

}

void WorkerNetwork::createNewWorker(){
    QVBoxLayout* vBoxLayout = new QVBoxLayout;

    ++m_workers;    

    QVector<char>* newJob = new QVector<char>();
    QThread* generateThread = new QThread;
    GeneratorWorker* generateWorker = new GeneratorWorker(newJob);
    generateWorker->setup(generateThread, QString::number(m_workers));
    generateWorker->moveToThread(generateThread);
    generateThread->start();

    QPushButton* sortButton      = new QPushButton(QString("Sort bin %1").arg(QString::number(m_workers)));
    QPushButton* randomizeButton = new QPushButton(QString("Randomize bin %1").arg(QString::number(m_workers)));
    vBoxLayout->addWidget(sortButton);
    vBoxLayout->addWidget(randomizeButton);

    m_mainHBoxLayout->addLayout(vBoxLayout);

    QThread* sorterThread = new QThread;
    SorterWorker* sortedWorker = new SorterWorker(newJob);
    sortedWorker->setup(sorterThread, QString::number(m_workers));
    sortedWorker->moveToThread(sorterThread);

    QThread* randomizerThread = new QThread;
    RandomizerWorker* randomizerWorker = new RandomizerWorker(newJob);
    randomizerWorker->setup(randomizerThread, QString::number(m_workers));
    randomizerWorker->moveToThread(randomizerThread);

    setupThreadAndWorkerConnection(sorterThread, sortedWorker, sortButton);
    setupThreadAndWorkerConnection(randomizerThread, randomizerWorker, randomizeButton);
}

void WorkerNetwork::setupThreadAndWorkerConnection(QThread* thread, Worker* worker, QPushButton* button){
    connect(button, &QPushButton::clicked, this, [this, thread, worker](){
        if(m_threadedCheckBox->isChecked()){
            thread->start();
        }else{
            qDebug() << "Program should be stalling";
            worker->work();
        }
    }, Qt::QueuedConnection);
}
