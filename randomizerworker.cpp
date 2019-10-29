#include "randomizerworker.h"

RandomizerWorker::RandomizerWorker(QVector<char>* job, QObject* parent) : Worker(job, parent){

}

void RandomizerWorker::work(){

    qDebug() << m_id << "has begun randomizing";
    std::random_shuffle(m_elements->begin(), m_elements->end());
    qDebug() << m_id << "is done randomizing";

    emit finished(0);

}


