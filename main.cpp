#include "widget.h"

#include <QApplication>
#include "serialtool.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    SerialTool serialTool;
    serialTool.show();

    return a.exec();
}
