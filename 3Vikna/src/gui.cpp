#include "../include/gui.h"
#include "ui_gui.h"
#include <iostream>
#include <QMessageBox>
#include <QDesktopServices>
#include <set>
#include <sstream>
#include <vector>
#include <QTimer>
#include <QDateTime>
#include <QLCDNumber>
#include <QMediaPlayer>
#include "include/ComputerScientist.h"
#include "include/magicaldataclass.h"
#include "include/computer.h"
#include "../include/addpopup.h"
#include "../include/sciencepopup.h"
#include "../include/FileData.h"
#include "../include/connections.h"
using namespace std;

/************************************************
 * explode
 *Creates a string arrray by breaking apart a string
 * Strings are seperated by a delimiter
 * ***********************************************/
vector<string> GUI::explode(const string s, char delim)
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
    QTimer *timer=new QTimer(this);
    connect(timer ,SIGNAL(timeout()),this,SLOT(showTime()));
    timer->start();

    this->setFixedSize(1029,459);

    ui->statusBar->showMessage("Now with sounds!", 5000);

    on_comboBox_currentIndexChanged(0);



    ui->mainTable->setSortingEnabled(true);

    //Sets the format on LCD counter
    ui->SciNumber->setDigitCount(3);
    ui->FavSciNumber->setDigitCount(3);
    ui->CompNumber->setDigitCount(3);
    ui->FavCompNumber->setDigitCount(3);


    //Sets the count on LCD counter
    ui->SciNumber->display(MyDataLayer->sciNumber());
    ui->FavSciNumber->display(MyDataLayer->favSciNumber());
    ui->CompNumber->display(MyDataLayer->compNumber());
    ui->FavCompNumber->display(MyDataLayer->favCompNumber());
}

void GUI::showTime()
{
    QTime time=QTime::currentTime();
    QString time_text=time.toString("hh : mm : ss");
    ui->Clock->setText(time_text);
    //ui->Clock->setStyleSheet("(color: #6394d5)");
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
        if(ui->comboBox->currentIndex() == 0)
        {
            sciencePopUp sciPop(0, this);
            sciPop.setModal(true);
            sciPop.exec();

        }

        if(ui->comboBox->currentIndex() == 1)
        {
            Dialog addPopUp(0, this);
            addPopUp.setModal(true);
            addPopUp.exec();
        }

        ui->SciNumber->display(MyDataLayer->sciNumber());
        ui->FavSciNumber->display(MyDataLayer->favSciNumber());
        ui->CompNumber->display(MyDataLayer->compNumber());
        ui->FavCompNumber->display(MyDataLayer->favCompNumber());
}

/************************************************
 * on_Remove_clicked
 * triggers then the REMOVE button is clicked
 * ***********************************************/
void GUI::on_Remove_clicked()
{

    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/new/audio/trashcan.wav"));
    music->play();

    QList<QTableWidgetItem *> selected = ui->mainTable->selectedItems();
    set<int> distinctRows;
    for(int i = 0; i < selected.size();i++)
    {
        distinctRows.insert(selected[i]->row());
    }
    for(set<int>::reverse_iterator I = distinctRows.rbegin(); I != distinctRows.rend();++I)
    {
        int i = (*I);
        if(ui->comboBox->currentIndex() % 2 == 0)
        {
            MyDataLayer->remove(getRowScientist(i));
        }
        else
        {
            MyDataLayer->remove(getRowComputer(i));
        }
        ui->mainTable->removeRow(i);
    }

    ui->SciNumber->display(MyDataLayer->sciNumber());
    ui->FavSciNumber->display(MyDataLayer->favSciNumber());
    ui->CompNumber->display(MyDataLayer->compNumber());
    ui->FavCompNumber->display(MyDataLayer->favCompNumber());

    ui->statusBar->showMessage("Index removed!", 2500);

}

/************************************************
 * on_Fostudagur_clicked
 * Triggeres when the FOSTUDAGUR button is clicked
 * ***********************************************/
void GUI::on_Fostudagur_clicked()
{
    vector <QString> links;

    QString otherLink = "https://en.wikipedia.org/wiki/Edsger_W._Dijkstra/";
    links.push_back(otherLink);
    otherLink = "https://en.wikipedia.org/wiki/Bill_Gates";
    links.push_back(otherLink);
    otherLink = "https://en.wikipedia.org/wiki/Donald_Knuth";
    links.push_back(otherLink);
    otherLink = "https://en.wikipedia.org/wiki/Alan_Turing";
    links.push_back(otherLink);
    otherLink = "https://en.wikipedia.org/wiki/Anita_Borg";
    links.push_back(otherLink);
    otherLink = "https://en.wikipedia.org/wiki/John_Mauchly";
    links.push_back(otherLink);
    otherLink = "https://en.wikipedia.org/wiki/Steve_Wozniak";
    links.push_back(otherLink);
    otherLink = "https://en.wikipedia.org/wiki/Tim_Cook";
    links.push_back(otherLink);



    QDesktopServices::openUrl(QUrl(links[qrand()%8]));
}

