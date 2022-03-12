#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_2,SIGNAL(clicked()),this,SLOT(generateSVG()));

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    scene = new QGraphicsScene;
    svgItem *svg = new svgItem(2);

    scene->setSceneRect(-150,-150,300,300);
    scene->addItem(svg);
    ui->graphicsView->setScene(scene);

    for(int i=0;i<16;i++){
        selectPatternButton* btn = new selectPatternButton(i+1);
//        btn->setIcon(QIcon(":/new/btn/round.png"));
        btn->setIcon(getPicFromDataBase(i+1));
        btn->setStyleSheet("QPushButton{background:transparent;border-width:0px;}");
        btn->setIconSize(QSize(60,60));
        connect(btn,SIGNAL(clicked()),this,SLOT(slotButtonClicked()));
        ui->gridLayout->addWidget(btn,i/4,i%4,1,1,Qt::AlignCenter);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotButtonClicked()
{
    selectPatternButton* btn = qobject_cast<selectPatternButton*>(sender());
//    btn->setText("clicked");
    qDebug()<<btn->getNumber();
    svgItem* svgitem = new svgItem(btn->getNumber());
    scene->addItem(svgitem);
}

void MainWindow::generateSVG()
{
    qDebug()<<"generate svg";
//    QList<QGraphicsItem*> bufList = this->scene->selectedItems();
//    if(bufList.length()==0)
//        return;
//    svgItem *svg = dynamic_cast<svgItem*>(bufList[0]);

    qDebug()<<"start render";
    QSvgGenerator generator;
    generator.setFileName("./testsvg.svg");
    generator.setSize(QSize(200, 200));
    generator.setViewBox(QRect(0, 0, 200, 200));
    QPainter painter;
    painter.begin(&generator);
//    svg->paintSVG(painter);
    scene->render(&painter);
    painter.end();
}

QPixmap MainWindow::getPicFromDataBase(int i){
    //数据库读取svg
    QSqlDatabase db;//建立和数据库的连接

    db = QSqlDatabase::addDatabase("QODBC");
    //设置数据库名字
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("svgSource");
    db.setUserName("paperfold");
    db.setPassword("123123");
    if(db.open()==true){
        qDebug("打开成功");
        QString str = QString("select * from btn where id=%1").arg(i);
        QSqlQuery query(str);
        QPixmap pix;
        while(query.next()){
            QByteArray arr = query.value(2).toByteArray();
            pix.loadFromData(arr);
        }
        return pix;
    }
}

