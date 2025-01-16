#ifndef DETENU_H
#define DETENU_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>



class admin
{
public:
    admin();
    admin(QString,QString,QString,QString);
    void setcin(QString c);
    void setprenom(QString pr);
    void setnom (QString n);
    void setadresse (QString adr);
    QString get_cin();
    QString get_prenom();
    QString get_nom();
    QString get_adresse();


    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString cin);
     QSqlQueryModel * trier();
     QSqlQueryModel * trierdec();

     void genererPDF();

private:
 QString cin, prenom, nom, adresse;


};

#endif // DETENU_H
