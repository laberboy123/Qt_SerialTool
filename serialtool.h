#ifndef SERIALTOOL_H
#define SERIALTOOL_H

#include <QWidget>
#include <QSerialPort>
#include <QComboBox>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>

class SerialTool : public QWidget
{
    Q_OBJECT

public:
    explicit SerialTool(QWidget *parent = nullptr);
    ~SerialTool();

private slots:
    void openSerialPort();
    void sendData();
    void readData();
    void refreshSerialPorts(); // ˢ�´����б�

private:
    void setupUI();
    void updatePortList(); // ���´����б�

    QSerialPort *serial;
    QComboBox *portComboBox;
    QComboBox *baudComboBox;
    QLineEdit *sendDataLineEdit;
    QTextEdit *statusText;
    QPushButton *openButton;
    QPushButton *sendButton;
    QPushButton *refreshButton; // ����ˢ�°�ť
};

#endif // SERIALTOOL_H
