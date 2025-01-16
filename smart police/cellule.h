#ifndef CELLULE_H
#define CELLULE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
class cellule
{
public:
    cellule();
    cellule(QString,QString,QString,QString);
    void setnum(QString nm);
    void setdateen(QString de);
    void setdateso(QString ds);
    void setdispo (QString dis);
    QString get_num();
    QString get_dateen();
    QString get_dateso();
    QString get_dispo();

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString num);
    void genererPDF();




private:
    QString num, dateen, dateso, dispo;

};

#endif // CELLULE_H