/************************************************
 * ErrorMessage()
 * Shows an error messages when there is an error in input
 * ***********************************************/
void GUI::ErrorMessage()
{
    ui->statusBar->showMessage("Could not add to database! Please input a valid name, year of birth and year death.");
}

/************************************************
 * AddToTable
 * adds a single row to the tableview
 * ***********************************************/
void GUI::AddToTable(QString field1,QString field2, QString field3, QString field4, QString field5)
{
    vector<string> data;
    data.push_back(field1.toStdString());
    data.push_back(field2.toStdString());
    data.push_back(field3.toStdString());
    data.push_back(field4.toStdString());
    data.push_back(field5.toStdString());

    ui->mainTable->setRowCount(ui->mainTable->rowCount()+1);
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,0, new QTableWidgetItem(field1));
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,1, new QTableWidgetItem(field2));
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,2, new QTableWidgetItem(field3));
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,3, new QTableWidgetItem(field4));
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,4, new QTableWidgetItem(field5));
    MyDataLayer->Add(data);
    ui->searchbar->setText(field1 + " " + field2);
    on_searchbar_returnPressed();
}

void GUI::AddToTable(QString field1,QString field2, QString field3, QString field4, QString field5, QString field6)
{

    ui->statusBar->showMessage("Index added!", 2500);

    ui->mainTable->setRowCount(ui->mainTable->rowCount()+1);

    string utf8_nameString = field1.toUtf8().constData();
    vector <string> fullNameString = explode(utf8_nameString, ' ');
    vector <QString> fullName;
    vector<string> entrydata;

    for(unsigned int i = 0; i < fullNameString.size(); i++)
    {
        fullName.push_back(QString::fromStdString(fullNameString[i]));
    }

    if(fullName.size() > 3)
    {
        QString middlename;
        for(int i = 1; i < fullName.size()-1;i++)
        {
            middlename += fullName[i] + " ";
        }
        ui->mainTable->setItem(ui->mainTable->rowCount()-1,0, new QTableWidgetItem(fullName[0]));
        ui->mainTable->setItem(ui->mainTable->rowCount()-1,1, new QTableWidgetItem(middlename));
        ui->mainTable->setItem(ui->mainTable->rowCount()-1,2, new QTableWidgetItem(fullName[fullName.size()-1]));

        entrydata.push_back(fullName[0].toStdString());
        entrydata.push_back(middlename.toStdString());
        entrydata.push_back(fullName[fullName.size()-1].toStdString());
    }

    else if(fullName.size() == 2)
    {
        ui->mainTable->setItem(ui->mainTable->rowCount()-1,0, new QTableWidgetItem(fullName[0]));
        ui->mainTable->setItem(ui->mainTable->rowCount()-1,2, new QTableWidgetItem(fullName[1]));
        entrydata.push_back(fullName[0].toStdString());
        entrydata.push_back("");
        entrydata.push_back(fullName[1].toStdString());
    }

    ui->mainTable->setItem(ui->mainTable->rowCount()-1,3, new QTableWidgetItem(field2));
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,4, new QTableWidgetItem(field3));
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,5, new QTableWidgetItem(field4));
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,6, new QTableWidgetItem(field5));
    ui->mainTable->setItem(ui->mainTable->rowCount()-1,7, new QTableWidgetItem(field6));

    entrydata.push_back(field2.toStdString());
    entrydata.push_back(field3.toStdString());
    entrydata.push_back(field4.toStdString());
    entrydata.push_back(field5.toStdString());
    entrydata.push_back(field6.toStdString());
    MyDataLayer->Add(entrydata);
    ui->searchbar->setText(fullName[0] + " " + fullName[fullName.size()-1]);
    on_searchbar_returnPressed();
}

/************************************************
 * on_comboBox_currentIndexChanged
 * Triggers when the drop down menu changes
 * ***********************************************/
