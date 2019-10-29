#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QThread>
#include <QVector>
#include <algorithm>
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

        connect(thread, &QThread::started, this,   &Worker::work,  Qt::DirectConnection);
        connect(this,   &Worker::finished, thread, &QThread::exit, Qt::DirectConnection);
    }

signals:

    void finished(int);

    void started();

protected:

    QVector<char>* m_elements;
    QString        m_id;

};

#endif // WORKER_H
