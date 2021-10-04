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

    //CustomItem *item = new CustomItem;
    bkgitem = new BkgItem;

    bkgitem->setFoldMode(BkgItem::sizhe);
    //item->setParentItem(bkgitem);

    //test svg
    svgItem *svg = new svgItem;


    scene->setSceneRect(-150,-150,300,300);
    scene->addItem(bkgitem);
    scene->addItem(svg);
    //scene->addItem(item);
    ui->graphicsView->setScene(scene);

    //ui->colorBtn->setStyleSheet("font-color::rgb(15,54,144);");
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
    qDebug()<<"this is roundHole pattern";
    CustomItem* round = new CustomItem("roundHole");
    scene->addItem(round);


}

void MainWindow::on_moonBtn_clicked()
{
    qDebug()<<"this is moon pattern";
    CustomItem* moon = new CustomItem("moon");
    scene->addItem(moon);
}

void MainWindow::on_commaBtn_clicked()
{
    qDebug()<<"this is comma pattern";
    CustomItem* comma = new CustomItem("comma");
    scene->addItem(comma);
}

void MainWindow::on_willowBtn_clicked()
{
    qDebug()<<"this is willow pattern";
    CustomItem* willow = new CustomItem("willow");
    scene->addItem(willow);
}

void MainWindow::on_simulateBtn_clicked()
{

    qDebug()<<ui->graphicsView->width()<<"----"<<ui->graphicsView->height();
    //save picture to pix
    int width = (ui->graphicsView->width() - bkgitem->width())/2;
    int height = (ui->graphicsView->height() - bkgitem->height())/2;
    QRect grabRect(width,height,bkgitem->width(),bkgitem->height());//(view.width-bkg.width)/2
    QPixmap pix;
    pix = ui->graphicsView->grab(grabRect);
    pix.save("qttest.jpg");

    Mat dstImg;
    Mat srcImg = imread("qttest.jpg");
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

void MainWindow::on_colorBtn_clicked()
{
    //按钮颜色改变
    QString qss = "background:transparent;";

    QColor color = QColorDialog::getColor();
    qss.append(QString("color:%1;").arg(color.name()));
    this->ui->colorBtn->setStyleSheet(qss);

    //修改组件颜色
    QList<QGraphicsItem*> bufList = this->scene->selectedItems();
    if(bufList.length()==0)
        return;
    qDebug()<<"selected:"<<bufList.length();
    qDebug()<<bufList[0];
    if(bufList[0] == bkgitem)
    {
        BkgItem *bkg = dynamic_cast<BkgItem*>(bufList[0]);
        bkg->changeColor(color.name());
    }
    else
    {
        svgItem *svg = dynamic_cast<svgItem*>(bufList[0]);
        svg->changeColor(color.name());
    }

}

