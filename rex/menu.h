#ifndef MENU_H
#define MENU_H
#include "QRect"
#include <QDesktopWidget>
#include <QPixmap>
#include <QMainWindow>
#include <QDesktopServices>
#include <QUrl>

namespace Ui {
class menu;
}

class menu : public QMainWindow{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

private slots:
    void on_pushButton_4_clicked();//кнопка, натискаючи яку закривається вікно меню

    void on_pushButton_clicked();//кнопка, натискаючи яку відкривається вікно з QGraphicsView і QGraphicsScene для гри rex

    void on_pushButton_2_clicked();//кнопка, натискаючи яку відкривається exe файл з грою «Tic-Tac-Toe»

    void on_pushButton_3_clicked();//кнопка, натискаючи яку відкривається exe файл з грою «Snake Bob»
private:
    Ui::menu *ui;
};

#endif // MENU_H
