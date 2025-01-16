#include "vehicule.h"
#include<QMessageBox>
#include<QPainter>
#include<QPdfWriter>
#include<QSystemTrayIcon>


vehicule::vehicule()
{
nom="";
type="";
num="";

}


vehicule::vehicule(QString n,QString ty,QString nu)
{
    nom=n;
    type=ty;
    num=nu;

}

/*void vehicule::setnom(QString n){nom=n;}
void vehicule::settype(QString ty){type=ty;}
void vehicule::setnum(QString nu){num=nu;}


QString vehicule::get_nom(){return nom;}
QString vehicule::get_type(){return type;}
QString vehicule::get_num(){return num ;} */



 bool vehicule::ajouter()
 {
 QSqlQuery query;

     query.prepare("INSERT INTO VEHICULE (NOM,TYPE,NUM,) VALUES (:nom, :type, :num )");
     query.bindValue(":nom",nom);
     query.bindValue(":type",type);
     query.bindValue(":num",num);


     return    query.exec();
     /*QSqlQuery query;
     query.prepare("INSERT INTO mission (id,numero,type,description) VALUES (:id,:numero,:type,:description)  ");
     query.bindValue(":id",id);
     query.bindValue(":numero",numero);
     query.bindValue(":type",type);
     query.bindValue(":description",description);
     return query.exec();*/

 }

QSqlQueryModel *vehicule ::afficher()
{

     QSqlQueryModel * model= new QSqlQueryModel();

     model->setQuery("select * from vehicule");
     model->setHeaderData(0, Qt::Horizontal, QObject::tr("nom"));
     model->setHeaderData(1, Qt::Horizontal, QObject::tr("type "));
     model->setHeaderData(2, Qt::Horizontal, QObject::tr("num "));



         return model;
 }

 bool vehicule::supprimer(QString num)
 {
     QSqlQuery query;
     query.prepare("Delete from vehicule where num = :num ");
     query.bindValue(":num",num);
     return    query.exec();

 }

 bool vehicule::modifier(QString num)
 {

     QSqlQuery query;
     query.prepare("UPDATE vehicule SET nom= :nom, type= :type, num= :num where num= :num ");
     query.bindValue(":nom",nom);
     query.bindValue(":type",type);
     query.bindValue(":num",num);





           return query.exec();
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


