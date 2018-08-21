#ifndef RANDOM_RANDOMTHREAD_H
#define RANDOM_RANDOMTHREAD_H

#include "thread.h"

/*------- RandomThread ------------------------------------------------------*/
class RandomThread : public Thread
{
	Q_OBJECT

public:
	RandomThread(Worker *worker, QObject *parent = 0);
};

/*------- RandomWorker ------------------------------------------------------*/
class RandomWorker : public Worker
{
	Q_OBJECT
};

#endif // RANDOM_RANDOMTHREAD_H
