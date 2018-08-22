#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>

class Thread;
class Worker;
class RandomThread;
class RandomWorker;

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void onStartButton();
	void onStopButton();
	void onGenerateButton();
	void onThreadStarted();
	void onThreadStopped();
	void onRandomThreadStarted();
	void onRandomThreadFinished();

private:
	Ui::MainWindow *ui;
	Thread *m_pThread;
	Worker *m_pWorker;
	RandomThread *m_pRandomThread;
	RandomWorker *m_pRandomWorker;
	QtCharts::QChart *m_pChart;

	void init();
	void connect();
};

#endif // MAINWINDOW_H
