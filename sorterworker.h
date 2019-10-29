#ifndef SORTERWORKER_H
#define SORTERWORKER_H

#include "worker.h"

class SorterWorker : public Worker{

    Q_OBJECT

public:

    SorterWorker(QVector<char>* job, QObject* parent = nullptr);

    void work() override;

};

#endif // SORTERWORKER_H
