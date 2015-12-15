#include "connections.h"
#include "ui_connections.h"
#include "gui.h"

Connections::Connections(GUI *parent,MagicalDataClass* dataThief) :
    QDialog(parent),
    ui(new Ui::Connections)
{
    ui->setupUi(this);
    daddy = parent;
    dataLayer = dataThief;

    this->setFixedSize(455,345);
}

Connections::~Connections()
{
    delete ui;
}

void Connections::on_OkButton_2_clicked()
{
    on_OkButton_clicked();
}

void Connections::on_OkButton_clicked()
{
   // close();
}

void Connections::on_quicksearch_returnPressed()
{
    if(ui->comboBox->currentIndex() == 0){
        vector<ComputerScientist> vecvec;
        dataLayer->Search(vecvec,ui->quicksearch->text().toStdString());
        ui->Right->clear();
        ui->Left->clear();
        for(int i = 0; i < vecvec.size();i++)
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
        for(int i = 0; i < vecvec.size();i++)
        {
            addTable(vecvec[i]);
        }
    }
}

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

void Connections::on_Left_itemClicked(QListWidgetItem *item)
{
    if(ui->comboBox->currentIndex() == 0)
    {
        vector<string> allWeNeed;
        vector<string> name;
        vector<string> years;
        allWeNeed = daddy->explode(item->text().toStdString(),'(');
        // 0 name, 1 date
        name = daddy->explode(allWeNeed[0],' ');
        years = daddy->explode(allWeNeed[1],'-');
        ComputerScientist entry(name[0],"",name[name.size()-1],"",years[0],"","","");
        vector<computer> connected = dataLayer->getConnections(entry);
        ui->Right->clear();
        for(int i = 0; i < connected.size();i++)
        {
            QString compdata = QString::fromStdString(connected[i].field(2) + " ("+connected[i].field(3)+","+connected[i].field(4)+")");
            ui->Right->insertItem(ui->Right->count(),new QListWidgetItem(compdata));
        }
    }
    else
    {
        vector<string> allWeNeed;
        vector<string> name;
        vector<string> years;
        vector<string> soTired;
        allWeNeed = daddy->explode(item->text().toStdString(),'(');
        // 0 name, 1 date
        name = daddy->explode(allWeNeed[0],' ');
        years = daddy->explode(allWeNeed[1],',');
        soTired = daddy->explode(years[1],')');
        computer entry(name[0],years[0],soTired[0],"true","");
        cout << years[0];
        vector<ComputerScientist> connected = dataLayer->getConnections(entry);
        ui->Right->clear();
        for(int i = 0; i < connected.size();i++)
        {
            QString compdata = QString::fromStdString(connected[i].field(1) + " " + connected[i].field(2) + " " + connected[i].field(3)
                             + " ("+connected[i].field(5)+"-"+connected[i].field(6)+ ")");
            ui->Right->insertItem(ui->Right->count(),new QListWidgetItem(compdata));
        }
    }
}

void Connections::on_comboBox_currentIndexChanged(int index)
{
    ui->Left->clear();
    ui->Right->clear();
}

void Connections::on_Remove_clicked()
{
    /*QList rightlist<QListWidgetItem*> = ui->Right->selectedItems();
    QList leftlist<QListWidgetItem*> = ui->Right->selectedItems();*/

}
