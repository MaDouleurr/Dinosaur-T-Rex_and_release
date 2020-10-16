#include "menu.h"
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    menu w;//створюється об'єкт класу menu(вікно menu.ui)

    w.setWindowState(Qt::WindowMaximized);//встановлюємо прапор розширення вікна до максимального розміру
    w.show();//показ вікна

    return a.exec();
}
