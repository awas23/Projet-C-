#include "agent.h"

Agent::Agent()
{
    Cin=0;
    Date="";
    Nom="";
    Prenom="";
}
Agent::Agent(int Cin, QString Date, QString Nom, QString Prenom)
{
    this->Cin=Cin;
    this->Date=Date;
    this->Nom=Nom;
    this->Prenom=Prenom;
}
bool Agent::Ajouter()
{
    QSqlQuery querry;
    QString res=QString::number(Cin);
    querry.prepare("INSERT INTO AGENT (CIN, NOM, PRENOM, DATE_DE_NAISSANCE) "
                   "VALUES (:Cin, :Nom, :Prenom, TO_DATE(:Date,'dd/mm/yyyy'))");
    querry.bindValue(":Cin",res);
    querry.bindValue(":Nom",Nom);
    querry.bindValue(":Prenom",Prenom);
    querry.bindValue(":Date",Date);

    return querry.exec();
}
QSqlQueryModel* Agent::afficher()
{
    QSqlQueryModel*model= new QSqlQueryModel();

    model->setQuery("select * from AGENT");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Date"));
      return model;
}
QSqlQueryModel * Agent::trier_Cin()
{
    // trier cin
    QSqlQueryModel * model=new QSqlQueryModel() ;
    model->setQuery("select * from AGENT order by Cin ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Date"));

        return model;
}

QSqlQueryModel * Agent::trier_Nom()
{
    // trier nom
    QSqlQueryModel * model=new QSqlQueryModel() ;
    model->setQuery("select * from AGENT order by Nom ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Date"));

        return model;
}

QSqlQueryModel * Agent::trier_Permon()
{
    // trier prenom
    QSqlQueryModel * model=new QSqlQueryModel() ;
    model->setQuery("select * from AGENT order by Prenom ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Date"));

        return model;
}

QSqlQueryModel * Agent::rechercher(QString chaine)
{
    QSqlQueryModel * model=new QSqlQueryModel() ;
    model->setQuery("select * from AGENT where Cin LIKE'%"+chaine+"%' OR NOM LIKE'%"+chaine+"%' OR PRENOM LIKE'%"+chaine+"%' ;");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Cin"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Prenom"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Date"));

        return model;

}
bool Agent::Modifier(int Cin_rechercher)
{

    QSqlQuery query,qry;
    QString res= QString::number(Cin_rechercher);
    bool Testquery=false;


    qry.prepare("select * from AGENT where Cin=?;");
    qry.addBindValue(Cin_rechercher);
    bool exist=false;
    if(qry.exec())
        if(qry.next())
        {
            QVariant ch=qry.value(0);
            QString verif =QVariant(ch).toString();
            if(verif==res)
            exist=true;
        }

        if(exist)
        {
            if(Nom!="")
            {
                query.prepare("UPDATE AGENT SET NOM=? WHERE Cin='"+res+"';");
                query.addBindValue(Nom);query.exec();Testquery=true;
            }
            if(Prenom!="")
            {
                query.prepare("UPDATE AGENT SET PRENOM=? WHERE Cin='"+res+"';");
                query.addBindValue(Prenom);query.exec();Testquery=true;
            }
            if(Date!="")
            {
                query.prepare("UPDATE AGENT SET DATE_DE_NAISSANCE=TO_DATE(:Date,'dd/mm/yyyy') WHERE Cin='"+res+"';");
                query.addBindValue(Date);query.exec();Testquery=true;
            }


        }

    return  Testquery;
}

bool Agent::Supprimer(int Cin)
{
QSqlQuery query;
query.prepare("Delete from Agent where CIN=:Cin");
query.bindValue(":Cin", Cin);
return    query.exec();
}
