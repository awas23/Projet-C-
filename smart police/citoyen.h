#ifndef CITOYEN_H
#define CITOYEN_H
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDate>

class Citoyen
{
private:
    int id;
    int cin;
    QString nom;
    QString prenom;
    int age;


public:
    Citoyen();
    Citoyen(int,int,QString,QString,int);

    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * chercher(QString);
    bool supprimer(QString);
    void getCitoyen(QString);
    QSqlQueryModel * trier();
    QSqlQueryModel * trier_down();




    int getId() const;
    void setId(int value);
    int getCin() const;
    void setCin(int value);
    QString getNom() const;
    void setNom(const QString &value);
    QString getPrenom() const;
    void setPrenom(const QString &value);
    int getAge() const;
    void setAge(int value);
};

#endif // CITOYEN_H
