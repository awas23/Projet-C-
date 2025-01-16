#ifndef BUDGET_H
#define BUDGET_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>


class budget
{
public:
    budget();
    budget(QString,QString,QString);
    QString getnumr(){return numr;}
    QString getdatere(){return dater;}
    QString getsommer(){return sommer;}

        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(QString);
        bool modifier(QString);
        QSqlQueryModel * trier();
        QSqlQueryModel * trierdec();
        QSqlQueryModel * chercher(QString);

private:
        QString numr,dater,sommer ;

};

#endif // BUDGET_H
