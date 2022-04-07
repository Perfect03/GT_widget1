#include "win.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // создание объекта приложения
	Win w;
    w.show(); // создание и показ окна
    return a.exec(); // запуск цикла обработки сообщений приложения
}