void GUI::on_comboBox_currentIndexChanged(int index)
{
    ui->mainTable->clear();
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
                if(Data[i].getFavorite())
                {
                    setRowColor(i);
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
                if(Data[i].getFavorite())
                {
                    setRowColor(i);
                }
            }
            break;
        }
        case 2:
        {
            vector<ComputerScientist> Data;
            MyDataLayer->GetFavorite(Data);

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
                if(Data[i].getFavorite())
                {
                    setRowColor(i);
                }
            }
           break;
        }
        case 3:
        {
            vector<computer> Data;
            MyDataLayer->GetFavorite(Data);

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
                if(Data[i].getFavorite())
                {
                    setRowColor(i);
                }
            }
           break;
        }
    }

    QFont myFont;
    myFont.setBold(true);


    //Column names
    if(ui->comboBox->currentIndex() == 0 || ui->comboBox->currentIndex() == 2)
    {
        ui->mainTable->setHorizontalHeaderLabels(QStringList()<<"First name"<<"Middle name"<<"Last name"<<"Gender"<<"Born"<<"Died"<<"Nationality"<<"Field");
        ui->mainTable->horizontalHeader()->setFont(myFont);

        ui->mainTable->setColumnWidth(0, 80);
        ui->mainTable->setColumnWidth(1, 105);
        ui->mainTable->setColumnWidth(2, 80);
        ui->mainTable->setColumnWidth(3, 50);
        ui->mainTable->setColumnWidth(4, 40);
        ui->mainTable->setColumnWidth(5, 40);
        ui->mainTable->setColumnWidth(6, 90);
        ui->mainTable->setColumnWidth(7, 315);
    }
    else if(ui->comboBox->currentIndex() == 1 || ui->comboBox->currentIndex() == 3)
    {
         ui->mainTable->setHorizontalHeaderLabels(QStringList()<<"Name"<<"Year"<<"Type"<<"Built"<<"Location");
         ui->mainTable->horizontalHeader()->setFont(myFont);

         ui->mainTable->setColumnWidth(0, 180);
         ui->mainTable->setColumnWidth(1, 152);
         ui->mainTable->setColumnWidth(2, 165);
         ui->mainTable->setColumnWidth(3, 145);
         ui->mainTable->setColumnWidth(4, 150);
    }
}


/************************************************
 * on_searchbar_returnPressed
 * Triggers when "enter" is pressed
 * Calls the search functions
 * ***********************************************/
