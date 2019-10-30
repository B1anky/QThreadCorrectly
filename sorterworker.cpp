#include "sorterworker.h"
#include <QMutex>
#include <QString>

SorterWorker::SorterWorker(QVector<char>* job, QObject* parent) : Worker(job, parent){

}

void SorterWorker::work(){

    qDebug() << m_id << "has begun sorting" << m_elements;
    if(m_id.toInt() & m_lockAcquirer.available()){
        m_lockAcquirer.acquire(2<<m_id.toInt());

        std::sort(m_elements->begin(), m_elements->end());
        qDebug() << m_id << "is done sorting";

        m_lockAcquirer.release(2<<m_id.toInt());
    }
    emit finished(0);

}
