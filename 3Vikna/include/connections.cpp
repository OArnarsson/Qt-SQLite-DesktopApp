#include "connections.h"
#include "ui_connections.h"
#include "gui.h"
#include <QMediaPlayer>

/***********************************
 * construct
 * ***********************************/
Connections::Connections(GUI *parent,MagicalDataClass* dataThief) :
    QDialog(parent),
    ui(new Ui::Connections)
{
    ui->setupUi(this);
    daddy = parent;
    dataLayer = dataThief;
    this->setFixedSize(455,345);
    on_comboBox_currentIndexChanged(0);
}

Connections::~Connections()
{
    delete ui;
}

/***********************************
 * Quicksearch
 * Searches the database and fills in table
 * ***********************************/
void Connections::on_quicksearch_returnPressed()
{
    if(ui->comboBox->currentIndex() == 0){
        vector<ComputerScientist> vecvec;
        dataLayer->Search(vecvec,ui->quicksearch->text().toStdString());
        ui->Right->clear();
        ui->Left->clear();
        for(unsigned int i = 0; i < vecvec.size();i++)
        {
            addTable(vecvec[i]);
        }
    }
    else
    {
        vector<computer> vecvec;
        dataLayer->Search(vecvec,ui->quicksearch->text().toStdString());
        ui->Right->clear();
        ui->Left->clear();
        for(unsigned int i = 0; i < vecvec.size();i++)
        {
            addTable(vecvec[i]);
        }
    }
}

/***********************************
 * Adds an item to the table
 * ***********************************/
void Connections::addTable(ComputerScientist compsci)
{
    QString name;
    name = QString::fromStdString(compsci.field(1) + " " + compsci.field(2) + " " + compsci.field(3)
         + " ("+compsci.field(5)+"-"+compsci.field(6)+ ")");
        ui->Left->insertItem(ui->Left->count(),new QListWidgetItem(name));
}

void Connections::addTable(computer compsci)
{
    QString name;
    name = QString::fromStdString(compsci.field(1) + " (" + compsci.field(2) + ","+compsci.field(3)+")");
        ui->Left->insertItem(ui->Left->count(),new QListWidgetItem(name));
}

/***********************************
 * When something is selected on the left
 * finds and displays all connections
 * ,parsing them to the correct form
 * ***********************************/
void Connections::on_Left_itemClicked(QListWidgetItem *item)
{
    if(ui->comboBox->currentIndex() == 0)
    {
        ComputerScientist entry = parseScientist(item->text().toStdString());
        vector<computer> connected = dataLayer->getConnections(entry);
        ui->Right->clear();
        for(unsigned int i = 0; i < connected.size();i++)
        {
            QString compdata = QString::fromStdString(connected[i].field(2) + " ("+connected[i].field(3)+","+connected[i].field(4)+")");
            ui->Right->insertItem(ui->Right->count(),new QListWidgetItem(compdata));
        }
    }
    else
    {
        computer entry = parseComputer(item->text().toStdString());
        vector<ComputerScientist> connected = dataLayer->getConnections(entry);
        ui->Right->clear();
        for(unsigned int i = 0; i < connected.size();i++)
        {
            QString compdata = QString::fromStdString(connected[i].field(1) + " " + connected[i].field(2) + " " + connected[i].field(3)
                             + " ("+connected[i].field(5)+"-"+connected[i].field(6)+ ")");
            ui->Right->insertItem(ui->Right->count(),new QListWidgetItem(compdata));
        }
    }
}

/***********************************
 * when the dropdown is changed
 * fills the table with all items connected to something
 * ***********************************/
void Connections::on_comboBox_currentIndexChanged(int index)
{
    ui->Left->clear();
    ui->Right->clear();
    if(index == 0)
    {
        vector<ComputerScientist> vecvec;
        dataLayer->allConnections(vecvec);
        cout << "Size k:" << vecvec.size()<<endl;
        ui->Left->clear();
        for(unsigned int i = 0; i < vecvec.size();i++)
        {
            QString name;
            name = QString::fromStdString(vecvec[i].field(1) + " " + vecvec[i].field(2) + " " + vecvec[i].field(3)
                 + " ("+vecvec[i].field(5)+"-"+vecvec[i].field(6)+ ")");
                ui->Left->insertItem(ui->Left->count(),new QListWidgetItem(name));
        }
    }
    else
    {
        vector<computer> vecvec;
        dataLayer->allConnections(vecvec);
        ui->Left->clear();
        for(unsigned int i = 0; i < vecvec.size();i++)
        {
            QString name;
            name = QString::fromStdString(vecvec[i].field(1) + " (" + vecvec[i].field(2) + ","+vecvec[i].field(3)+")");
                ui->Left->insertItem(ui->Left->count(),new QListWidgetItem(name));
        }
    }
}

