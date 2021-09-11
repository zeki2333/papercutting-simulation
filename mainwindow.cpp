#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

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

void MainWindow::on_simulateBtn_clicked()
{
    Mat dstImg;
    Mat srcImg = imread("C:\\Users\\11130\\Desktop\\qttest.jpg");
    //imshow("simulate",srcImg);
    imageAdjust(srcImg,dstImg);
    sifangduizhe(dstImg);

}

void MainWindow::sifangduizhe(const Mat &shuru)
{
    Mat zuoshang, zuoxia, youxia;
    flip(shuru, zuoshang, 1);
    flip(shuru, youxia, 0);
    flip(shuru, zuoxia, -1);
    Mat shuchu, combine1, combine2;
    hconcat(zuoshang, shuru, combine1);
    hconcat(zuoxia, youxia, combine2);
    vconcat(combine1, combine2, shuchu);
    namedWindow("四方对折", WINDOW_AUTOSIZE);
    //imshow("原图", shuru);//原图是否显示
    imshow("四方对折", shuchu);
}
/**
 * @brief MainWindow::imageAdjust 将图像调整为220X200大小后再裁剪边缘得到200X200大小的图像
 * @param shuru
 * @param shuchu
 */
void MainWindow::imageAdjust(const Mat &shuru, Mat &shuchu)
{
    Mat rscale;
    cv::resize(shuru, rscale, Size(220, 220));
    shuchu = rscale(cv::Rect(10, 10, 200, 200));
}
