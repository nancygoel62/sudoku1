#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <iostream>
#include <cstring>

#define FOR(i,n) for(int i=0;i<n;i++)
#define IFOR(i,a,n) for(int i=a;i<n;i++)
#define FOR_(i,n) for(int i=n;i>0;i--)
#define IFOR_(i,a,n) for(int i=n;i>a;i--)

#define i(n) cin>>n
#define o(n) cout<<n

//Sudoku Dimensions
#define SIZE 9
#define FALSE 0
#define TRUE 1
#define HEIGHT_BOX 3
#define WIDTH_BOX 3

using namespace std;

int cell[9][9]={0};
//memset(cell,0,9*9*sizeof(int));


//Fill Sudoku
bool checkSafe(int i, int j, int trialNumber)
{
    if(i>SIZE-1 || j>SIZE-1 || i<0 || j<0) return FALSE;
    //box is the sub-grids in which a number cannot be repeated.
    int boxCol, boxRow;
    boxCol = ((int)j/WIDTH_BOX)*WIDTH_BOX;
    boxRow = ((int)i/HEIGHT_BOX)*HEIGHT_BOX;

    //For checking in a box.
    for(int k=boxCol;k<boxCol+WIDTH_BOX;k++)
    {
        for(int l=boxRow; l<boxRow + HEIGHT_BOX;l++)
        {
            if((i==l && j!=k) || (j==k && i!=l))
            {
                if(cell[l][k]==trialNumber) return FALSE;
            }
        }
    }

    //Checking in jth column.
    for(int l=0;l<SIZE;l++)
    {
        if((i!=l && (cell[l][j]==trialNumber))) return FALSE;
    }

    //Checking in ith row.
    for(int l=0;l<SIZE;l++)
    {
        if((j!=l && (cell[i][l] == trialNumber))) return FALSE;
    }
    return TRUE;
}

//Function to find next unassigned writable value in the grid; also
//to check if grid is full or not.
bool findUnassigned(int &row, int &col)
{
    for(col=0;col<SIZE;col++)
    {
        for(row=0;row<SIZE;row++)
        {
            if(cell[row][col]==0) {return TRUE;}
        }
    }
    return FALSE;
}

//Main solver function
bool fillSudoku()
{
    int row, col;
    //Check whether grid is filled; if not then return first unassigned value
    if(!findUnassigned(row, col))
    {
        return TRUE;
    }

    //Backtracking is used here.
    int num;
    for(num=1;num<SIZE+1;num++)
    {
            if(checkSafe(row,col,num))
            {
                cell[row][col]=num;
                if(fillSudoku()) return TRUE;
                cell[row][col]=0;
            }
    }
    return FALSE;
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_pressed()
{
    fillSudoku();
    FOR(row,SIZE)
    {
        FOR(column,SIZE)
        {
//          QString s=QString::number(cell[i][j]);
            QTableWidgetItem* newItem = new QTableWidgetItem();
            newItem->setText(QString::number(cell[row][column]));
            ui->tableWidget->setItem(row,column,newItem);
            //ui->tableWidget->item(row,column)->setBackgroundColor(Qt::red);
        }
    }
}


//Input sudoku
void MainWindow::on_tableWidget_cellChanged(int row, int column)
{
    QString str = ui->tableWidget->item(row,column)->text();
    cell[row][column]=str.toInt();
}


void MainWindow::on_pushButton_2_clicked()
{
    FOR(i,SIZE)
    {
        FOR(j,SIZE) cell[i][j]=0;
    }
    ui->tableWidget->clear();
}
