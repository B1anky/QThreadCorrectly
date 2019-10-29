#ifndef GENERATORWORKER_H
#define GENERATORWORKER_H

#include "worker.h"

class GeneratorWorker : public Worker{

    Q_OBJECT

public:

    GeneratorWorker(QVector<char>* job, QObject* parent = nullptr);

    void work() override;

};

#endif // GENERATORWORKER_H
