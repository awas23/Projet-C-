#include "certificat.h"

certificat::certificat()
{
    idcer="";
    nomcer="";
    prenomcer="";
    nompere="";
    datesor="";
    adresseres="";
}
certificat::certificat(QString idc,QString ncr,QString pcr,QString npr,QString dsor,QString adres )
{
    idcer=idc;
    nomcer=ncr;
    prenomcer=pcr;
    nompere=npr;
    datesor=dsor;
    adresseres=adres;
}
bool certificat::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO certificat (idcer,nomcer,prenomcer,nompere,datesor,adresseres)"
                  "VALUES(:idcer, :nomcer, :prenomcer, :nompere, :datesor, :adresseres)");
    query.bindValue(":idcer",idcer);
    query.bindValue(":nomcer",nomcer);
    query.bindValue(":prenomcer",prenomcer);
    query.bindValue(":nompere",nompere);
    query.bindValue(":datesor",datesor);
    query.bindValue(":adresseres",adresseres);


    return query.exec();
}
QSqlQueryModel *certificat::afficher(){

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from certificat");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("id certif"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3,Qt::Horizontal, QObject::tr("nom de pere"));
    model->setHeaderData(4,Qt::Horizontal, QObject::tr("date sortie"));
    model->setHeaderData(5,Qt::Horizontal, QObject::tr("adresse res"));
    model->setHeaderData(6,Qt::Horizontal, QObject::tr("metier"));

    return model;
}
bool certificat::supprimer(QString idcer){

    QSqlQuery query;
    query.prepare("delete from certificat where idcer = :idcer");
    query.bindValue(":idcer",idcer);
    return query.exec();
}
bool certificat::modifier(QString idcer){
    QSqlQuery query;
    query.prepare("update certificat set  nomcer= :nomcer ,prenomcer= :prenomcer ,nomcpere= :nompere ,datesor= :datesor ,adresseres= :adresseres  where idcer = :idcer");
    query.bindValue(":idcer",idcer);
    query.bindValue(":nomcer",nomcer);
    query.bindValue(":prenomcer",prenomcer);
    query.bindValue(":nompere",nompere);
    query.bindValue(":datesor",datesor);
    query.bindValue(":adresseres",adresseres);
    return query.exec();


}
QSqlQueryModel *certificat::recherche(QString idcer)
 {
     QSqlQueryModel * model= new QSqlQueryModel();
     model->setQuery("select * from certificat where idcer LIKE '"+idcer+"%' or nomcer LIKE '"+idcer+"%'or prenomcer LIKE '"+idcer+"%' or adresseres LIKE '"+idcer+"%'");


     model->setHeaderData(0,Qt::Horizontal, QObject::tr("idcer"));
     model->setHeaderData(1,Qt::Horizontal, QObject::tr("nomcer"));
     model->setHeaderData(2,Qt::Horizontal, QObject::tr("prenomcer"));
     model->setHeaderData(3,Qt::Horizontal, QObject::tr("adresseres"));

 return model;
}

QSqlQueryModel *certificat::trier() //ml A-Z lieu // m sghir lel kbir
{
    QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM certificat order by nomcer ASC");
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
QSqlQueryModel *certificat::trierdec() //ml Z-A
{
    /*QSqlQuery * q = new  QSqlQuery ();
           QSqlQueryModel * model = new  QSqlQueryModel ();
           q->prepare("SELECT * FROM certificat order by nomc ASC");
           q->exec();
           model->setQuery(*q);
           return model;*/
     //ml kbir l sghir
           QSqlQuery * q = new  QSqlQuery ();
                  QSqlQueryModel * model = new  QSqlQueryModel ();
                  q->prepare("SELECT * FROM certificat order by nomcer DESC");
                  q->exec();
                  model->setQuery(*q);
                  return model;
}
