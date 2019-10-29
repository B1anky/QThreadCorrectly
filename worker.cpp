#include "worker.h"

Worker::Worker(QObject *parent) : QObject(parent){

}

void Worker::work(){
    qDebug() << m_id << "has begun sorting";
    std::sort(m_elements.begin(), m_elements.end());
    qDebug() << m_id << "is done sorting";

    emit finished(0);
}

void Worker::setup(QThread* thread, QString id){
    m_id = id;

    connect(thread, &QThread::started, this, &Worker::work, Qt::DirectConnection);
    connect(this, &Worker::finished, thread, &QThread::exit, Qt::DirectConnection);

    qDebug() << m_id << "is setting up, the program should be stalling now";

    for(int i = 0; i < 10000000; ++i){
        m_elements.push_back(i);
    }

    std::random_shuffle(m_elements.begin(), m_elements.end());

    qDebug() << m_id << "is done setting up";

}
