#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene = new QGraphicsScene;

    CustomItem *item = new CustomItem;
    BkgItem *bkgitem = new BkgItem;

    bkgitem->setFoldMode(BkgItem::sizhe);
    //item->setParentItem(bkgitem);

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


void MainWindow::on_roundHoleBtn_clicked()
{
    qDebug()<<"this is roundHole";
    qDebug()<<ui->graphicsView->width()<<"----"<<ui->graphicsView->height();
    //save picture
    QRect grabRect(QPoint(112,191),QPoint(311,390));//(view.width-bkg.width)/2
    QPixmap pix;
    pix = ui->graphicsView->grab(grabRect);
    pix.save("qttest.jpg");

}

void MainWindow::on_moonBtn_clicked()
{
    qDebug()<<"this is moon";
}

void MainWindow::on_commaBtn_clicked()
{
    qDebug()<<"this is comma";
}

void MainWindow::on_willowBtn_clicked()
{
    qDebug()<<"this is willow";
}
