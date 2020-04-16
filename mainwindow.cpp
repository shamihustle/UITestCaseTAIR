#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "IProtocol.h"

#include <QTimer>
#include <QChart>
#include <QChartView>
#include <QVector>
#include <QLineSeries>
#include <QDateTimeAxis>
#include <QMessageBox>
#include <QTcpSocket>
#include <sockets2vna.h>
#include <scpicommands.h>
#include <scpiretrieval.h>
#include <QVector>
#include <IProtocol.h>

using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(this->ui->lineEdit_frequencyPoints, SIGNAL(returnPressed()), SLOT(enterPressedFrequencyPoint()));
    connect(this->ui->lineEdit_FilterStrip, SIGNAL(returnPressed()), SLOT(enterPressedFilterStrip()));
    connect(this->ui->lineEdit_StartFrequency, SIGNAL(returnPressed()), SLOT(enterPressedStartFrequency()));
    connect(this->ui->lineEdit_StopFrequency, SIGNAL(returnPressed()), SLOT(enterPressedStopFrequency()));

    thread = new QThread();
    _threadS2VNA = new ThreadS2VNA();

    _threadS2VNA->moveToThread(thread);

    connect(thread, SIGNAL(started()), _threadS2VNA, SLOT(run()), Qt::DirectConnection);

    connect(_threadS2VNA, SIGNAL(finished()), thread, SLOT(terminate()), Qt::DirectConnection);

    connect(_threadS2VNA, SIGNAL(sendFrequency(QVector<double>)), this, SLOT(setFrequency(QVector<double>)),  Qt::DirectConnection);
    connect(_threadS2VNA, SIGNAL(sendMeasurement(QVector<double>)), this, SLOT(setMeasurement(QVector<double>)), Qt::DirectConnection);
    connect(_threadS2VNA, SIGNAL(runningChanged(bool)), this, SLOT(changeButtonStart(bool)), Qt::DirectConnection);

    connect(_threadS2VNA, SIGNAL(startDraw(bool)), this, SLOT(draw(bool)), Qt::DirectConnection);

    connect(this, SIGNAL(boolChanged()), this, SLOT(DataChanges()));

    chartView = new QChartView(this);

    setChartSettings(chartView);

    ui->layoutWidget_Chart->addWidget(chartView);

    setReadOnlyLineEdit(true);
}


// Нажатие на кнопку старт
void MainWindow::on_pushButton_Start_clicked()
{
    if (_threadS2VNA->running() == false)
    {
        setReadOnlyLineEdit(false);

        _threadS2VNA->setRunning(true);
        thread->start();
    }
    else
    {
        setReadOnlyLineEdit(true);
        _threadS2VNA->setRunning(false);
    }

}

void MainWindow::DataChanges()
{
    drawChart(_frequency, _measurement);
}

void MainWindow::enterPressedFrequencyPoint()
{
    if (_threadS2VNA->running()&& numberOfPointsCheck(ui->lineEdit_frequencyPoints->text().toStdString()))
        _threadS2VNA->setFrequencyPoint(SCPICommands::SetNumberOfPoints(1,ui->lineEdit_frequencyPoints->text().toInt()));
    else
    {
        QMessageBox::critical(this,"Connect", "Incorrect frequency point");
        return;
    }

}

void MainWindow::enterPressedFilterStrip()
{
    if (_threadS2VNA->running() && filterBandCheck(ui->lineEdit_FilterStrip->text().toStdString()))
        _threadS2VNA->setFilterStrip(SCPICommands::SetFilterBand(1,ui->lineEdit_FilterStrip->text().toInt()));
    else
    {
        QMessageBox::critical(this,"Connect", "Incorrect filter strip");
        return;
    }
}

void MainWindow::enterPressedStartFrequency()
{
    if (_threadS2VNA->running() && frequencyChek(ui->lineEdit_StartFrequency->text().toStdString()))
        _threadS2VNA->setStartFrequency(SCPICommands::SetStartFrequency(1,ui->lineEdit_StartFrequency->text().toDouble()));
    else
    {
        QMessageBox::critical(this,"Connect", "Incorrect start frequency");
        return;
    }
}

