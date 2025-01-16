#include "connection.h"
#include "QSqlDatabase"
Connection::Connection()
{

}

bool Connection::ouvrirconnexion()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("base");
db.setUserName("sylla");//inserer nom de l'utilisateur
db.setPassword("1234");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;
    return  test;
}


void Connection::fermerconnexion()
{

    db.close();
    db.removeDatabase("db");
}
