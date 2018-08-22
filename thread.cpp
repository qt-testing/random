#include "thread.h"
#include <QThread>

/*------- Thread ------------------------------------------------------------*/
Thread::Thread(Worker *worker, QObject *parent)
	: QObject(parent)
{
	m_pThread = new QThread;
	m_pWorker = worker;

	m_pWorker->moveToThread(m_pThread);

	connect();
}

Thread::~Thread()
{
	m_pThread->quit();
	m_pThread->wait();

	delete m_pThread;
	m_pThread = 0;
}

void Thread::start()
{
	m_pThread->start();

	emit signalStart();
}

void Thread::stop()
{
	m_pWorker->stop();
}

void Thread::onWorkerFinished()
{
	m_pThread->quit();
	m_pThread->wait();
}

void Thread::connect()
{
	QObject::connect(m_pWorker, SIGNAL(stopped()),
					 SLOT(onWorkerFinished()));

	QObject::connect(m_pWorker, SIGNAL(finished()),
					 SLOT(onWorkerFinished()));

	QObject::connect(m_pWorker, SIGNAL(finished()),
					 this, SIGNAL(finished()));

	QObject::connect(m_pThread, SIGNAL(started()),
					 SIGNAL(started()));

	QObject::connect(m_pThread, SIGNAL(finished()),
					 SIGNAL(stopped()));

	QObject::connect(this, SIGNAL(signalStart()),
					 m_pWorker, SLOT(start()));
}

/*------- Worker ------------------------------------------------------------*/
Worker::Worker()
{
	m_stop = true;
}

Worker::~Worker()
{
}

void Worker::start()
{
	m_mutex.lock();
	m_stop = false;
	m_mutex.unlock();
}

void Worker::stop()
{
	QMutexLocker locker(&m_mutex);
	m_stop = true;

	emit stopped();
}
