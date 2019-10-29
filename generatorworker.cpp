#include "generatorworker.h"


GeneratorWorker::GeneratorWorker(QVector<char>* job, QObject* parent) : Worker(job, parent){

}

void GeneratorWorker::work(){

    qDebug() << QString("Begun generating for bin %1").arg(m_id);
    for(int i = 0; i < 1000000; ++i){
        for(char j = 0; j < CHAR_MAX; ++j){
            m_elements->push_back(j);
        }
    }
    qDebug() << QString("Finished generating for bin %1").arg(m_id);

    emit finished(0);

}
