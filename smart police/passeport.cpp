#include "passeport.h"

passeport::passeport()
{
    idp="";
    cinp="";
    nomp="";
    prenomp="";
    datep="";
    adressep="";
    metierp="";
}
passeport::passeport(QString ip,QString cp,QString np,QString pp,QString dp,QString ap,QString mp)
{

    idp=ip;
    cinp=cp;
    nomp=np;
    prenomp=pp;
    datep=dp;
    adressep=ap;
    metierp=mp;
}
bool passeport::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO passeportdoc (idp,cinp,nomp,prenomp,datep,adressep,metierp)"
                  "VALUES( :idp,:cinp, :nomp, :prenomp, :datep, :adressep, :metierp)");
    query.bindValue(":idp",idp);
    query.bindValue(":cinp",cinp);
    query.bindValue(":nomp",nomp);
    query.bindValue(":prenomp",prenomp);
    query.bindValue(":datep",datep);
    query.bindValue(":adressep",adressep);
    query.bindValue(":metierp",metierp);
    return query.exec();
}
QSqlQueryModel *passeport::afficher(){

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from passeportdoc");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("id passeport"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("cin"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(6,Qt::Horizontal, QObject::tr("metier"));
    return model;
}
bool passeport::supprimer(QString idp){

    QSqlQuery query;
    query.prepare("delete from passeportdoc where idp = :idp");
    query.bindValue(":idp",idp);
    return query.exec();
}
bool passeport::modifier(QString idp){
    QSqlQuery query;
    query.prepare("update passeportdoc set cinp= :cinp  nomp= :nomp ,prenomp= :prenomp ,adressep= :adressep ,metierp= :metierp where idp = :idp");
    query.bindValue(":idp",idp);
    query.bindValue(":cinp",cinp);
    query.bindValue(":nomp",nomp);
    query.bindValue(":prenomp",prenomp);
    query.bindValue(":datep",datep);
    query.bindValue(":adressep",adressep);
    query.bindValue(":metierp",metierp);
    return query.exec();


}
QSqlQueryModel *passeport::recherche(QString idp)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from passeportdoc where idp LIKE '"+idp+"%' or nomp LIKE '"+idp+"%'or prenomp LIKE '"+idp+"%' or adressep LIKE '"+idp+"%'");


     model->setHeaderData(0,Qt::Horizontal, QObject::tr("idp"));
     model->setHeaderData(1,Qt::Horizontal, QObject::tr("nomp"));
     model->setHeaderData(2,Qt::Horizontal, QObject::tr("prenomp"));
     model->setHeaderData(3,Qt::Horizontal, QObject::tr("adressep"));

 return model;
}

QSqlQueryModel *passeport::trier() //ml A-Z lieu // m sghir lel kbir
{
    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM passeportdoc order by nomp ASC");
           q->exec();
           model->setQuery(*q);
           return model;

}
QSqlQueryModel *passeport::trierdec() //ml Z-A
{

           QSqlQuery * q = new  QSqlQuery ();
                  QSqlQueryModel * model = new  QSqlQueryModel ();
                  q->prepare("SELECT * FROM passeportdoc order by nomp DESC");
                  q->exec();
                  model->setQuery(*q);
                  return model;
}
