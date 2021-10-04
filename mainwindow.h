#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsRectItem>
#include <QDebug>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
#include "CustomItem.h"
#include "bkgitem.h"
#include "svgitem.h"

using namespace cv;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_erfangBtn_clicked();

    void on_sizheBtn_clicked();

    void on_commaBtn_clicked();

    void on_roundHoleBtn_clicked();

    void on_moonBtn_clicked();

    void on_willowBtn_clicked();

    void on_simulateBtn_clicked();

private:
    QPixmap SnapShootPix;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *rectbg;
    void sifangduizhe(const Mat& shuru);
    void imageAdjust(const Mat& shuru,Mat& shuchu);
    BkgItem *bkgitem;
};
#endif // MAINWINDOW_H
