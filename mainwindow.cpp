#include "Python.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initPython();

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    ui->sizeBox->setMaximum(2000);

    scene = new QGraphicsScene;

    bkgitem = new BkgItem;

    bkgitem->setFoldMode(BkgItem::sizhe);
    connect(bkgitem,SIGNAL(sync(int,QString)),this,SLOT(syncProperty(int,QString)));
    //item->setParentItem(bkgitem);

    //test svg
    svgItem *svg = new svgItem(20);

    scene->setSceneRect(-150,-150,300,300);
    scene->addItem(bkgitem);
    scene->addItem(svg);

    connect(svg,SIGNAL(sync(int,QString)),this,SLOT(syncProperty(int,QString)));

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
    bkgitem->setFoldMode(BkgItem::erfanglianxu);

}

void MainWindow::on_sizheBtn_clicked()
{
    qDebug()<<"四折";
    bkgitem->setFoldMode(BkgItem::sizhe);
}

void MainWindow::on_wuzheBtn_clicked()
{
    qDebug()<<"五折";
    bkgitem->setFoldMode(BkgItem::wuzhe);
}


void MainWindow::on_bazheBtn_clicked()
{
    qDebug()<<"八折";
    bkgitem->setFoldMode(BkgItem::bazhe);
}


void MainWindow::on_NzheBtn_clicked()
{
    qDebug()<<"N折";
    bkgitem->setFoldMode(BkgItem::Nzhe);
}

void MainWindow::on_roundHoleBtn_clicked()
{
    qDebug()<<"this is roundHole pattern";
    svgItem* round = new svgItem("roundHole");
    connect(round,SIGNAL(sync(int,QString)),this,SLOT(syncProperty(int,QString)));
    scene->addItem(round);
}

void MainWindow::on_moonBtn_clicked()
{
    qDebug()<<"this is moon pattern";
    svgItem* moon = new svgItem("moon");
    connect(moon,SIGNAL(sync(int,QString)),this,SLOT(syncProperty(int,QString)));
    scene->addItem(moon);
}

void MainWindow::on_commaBtn_clicked()
{
    qDebug()<<"this is comma pattern";
    svgItem* comma = new svgItem("comma");
    connect(comma,SIGNAL(sync(int,QString)),this,SLOT(syncProperty(int,QString)));
    scene->addItem(comma);
}

void MainWindow::on_waterBtn_clicked()
{
    qDebug()<<"this is water pattern";
    svgItem* water = new svgItem(5);
    connect(water,SIGNAL(sync(int,QString)),this,SLOT(syncProperty(int,QString)));
    scene->addItem(water);
}

void MainWindow::on_willowBtn_clicked()
{
    qDebug()<<"this is willow pattern";
    svgItem* willow = new svgItem("willow");
    connect(willow,SIGNAL(sync(int,QString)),this,SLOT(syncProperty(int,QString)));
    scene->addItem(willow);
}

