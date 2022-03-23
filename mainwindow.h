#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <selectpatternbutton.h>
#include <QUrl>
#include <QDebug>
#include <QSvgGenerator>

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlError>

#include "svgitem.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QPixmap getPicFromDataBase(int i);
public slots:
    void slotButtonClicked();
    void generateSVG();
    void changeClassicPage();
};
#endif // MAINWINDOW_H
