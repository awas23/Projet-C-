#ifndef CATEGORIES_H
#define CATEGORIES_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>

class Categories
{
public:
    Categories();
    Categories(int,QString,QString,int);


    bool Ajouter();
    bool Supprimer(int);
    bool Modifier(int );
    QSqlQueryModel* afficher();
    QSqlQueryModel* rechercher(QString);
    QSqlQueryModel * trier_Grade();

    QSqlQueryModel * trier_Poste();

    QSqlQueryModel * trier_ID();
    void CREATION_PDF();


private:
    QString Poste,Grade;
    int Id,Note;
};

#endif // CATEGORIES_H
