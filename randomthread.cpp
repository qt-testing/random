#include "randomthread.h"

/*------- RandomThread ------------------------------------------------------*/
RandomThread::RandomThread(Worker *worker, QObject *parent)
	: Thread(worker, parent)
{
}
