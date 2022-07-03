#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->UserName->setPlaceholderText("Enter Your UserName");
    ui->Password->setPlaceholderText("Enter Your Password");
    ui->Email->setPlaceholderText("Enter Your Email");
    ui->Phone->setPlaceholderText("Enter Your Phone");
    ui->UserNameLogin->setPlaceholderText("Please Enter UserName");
    ui->PasswordLogin->setPlaceholderText("Please Enter Password");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_registerBtn_clicked()
{
    AddQMYSQLWithCredentials(database);

    if(database.open()) {
        // Retrieve Data From Input Fileds

        QString username = ui->UserName->text();
        QString password = ui->Password->text();
        QString email = ui->Email->text();
        QString phone = ui->Phone->text();

        //Run Our Insert Query

        QSqlQuery qry;

        qry.prepare("INSERT INTO users (username, password, email, phone)"
                    "VALUES (:username, :password, :email, :phone)");

        qry.bindValue(":username", username);
        qry.bindValue(":password", password);
        qry.bindValue(":email", email);
        qry.bindValue(":phone", phone);

        if(qry.exec()) {
            QMessageBox::information(this, "Inserted", "Data Inserted Successfully");
        }else {
            QMessageBox::information(this, "Not Inserted", "Data Is Not Inserted");
        }
    }else {
        QMessageBox::information(this, "Not Connected", "Database is not connected");
    }
}


void MainWindow::on_loginBtn_clicked()
{
    QSqlDatabase db;
    AddQMYSQLWithCredentials(db);

    QString usernameLogin = ui->UserNameLogin->text();
    QString passwordLogin = ui->PasswordLogin->text();

    if(db.open()) {
        QSqlQuery query(QSqlDatabase::database("MyConnect"));

        query.prepare(QString("SELECT * FROM users WHERE username = :username AND password = :password"));

        query.bindValue(":username", usernameLogin);
        query.bindValue(":password", passwordLogin);

        if(!query.exec()) {
            QMessageBox::information(this, "Failed", "Query Failed To Execute");
        }else {
            while(query.next()) {
                QString usernameFromDB = query.value(1).toString();
                QString passwordFromDB = query.value(2).toString();

                if(usernameFromDB == usernameLogin && passwordFromDB == passwordLogin) {
                    QMessageBox::information(this, "Success", "Login Success");

                    MyDialog dialog;
                    dialog.setModal(true);
                    dialog.exec();
                }
            }
        }
    }else {
        QMessageBox::information(this, "Database Failed", "Database Connection Failed");
    }
}

// Connecting To Mysql Database
void MainWindow::AddQMYSQLWithCredentials(QSqlDatabase &db)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("");
    db.setDatabaseName("qt5register");
}

