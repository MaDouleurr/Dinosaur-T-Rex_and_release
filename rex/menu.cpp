#include "menu.h"
#include "ui_menu.h" //підключаємо форму
#include "rex.h"

menu::menu(QWidget *parent) :QMainWindow(parent),ui(new Ui::menu){
    ui->setupUi(this);
    this->setWindowFlags( Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);//встановлюємо прапори для кнопок «закрити» та «згорнути»
    QDesktopWidget *d = QApplication::desktop();//створюємо об'єкт класу QDesktopWidget для визначення розмірів екрана персонального пристрою
    ui->widget->move(d->width()/2-ui->widget->width()/2,  d->height()/2 - ui->widget->height());//встановлюємо віджети на центр відносно екрана
    ui->label->move(d->width()/2-ui->label->width()/2,ui->widget->y()-ui->label->height());
    this->setStyleSheet("QMainWindow { background-color: rgb(143,188,143) }");
    this->setMinimumSize(d->width(),  d->height() );//встановлюємо мінімальний розмір вікна
    ui-> widget->setStyleSheet("* { background-color: rgb(46,139,87) }");
}

menu::~menu(){
    delete ui;
}

void menu::on_pushButton_4_clicked(){
    this->close();
}

void menu::on_pushButton_clicked(){
    rex Rex;//створюємо об'єкт rex
    Rex.setWindowState(Qt::WindowMaximized);//встановлюємо прапор для збільшення вікна до максимальних розмірів
    Rex.setWindowFlags(Qt::WindowCloseButtonHint | Qt::WindowMinimizeButtonHint);//встановлюємо прапори для кнопок «закрити» та «згорнути»
    Rex.exec();
}

void menu::on_pushButton_2_clicked(){
   QDesktopServices::openUrl(QUrl("krestic.exe",QUrl::TolerantMode));//запускаємо exe файл «krestic.exe» з грою «Tic-Tac-Toe»
}

void menu::on_pushButton_3_clicked(){
   QDesktopServices::openUrl(QUrl("SNAKE.exe",QUrl::TolerantMode));//запускаємо exe файл «SNAKE.exe» з грою «Snake Bob»
}
