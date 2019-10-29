#ifndef RANDOMIZERWORKER_H
#define RANDOMIZERWORKER_H

#include "worker.h"

class RandomizerWorker : public Worker{

    Q_OBJECT

public:

    RandomizerWorker(QVector<char>* job, QObject* parent = nullptr);

    void work() override;

};

#endif // RANDOMIZERWORKER_H
