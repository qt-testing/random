#ifndef RANDOM_THREAD_H
#define RANDOM_THREAD_H

#include <QMutex>
#include <QObject>

class QThread;
class Worker;

/*------- Thread ------------------------------------------------------------*/
class Thread : public QObject
{
	Q_OBJECT

public:
	Thread(Worker *worker, QObject *object = 0);
	virtual ~Thread();

public slots:
	void start();
	void stop();

signals:
	void started();
	void stopped();
	void finished();

	void signalStart();
	void signalStop();

protected slots:
	void onWorkerFinished();

protected:
	QThread *m_pThread;
	Worker *m_pWorker;

	void connect();
};

/*------- Worker ------------------------------------------------------------*/
class Worker : public QObject
{
	Q_OBJECT

public:
	Worker();
	virtual ~Worker();

public slots:
	virtual void start();
	virtual void stop();

signals:
	void stopped();
	void finished();

protected:
	QMutex m_mutex;
	bool m_stop;
};

#endif // RANDOM_THREAD_H
