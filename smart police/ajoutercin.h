#ifndef AJOUTERCIN_H
#define AJOUTERCIN_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class ajoutercin
{
public:
    ajoutercin();
    ajoutercin(QString,QString,QString,QString,QString,QString,QString,QString);
    QString getidc(){return idc;}
    QString getnomc(){return nomc;}
    QString getprennomc(){return prenomc;}
    QString getdate(){return datec;}
    QString getlieu(){return lieuc;}
    QString getadressec(){return adressec;}
    QString getmetierc(){return metierc;}
    QString getsexe(){return sexe;}


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString);
    QSqlQueryModel* recherche(QString);
    QSqlQueryModel * trier();
    QSqlQueryModel * trierdec();


private:

      QString idc,nomc,prenomc,datec,lieuc,adressec,metierc,sexe ;
};

#endif // AJOUTERCIN_H
