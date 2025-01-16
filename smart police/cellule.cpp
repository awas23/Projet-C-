#include "cellule.h"
#include<QMessageBox>
#include<QPainter>
#include<QPdfWriter>
#include<QSystemTrayIcon>

cellule::cellule()
{
num="";
dateen="";
dateso="";
dispo="";
}
cellule::cellule(QString n,QString en,QString so,QString dis)
{
    num=n;
   dateen=en;
    dateso=so;
    dispo=dis;

}
void cellule::setnum(QString n){num=n;}
void cellule::setdateen(QString en){dateen=en;}
void cellule::setdateso(QString so){dateso=so;}
void cellule::setdispo(QString dis){dispo=dis;}

QString cellule::get_num(){return num;}
QString cellule::get_dateen(){return dateen;}
QString cellule::get_dateso(){return dateso;}
QString cellule::get_dispo(){return dispo;}

bool cellule::ajouter()
{
QSqlQuery query;
    //QString num= QString::number(num);
    query.prepare("INSERT INTO cellule (num,dateen,dateso,dispo) "
                        "VALUES (:num, :dateen, :dateso , :dispo)");
    query.bindValue(":num",num);
    query.bindValue(":dateen",dateen);
    query.bindValue(":dateso",dateso);
    query.bindValue(":dispo",dispo);



    return    query.exec();

}

QSqlQueryModel * cellule::afficher()
{

    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from cellule");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("num"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("dateen "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("dateso "));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("dispo "));


        return model;
}

bool cellule::supprimer(QString num)
{
    QSqlQuery query;
    query.prepare("Delete from cellule where num = :num ");
    query.bindValue(":num",num);
    return    query.exec();

}

bool cellule::modifier(QString num)
{

    QSqlQuery query;
    query.prepare("UPDATE cellule SET dateentree= :dateentree, datesortie= :datesortie where num= :num ");
    query.bindValue(":num",num);
    query.bindValue(":dateen",dateen);
    query.bindValue(":dateso",dateso);
    query.bindValue(":dispo",dispo);





          return query.exec();
}

/*void  cellule::genererPDF(){
//QDateTime datecreation = date.currentDateTime();
              //QString afficheDC = "Date de Creation PDF : " + datecreation.toString() ;
                     QPdfWriter pdf("C:/documents/amir/pgd.pdf");
                     QPainter painter(&pdf);
                    int i = 4000;
                         painter.setPen(Qt::red);
                         painter.setFont(QFont("Arial", 30));
                         painter.drawText(1100,1200,"Liste Des cellules");
                         painter.setPen(Qt::black);
                         painter.setFont(QFont("Arial", 15));
                        // painter.drawText(1100,2000,afficheDC);
                         painter.drawRect(100,100,7300,2600);
                         //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/RH/Desktop/projecpp/image/logopdf.png"));//
                         painter.drawRect(0,3000,9600,500);
                         painter.setFont(QFont("Arial", 9));
                         painter.drawText(200,3300,"num");
                         painter.drawText(1300,3300,"dateen");
                         painter.drawText(2100,3300,"dateso");
                         painter.drawText(2100,3300,"dispo");


                         QSqlQuery query;
                         query.prepare("select * from cellule");
                         query.exec();
                         while (query.next())
                         {
                             painter.drawText(200,i,query.value(0).toString());
                             painter.drawText(1300,i,query.value(1).toString());
                             painter.drawText(2200,i,query.value(2).toString());
                             painter.drawText(3200,i,query.value(3).toString());

                            i = i + 500;
                         }


      int reponse = QMessageBox::Yes;
          if (reponse == QMessageBox::Yes)
          {
              QSystemTrayIcon *notifyIcon = new QSystemTrayIcon;
              notifyIcon->show();
              notifyIcon->setIcon(QIcon("icone1.png"));

              notifyIcon->showMessage("GESTION DES  cellules ","Liste cellule pret dans PDF",QSystemTrayIcon::Information,15000);

              painter.end();
          }
          if (reponse == QMessageBox::No)
          {
               painter.end();
          }
}*/



