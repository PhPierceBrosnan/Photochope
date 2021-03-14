#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QLabel>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*QGraphicsScene scene;
    QGraphicsView view(&scene);
    QGraphicsPixmapItem item(QPixmap("C:\\Users\\Bruno\\Documents\\Photochope\\imagem.jpg"));
    QGraphicsPixmapItem item2(QPixmap("C:\\Users\\Bruno\\Documents\\Photochope\\saida.jpg"));
    scene.addItem(&item);
    scene.addItem(&item2);
    view.show();
    */
    MainWindow w;

    QImage imageQ1;
    QLabel *label_img1 = new QLabel ();
    QImage imageQ2;
    QLabel *label_img2 = new QLabel ();

    w.setWindowIcon(QIcon("icon.ico"));
    w.showMaximized();


    return a.exec();
}
