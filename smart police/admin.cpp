#include "admin.h"
#include<QMessageBox>
#include<QPainter>
#include<QPdfWriter>
#include<QSystemTrayIcon>


admin::admin()
{
cin="";
prenom="";
nom="";
adresse="";
}

admin::admin(QString c,QString pr,QString n,QString adr)
{
    cin=c;
    prenom=pr;
    nom=n;
    adresse=adr;

}
void admin::setcin(QString c){cin=c;}
void admin::setprenom(QString pr){prenom=pr;}
void admin::setnom(QString n){nom=n;}
void admin::setadresse(QString adr){adresse=adr;}

QString admin::get_cin(){return cin;}
QString admin::get_prenom(){return prenom;}
QString admin::get_nom(){return nom;}
QString admin::get_adresse(){return adresse;}


 bool admin::ajouter()
 {
 QSqlQuery query;
     //QString cin= QString::number(cin);
     query.prepare("INSERT INTO detenu (cin,prenom,nom,adresse) "
                         "VALUES (:cin, :prenom, :nom , :adresse)");
     query.bindValue(":cin",cin);
     query.bindValue(":prenom",prenom);
     query.bindValue(":nom",nom);
     query.bindValue(":adresse",adresse);



     return    query.exec();

 }

QSqlQueryModel *admin ::afficher()
{

     QSqlQueryModel * model= new QSqlQueryModel();

     model->setQuery("select * from detenu");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("prenom "));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("nom "));
     model->setHeaderData(3, Qt::Horizontal, QObject::tr("adresse "));


         return model;
 }

 bool admin::supprimer(QString cin)
 {
     QSqlQuery query;
     query.prepare("Delete from detenu where cin = :cin ");
     query.bindValue(":cin",cin);
     return    query.exec();

 }

 bool admin::modifier(QString cin)
 {

     QSqlQuery query;
     query.prepare("UPDATE detenu SET cin= :cin, prenom= :prenom, nom= :nom where cin= :cin ");
     query.bindValue(":cin",cin);
     query.bindValue(":prenom",prenom);
     query.bindValue(":nom",nom);
     query.bindValue(":adresse",adresse);




           return query.exec();
 }


 QSqlQueryModel *admin::trier() //ml A-Z lieu // m sghir lel kbir
 {
     QSqlQuery * q = new  QSqlQuery ();
            QSqlQueryModel * model = new  QSqlQueryModel ();
            q->prepare("SELECT * FROM detenu order by prenom ASC");
            q->exec();
            model->setQuery(*q);
            return model;

 }
 QSqlQueryModel *admin::trierdec() //ml Z-A
 {

            QSqlQuery * q = new  QSqlQuery ();
                   QSqlQueryModel * model = new  QSqlQueryModel ();
                   q->prepare("SELECT * FROM detenu order by prenom DESC");
                   q->exec();
                   model->setQuery(*q);
                   return model;
 }


 /*void  admin::genererPDF(){
 //QDateTime datecreation = date.currentDateTime();
               //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
                      QPdfWriter pdf("C:/documents/amir/pdf.pdf");
                      QPainter painter(&pdf);
                     int i = 4000;
                          painter.setPen(Qt::red);
                          painter.setFont(QFont("Arial", 30));
                          painter.drawText(1100,1200,"Liste Des detenu");
                          painter.setPen(Qt::black);
                          painter.setFont(QFont("Arial", 15));
                         // painter.drawText(1100,2000,afficheDC);
                          painter.drawRect(100,100,7300,2600);
                          //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));//
                          painter.drawRect(0,3000,9600,500);
                          painter.setFont(QFont("Arial", 9));
                          painter.drawText(200,3300,"cin");
                          painter.drawText(1300,3300,"prenom");
                          painter.drawText(2100,3300,"nom");
                          painter.drawText(3100,3300,"adresse");


                          QSqlQuery query;
                          query.prepare("select * from detenu");
                          query.exec();
                          while (query.next())
                          {
                              painter.drawText(200,i,query.value(0).toString());
                              painter.drawText(1300,i,query.value(1).toString());
                              painter.drawText(2200,i,query.value(2).toString());
                              painter.drawText(3200,i,query.value(3).toString());

                             i = i + 500;
                          }*/


      /* int reponse = QMessageBox::Yes;
           if (reponse == QMessageBox::Yes)
           {
               QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
               notifyIcon->show();
               notifyIcon->setIcon(QIcon("icone.png"));

               notifyIcon->showMessage("GESTION DES  admin ","Liste detenu pret dans PDF",QSystemTrayIcon::Information,15000);

               painter.end();
           }
           if (reponse == QMessageBox::No)
           {
                painter.end();
           }
 }*/


