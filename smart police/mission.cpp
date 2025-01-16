#include "mission.h"

Mission::Mission()
{

}


bool Mission::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO mission (id,numero,type,description) VALUES (:id,:numero,:type,:description)  ");
    query.bindValue(":id",id);
    query.bindValue(":numero",numero);
    query.bindValue(":type",type);
    query.bindValue(":description",description);
    return query.exec();
}


QSqlQueryModel * Mission::afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from mission");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Description"));


    return model;
}

QSqlQueryModel * Mission::trier()
{
    QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from mission order by numero asc");

model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Description"));


    return model;
}
QSqlQueryModel *Mission::trier_down() {
    QSqlQuery query;
    QSqlQueryModel *model = new QSqlQueryModel();


      query.prepare(" SELECT * FROM mission ORDER BY numero desc; ");
      query.exec();
      model->setQuery(query);


      model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
      model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Description"));
    return model;
  }


bool Mission::supprimer(QString sup)
{
    QSqlQuery query;
    query.prepare("DELETE FROM mission WHERE id = :id");
    query.bindValue(":id", sup);
    return    query.exec();
}

QSqlQueryModel * Mission::chercher(QString rech)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from mission where upper(numero) like upper('%"+rech+"%') or upper(type) like upper('%"+rech+"%') or upper(description) like upper('%"+rech+"%') ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Numero"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Description"));


        return model;
}


void Mission::getMission(QString id)
{
    QSqlQuery query;
    if(query.exec("select id,numero,type,description from mission where id ='"+id+"'"))
    {
        while(query.next())
        {
            this->setId(query.value(0).toInt());
            this->setNumero(query.value(1).toInt());
            this->setType(query.value(2).toString());
            this->setDescription(query.value(3).toString());
        }
    }
}


Mission::Mission(int id, int numero, QString type,QString description)
{
    this->id=id;
    this->numero=numero;
    this->type=type;
    this->description=description;
}


int Mission::getId() const
{
    return id;
}

void Mission::setId(int value)
{
    id = value;
}

int Mission::getNumero() const
{
    return numero;
}

void Mission::setNumero(int value)
{
    numero = value;
}

QString Mission::getType() const
{
    return type;
}

void Mission::setType(const QString &value)
{
    type = value;
}

QString Mission::getDescription() const
{
    return description;
}

void Mission::setDescription(const QString &value)
{
    description = value;
}