void GUI::on_searchbar_returnPressed()
{
    ui->mainTable->clear();
    if(ui->comboBox->currentIndex() == 0)
    {
        searchCompSci();
    }
    if(ui->comboBox->currentIndex() == 1)
    {
        searchComputer();
    }
    QFont myFont;
    myFont.setBold(true);


    //Column names
    if(ui->comboBox->currentIndex() == 0 || ui->comboBox->currentIndex() == 2)
    {
        ui->mainTable->setHorizontalHeaderLabels(QStringList()<<"First name"<<"Middle name"<<"Last name"<<"Gender"<<"Born"<<"Died"<<"Nationality"<<"Field");
        ui->mainTable->horizontalHeader()->setFont(myFont);
    }

    else if(ui->comboBox->currentIndex() == 1 || ui->comboBox->currentIndex() == 3)
    {
         ui->mainTable->setHorizontalHeaderLabels(QStringList()<<"Name"<<"Year"<<"Type"<<"Built"<<"Location");
         ui->mainTable->horizontalHeader()->setFont(myFont);
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

/************************************************
 * SetRowColor
 * ***********************************************/

bool GUI::setRowColor(int row)
{
    int colcount = ui->mainTable->columnCount();
    bool ret = false;
    for(int i = 0; i < colcount; i++)
    {
        QTableWidgetItem* currenTable = ui->mainTable->item(row,i);
        if(currenTable->backgroundColor() != QColor(255,200,200,255))
        {
            currenTable->setBackgroundColor(QColor(255,200,200,255));
            ret = true;
        }
        else
        {
            currenTable->setBackgroundColor(QColor(255,255,255,255));
            ret = false;
        }
    }
    return ret;
}

void GUI::on_Favorite_clicked()
{
    QList<QTableWidgetItem *> selected = ui->mainTable->selectedItems();
    set<int> distinctRows;
    for(int i = 0; i < selected.size();i++)
    {
        distinctRows.insert(selected[i]->row());
    }
    for(set<int>::reverse_iterator I = distinctRows.rbegin(); I != distinctRows.rend();++I)
    {
        int i = (*I);
        if(ui->comboBox->currentIndex() % 2 == 0)
        {
            MyDataLayer->setFavorite(getRowScientist(i),setRowColor(i));
        }
        else
        {
            MyDataLayer->setFavorite(getRowComputer(i),setRowColor(i));
        }
    }

    ui->SciNumber->display(MyDataLayer->sciNumber());
    ui->FavSciNumber->display(MyDataLayer->favSciNumber());
    ui->CompNumber->display(MyDataLayer->compNumber());
    ui->FavCompNumber->display(MyDataLayer->favCompNumber());
}

void GUI::on_Connections_clicked()
{
    Connections Connect(this,MyDataLayer);
    Connect.setModal(true);
    Connect.exec();
}



void GUI::on_Edit_clicked()
{
    if(ui->comboBox->currentIndex() % 2 == 0)
    {
        QList<QTableWidgetItem*> selected = ui->mainTable->selectedItems();
        ComputerScientist scifi = getRowScientist(selected[0]->row());
        sciencePopUp sciPop(0, this);
        sciPop.setModal(true);
        sciPop.mode(scifi);
        sciPop.exec();
    }
    else
    {
        QList<QTableWidgetItem*> selected = ui->mainTable->selectedItems();
        computer scifi = getRowComputer(selected[0]->row());
        Dialog sciPop(0, this);
        sciPop.setModal(true);
        sciPop.mode(scifi);
        sciPop.exec();
    }
}

void GUI::change(QString field1,QString field2, QString field3, QString field4, QString field5)
{
    computer newdata(field1.toStdString(),field2.toStdString(),field3.toStdString(),field4.toStdString(),field5.toStdString());
    QList<QTableWidgetItem*> selected = ui->mainTable->selectedItems();
    int row = selected[0]->row();
    computer olddata = getRowComputer(row);

    ui->mainTable->setItem(row,0, new QTableWidgetItem(field1));
    ui->mainTable->setItem(row,1, new QTableWidgetItem(field2));
    ui->mainTable->setItem(row,2, new QTableWidgetItem(field3));
    ui->mainTable->setItem(row,3, new QTableWidgetItem(field4));
    ui->mainTable->setItem(row,4, new QTableWidgetItem(field5));
    MyDataLayer->update(olddata,newdata);
}
void GUI::change(QString field1,QString field2, QString field3, QString field4, QString field5, QString field6)
{
    string utf8_nameString = field1.toUtf8().constData();
    vector <string> fullNameString = explode(utf8_nameString, ' ');
    vector <QString> fullName;
    vector<string> entrydata;
    QList<QTableWidgetItem*> selected = ui->mainTable->selectedItems();
    int row = selected[0]->row();
    ComputerScientist oldscifi = getRowScientist(row);

    for(unsigned int i = 0; i < fullNameString.size(); i++)
    {
        fullName.push_back(QString::fromStdString(fullNameString[i]));
    }

    if(fullName.size() > 2)
    {
        QString middlename;
        for(int i = 1; i < fullName.size()-1;i++)
        {
            middlename += fullName[i] + " ";
        }
        ui->mainTable->setItem(row,0, new QTableWidgetItem(fullName[0]));
        ui->mainTable->setItem(row,1, new QTableWidgetItem(middlename));
        ui->mainTable->setItem(row,2, new QTableWidgetItem(fullName[fullName.size()-1]));

        entrydata.push_back(fullName[0].toStdString());
        entrydata.push_back(middlename.toStdString());
        entrydata.push_back(fullName[fullName.size()-1].toStdString());
    }

    else if(fullName.size() == 2)
    {
        ui->mainTable->setItem(row,0, new QTableWidgetItem(fullName[0]));
        ui->mainTable->setItem(row,2, new QTableWidgetItem(fullName[1]));
        entrydata.push_back(fullName[0].toStdString());
        entrydata.push_back("");
        entrydata.push_back(fullName[1].toStdString());
    }

    ui->mainTable->setItem(row,3, new QTableWidgetItem(field2));
    ui->mainTable->setItem(row,4, new QTableWidgetItem(field3));
    ui->mainTable->setItem(row,5, new QTableWidgetItem(field4));
    ui->mainTable->setItem(row,6, new QTableWidgetItem(field5));
    ui->mainTable->setItem(row,7, new QTableWidgetItem(field6));

    entrydata.push_back(field2.toStdString());
    entrydata.push_back(field3.toStdString());
    entrydata.push_back(field4.toStdString());
    entrydata.push_back(field5.toStdString());
    entrydata.push_back(field6.toStdString());
    ComputerScientist newscifi(entrydata[0],entrydata[1],entrydata[2],entrydata[3],entrydata[4],entrydata[5],entrydata[6],entrydata[7]);
    MyDataLayer->update(oldscifi,newscifi);
}