void MainWindow::enterPressedStopFrequency()
{
    QString str = ui->lineEdit_StopFrequency->text();
    if (_threadS2VNA->running() && frequencyChek(ui->lineEdit_StopFrequency->text().toStdString()))
        _threadS2VNA->setStopFrequency(SCPICommands::SetStopFrequency(1,ui->lineEdit_StopFrequency->text().toDouble()));
    else
    {
        QMessageBox::critical(this,"Connect", "Incorrect stop frequency");
        return;
    }
}

void MainWindow::setFrequency(QVector<double> freq)
{
    _frequency = freq;
}

void MainWindow::setMeasurement(QVector<double> meas)
{
    _measurement = meas;
}

void MainWindow::draw(bool start)
{
    emit boolChanged();
}

void MainWindow::setReadOnlyLineEdit(bool readOnly)
{
    ui->lineEdit_frequencyPoints->setReadOnly(readOnly);
    ui->lineEdit_FilterStrip->setReadOnly(readOnly);
    ui->lineEdit_StartFrequency->setReadOnly(readOnly);
    ui->lineEdit_StopFrequency->setReadOnly(readOnly);
}

// Изменение надписи на кнопке
void MainWindow::changeButtonStart(bool startChange)
{
    if (!startChange)
    {
        ui->pushButton_Start->setText("Start");
        QMessageBox::warning(this, "Connect","Connect is broken");
    }
    else
    {
        ui->pushButton_Start->setText("Stop");
        QMessageBox::information(this, "Connect","Connection established");
    }

}

// Отрисовка графика
// Принимает вектор частот и вектор данных из программы S2VNA
void MainWindow::drawChart(QVector<double> freq, QVector<double> data)
{
    chartView->chart()->removeAxis(xAxis);
    chartView->chart()->removeAxis(yAxis);


    xAxis->setRange(freq.first(), freq.back());
    yAxis->setRange(*min_element(data.begin(),data.end()) , *max_element(data.begin(),data.end()));

    meas->clear();

    for(int i = 0; i < freq.size(); i++)
    {
        *meas << QPointF(freq[i], data[i]);
    }

    chartView->chart()->addSeries(meas);         // Добавить на график

    meas->attachAxis(xAxis);
    meas->attachAxis(yAxis);

    chartView->chart()->setAxisX(xAxis, meas);   // Назначить ось xAxis, осью X для measurement
    chartView->chart()->setAxisY(yAxis, meas);   // Назначить ось yAxis, осью Y для measurement
    chartView->update();
    chartView->repaint();

}

// Установка настроенк для графиков QrCharts
void MainWindow::setChartSettings(QtCharts::QChartView *chartView)
{
    xAxis = new QtCharts::QValueAxis;
    xAxis->setRange(0, 9000000000000);
    xAxis->setTitleText(tr("Frequency"));
    xAxis->setTitleBrush(Qt::gray);
    xAxis->setLabelsColor(Qt::gray);

    yAxis = new QtCharts::QValueAxis;
    yAxis->setRange(-1000, 1000);
    yAxis->setTitleText(tr("Values"));
    yAxis->setTitleBrush(Qt::gray);
    yAxis->setLabelsColor(Qt::gray);


    graphicPen.setWidthF(0.5f);   // Установить ширину линии
    graphicPen.setBrush(Qt::yellow);

    meas = new QtCharts::QLineSeries;
    meas->setName("Measurement");
    meas->setPen(graphicPen);
    meas->setUseOpenGL(true);


    chartView->chart()->setTheme(QtCharts::QChart::ChartThemeDark);

    chartView->chart()->setAxisX(xAxis);   // Назначить ось xAxis, осью X для measurement
    chartView->chart()->setAxisY(yAxis);   // Назначить ось yAxis, осью Y для measurement
    chartView->chart()->update();
}


MainWindow::~MainWindow()
{
    delete ui;
}



