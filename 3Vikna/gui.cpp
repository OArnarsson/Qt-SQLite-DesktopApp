#include "gui.h"
#include "ui_gui.h"
#include <iostream>
#include <QMessageBox>
#include <QDesktopServices>
#include <sstream>
#include "include/ComputerScientist.h"
#include "include/magicaldataclass.h"
#include "include/computer.h"
#include "addpopup.h"


/************************************************
 * explode
 *Creates a string arrray by breaking apart a string
 * Strings are seperated by a delimiter
 * ***********************************************/
vector<string> explode(const string s, char delim)
{
     vector<string> ret;
     stringstream stream(s);
     string temp;
     while(getline(stream, temp, delim))
     {
          ret.push_back(temp);
     }
     return ret;
}

/************************************************
 * constuctor
 * ***********************************************/
GUI::GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUI)
{
    ui->setupUi(this);
    MyDataLayer = new MagicalDataClass("CompDataBase.sqlite");

    vector<ComputerScientist> initialData;
    MyDataLayer->GetAll(initialData);

    ui->mainTable->setRowCount(initialData.size());
    ui->mainTable->setColumnCount(8);
    ui->mainTable->setTabKeyNavigation(true);

    for(unsigned int i = 0; i < initialData.size(); i++)
    {
        for(int j = 0; j < 8; j++)
        {
            QString entry;
            entry = QString::fromStdString(initialData[i].field(j+1));
            ui->mainTable->setItem(i,j, new QTableWidgetItem(entry));
        }
    }

    ui->statusBar->showMessage("Error, no error.", 2000);

    ui->mainTable->setSortingEnabled(true);
}

/************************************************
 * Destructure
 * ***********************************************/
GUI::~GUI()
{
    delete ui;
}

/************************************************
 * on_Add_clicked()
 * triggers when the ADD button is pressed
 * ***********************************************/
void GUI::on_Add_clicked()
{
    Dialog addPopUp(0, this);
    addPopUp.setModal(true);
    addPopUp.exec();
}

/************************************************
 * on_Remove_clicked
 * triggers then the REMOVE button is clicked
 * ***********************************************/
void GUI::on_Remove_clicked()
{
     (*MyDataLayer).remove(ComputerScientist());
}

/************************************************
 * on_Fostudagur_clicked
 * Triggeres when the FOSTUDAGUR button is clicked
 * ***********************************************/
void GUI::on_Fostudagur_clicked()
{
    QString link = "http://bigassmessage.com/00f2e";
    QDesktopServices::openUrl(QUrl(link));
}

/************************************************
 * ErrorMessage()
 * Shows an error messages when there is an error in input
 * ***********************************************/
void GUI::ErrorMessage()
{
    ui->statusBar->showMessage("Please input a valid name.");
}

/************************************************
 * AddToTable
 * adds a single row to the tableview
 * ***********************************************/
void GUI::AddToTable(QString field1,QString field2, QString field3, QString field4, QString field5)
{
   /* vector<string> data;
    data.push_back(field1);
    data.push_back(field1);
    data.push_back(field1);
    data.push_back(field1);*/
    ui->mainTable->setRowCount(ui->mainTable->rowCount()+1);
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,0, new QTableWidgetItem(field1));
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,1, new QTableWidgetItem(field2));
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,2, new QTableWidgetItem(field3));
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,3, new QTableWidgetItem(field4));
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,4, new QTableWidgetItem(field5));
    //MyDataLayer->Add();
}

/************************************************
 * on_comboBox_currentIndexChanged
 * Triggers when the drop down menu changes
 * ***********************************************/
