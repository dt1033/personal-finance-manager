#include "database.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

Database::Database() {
    initializeDatabase();
}

void Database::initializeDatabase() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("finance.db");

    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
    } else {
        qDebug() << "Database: connection ok";
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, username TEXT, password TEXT)");
    query.exec("CREATE TABLE IF NOT EXISTS transactions (id INTEGER PRIMARY KEY, description TEXT, amount REAL)");

    // Add a test user
    query.exec("INSERT INTO users (username, password) VALUES ('test', 'test123')");
}

bool Database::authenticateUser(const QString &username, const QString &password) {
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    query.exec();

    if (query.next()) {
        return true;
    }

    return false;
}

QStringList Database::getTransactions() {
    QStringList transactions;
    QSqlQuery query("SELECT description, amount FROM transactions");

    while (query.next()) {
        QString description = query.value(0).toString();
        double amount = query.value(1).toDouble();
        transactions.append(description + ": " + QString::number(amount));
    }

    return transactions;
}

void Database::addTransaction(const QString &description, double amount) {
    QSqlQuery query;
    query.prepare("INSERT INTO transactions (description, amount) VALUES (:description, :amount)");
    query.bindValue(":description", description);
    query.bindValue(":amount", amount);
    query.exec();
}
