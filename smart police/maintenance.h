#ifndef MAINTENANCE_H
#define MAINTENANCE_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QTableView>
#include <QPrinter>
#include<QPainter>
#include <QTextDocument>
#include <QTableWidget>



class maintenance
{
public:
    maintenance();
    maintenance(QString,QString,QString);
    QString getnumm(){return numm;}
    QString getdatem(){return datem;}
    QString gettypem(){return typem;}

        bool ajouter();
        QSqlQueryModel * afficher();
        bool supprimer(QString);
        bool modifier(QString);
        QSqlQueryModel * chercher(QString);
       static void printPDF(QTableView * tableView_2);
private:
        QString numm,datem,typem ;

};

#endif // MAINTENANCE_H
