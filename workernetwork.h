#ifndef WORKERNETWORK_H
#define WORKERNETWORK_H

#include "generatorworker.h"
#include "sorterworker.h"
#include "randomizerworker.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>
#include <QWidget>

class WorkerNetwork : public QWidget{

    Q_OBJECT

public:

    WorkerNetwork(QWidget* parent = nullptr);

    void setupThreadAndWorkerConnection(QThread* thread, Worker* worker, QPushButton* button);

public slots:

    void createNewWorker();

protected:    

    QHBoxLayout* m_mainHBoxLayout;
    QCheckBox*   m_threadedCheckBox;
    QPushButton* m_addNewWorkersButton;

    int          m_workers;

};

#endif // WORKERNETWORK_H
