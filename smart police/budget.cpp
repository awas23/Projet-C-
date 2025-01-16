#include "budget.h"

budget::budget()
{
    numr="";
    dater="";
    sommer="";
}
budget::budget(QString nr,QString dtr,QString tr)
{
    numr=nr;
    dater=dtr;
    sommer=tr;
}
bool budget::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO budget (numr,dater,sommer)"
                  "VALUES(:numr, :dater, :sommer)");
    query.bindValue(":numr",numr);
    query.bindValue(":dater",dater);
    query.bindValue(":sommer",sommer);
    return query.exec();
}
QSqlQueryModel *budget::afficher(){

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from budget");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("numero"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("somme"));
   return model;
}
bool budget::supprimer(QString numr){

    QSqlQuery query;
    query.prepare("delete from budget where numr = :numr");
    query.bindValue(":numr",numr);
    return query.exec();
}
bool budget::modifier(QString numr){
    QSqlQuery query;
    query.prepare("update budget set  sommer= :sommer where numr = :numr ");
    query.bindValue(":numr",numr);
    query.bindValue(":sommer",sommer);
    return query.exec();


}
//trier asc
QSqlQueryModel *budget::trier()
{
    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM budget order by sommer ASC");
           q->exec();
           model->setQuery(*q);
           return model;
     //ml kbir l sghir
       /*    QSqlQuery * q = new  QSqlQuery ();
                  QSqlQueryModel * model = new  QSqlQueryModel ();
                  q->prepare("SELECT * FROM permisconstruction order by codepostale DESC");
                  q->exec();
                  model->setQuery(*q);
                  return model;*/
}
//trie dcs
QSqlQueryModel *budget::trierdec() //ml Z-A
{
    /*QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM budget order by ref_produit ASC");
           q->exec();
           model->setQuery(*q);
           return model;*/
     //ml kbir l sghir
           QSqlQuery * q = new  QSqlQuery ();
                  QSqlQueryModel * model = new  QSqlQueryModel ();
                  q->prepare("SELECT * FROM budget order by sommer DESC");
                  q->exec();
                  model->setQuery(*q);
                  return model;
}
QSqlQueryModel * budget::chercher(QString r)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM budget WHERE numr like ('%"+r+"%') or dater like ('%"+r+"%') or sommer like ('%"+r+"%') ");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("numero"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("somme"));
     return model;
}
