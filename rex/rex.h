#ifndef REX_H
#define REX_H
#include "QGraphicsScene"
#include <QTextItem>
#include <QDesktopWidget>
#include "QRect"
#include <QGraphicsPixmapItem>
#include <QDialog>
#include <windows.h>
#include <QTimer>
namespace Ui {
class rex;
}

class rex : public QDialog{
    Q_OBJECT
public slots:
    void gametimer();// публічний слот для самої гри rex
public:
    void game_over();
    explicit rex(QWidget *parent = nullptr);
    ~rex();

private:
    Ui::rex *ui;//створюється вказівник на вікно
    QGraphicsScene *scene;//створюється вказівник на QGraphicsScene
    QDesktopWidget * d;// d для визначення розмірів екрана
    QImage** images;//масив вказівників на картинки
    QGraphicsPixmapItem ** items;//масив вказівників на об'єкти з картинками
    clock_t  start;// зміння для таймера
    QTimer *t;//вказівник на об'єкт для таймера, для виклику слота
    QGraphicsSimpleTextItem  * score;//вказівник на текстовий об'єкт з рахунком
    int intscore = 0;//змінна для рахунку
    const int n = 8;//розмірність для масиву об'єктів, що рухаються
    QGraphicsPixmapItem * R;//вказівник на об'єкт для картинки rex
    int  * sostim;//масив, що зберігає порядкові номера картинок до відповідних об'єктам(по індексу)
    double * sostY;//масив положень по y об'єктів на сцені
    double R_y;//стандартна висота rex
    bool raz = 0;//для розуміння перша спроба чи ні
};

#endif // REX_H
