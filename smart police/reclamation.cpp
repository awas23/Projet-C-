#include "reclamation.h"

reclamation::reclamation()
{
cin="";
nomr="";
prenomr="";
adresser="";
telr="";
datere="";
recl="";
}
reclamation::reclamation(QString c,QString nmr,QString prn,QString adr,QString tel,QString dtr,QString rec)
{
    cin=c;
    nomr=nmr;
    prenomr=prn;
    adresser=adr;
    telr=tel;
    datere=dtr;
    recl=rec;
}
bool reclamation::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO reclamation (cin,nomr,prenomr,adresser,telr,dater,recl)"
                  "VALUES(:cin, :nomr, :prenomr, :adresser, :telr, :dater, :recl)");
    query.bindValue(":cin",cin);
    query.bindValue(":nomr",nomr);
    query.bindValue(":prenomr",prenomr);
    query.bindValue(":adresser",adresser);
    query.bindValue(":telr",telr);
    query.bindValue(":dater",datere);
    query.bindValue(":recl",recl);

    return query.exec();
}
QSqlQueryModel *reclamation::afficher(){

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from reclamation");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("telephone"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("date reclamation"));
    model->setHeaderData(6,Qt::Horizontal, QObject::tr("reclamation"));

    return model;
}
bool reclamation::supprimer(QString cin){

    QSqlQuery query;
    query.prepare("delete from reclamation where cin = :cin");
    query.bindValue(":cin",cin);
    return query.exec();
}
bool reclamation::modifier(QString cin){
    QSqlQuery query;
    query.prepare("update reclamation set  nomr= :nomr ,prenomr= :prenomr ,adresser= :adresser ,telr= :telr ,recl= :recl where cin = :cin");
    query.bindValue(":cin",cin);
    query.bindValue(":nomr",nomr);
    query.bindValue(":prenomr",prenomr);
    query.bindValue(":adresser",adresser);
    query.bindValue(":telr",telr);
    query.bindValue(":recl",recl);
    return query.exec();


}
QSqlQueryModel *reclamation::recherche(QString cin)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from reclamation where cin LIKE '"+cin+"%' or nomr LIKE '"+cin+"%'or prenomr LIKE '"+cin+"%' or adresser LIKE '"+cin+"%'");


     model->setHeaderData(0,Qt::Horizontal, QObject::tr("cin"));
     model->setHeaderData(1,Qt::Horizontal, QObject::tr("nomr"));
     model->setHeaderData(2,Qt::Horizontal, QObject::tr("prenomr"));
     model->setHeaderData(3,Qt::Horizontal, QObject::tr("adresser"));

 return model;
}

QSqlQueryModel *reclamation::trier() //ml A-Z lieu // m sghir lel kbir
{
    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM reclamation order by nomr ASC");
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
QSqlQueryModel *reclamation::trierdec() //ml Z-A
{
    /*QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM certificat order by nomr ASC");
           q->exec();
           model->setQuery(*q);
           return model;*/
     //ml kbir l sghir
           QSqlQuery * q = new  QSqlQuery ();
                  QSqlQueryModel * model = new  QSqlQueryModel ();
                  q->prepare("SELECT * FROM reclamation order by nomr DESC");
                  q->exec();
                  model->setQuery(*q);
                  return model;
}
