#include "sorterworker.h"

SorterWorker::SorterWorker(QVector<char>* job, QObject* parent) : Worker(job, parent){

}

void SorterWorker::work(){

    qDebug() << m_id << "has begun sorting";
    std::sort(m_elements->begin(), m_elements->end());
    qDebug() << m_id << "is done sorting";

    emit finished(0);

}
