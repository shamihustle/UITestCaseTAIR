#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "IProtocol.h"

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

    protocol = new SocketS2VNA();

    if(!protocol->Connect("localhost", 5025))
            QMessageBox::critical(this,"Connect", "Connect error");

    chartView = new QChartView(this);

    SetChartSettings(chartView);

    ui->layoutWidget_Chart->addWidget(chartView);

}


// Нажатие на кнопку старт
void MainWindow::on_pushButton_Start_clicked()
{
    if (protocol->Connect("localhost", 5025) == false)
    {
        QMessageBox::critical(this,"Connect", "Connect error");
        return;
    }
    else
    {
        SCPIRetrieval retrieval(protocol);

        if (NumberOfPointsCheck(ui->lineEdit_frequencyPoints->text().toStdString()))
            protocol->SendCommand(SCPICommands::SetNumberOfPoints(1,ui->lineEdit_frequencyPoints->text().toInt()));
        else
        {
            QMessageBox::critical(this,"Connect", "Incorrect frequency point");
            return;
        }

        if (FilterBandCheck(ui->lineEdit_FilterStrip->text().toStdString()))
            protocol->SendCommand(SCPICommands::SetFilterBand(1,ui->lineEdit_FilterStrip->text().toInt()));
        else
        {
            QMessageBox::critical(this,"Connect", "Incorrect filter band");
            return;
        }


        if (FrequencyChek(ui->lineEdit_StartFrequency->text().toStdString()))
            protocol->SendCommand(SCPICommands::SetStartFrequency(1, ui->lineEdit_StartFrequency->text().toDouble()));
        else
        {
            QMessageBox::critical(this,"Connect", "Incorrect start frequency");
            return;
        }

        if (FrequencyChek(ui->lineEdit_StopFrequency->text().toStdString()))
            protocol->SendCommand(SCPICommands::SetStopFrequency(1, ui->lineEdit_StopFrequency->text().toDouble()));
        else
        {
            QMessageBox::critical(this,"Connect", "Incorrect stop frequency");
            return;
        }


        if (ui->comboBox_Parameters->currentIndex() == 0)
            protocol->SendCommand(SCPICommands::SelectionMeasuredParameter(1,1,"S11"));
        if (ui->comboBox_Parameters->currentIndex() == 1)
            protocol->SendCommand(SCPICommands::SelectionMeasuredParameter(1,1,"S12"));
        if (ui->comboBox_Parameters->currentIndex() == 2)
            protocol->SendCommand(SCPICommands::SelectionMeasuredParameter(1,1,"S21"));
        if (ui->comboBox_Parameters->currentIndex() == 3)
            protocol->SendCommand(SCPICommands::SelectionMeasuredParameter(1,1,"S22"));

        try
        {
            retrieval.DataScaning();
        }
        catch (std::exception &exception)
        {
            QMessageBox::critical(this, exception.what(),exception.what());
            return;
        }

        QVector<double> freq = retrieval.FrequencyRetrieval(1);
        QVector<double> data = retrieval.MeasurementRetrieval(1);

        for (int i = 0; i < data.size(); i++)
        {
            if(data[i] == 0)
                data.remove(i);
        }
        DrawChart(freq, data);
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
