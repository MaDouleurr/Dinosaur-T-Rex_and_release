#include "rex.h"
#include "ui_rex.h"

rex::rex(QWidget *parent) :QDialog(parent),ui(new Ui::rex){
        ui->setupUi(this);
        d = QApplication::desktop();//ініціалізація об'єкта
        start = NULL;
        this->setMinimumSize(d->width(),d->height()-d->height()*0.1);//встановлюється мінімальний розмір вікна
        scene = new QGraphicsScene;//иніціалізація об'єкта графічної сцени
        scene->setSceneRect(0,0,d->width()*0.95,d->height()*0.9);//встановлюється розміру і положення сцени
        ui->graphicsView->setMinimumSize(d->width()*0.975,d->height());//мінімальний розмір graphicsView
        ui->graphicsView->setScene(scene);//встановлюється сцена в graphicsView
        ui->graphicsView->show();//показати graphicsView
        images = new QImage*[6];//ініціалізація масива вказівників для картинок
        images[0] = new QImage(":/img/cactus1.png");//ініціалізація вказівників
        images[1] = new QImage(":/img/cactus2.png");
        images[2] = new QImage(":/img/cactus3.png");
        images[3] = new QImage(":/img/cactus4.png");
        images[4] = new QImage(":/img/land2.png");
        images[5] = new QImage(":/img/rex.png");
        QRect *  rect5 = new QRect(500,500,1050,1150);//обрізання картинок
        *images[5] = images[5]->copy(*rect5);
        rect5->setRect(0,762,2000,2000-762);
        *images[0] = images[0]->copy(*rect5);
        rect5->setRect(0,1089,2000,2000-1089);
        *images[1] = images[1]->copy(*rect5);
        rect5->setRect(0,1219,2000,2000-1219);
        *images[2] = images[2]->copy(*rect5);
        rect5->setRect(0,945,2000,2000-945);
        *images[3] = images[3]->copy(*rect5);
        rect5->setRect(0,1513,2000,2000-1513);
        *images[4] = images[4]->copy(*rect5);
        sostim = new int[n];//масив станів
        sostY = new double[5];
        for(int i = 0; i < 5;i++){
            sostY[i] = scene->height()/2-0.07*(new QGraphicsPixmapItem(QPixmap::fromImage(*images[i])))->boundingRect().height();
        }
        items = new QGraphicsPixmapItem*[n];//виділення пам'яті під масив вказівників
        for(int i = 0; i <n;i++){
            items[i] = new QGraphicsPixmapItem(QPixmap::fromImage(*images[4]));//ініціалізація вказівників з картинкою land2
            sostim[i] = 4;//ініціалізуємо масив станів картинок
            items[i]->setScale(0.07);//зменшуємо
            items[i]->setX((scene->width()-n*0.07*2000)/2+i*2000*0.07);//встановлюємо розміщення на граф-й сцені
            items[i]->setY(sostY[4]);
            scene->addItem(items[i]);//встановлюємо об'єкти на сцені
        }
        R = new QGraphicsPixmapItem(QPixmap::fromImage(*images[5]));//виділяємо пам'ять і встановлюємо картинку
        R->setScale(0.07);
        R->setX((scene->width()-n*0.07*2000)/2+0.07*2000);
        R_y = sostY[4]-0.07*R->boundingRect().height();
        R->setY(R_y);//встановлюємо положення по y
        scene->addItem(R);//додаємо на сцену rex
        score = new QGraphicsSimpleTextItem ;
        score->setPos(0.9*d->width(),50);
        score->setText("score 0");
        scene->addItem(score);//Додаємо об'єкт score  на сцену
        srand(time(NULL));
        t = new QTimer();//ініціалізуємо змінну QTimer
        connect(t,&QTimer::timeout,this,&rex::gametimer);//З'єднуємо таймер зі слотом gametimer
        t->start(5);//запускаємо таймер
}

