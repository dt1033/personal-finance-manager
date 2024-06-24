#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QStringList>

class Database {
public:
    Database();
    bool authenticateUser(const QString &username, const QString &password);
    QStringList getTransactions();
    void addTransaction(const QString &description, double amount);

private:
    void initializeDatabase();
};

#endif // DATABASE_H
