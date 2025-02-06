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
    void refreshSerialPorts(); // 刷新串口列表

private:
    void setupUI();
    void updatePortList(); // 更新串口列表

    QSerialPort *serial;
    QComboBox *portComboBox;
    QComboBox *baudComboBox;
    QLineEdit *sendDataLineEdit;
    QTextEdit *statusText;
    QPushButton *openButton;
    QPushButton *sendButton;
    QPushButton *refreshButton; // 新增刷新按钮
};

#endif // SERIALTOOL_H
