#ifndef AGENT_H
#define AGENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Agent
{
public:
    Agent();
    Agent(int,QString,QString,QString);

    bool Ajouter();
    bool Supprimer(int);
    bool Modifier(int);
    QSqlQueryModel* trier_Cin();
    QSqlQueryModel* trier_Nom();
    QSqlQueryModel* trier_Permon();
    QSqlQueryModel* afficher();
    QSqlQueryModel * rechercher(QString);

private:
    QString Nom,Prenom,Date;
    int Cin;
};

#endif // AGENT_H