void rex:: gametimer(){
    static bool stan = 0;//змінна для визначення станів картинки на граф. сцені
    static int prig = 0;//змінна для визначення стану rex
        if(GetAsyncKeyState(VK_SPACE)&&stan==0&&raz==0){// при натисканні "space"  запускається рух картинки(stan=1) і таймер
            stan = 1;
            start = clock();//включаємо
        }
        if(GetAsyncKeyState(VK_SPACE)&&stan==0&&raz==1){//при натисканні "space"  запускається рух картинки(stan=1) і таймер
            for(int i = 0; i < n;i++){
                scene->removeItem(items[i]);
                delete items[i];
                items[i] = new QGraphicsPixmapItem(QPixmap::fromImage(*images[4]));//ініціалізація вказівників з картинкою land2
                sostim[i] = 4;//ініціалізуємо масив станів картинок
                items[i]->setScale(0.07);//зменшуємо
                items[i]->setX((scene->width()-n*0.07*2000)/2+i*2000*0.07);//встановлюємо розміщення на граф-й сцені
                items[i]->setY(sostY[sostim[i]]);
                scene->addItem(items[i]);//встановлюємо об'єкти на сцені
        }
            ui->label->clear();
            intscore = 0;
            R->setY(R_y);
            stan = 1;
            start = clock();
        }
        if(items[0]->x()-(scene->width()-n*0.07*2000)/2<=-70){//видалення крайнього лівого об'єкта при досяганні 70ти пікселів зліва і додаванн праворуч
            scene->removeItem(items[0]);
            delete items[0];
            for(int i = 0; i < n-1;i++){//зсув на 1 ліворуч в масиві об'єктів
                items[i] = items[i+1];
                sostim[i] = sostim[i+1];
            }
            int a ;
            //рандомайзер для нового об'єкта
                a = ( rand()%100>50)? rand()%4 :4;
                if(sostim[n-2]!=4&&sostim[n-3]!=4&&a!=4){
                    a =4;
                }
            items[n-1] = new QGraphicsPixmapItem(QPixmap::fromImage(*images[a]));//ініціалізуємо n-1 елемент
            sostim[n-1] = a;
            items[n-1]->setScale(0.07);
            items[n-1]->setX(items[n-2]->x()+140);
            items[n-1]->setY(sostY[a]);
            scene->addItem(items[n-1]);
        }
        if(stan==1)
            //перетин
            switch (sostim[1]) {
                case 0:if(items[1]->x()-0.07*150<=R->x()&&R_y-750*0.07<=R->y()&&R->x()<=items[1]->x()+60){
                    stan = 0;
                    raz = 1;
                    game_over();
                    start = NULL;//обнуляємо таймер
                }
                break;
            case 1:if(items[1]->x()+0.07*100<=R->x()&&R_y-350*0.07<=R->y()&&R->x()<=items[1]->x()+80){
                    stan = 0;
                    raz = 1;
                    game_over();
                    start = NULL;
            }break;
            case 2:if(items[1]->x()+0.07*100<=R->x()&&R_y-350*0.07<=R->y()&&R->x()<=items[1]->x()+60){
                    stan = 0;
                    raz = 1;
                    game_over();
                    start = NULL;
            }break;
            case 3:if(items[1]->x()+0.07*1<=R->x()&&R_y-450*0.07<=R->y()&&R->x()<=items[1]->x()+55){
                     stan = 0;
                     raz = 1;
                     game_over();
                     start = NULL;
            }break;
                case 4 : break;
            }
        if(stan == 1){//рух картинки, збільшення лічільника рахунку, збільшення швидкості  картинки і стрибка rex
            intscore+=(1 + (clock()-start)/(CLOCKS_PER_SEC*25.0));
            score->setText("score " + QString::number(intscore/10));//обновлення рахунку
            for(int i = 0; i < n;i++)//зміна положення картинок
                items[i]->setX(items[i]->x()-1 - (clock()-start)/(CLOCKS_PER_SEC*25.0));//позиція х зменшується
            if(GetAsyncKeyState(VK_UP)&&prig==0)//стрибок
                prig=1;
            if(prig==1){//прыжок вверх
                if(R_y-200<R->y())
                    R->setY(R->y()-1 - (clock()-start)/(CLOCKS_PER_SEC*25.0));
                if(R_y-200>=R->y())//коли долітає до верху
                    prig = 2;
            }
            if(prig ==2){//прыжок вниз
                if(R_y>R->y())
                    R->setY(R->y()+1 + (clock()-start)/(CLOCKS_PER_SEC*25.0));
                if(R_y<=R->y()){
                    prig = 0;
                    R->setY(R_y);
                }
            }
            if(GetAsyncKeyState(VK_DOWN))//    4 вниз по кнопці
                prig=3;
            if(prig==3){
                if(R_y>R->y())
                    R->setY(R->y()+5+(clock()-start)/(CLOCKS_PER_SEC*25.0));
                if(R_y<=R->y()){
                    R->setY(R_y);
                    prig = 0;
                }
            }
        }
        scene->update();
}

void rex:: game_over(){
     QPixmap pix(":/img/game_over.png");
     ui->label->move(d->width()/2-ui->label->width()/2,  d->height()/2 - ui->label->height());//ставимо віджети на центр відносно екрана
     ui->label->setPixmap(pix.scaled(ui->label->width(),ui->label->height(),Qt::KeepAspectRatio));
}

rex::~rex(){
    delete ui;
}
