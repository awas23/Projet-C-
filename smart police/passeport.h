#ifndef PASSEPORT_H
#define PASSEPORT_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
class passeport
{
public:
    passeport();
    passeport(QString,QString,QString,QString,QString,QString,QString);
    QString geticinp(){return cinp;}
    QString getidp(){return idp;}
    QString getnomp(){return nomp;}
    QString getprennomp(){return prenomp;}
    QString getdatep(){return datep;}
    QString getadressep(){return adressep;}
    QString getmetierp(){return metierp;}

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString);
    QSqlQueryModel* recherche(QString);
    QSqlQueryModel * trier();
    QSqlQueryModel * trierdec();
private:
    QString cinp,idp,nomp,prenomp,datep,adressep,metierp ;

};

#endif // PASSEPORT_H
