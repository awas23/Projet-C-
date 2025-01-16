#ifndef VEHICULE_H
#define VEHICULE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>



class vehicule
{
public:
    vehicule();
    vehicule(QString,QString,QString);
    void setnom(QString n);
    void settype(QString ty);
    void setnum (QString nu);
    QString getnom();
    QString gettype();
    QString getnum();


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString num);



private:
 QString nom, type, num;


};

#endif // VEHICULE_H