/***********************************
 * Destroyes a connection
 * parses the item in the table to remove it
 * ***********************************/
void Connections::on_Remove_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/new/audio/trashcan.wav"));
    music->play();

    QList<QListWidgetItem*> rightlist = ui->Right->selectedItems();
    QList<QListWidgetItem*> leftlist = ui->Left->selectedItems();
    if(rightlist.size() > 0 && leftlist.size() > 0)
    {
        if(ui->comboBox->currentIndex() == 0)
        {
            ComputerScientist Scifi = parseScientist(leftlist[0]->text().toStdString());
            computer Compfi = parseComputer(rightlist[0]->text().toStdString());
            dataLayer->removeConnection(Scifi,Compfi);
        }
        else
        {
            ComputerScientist Scifi = parseScientist(rightlist[0]->text().toStdString());
            computer Compfi = parseComputer(leftlist[0]->text().toStdString());
            dataLayer->removeConnection(Scifi,Compfi);
        }
    }
}

/***********************************
 * Turns the table string to a computer
 * ***********************************/
computer Connections::parseComputer(string term)
{
    vector<string> allWeNeed;
    vector<string> name;
    vector<string> years;
    vector<string> soTired;

    allWeNeed = daddy->explode(term,'(');
    name = daddy->explode(allWeNeed[0],' ');
    years = daddy->explode(allWeNeed[1],',');
    soTired = daddy->explode(years[1],')');

    computer entry(name[0],years[0],soTired[0],"true","");
    return entry;
}

/***********************************
 * Turns the string into a scientist
 * ***********************************/
ComputerScientist Connections::parseScientist(string term)
{
    vector<string> allWeNeed;
    vector<string> name;
    vector<string> years;
    allWeNeed = daddy->explode(term,'(');
    // 0 name, 1 date
    name = daddy->explode(allWeNeed[0],' ');
    years = daddy->explode(allWeNeed[1],'-');
    ComputerScientist entry(name[0],"",name[name.size()-1],"",years[0],"","","");
    cout << name[0] << ";" << endl;
    return entry;
}

/***********************************
 * Searches the database for scientist
 * fills the left table
 * ***********************************/
void Connections::on_leftsearch_returnPressed()
{
    vector<ComputerScientist> vecvec;
    dataLayer->Search(vecvec,ui->leftsearch->text().toStdString());
    ui->left2->clear();
    for(unsigned int i = 0; i < vecvec.size();i++)
    {
        QString name;
        name = QString::fromStdString(vecvec[i].field(1) + " " + vecvec[i].field(2) + " " + vecvec[i].field(3)
             + " ("+vecvec[i].field(5)+"-"+vecvec[i].field(6)+ ")");
            ui->left2->insertItem(ui->left2->count(),new QListWidgetItem(name));
    }
}

/***********************************
 * searches the database on the right
 * fills right table with computers
 * ***********************************/
void Connections::on_rightsearch_returnPressed()
{
    vector<computer> vecvec;
    dataLayer->Search(vecvec,ui->rightsearch->text().toStdString());
    ui->right2->clear();
    for(unsigned int i = 0; i < vecvec.size();i++)
    {
        QString name;
        name = QString::fromStdString(vecvec[i].field(1) + " (" + vecvec[i].field(2) + ","+vecvec[i].field(3)+")");
            ui->right2->insertItem(ui->right2->count(),new QListWidgetItem(name));
    }
}

/***********************************
 * Adds a connection
 * finds what is selected either side
 * connects them
 * ***********************************/
void Connections::on_Add_clicked()
{
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/new/audio/ping.wav"));
    music->play();

    QList<QListWidgetItem*> rightlist = ui->right2->selectedItems();
    QList<QListWidgetItem*> leftlist = ui->left2->selectedItems();
    cout << rightlist.size();
    cout << leftlist.size();
    if(rightlist.size() > 0 && leftlist.size() > 0)
    {
        ComputerScientist Scifi = parseScientist(leftlist[0]->text().toStdString());
        computer Compfi = parseComputer(rightlist[0]->text().toStdString());
        dataLayer->AddConnection(Scifi,Compfi);
    }
}
