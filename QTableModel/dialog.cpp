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
        tableModel = new QSqlTableModel();
        tableModel->setTable("users");
        tableModel->select();

        tableModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        tableModel->setHeaderData(1, Qt::Horizontal, tr("USERNAME"));
        tableModel->setHeaderData(2, Qt::Horizontal, tr("PASSWORD"));
        tableModel->setHeaderData(3, Qt::Horizontal, tr("EMAIL"));
        tableModel->setHeaderData(4, Qt::Horizontal, tr("PHONE"));

        ui->tableView->setModel(tableModel);
    }else {
        QMessageBox::information(this, "Database Failed", "Database Connection Failed");
    }
}

Dialog::~Dialog()
{
    database.close();
    delete ui;
}

