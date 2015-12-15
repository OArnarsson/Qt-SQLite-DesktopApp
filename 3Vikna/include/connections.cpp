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
        ComputerScientist entry = parseScientist(item->text().toStdString());
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
        computer entry = parseComputer(item->text().toStdString());
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

computer Connections::parseComputer(string term)
{
    vector<string> allWeNeed;
    vector<string> name;
    vector<string> years;
    vector<string> soTired;
    cout << 130 << endl;
    allWeNeed = daddy->explode(term,'(');
    // 0 name, 1 date
        cout << 133 << endl;
    name = daddy->explode(allWeNeed[0],' ');
        cout << 135 << endl;
    years = daddy->explode(allWeNeed[1],',');
        cout << 137 << endl;
        cout << years[0] << endl;
    soTired = daddy->explode(years[1],')');

    cout << 140 << endl;
    computer entry(name[0],years[0],soTired[0],"true","");
    return entry;
}

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

void Connections::on_leftsearch_returnPressed()
{
    vector<ComputerScientist> vecvec;
    dataLayer->Search(vecvec,ui->leftsearch->text().toStdString());
    ui->left2->clear();
    for(int i = 0; i < vecvec.size();i++)
    {
        QString name;
        name = QString::fromStdString(vecvec[i].field(1) + " " + vecvec[i].field(2) + " " + vecvec[i].field(3)
             + " ("+vecvec[i].field(5)+"-"+vecvec[i].field(6)+ ")");
            ui->left2->insertItem(ui->left2->count(),new QListWidgetItem(name));
    }
}

void Connections::on_rightsearch_returnPressed()
{
    vector<computer> vecvec;
    dataLayer->Search(vecvec,ui->rightsearch->text().toStdString());
    ui->right2->clear();
    for(int i = 0; i < vecvec.size();i++)
    {
        QString name;
        name = QString::fromStdString(vecvec[i].field(1) + " (" + vecvec[i].field(2) + ","+vecvec[i].field(3)+")");
            ui->right2->insertItem(ui->right2->count(),new QListWidgetItem(name));
    }
}

void Connections::on_Add_clicked()
{
    QList<QListWidgetItem*> rightlist = ui->right2->selectedItems();
    QList<QListWidgetItem*> leftlist = ui->left2->selectedItems();
    cout << rightlist.size();
    cout << leftlist.size();
    if(rightlist.size() > 0 && leftlist.size() > 0)
    {
        cout << 188 << endl;
        ComputerScientist Scifi = parseScientist(leftlist[0]->text().toStdString());
                cout << 190 << endl;
        computer Compfi = parseComputer(rightlist[0]->text().toStdString());
                cout << 192 << endl;
        dataLayer->AddConnection(Scifi,Compfi);
    }
}
