#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>
#include <QVector>
#include <algorithm>
#include <QMutex>
#include <QSemaphore>
#include <QDebug>


class Worker : public QObject{

    Q_OBJECT

public:

    Worker(QVector<char>* job, QObject* parent = nullptr) : QObject(parent), m_elements(job){
    }

    virtual void work() = 0;

public slots:

    virtual void setup(QThread* thread, QString id){
        m_id = id;

        connect(thread, &QThread::started, this,   &Worker::work,  Qt::QueuedConnection);
        connect(this,   &Worker::finished, thread, &QThread::exit, Qt::QueuedConnection);
    }

signals:

    void finished(int);

    void started();

protected:

    QVector<char>* m_elements;
    QString        m_id;
    static inline QMutex m_mutex = QMutex();
    static inline QSemaphore m_lockAcquirer = QSemaphore(0);

};



#endif // WORKER_H
