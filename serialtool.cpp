#include "serialtool.h"
#include <QSerialPortInfo>
#include <QVBoxLayout>
#include <QDebug>

SerialTool::SerialTool(QWidget *parent)
    : QWidget(parent), serial(new QSerialPort(this))
{
    setupUI();

    connect(openButton, &QPushButton::clicked, this, &SerialTool::openSerialPort);
    connect(sendButton, &QPushButton::clicked, this, &SerialTool::sendData);
    connect(serial, &QSerialPort::readyRead, this, &SerialTool::readData);
    connect(refreshButton, &QPushButton::clicked, this, &SerialTool::refreshSerialPorts); // 连接刷新按钮
}

SerialTool::~SerialTool()
{
    if (serial->isOpen())
    {
        serial->close();
    }
}

void SerialTool::setupUI()
{
    // 设置界面控件
    portComboBox = new QComboBox(this);
    baudComboBox = new QComboBox(this);
    sendDataLineEdit = new QLineEdit(this);
    statusText = new QTextEdit(this);
    openButton = new QPushButton("Open Serial Port", this);
    sendButton = new QPushButton("Send Data", this);
    refreshButton = new QPushButton("Refresh Serial Ports", this); // 刷新按钮

    baudComboBox->addItems({"9600", "115200", "19200", "38400", "57600"});

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(portComboBox);
    layout->addWidget(baudComboBox);
    layout->addWidget(openButton);
    layout->addWidget(sendDataLineEdit);
    layout->addWidget(sendButton);
    layout->addWidget(refreshButton); // 添加刷新按钮
    layout->addWidget(statusText);

    setLayout(layout);
    setWindowTitle("Serial Port Tool");

    // 自动加载可用串口
    updatePortList();
}

void SerialTool::updatePortList()
{
    portComboBox->clear(); // 清空原有串口列表

    QList<QSerialPortInfo> serialPortInfos = QSerialPortInfo::availablePorts();
    if (serialPortInfos.isEmpty())
    {
        statusText->append("No serial ports found.");
    }
    else
    {
        for (const QSerialPortInfo &info : serialPortInfos)
        {
            portComboBox->addItem(info.portName());
        }
    }
}

void SerialTool::refreshSerialPorts()
{
    // 点击刷新按钮时更新串口列表
    updatePortList();
}

void SerialTool::openSerialPort()
{
    if (serial->isOpen())
    {
        serial->close();
        openButton->setText("Open Serial Port");
        statusText->append("Serial Port Closed.");
    }
    else
    {
        serial->setPortName(portComboBox->currentText());
        serial->setBaudRate(baudComboBox->currentText().toInt());
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);

        if (serial->open(QIODevice::ReadWrite))
        {
            openButton->setText("Close Serial Port");
            statusText->append("Serial Port Opened.");
        }
        else
        {
            statusText->append("Failed to Open Serial Port.");
        }
    }
}

void SerialTool::sendData()
{
    QByteArray data = sendDataLineEdit->text().toUtf8();
    if (serial->isOpen() && serial->isWritable())
    {
        serial->write(data);
        statusText->append("Sent: " + data);
    }
    else
    {
        statusText->append("Failed to send data.");
    }
}

void SerialTool::readData()
{
    QByteArray data = serial->readAll();
    statusText->append("Received: " + data);
}