void MainWindow::on_flowerBtn_clicked()
{
    qDebug()<<"this is flower pattern";
    svgItem* flower = new svgItem(6);
    connect(flower,SIGNAL(sync(int,QString)),this,SLOT(syncProperty(int,QString)));
    scene->addItem(flower);
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
    pix.save("qttest.png");

    Mat srcImg = imread("qttest.png");
    int currentMode = this->bkgitem->getMode();
    if(currentMode == 1)
        sifangduizhe(srcImg);
    else if(currentMode == 2)
        erfangkaizhe(srcImg);
    else
        qDebug()<<"无效模式";
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

void MainWindow::erfangkaizhe(const Mat &shuru)
{
    Mat duizhe1, duizhe2, duizhe3;
    Mat combine1, combine2, combine3;
    flip(shuru, duizhe1, 1);
    hconcat(duizhe1, shuru, combine1);
    flip(combine1, duizhe2, 1);
    hconcat(duizhe2, combine1, combine2);
    flip(combine2, duizhe3, 1);
    hconcat(duizhe3, combine2, combine3);
    namedWindow("二方连续开折",WINDOW_AUTOSIZE);
    imshow("二方连续对折", combine3);
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

void MainWindow::syncProperty(int size, QString color)
{
    qDebug()<<"sync"<<size<<"  "<<color;
    //从item同步颜色
    QString qss = "background:transparent;";
    qss.append(QString("color:%1;").arg(color));
    this->ui->colorBtn->setStyleSheet(qss);

    //从item同步大小
    this->ui->sizeBox->setValue(size);
}



void MainWindow::on_sizeBox_valueChanged(int arg1)
{
    //修改组件大小
    QList<QGraphicsItem*> bufList = this->scene->selectedItems();
    if(bufList.length()==0)
        return;
    if(bufList[0] == bkgitem)
    {
        BkgItem *bkg = dynamic_cast<BkgItem*>(bufList[0]);
        bkg->changeSize(arg1);
    }
    else
    {
        svgItem *svg = dynamic_cast<svgItem*>(bufList[0]);
        svg->changeSize(arg1);
    }
}

void MainWindow::on_foldNumBox_valueChanged(int arg1)
{
    bkgitem->setNFoldNum(arg1);
}


void MainWindow::on_curveBtn_clicked()
{
    qDebug()<<"this is curve pattern";
    svgItem* curve = new svgItem(7);
    connect(curve,SIGNAL(sync(int,QString)),this,SLOT(syncProperty(int,QString)));
    scene->addItem(curve);
}

void MainWindow::on_flower2Btn_clicked()
{
    qDebug()<<"this is flower2 pattern";
    svgItem* curve = new svgItem(8);
    connect(curve,SIGNAL(sync(int,QString)),this,SLOT(syncProperty(int,QString)));
    scene->addItem(curve);
}

void MainWindow::on_triangleBtn_clicked()
{
    qDebug()<<"this is triangle pattern";
    svgItem* curve = new svgItem(9);
    connect(curve,SIGNAL(sync(int,QString)),this,SLOT(syncProperty(int,QString)));
    scene->addItem(curve);
}

void MainWindow::on_flower3Btn_clicked()
{
    qDebug()<<"this is flower3 pattern";
    svgItem* curve = new svgItem(10);
    connect(curve,SIGNAL(sync(int,QString)),this,SLOT(syncProperty(int,QString)));
    scene->addItem(curve);
}

void MainWindow::on_willow2Btn_clicked()
{
    qDebug()<<"this is willow2 pattern";
    svgItem* curve = new svgItem(11);
    connect(curve,SIGNAL(sync(int,QString)),this,SLOT(syncProperty(int,QString)));
    scene->addItem(curve);
}

void MainWindow::on_edgeBtn_clicked()
{
    qDebug()<<"this is edge pattern";
    svgItem* curve = new svgItem(12);
    connect(curve,SIGNAL(sync(int,QString)),this,SLOT(syncProperty(int,QString)));
    scene->addItem(curve);
}

void MainWindow::on_sawtoothBtn_clicked()
{
    qDebug()<<"this is sawtooth pattern";
    svgItem* curve = new svgItem(13);
    connect(curve,SIGNAL(sync(int,QString)),this,SLOT(syncProperty(int,QString)));
    scene->addItem(curve);
}

void MainWindow::on_sawtooth2Btn_clicked()
{
    qDebug()<<"this is sawtooth2 pattern";
    svgItem* curve = new svgItem(14);
    connect(curve,SIGNAL(sync(int,QString)),this,SLOT(syncProperty(int,QString)));
    scene->addItem(curve);
}

void MainWindow::on_moon2Btn_clicked()
{
    qDebug()<<"this is moon2 pattern";
    svgItem* curve = new svgItem(15);
    connect(curve,SIGNAL(sync(int,QString)),this,SLOT(syncProperty(int,QString)));
    scene->addItem(curve);
}

void MainWindow::on_sawtooth3Btn_clicked()
{
    qDebug()<<"this is sawtooth3 pattern";
    svgItem* curve = new svgItem(16);
    connect(curve,SIGNAL(sync(int,QString)),this,SLOT(syncProperty(int,QString)));
    scene->addItem(curve);
}

int MainWindow::initPython()
{
    Py_SetPythonHome(L"E:/APP/anaconda3");
    Py_Initialize();
    if(Py_IsInitialized())
    {
        qDebug("python 初始化成功");
    }
    PyObject* pModule = PyImport_ImportModule("hello");//.py文件名
    if(!pModule)
    {
        qDebug()<<"cant open python file\n";
    }
    PyObject* pFunhello = PyObject_GetAttrString(pModule,"hello");//函数名
    if(!pFunhello)
    {
        qDebug()<<"Get function hello failed\n";
    }
    PyObject_CallFunction(pFunhello,NULL);
    Py_Finalize();
}


void MainWindow::on_uploadBtn_clicked()
{
    //添加数据库驱动
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    //设置数据库名字
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("svgSource");
    db.setUserName("paperfold");
    db.setPassword("123123");
    if(db.open() == true)
    {
        //QMessageBox::information(this,"infor","success");
        qDebug("打开成功");
    }
    else
    {
        //QMessageBox::information(this,"infor","failed");
        qDebug("打开失败");
    }
    //查询目前纹样个数
    QString qStr="select count(*) from img;";
    QSqlQuery qquery(qStr);
    int res;//获取目前纹样库的个数
    while(qquery.next())
    {
        res = qquery.value(0).toInt()+1;
        qDebug()<<res;
    }

    //插入操作
    QSqlQuery query;
    QString filename = QFileDialog::getOpenFileName(this,tr("Open Images"),".",tr("Image File(*.svg)"));
    qDebug()<<"filename.toLatin1().data():"<<filename.toLatin1().data();
    filename = filename.toLatin1().data();
    QFile svgfile(filename);
    svgfile.open(QIODevice::ReadOnly);
    QByteArray svgArr = svgfile.readAll();
    //qDebug()<<svgArr;
    svgArr=svgArr.toHex();
    QString queryStr = QString("INSERT INTO `img` VALUES (%1,0x%2);").arg(QString::number(res)).arg(QString(svgArr));
    //qDebug()<<queryStr;


    if(query.exec(queryStr)==false)
    {
        qDebug()<<queryStr;
        qDebug()<<"failed";
    }
    else
    {
        qDebug()<<"插入成功";
    }
}
