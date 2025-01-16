#include "ajoutercin.h"

ajoutercin::ajoutercin()
{
idc="";
nomc="";
prenomc="";
datec="";
lieuc="";
adressec="";
metierc="";
sexe="";
}
ajoutercin::ajoutercin(QString i,QString n,QString p,QString d,QString l,QString m,QString a ,QString s)
{
idc=i;
nomc=n;
prenomc=p;
datec=d;
lieuc=l;
metierc=m;
adressec=a;
sexe=s;
}
bool ajoutercin::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO documentcin (idc,nomc,prenomc,datec,lieuc,adressec,metierc,sexe)"
                  "VALUES(:idc, :nomc, :prenomc, :datec, :lieuc, :adressec, :metierc, :sexe)");
    query.bindValue(":idc",idc);
    query.bindValue(":nomc",nomc);
    query.bindValue(":prenomc",prenomc);
    query.bindValue(":datec",datec);
    query.bindValue(":lieuc",lieuc);
    query.bindValue(":adressec",adressec);
    query.bindValue(":metierc",metierc);
    query.bindValue(":sexe",sexe);


    return query.exec();
}
QSqlQueryModel *ajoutercin::afficher(){

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from documentcin");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("lieu naissance"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(6,Qt::Horizontal, QObject::tr("metier"));
    model->setHeaderData(7,Qt::Horizontal, QObject::tr("sexe"));

    return model;
}
bool ajoutercin::supprimer(QString idc){

    QSqlQuery query;
    query.prepare("delete from documentcin where idc = :idc");
    query.bindValue(":idc",idc);
    return query.exec();
}
bool ajoutercin::modifier(QString idc){
    QSqlQuery query;
    query.prepare("update documentcin set  nomc= :nomc ,prenomc= :prenomc ,adressec= :adressec ,lieuc= :lieuc ,metierc= :metierc where idc = :idc");
    query.bindValue(":idc",idc);
    query.bindValue(":nomc",nomc);
    query.bindValue(":prenomc",prenomc);
    query.bindValue(":datec",datec);
    query.bindValue(":lieuc",lieuc);
    query.bindValue(":adressec",adressec);
    query.bindValue(":metierc",metierc);
    return query.exec();


}
QSqlQueryModel *ajoutercin::recherche(QString idc)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from documentcin where idc LIKE '"+idc+"%' or nomc LIKE '"+idc+"%' or adressec LIKE '"+idc+"%'");


     model->setHeaderData(0,Qt::Horizontal, QObject::tr("idc"));
     model->setHeaderData(1,Qt::Horizontal, QObject::tr("nomc"));
     model->setHeaderData(2,Qt::Horizontal, QObject::tr("adresse"));

 return model;
}
QSqlQueryModel *ajoutercin::trier() //ml A-Z lieu // m sghir lel kbir
{
    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM documentcin order by nomc ASC");
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
QSqlQueryModel *ajoutercin::trierdec() //ml Z-A
{
    /*QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM documentcin order by nomc ASC");
           q->exec();
           model->setQuery(*q);
           return model;*/
     //ml kbir l sghir
           QSqlQuery * q = new  QSqlQuery ();
                  QSqlQueryModel * model = new  QSqlQueryModel ();
                  q->prepare("SELECT * FROM documentcin order by nomc DESC");
                  q->exec();
                  model->setQuery(*q);
                  return model;
}
