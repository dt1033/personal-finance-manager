#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Load transactions from the database and display
    Database db;
    QStringList transactions = db.getTransactions();
    ui->transactionListWidget->addItems(transactions);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_addTransactionButton_clicked() {
    QString description = ui->descriptionLineEdit->text();
    double amount = ui->amountDoubleSpinBox->value();

    Database db;
    db.addTransaction(description, amount);

    ui->transactionListWidget->addItem(description + ": " + QString::number(amount));
}
