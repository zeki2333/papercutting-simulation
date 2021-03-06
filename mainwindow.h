#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsRectItem>
#include <QColorDialog>
#include <QDebug>
#include <QFileDialog>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc/types_c.h>
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

    void on_colorBtn_clicked();

    void on_sizeBox_valueChanged(int arg1);

    void on_bazheBtn_clicked();

    void on_waterBtn_clicked();


    void on_flowerBtn_clicked();

    void on_curveBtn_clicked();

    void on_flower2Btn_clicked();

    void on_triangleBtn_clicked();

    void on_flower3Btn_clicked();

    void on_willow2Btn_clicked();

    void on_edgeBtn_clicked();

    void on_sawtoothBtn_clicked();

    void on_sawtooth2Btn_clicked();

    void on_moon2Btn_clicked();

    void on_sawtooth3Btn_clicked();

    void on_wuzheBtn_clicked();

    void on_NzheBtn_clicked();

    void on_foldNumBox_valueChanged(int arg1);

    void on_uploadBtn_clicked();

public slots:
    void syncProperty(int size,QString color);
private:
    QPixmap SnapShootPix;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *rectbg;
    void sifangduizhe(const Mat& shuru);
    void erfangkaizhe(const Mat& shuru);
    Mat Rotatefold(const Mat & _input, double angle);
    Mat mixall(const Mat& image1, const Mat& image2);
    void rofold(const Mat& _input, int n);
    void imageAdjust(const Mat& shuru,Mat& shuchu);
    BkgItem *bkgitem;

    int initPython();
};
#endif // MAINWINDOW_H
