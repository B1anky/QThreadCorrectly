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

    Worker(QObject* parent = nullptr);

    void work();

public slots:

    void setup(QThread* thread, QString id);

signals:
    void finished(int);

private:

    QVector<int> m_elements;
    QString      m_id;
};

#endif // WORKER_H
