#include "randomthread.h"
#include <random>

/*------- RandomThread ------------------------------------------------------*/
RandomThread::RandomThread(Worker *worker, QObject *parent)
	: Thread(worker, parent)
{
}

const std::map<int, int> &RandomThread::data() const
{
	return static_cast<const RandomWorker *>(m_pWorker)->data();
}

std::mutex &RandomThread::mutex()
{
	return static_cast<RandomWorker *>(m_pWorker)->mutex();
}

/*------- RandomWorker ------------------------------------------------------*/
void RandomWorker::start()
{
	Worker::start();

	std::random_device rd;
	std::default_random_engine e(rd());
	std::normal_distribution<> uid(0, 100.0);

	std::lock_guard<std::mutex> lock(m_mutex);

	m_map.clear();

	for (int i = 0; i < 100000; ++i) {
			m_map[uid(e)]++;
	}

	emit finished();
}

const std::map<int, int> &RandomWorker::data() const
{
	return m_map;
}

std::mutex &RandomWorker::mutex()
{
	return m_mutex;
}
