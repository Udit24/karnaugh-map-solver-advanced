#ifndef INPUTNOOFVARIABLESWINDOW_H
#define INPUTNOOFVARIABLESWINDOW_H

#include <QMainWindow>
#include "kmapwindow.h"
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QPixmap>
#define MROW 16
#define MCOLUMN 16



namespace Ui {
class InputNoOfVariablesWindow;
}

class InputNoOfVariablesWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InputNoOfVariablesWindow(QWidget *parent = 0);
    ~InputNoOfVariablesWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::InputNoOfVariablesWindow *ui;
    void RecieveInputWindow();
    KMapWindow *window;
    QGridLayout *layout;
    QPushButton *button[MROW][MCOLUMN];
    int NOV,ROW,COLUMN,side;


};

#endif // INPUTNOOFVARIABLESWINDOW_H
