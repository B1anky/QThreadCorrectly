#include "randomizerworker.h"

RandomizerWorker::RandomizerWorker(QVector<char>* job, QObject* parent) : Worker(job, parent){

}

void RandomizerWorker::work(){

    qDebug() << m_id << "has begun randomizing" << m_elements;
    if(m_id.toInt() & m_lockAcquirer.available()){
        m_lockAcquirer.acquire(2<<m_id.toInt());

        std::random_shuffle(m_elements->begin(), m_elements->end());
        qDebug() << m_id << "is done randomizing";

        m_lockAcquirer.release(2<<m_id.toInt());
    }
    emit finished(0);

}


