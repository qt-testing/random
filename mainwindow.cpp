#include "mainwindow.h"
#include "randomthread.h"
#include "thread.h"
#include "ui_mainwindow.h"

#include <QChart>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_pWorker = new Worker;
	m_pThread = new Thread(m_pWorker);

	m_pRandomWorker = new RandomWorker;
	m_pRandomThread = new RandomThread(m_pRandomWorker);

	m_pChart = new QtCharts::QChart;

	init();
	connect();
}

MainWindow::~MainWindow()
{
	delete m_pThread;
	delete m_pWorker;

	delete m_pRandomThread;
	delete m_pRandomWorker;

	delete m_pChart;

	delete ui;
}

void MainWindow::onStartButton()
{
	m_pThread->start();
}

void MainWindow::onStopButton()
{
	m_pThread->stop();
}

void MainWindow::onGenerateButton()
{
	m_pRandomThread->start();
}

void MainWindow::onThreadStarted()
{
	ui->pushButtonStart->setEnabled(false);
	ui->pushButtonStop->setEnabled(true);

	QPalette palette = ui->pushButtonLight->palette();
	palette.setColor(QPalette::Button, QColor(Qt::green));
	ui->pushButtonLight->setPalette(palette);
}

void MainWindow::onThreadStopped()
{
	ui->pushButtonStop->setEnabled(false);
	ui->pushButtonStart->setEnabled(true);

	QPalette palette = ui->pushButtonLight->palette();
	palette.setColor(QPalette::Button, QColor(Qt::red));
	ui->pushButtonLight->setPalette(palette);
}

void MainWindow::onRandomThreadStarted()
{
	ui->pushButtonGenerate->setEnabled(false);
}

void MainWindow::onRandomThreadFinished()
{
	ui->pushButtonGenerate->setEnabled(true);

	m_pChart->removeAllSeries();

	QLineSeries *series = new QLineSeries;

	std::lock_guard<std::mutex> lock(m_pRandomThread->mutex());
	const std::map<int, int> &map = m_pRandomThread->data();

	for (auto item : map) {
		series->append(item.first, item.second);
	}

	m_pChart->addSeries(series);
	m_pChart->createDefaultAxes();
}

void MainWindow::init()
{
	QLineSeries *series = new QLineSeries();
	*series << QPointF(0.0, 10.0) << QPointF(1.0, 20.0) << QPointF(3.0, 15.0);
	m_pChart->addSeries(series);
	m_pChart->createDefaultAxes();
	m_pChart->setTitle("Random values");
	m_pChart->legend()->hide();

	ui->chartView->setChart(m_pChart);
}

void MainWindow::connect()
{
	QObject::connect(ui->pushButtonStart, SIGNAL(clicked(bool)),
					 SLOT(onStartButton()));

	QObject::connect(ui->pushButtonStop, SIGNAL(clicked(bool)),
					 SLOT(onStopButton()));

	QObject::connect(ui->pushButtonGenerate, SIGNAL(clicked(bool)),
					 SLOT(onGenerateButton()));

	QObject::connect(m_pThread, SIGNAL(started()),
					 SLOT(onThreadStarted()));

	QObject::connect(m_pThread, SIGNAL(stopped()),
					 SLOT(onThreadStopped()));

	QObject::connect(m_pRandomThread, SIGNAL(started()),
					 SLOT(onRandomThreadStarted()));

	QObject::connect(m_pRandomThread, SIGNAL(finished()),
					 SLOT(onRandomThreadFinished()));
}
