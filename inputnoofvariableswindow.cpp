#include "inputnoofvariableswindow.h"
#include "ui_inputnoofvariableswindow.h"

InputNoOfVariablesWindow::InputNoOfVariablesWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::InputNoOfVariablesWindow)
{
    ui->setupUi(this);
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

InputNoOfVariablesWindow::~InputNoOfVariablesWindow()
{
    delete ui;
}

void InputNoOfVariablesWindow::RecieveInputWindow()
{

    window =new KMapWindow();
    side=64;
    this->hide();
    //Desciding the ROW and COLUMN
        int noOfVar=NOV;
        if(noOfVar%2==0){
        ROW=COLUMN=pow(2,noOfVar/2);
        }else{
        ROW=pow(2,noOfVar/2);
        COLUMN=pow(2,(noOfVar/2)+1 );
        }

        //Desciding the side
        if(NOV==6||NOV==7){
                   side=32;
               }
               else if(NOV==8){
                   side=16;
               }
               else if(NOV==9||NOV==10){
                   side=8;

               }


        QWidget *inputWindow= new QWidget;

        //GridLayout
        layout=new QGridLayout;

        for(int i=0;i<ROW;i++){
           for(int j=0;j<COLUMN;j++){

               //Adding a button
               button[i][j]=new QPushButton(this);
               layout->addWidget(button[i][j],i,j,1,1,Qt::AlignCenter);
               button[i][j]->setFixedSize(side,side);
               button[i][j]->setText("0");
               button[i][j]->setFlat(true);


              window->setter(layout,button[i][j],i,j,NOV,ROW,COLUMN,side);
              connect(button[i][j], SIGNAL (pressed()),window, SLOT (setMap()));

              }
           }

            inputWindow->setLayout(layout);
            window->setCentralWidget(inputWindow);
            window->setFixedSize(side*(COLUMN-1)+100,side*(ROW-1)+150);
            window->show();

}

void InputNoOfVariablesWindow::on_pushButton_2_clicked()
{
   NOV=2;
   RecieveInputWindow();
}

void InputNoOfVariablesWindow::on_pushButton_3_clicked()
{
    NOV=3;
    RecieveInputWindow();
}

void InputNoOfVariablesWindow::on_pushButton_4_clicked()
{
    NOV=4;
    RecieveInputWindow();
}

void InputNoOfVariablesWindow::on_pushButton_5_clicked()
{
    NOV=5;
    RecieveInputWindow();
}

void InputNoOfVariablesWindow::on_pushButton_6_clicked()
{
    NOV=6;
    RecieveInputWindow();
}

void InputNoOfVariablesWindow::on_pushButton_7_clicked()
{
    NOV=7;
    RecieveInputWindow();
}

void InputNoOfVariablesWindow::on_pushButton_8_clicked()
{
    NOV=8;
    RecieveInputWindow();
}
