#ifndef RECLAMATION_H
#define RECLAMATION_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class reclamation
{
public:
    reclamation();
    reclamation(QString,QString,QString,QString,QString,QString,QString);
    QString getcin(){return cin;}
    QString getnomr(){return nomr;}
    QString getprenomr(){return prenomr;}
    QString getadresser(){return adresser;}
    QString gettel(){return telr;}
    QString getdatere(){return datere;}
    QString getrecl(){return recl;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString);
    QSqlQueryModel* recherche(QString);
    QSqlQueryModel * trier();
    QSqlQueryModel * trierdec();
private:
    QString cin,nomr,prenomr,adresser,telr,datere,recl;
};
#endif // RECLAMATION_H
