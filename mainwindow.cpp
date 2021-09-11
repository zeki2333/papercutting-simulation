#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    scene = new QGraphicsScene;

    CustomItem *item = new CustomItem;
    BkgItem *bkgitem = new BkgItem;
    bkgitem->setFoldMode(BkgItem::sizhe);

    scene->setSceneRect(-150,-150,300,300);
    scene->addItem(bkgitem);
    scene->addItem(item);
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_erfangBtn_clicked()
{
    qDebug()<<"二方连续开折";

}

void MainWindow::on_sizheBtn_clicked()
{
    qDebug()<<"四折";
    QPolygonF poly;
    poly<<QPointF(0,0)<<QPoint(30,30)<<QPoint(0,60);

}
