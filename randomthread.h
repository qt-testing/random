#ifndef RANDOM_RANDOMTHREAD_H
#define RANDOM_RANDOMTHREAD_H

#include "thread.h"
#include <mutex>

/*------- RandomThread ------------------------------------------------------*/
class RandomThread : public Thread
{
	Q_OBJECT

public:
	RandomThread(Worker *worker, QObject *parent = 0);

	const std::map<int, int> &data() const;
	std::mutex &mutex();
};

/*------- RandomWorker ------------------------------------------------------*/
class RandomWorker : public Worker
{
	Q_OBJECT

public:
	const std::map<int, int> &data() const;
	std::mutex &mutex();

public slots:
	void start();

private:
	std::mutex m_mutex;
	std::map<int, int> m_map;
};

#endif // RANDOM_RANDOMTHREAD_H
