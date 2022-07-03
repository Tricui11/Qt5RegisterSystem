#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("localhost");
    database.setUserName("root");
    database.setPassword("");
    database.setDatabaseName("qt5register");

    if(database.open()) {
        queryModel = new QSqlQueryModel();
        queryModel->setQuery("SELECT * FROM users");
        ui->tableView->setModel(queryModel);
    }else {
        QMessageBox::information(this, "Database Failed", "Database Connection Failed");
    }
}

Dialog::~Dialog()
{
    database.close();
    delete ui;
}

