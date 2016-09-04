#include "kmapwindow.h"
#include "ui_kmapwindow.h"

KMapWindow::KMapWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KMapWindow)
{
    k= new KMap();
    ui->setupUi(this);
    for(int i=0;i<MROW;i++){
        for(int j=0;j<MCOLUMN;j++){
            k->Map[i][j]=0;
        }
    }

    connect(ui->actionSOP,SIGNAL(triggered()),this ,SLOT(GenerateSOP()));
    connect(ui->actionPOS,SIGNAL(triggered()),this ,SLOT(GeneratePOS()));
    connect(ui->actionRefresh,SIGNAL(triggered()),this ,SLOT(Refresh()));

    QPixmap windowIcon;
    if (windowIcon.load(":/resource/resources/KM.ico")) {
        qDebug("\nLoaded icon file");
    }
    else {
        qDebug("\ncould not load icon file");
    }
    QIcon icon(windowIcon);
    this->setWindowIcon(icon);

}

void KMapWindow::setter(QGridLayout *layout, QPushButton *button,int i,int j, int NOV, int ROW, int COLUMN, int side)
{
    this->layout=layout;
    this->button[i][j]=button;
    this->NOV=NOV;
    this->ROW=ROW;
    this->COLUMN=COLUMN;
    this->side=side;
    if(this->NOV>=4)
    ui->statusbar->showMessage("Click on the cells of the Map,to change their values");
    else
    ui->statusbar->showMessage("Click on cells to set Map");

}

void KMapWindow::setMap()
{
    ui->statusbar->clearMessage();    
    QWidget *buttonWidget = qobject_cast<QWidget*>(sender());
    if (!buttonWidget)
        return;

    int indexOfButton = layout->indexOf(buttonWidget);
    int rowOfButton, columnOfButton, rowSpanOfButton, columnSpanOfButton;

    layout->getItemPosition(indexOfButton,
                            &rowOfButton,
                            &columnOfButton,
                            &rowSpanOfButton,
                            &columnSpanOfButton);
    // Now you can get a reference to that specific QPushButton
    QLayoutItem *item = layout->itemAtPosition(rowOfButton, columnOfButton);
    QPushButton *clickedButton = qobject_cast<QPushButton*>(item->widget());
    if (!clickedButton)
        return;



    int i=rowOfButton,j=columnOfButton;
    if(k->Map[i][j]==0)
    {
        button[i][j]->setText("1");
        k->Map[i][j]=1;
    }
    else if(k->Map[i][j]==1)
    {
        button[i][j]->setText("0");
        k->Map[i][j]=0;
    }
}

void KMapWindow::ImplementMap()
{
//    qDebug("\n Action performed");

    k->TheMapIs();
    k->MapGenerator();
    k->FringeMapGenerator_Vertical();
    k->FringeMapGenerator_Horizontal();
    k->cornerMap();
    k->TheEliminator();
    k->TheEliminatorSecondary();
    k->cleaner();
    k->cleanerSecondary();

    k->ExpressionGen();

    QMessageBox *exp= new QMessageBox(this);
    exp->setText(k->printExp());
    int ret=exp->exec();
    if(ret==QMessageBox::Ok){

//        k=new KMap();
//        k->set(this->NOV,this->ROW,this->COLUMN,this->side);
//        for(int i=0;i<k->ROW;i++){
//            for(int j=0;j<k->COLUMN;j++){
//                k->Map[i][j]=0;

//            }
//        }
//        for(int i=0;i<k->ROW;i++){
//            for(int j=0;j<k->COLUMN;j++){
//                button[i][j]->setText("0");
//            }
//        }
    }
}

void KMapWindow::GenerateSOP()
{
    k->setSOP(1);
    k->set(this->NOV,this->ROW,this->COLUMN,this->side);
    ImplementMap();
}

void KMapWindow::GeneratePOS()
{
    k->setSOP(0);
    k->set(this->NOV,this->ROW,this->COLUMN,this->side);
    ImplementMap();
}

void KMapWindow::Refresh()
{
    k=new KMap();
    k->set(this->NOV,this->ROW,this->COLUMN,this->side);
    for(int i=0;i<k->ROW;i++){
        for(int j=0;j<k->COLUMN;j++){
            k->Map[i][j]=0;

        }
    }
    for(int i=0;i<k->ROW;i++){
        for(int j=0;j<k->COLUMN;j++){
            button[i][j]->setText("0");
        }
    }
}

KMapWindow::~KMapWindow()
{
    delete ui;
}
