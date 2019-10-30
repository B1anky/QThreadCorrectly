#include "generatorworker.h"


GeneratorWorker::GeneratorWorker(QVector<char>* job, QObject* parent) : Worker(job, parent){

}

void GeneratorWorker::work(){

    qDebug() << QString("Begun generating for bin %1").arg(m_id);
    if(m_lockAcquirer.available() ^ (1 << m_id.toInt())){
        m_lockAcquirer.acquire(m_lockAcquirer.available() ^ (1 << m_id.toInt()));
        for(int i = 0; i < 100000; ++i){
            for(char j = 0; j < CHAR_MAX; ++j){
                m_elements->push_back(j);
            }
        }
        m_lockAcquirer.release(m_lockAcquirer.available() ^ (1 << m_id.toInt()));
        qDebug() << QString("Finished generating for bin %1").arg(m_id);
    }

    emit finished(0);

}

void GeneratorWorker::setup(QThread *thread, QString id){
    m_mutex.lock();
    m_id = id;
    int curAvail = m_lockAcquirer.available();
    qDebug() << (1 << (m_id.toInt() - 1)) << curAvail;
    m_lockAcquirer.acquire(m_lockAcquirer.available());
    qDebug() << m_lockAcquirer.available();
    m_lockAcquirer.release(curAvail  ^ (1 << (m_id.toInt() - 1)));
    qDebug() << m_lockAcquirer.available();
    m_mutex.unlock();

    connect(thread, &QThread::started, this,   &Worker::work,  Qt::QueuedConnection);
    connect(this,   &Worker::finished, thread, &QThread::exit, Qt::QueuedConnection);
}
