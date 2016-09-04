#ifndef KMAPWINDOW_H
#define KMAPWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#define MROW 16
#define MCOLUMN 16
#include "kmap.h"

namespace Ui {
class KMapWindow;
}

class KMapWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit KMapWindow(QWidget *parent = 0);
    void setter(QGridLayout *layout,
    QPushButton *button, int i, int j,
    int NOV, int ROW, int COLUMN, int side);
    ~KMapWindow();

public slots:

    void setMap();
    void GenerateSOP();
    void GeneratePOS();
    void Refresh();

private:
    Ui::KMapWindow *ui;
    QGridLayout *layout;
    QPushButton *button[MROW][MCOLUMN];
    int NOV,ROW,COLUMN,side;
    KMap *k;
    void ImplementMap();
};

#endif // KMAPWINDOW_H
