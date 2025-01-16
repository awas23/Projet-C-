#ifndef CERTIFCAT_H
#define CERTIFCAT_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class certificat
{
public:
    certificat();
    certificat(QString,QString,QString,QString,QString,QString);
    QString getidc(){return idcer;}
    QString getnomc(){return nomcer;}
    QString getprennomc(){return prenomcer;}
    QString getnompere(){return nompere;}
    QString getdate(){return datesor;}
    QString getadressec(){return adresseres;}



    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString);
    QSqlQueryModel * recherche(QString);
    QSqlQueryModel * trier();
    QSqlQueryModel * trierdec();


private:

      QString idcer,nomcer,prenomcer,nompere,datesor,adresseres ;
};

#endif // CERTIFCAT_H