void GUI::on_comboBox_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0:
        {
            vector<ComputerScientist> Data;
            MyDataLayer->GetAll(Data);

            ui->mainTable->setRowCount(Data.size());
            ui->mainTable->setColumnCount(8);

            for(unsigned int i = 0; i < Data.size(); i++)
            {
                for(int j = 0; j < 8; j++)
                {
                    QString entry;
                    entry = QString::fromStdString(Data[i].field(j+1));
                    ui->mainTable->setItem(i,j, new QTableWidgetItem(entry));
                }
            }
            break;
        }
        case 1:
        {
            vector<computer> Data;
            MyDataLayer->GetAll(Data);

            ui->mainTable->setRowCount(Data.size());
            ui->mainTable->setColumnCount(5);

            for(unsigned int i = 0; i < Data.size(); i++)
            {
                for(int j = 0; j < 5; j++)
                {
                    QString entry;
                    entry = QString::fromStdString(Data[i].field(j+1));
                    ui->mainTable->setItem(i,j, new QTableWidgetItem(entry));
                }
            }
            break;
        }
    }
}


/************************************************
 * on_searchbar_returnPressed
 * Triggers when "enter" is pressed
 * Calls the search functions
 * ***********************************************/
void GUI::on_searchbar_returnPressed()
{
    if(ui->comboBox->currentIndex() == 0)
    {
        searchCompSci();
    }
    if(ui->comboBox->currentIndex() == 1)
    {
        searchComputer();
    }
}

/************************************************
 * search<>
 * Searches the database for the terms entered
 * ***********************************************/
void GUI::searchCompSci()
{
    string term;
    vector<ComputerScientist> vec;
    term = ui->searchbar->text().toStdString();
    if(term.size() < 1)
    {
        MyDataLayer->GetAll(vec);
    }
    else
    {
        vector <string> newSearchTerm = explode(term, ' ');
        (*MyDataLayer).Search(vec,newSearchTerm[0]);

        for(unsigned int i = 0; i < newSearchTerm.size(); i++)
        {
            (*MyDataLayer).thin(vec, newSearchTerm[i]);
        }
    }

    ui->mainTable->setRowCount(vec.size());
    ui->mainTable->setColumnCount(8);

    for(unsigned int i = 0; i < vec.size(); i++)
    {
        for(int j = 0; j < 8; j++)
        {
            QString entry;
            entry = QString::fromStdString(vec[i].field(j+1));
            ui->mainTable->setItem(i,j, new QTableWidgetItem(entry));
        }
    }

}

/************************
//Searches the computers
*************************/
void GUI::searchComputer()
{
    string term;
    vector<computer> vec;
    term = ui->searchbar->text().toStdString();
    if(term.size() < 1)
    {
        MyDataLayer->GetAll(vec);
    }
    else
    {
        vector <string> newSearchTerm = explode(term, ' ');
        (*MyDataLayer).Search(vec,newSearchTerm[0]);

        for(unsigned int i = 0; i < newSearchTerm.size(); i++)
        {
            (*MyDataLayer).thin(vec, newSearchTerm[i]);
        }
    }

    ui->mainTable->setRowCount(vec.size());
    ui->mainTable->setColumnCount(5);

    for(unsigned int i = 0; i < vec.size(); i++)
    {
        for(int j = 0; j < 5; j++)
        {
            QString entry;
            entry = QString::fromStdString(vec[i].field(j+1));
            ui->mainTable->setItem(i,j, new QTableWidgetItem(entry));
        }
    }
}

/************************************************
 * search<>
 * Searches the database for the terms entered
 * ***********************************************/
ComputerScientist GUI::getRowScientist(int rown)
{
    string Item[8];
    for(int i = 0; i < 8; i++)
    {
        QTableWidgetItem* currentable = ui->mainTable->item(rown,i);
        Item[i] = currentable->text().toStdString();
    }
    ComputerScientist ret(Item[0],Item[1],Item[2],Item[3],Item[4],Item[5],Item[6],Item[7]);
    return ret;
}

computer GUI::getRowComputer(int rown)
{
    string Item[5];
    for(int i = 0; i < 5; i++)
    {
        QTableWidgetItem* currentable = ui->mainTable->item(rown,i);
        Item[i] = currentable->text().toStdString();
    }
    computer ret(Item[0],Item[1],Item[2],Item[3],Item[4]);
    return ret;
}
