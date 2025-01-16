#include "arme.h"
#include<QMessageBox>
#include<QPainter>
#include<QPdfWriter>
#include<QSystemTrayIcon>

arme::arme()
{
nm1="";
ty1="";
num1="";

}
arme::arme(QString n,QString ty,QString nu11)
{
    nm1=n;
   ty1=ty;
    num1=nu11;


}
/*void arme::setnom1(QString nm1){nom1=nm1;}
void arme::settype1(QString ty1){type1=ty1;}
void arme::setnumero1(QString num1){numero1=num1;}

QString arme::get_nom1(){return nm1;}
QString arme::get_type1(){return ty1;}
QString arme::get_numero1(){return num1;}*/


bool arme::ajouter()
{
QSqlQuery query;
    //QString num= QString::number(num);
    query.prepare("INSERT INTO arme (nm1,ty1,num1) "
                        "VALUES (:nm1, :ty1, :num1)");
    query.bindValue(":nm1",nm1);
    query.bindValue(":ty1",ty1);
    query.bindValue(":num1",num1);


    return    query.exec();

}

QSqlQueryModel * arme::afficher()
{

    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from arme");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("nm1"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("ty1 "));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("num1 "));

        return model;
}

bool arme::supprimer(QString num1)
{
    QSqlQuery query;
    query.prepare("Delete from arme where num1 = :num1 ");
    query.bindValue(":num1",num1);
    return    query.exec();

}

bool arme::modifier(QString num1)
{

    QSqlQuery query;
    query.prepare("UPDATE arme SET num1 where num1= :num1 ");
    query.bindValue(":num1",num1);






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



