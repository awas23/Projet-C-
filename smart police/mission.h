#ifndef MISSION_H
#define MISSION_H
#include <QString>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlQueryModel>
#include <QDate>

class Mission
{
private:
    int id;
    int numero;
    QString type;
    QString description;

public:
    Mission();
    Mission(int,int,QString,QString);


    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * chercher(QString);
    bool supprimer(QString);
    void getMission(QString);
    QSqlQueryModel * trier();
QSqlQueryModel * trier_down();

    int getId() const;
    void setId(int value);
    int getNumero() const;
    void setNumero(int value);
    QString getType() const;
    void setType(const QString &value);
    QString getDescription() const;
    void setDescription(const QString &value);

};

#endif // MISSION_H
