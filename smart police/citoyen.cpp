#include "citoyen.h"


Citoyen::Citoyen()
{

}

Citoyen::Citoyen(int id,int cin,QString nom, QString prenom,int age)
{
    this->id=id;
    this->cin=cin;
    this->nom=nom;
    this->prenom=prenom;
    this->age=age;
}

bool Citoyen::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO citoyen (id,cin,nom,prenom,age) VALUES (:id,:cin,:nom,:prenom,:age)  ");
    query.bindValue(":id",id);
    query.bindValue(":cin",cin);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":age",age);
    return query.exec();
}

QSqlQueryModel * Citoyen::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from citoyen");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cin"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Age"));
    return model;
}

QSqlQueryModel * Citoyen::trier()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from citoyen order by age asc");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cin"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Age"));

    return model;
}
QSqlQueryModel *Citoyen::trier_down() {
    QSqlQuery query;
    QSqlQueryModel *model = new QSqlQueryModel();


      query.prepare(" SELECT * FROM citoyen ORDER BY age desc");
      query.exec();
      model->setQuery(query);


      model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Description"));
    return model;
  }

bool Citoyen::supprimer(QString sup)
{
    QSqlQuery query;
    query.prepare("DELETE FROM citoyen WHERE id = :id");
    query.bindValue(":id", sup);
    return    query.exec();
}

QSqlQueryModel * Citoyen::chercher(QString rech)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from citoyen where upper(cin) like upper('%"+rech+"%') or upper(nom) like upper('%"+rech+"%') or upper(prenom) like upper('%"+rech+"%') or upper(age) like upper('%"+rech+"%') ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Age"));


        return model;
}

void Citoyen::getCitoyen(QString id)
{
    QSqlQuery query;
    if(query.exec("select id,cin,nom,prenom,age from citoyen where id ='"+id+"'"))
    {
        while(query.next())
        {
            this->setId(query.value(0).toInt());
            this->setCin(query.value(1).toInt());
            this->setNom(query.value(2).toString());
            this->setPrenom(query.value(3).toString());
            this->setAge(query.value(4).toInt());
        }
    }
}


int Citoyen::getId() const
{
    return id;
}

void Citoyen::setId(int value)
{
    id = value;
}

int Citoyen::getCin() const
{
    return cin;
}

void Citoyen::setCin(int value)
{
    cin = value;
}

QString Citoyen::getNom() const
{
    return nom;
}

void Citoyen::setNom(const QString &value)
{
    nom = value;
}

QString Citoyen::getPrenom() const
{
    return prenom;
}

void Citoyen::setPrenom(const QString &value)
{
    prenom = value;
}

int Citoyen::getAge() const
{
    return age;
}

void Citoyen::setAge(int value)
{
    age = value;
}


