#include <QApplication>
#include "workernetwork.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    WorkerNetwork* workerNetwork = new WorkerNetwork;
    workerNetwork->show();

    return a.exec();
}
