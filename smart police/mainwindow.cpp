#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mission.h"
#include "citoyen.h"
#include "categories.h"
#include "arduino.h"
#include "admin.h"
#include "agent.h"
#include "reclamation.h"
#include "budget.h"
#include "notification.h"
#include "QDebug"
#include <QVector>
#include <QPrintDialog>
#include <QtPrintSupport/QPrinter>
#include <QTextDocument>
#include <QPainter>
#include <QIntValidator>
#include <QPixmap>
#include <QDateTime>
#include "src/SmtpMime"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer=new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(myfunction()));
    timer->start(1000);

    QPixmap pix("C:/Users/awasylla/Desktop/ppp");
    QPixmap pixe("C:/Users/awasylla/Desktop/BACKKKK.jpg");
     QPixmap pixee("C:/Users/awasylla/Desktop/838.jpg");
     ui->incendie->setPixmap(pixee.scaled(1100,15000,Qt::KeepAspectRatio));
    ui->label_pic->setPixmap(pix.scaled(1100,15000,Qt::KeepAspectRatio));
     ui->label_4->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
      ui->label_6->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
      ui->label_8->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
       ui->label_9->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
       ui->label_10->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
       ui->label_11->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
       ui->label_7->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
        ui->label_pic2->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
         ui->label_pic3->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
          ui->label_pic4->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
           ui->label_pic6->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
            ui->label_pic7->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
             ui->label_pic8->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
             ui->label_186->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
             ui->label_187->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
             ui->label_188->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
             ui->label_189->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
              //ui->label_pic9->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
               ui->label_pic10->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
                ui->label_pic11->setPixmap(pixe.scaled(1100,15000,Qt::KeepAspectRatio));
       player = new QMediaPlayer(this);
       QString fileName="C:/Users/awasylla/Pictures/ProjetFINAL/PoliceStation/resc/Welcome.mp3";
       player->setMedia(QUrl::fromLocalFile(fileName));
       player->setVolume(10);
       player->play();
    Mission mission;
    ui->liste_missions->setModel(mission.afficher());
    ui->numero_input_ajout->setValidator( new QIntValidator(0, 10000000, this) );
    ui->numero_input_modif->setValidator( new QIntValidator(0, 10000000, this) );

    ui->age_input_ajout->setValidator(new QIntValidator(0, 100, this));


    notifyicon=new QSystemTrayIcon(this);
    notifyicon->setIcon(QIcon(":/img/img/Notification.jpg"));
    notifyicon->setVisible(true);
    ui->StackedMission->setCurrentIndex(0);
    //controle de saisie
    QRegExp rx("(|\"|/|\\.,|[A-Z,a-z]){30}");
    ui->line1->setValidator(new QRegExpValidator(rx,this));
    ui->prenomcin->setValidator(new QRegExpValidator(rx, this));
    ui->adressecin->setValidator(new QRegExpValidator(rx, this));
    ui->metiercin->setValidator(new QRegExpValidator(rx, this));

    //placeholder
    ui->line1->setPlaceholderText("Nom");
    ui->prenomcin->setPlaceholderText("Prenom");
    ui->adressecin->setPlaceholderText("Adresse");
    ui->metiercin->setPlaceholderText("Metier");
    ui->idcin->setPlaceholderText("ID");
    ui->lieuc->setPlaceholderText("lieu");
    ui->rech->setPlaceholderText("Recherche");
    ui->deletecer->setPlaceholderText("id a supprimer");
    ui->cinp->setPlaceholderText("cin");
    ui->idp->setPlaceholderText("numero pass");
    ui->nomp->setPlaceholderText("Nom");
    ui->prenomp->setPlaceholderText("prenom");
    ui->metierp->setPlaceholderText("metier");
    ui->adressep->setPlaceholderText("adresse");


    //clear line edit
    ui->line1->setClearButtonEnabled(true);
    ui->prenomcin->setClearButtonEnabled(true);
    ui->adressecin->setClearButtonEnabled(true);
    ui->metiercin->setClearButtonEnabled(true);
    ui->idcin->setClearButtonEnabled(true);
    ui->rech->setClearButtonEnabled(true);
    ui->deletecer->setClearButtonEnabled(true);
    ui->lieuc->setClearButtonEnabled(true);


  //*******arduino1
     int ret1 = A.connect_arduino(); // lancer la connexion à arduino
     switch (ret1) {
     case (0):
       qDebug() << "arduino is available and connected to : "
                << A.getarduino_port_name();
       break;
     case (1):
       qDebug() << "arduino is available but not connected to :"
                << A.getarduino_port_name();
       break;
     case (-1):
       qDebug() << "arduino is not available";
     }
     QObject::connect(A.getserial(), SIGNAL(readyRead()), this,
                      SLOT(update_label1())); // permet de lancer
     // le slot update_label suite à la reception du signal readyRead (reception
     // des données).
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btn_mission_clicked()
{
    Mission mission;
    ui->liste_missions->setModel(mission.afficher());
    ui->StackedMission->setCurrentIndex(3);
}

void MainWindow::on_btn_citoyen_clicked()
{
    Citoyen citoyen;
    ui->liste_citoyens->setModel(citoyen.afficher());
    ui->StackedMission->setCurrentIndex(4);
}

void MainWindow::on_btn_confirmer_ajout_clicked()
{
    QSqlQuery query;
    QVector <int> tab;
    int i;
        int id=-1;
        if(query.exec("select id from mission"))
            {
                while (query.next())
                {
                    tab.push_back(query.value(0).toInt());

                }

            }

            qSort(tab.begin(),tab.end());
            if(tab.size()==0)
            {
                id=1;
            }
            else if(tab[0]!=1)
            { id=1;}
            else if(tab.size()==1)
            {
                id=2;
            }

            else
            {for(i=1;i<tab.size();i++)
            {

                if (tab[i]-tab[i-1]>1)
                {
                    id=tab[i-1]+1;
                    break;
                }
            }
            }
            if (id==-1)
            {
                id=tab.size()+1;
            }
    if(ui->numero_input_ajout->text()=="" || ui->type_input_ajout->text()=="" || ui->descriptio_input_ajout->text()==""  )
    {
        qDebug()<<"Champs vide !!";
        QMessageBox::critical(nullptr, QObject::tr("Ajouter une mission"),
                                   QObject::tr("Veillez remplir tous les champs.\n"
                                               "Click Close to exit."), QMessageBox::Close);
    }
    else
    {
        Mission mission(id,ui->numero_input_ajout->text().toInt(),ui->type_input_ajout->text(),ui->descriptio_input_ajout->text());
        qDebug()<<id;
        if(mission.ajouter())
            {
            ui->numero_input_ajout->setText("");
            ui->type_input_ajout->setText("");
            ui->descriptio_input_ajout->setText("");
            ui->liste_missions->setModel(mission.afficher());
            QMessageBox::information(nullptr, QObject::tr("Ajouter une mission"),
                               QObject::tr("Ajout avec succès !.\n"
                                           "Click Close to exit."), QMessageBox::Close);
            notifyicon->show();
            notifyicon->showMessage("Success","Ajout avec succes",QSystemTrayIcon::Critical,2000);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Ajouter une mission"),
                                   QObject::tr("Erreur!.\n"
                                               "Click Close to exit."), QMessageBox::Close);
            }
    }


}

void MainWindow::on_pushButton_clicked()
{
   reclamation r;
    ui->tableView_3->setModel(r.afficher());
    ui->StackedMission->setCurrentIndex(5);
}

void MainWindow::on_chercherMission_textChanged(const QString &arg1)
{
    Mission mission;
    ui->liste_missions->setModel(mission.chercher(ui->chercherMission->text()));

}

void MainWindow::on_supprimerMission_clicked()
{
    QString val=ui->liste_missions->model()->data(ui->liste_missions->model()->index(ui->liste_missions->selectionModel()->currentIndex().row(),0)).toString();
    qDebug()<<val;
    Mission mission;
    mission.supprimer(val);
    ui->liste_missions->setModel(mission.afficher());

}

void MainWindow::on_modifierMission_clicked()
{
    Mission mission;
    QString val=ui->liste_missions->model()->data(ui->liste_missions->model()->index(ui->liste_missions->selectionModel()->currentIndex().row(),0)).toString();
    mission.getMission(val);
    ui->id_input_modif->setText(QString::number(mission.getId()));
    ui->numero_input_modif->setText(QString::number(mission.getNumero()));
    ui->type_input_modif->setText(mission.getType());
    ui->description_input_modif->setText(mission.getDescription());
    ui->MissionTab->setCurrentIndex(2);

}
void MainWindow::on_btn_confirmer_modif_clicked()
{
    int x=0;
        if(ui->numero_input_modif->text()=="")
        {
            ui->label_numero_modif->setText("Ce champ ne peut pas être vide !");
            ui->label_numero_modif->setStyleSheet("QLabel {color : red; }");
            x=1;
        }
        if(ui->type_input_modif->text()=="")
        {
            ui->label_type_modif->setText("Ce champ ne peut pas être vide !");
            ui->label_type_modif->setStyleSheet("QLabel {color : red; }");
            x=1;
        }
        if(ui->description_input_modif->text()=="")
        {
            ui->label_description_modif->setText("Ce champ ne peut pas être vide !");
            ui->label_description_modif->setStyleSheet("QLabel {color : red; }");
            x=1;
        }
    if(x==0)
    {
        Mission mission(ui->id_input_modif->text().toInt(),ui->numero_input_modif->text().toInt(),ui->type_input_modif->text(),ui->description_input_modif->text());
        mission.supprimer(ui->id_input_modif->text());
        if(mission.ajouter())
        {
            ui->id_input_modif->setText("");
            ui->numero_input_modif->setText("");
            ui->type_input_modif->setText("");
            ui->description_input_modif->setText("");

            ui->label_numero_modif->setText("");
            ui->label_type_modif->setText("");
            ui->label_description_modif->setText("");

            ui->liste_missions->setModel(mission.afficher());

            QMessageBox::information(nullptr, QObject::tr("Modifier une mission"),
                                   QObject::tr("Modification avec succès !.\n"
                                               "Click Close to exit."), QMessageBox::Close);

        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("Ajouter un abonnement"),
                                       QObject::tr("Erreur !.\n"
                                                   "Click Close to exit."), QMessageBox::Close);
        }
    }

}



void MainWindow::on_trierMission_clicked()
{
    Mission mission;
   // ui->liste_missions->setModel(mission.trier());
    QSqlQueryModel * model =new QSqlQueryModel();

  if(ui->radioButton->isChecked())
  model = mission.trier();

 else if(ui->radioButton_2->isChecked())
    model=mission.trier_down();

  else
      model=mission.afficher();

   ui->liste_missions->setModel(model);
}

void MainWindow::on_imprimerMission_clicked()
{
    QString strStream;
    QTextStream out(&strStream);
    const int rowCount = ui->liste_missions->model()->rowCount();
    const int columnCount =ui->liste_missions->model()->columnCount();
    out <<  "<html>\n"
                            "<head>\n"
                            "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                            <<  QString("<title>%1</title>\n").arg("mission")
                            <<  "</head>\n"
                            "<body bgcolor=#CFC4E1 link=#5000A0>\n"
                                "<img src=':/new/prefix1/icon/logo.webp' width='100' height='100'>\n"
                                "<h1>Liste des missions</h1>"



                                "<table border=1 cellspacing=0 cellpadding=2>\n";


                    // headers
                        out << "<thead><tr bgcolor=#f0f0f0>";
                        for (int column = 0; column < columnCount; column++)
                            if (!ui->liste_missions->isColumnHidden(column))
                                out << QString("<th>%1</th>").arg(ui->liste_missions->model()->headerData(column, Qt::Horizontal).toString());
                        out << "</tr></thead>\n";
                        // data table
                           for (int row = 0; row < rowCount; row++) {
                               out << "<tr>";
                               for (int column = 0; column < columnCount; column++) {
                                   if (!ui->liste_missions->isColumnHidden(column)) {
                                       QString data = ui->liste_missions->model()->data(ui->liste_missions->model()->index(row, column)).toString().simplified();
                                       out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                                   }
                               }
                               out << "</tr>\n";
                           }
                           out <<  "</table>\n"
                               "</body>\n"
                               "</html>\n";

                           QTextDocument *document = new QTextDocument();
                           document->setHtml(strStream);

                           QPrinter printer;

                           QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                           if (dialog->exec() == QDialog::Accepted) {
                               document->print(&printer);}
}

void MainWindow::on_confirmer_ajout_citoyen_clicked()
{
    QSqlQuery query;
    QVector <int> tab;
    int i;
        int id=-1;
        if(query.exec("select id from citoyen"))
            {
                while (query.next())
                {
                    tab.push_back(query.value(0).toInt());

                }

            }

            qSort(tab.begin(),tab.end());
            if(tab.size()==0)
            {
                id=1;
            }
            else if(tab[0]!=1)
            { id=1;}
            else if(tab.size()==1)
            {
                id=2;
            }

            else
            {for(i=1;i<tab.size();i++)
            {

                if (tab[i]-tab[i-1]>1)
                {
                    id=tab[i-1]+1;
                    break;
                }
            }
            }
            if (id==-1)
            {
                id=tab.size()+1;
            }
    if(ui->cin_input_ajout->text()=="" || ui->nom_input_ajout->text()=="" || ui->prenom_input_ajout->text()=="" || ui->age_input_ajout->text()==""  )
    {
        qDebug()<<"Champs vide !!";
        QMessageBox::critical(nullptr, QObject::tr("Ajouter un citoyen"),
                                   QObject::tr("Veillez remplir tous les champs.\n"
                                               "Click Close to exit."), QMessageBox::Close);
    }
    else
    {
        Citoyen citoyen(id,ui->cin_input_ajout->text().toInt(),ui->nom_input_ajout->text(),ui->prenom_input_ajout->text(),ui->age_input_ajout->text().toInt());
        qDebug()<<id;
        if(citoyen.ajouter())
            {
            ui->cin_input_ajout->setText("");
            ui->nom_input_ajout->setText("");
            ui->prenom_input_ajout->setText("");
            ui->age_input_ajout->setText("");
            ui->liste_citoyens->setModel(citoyen.afficher());
            QMessageBox::information(nullptr, QObject::tr("Ajouter un citoyen"),
                               QObject::tr("Ajout avec succès !.\n"
                                           "Click Close to exit."), QMessageBox::Close);
            notifyicon->show();
            notifyicon->showMessage("Success","Ajout avec succes",QSystemTrayIcon::Critical,2000);
            }
            else
            {
                QMessageBox::critical(nullptr, QObject::tr("Ajouter un citoyen"),
                                   QObject::tr("Erreur!.\n"
                                               "Click Close to exit."), QMessageBox::Close);
            }
    }


}

void MainWindow::on_supprimer_citoyen_clicked()
{
    QString val=ui->liste_citoyens->model()->data(ui->liste_citoyens->model()->index(ui->liste_citoyens->selectionModel()->currentIndex().row(),0)).toString();
    qDebug()<<val;
    Citoyen citoyen;
    citoyen.supprimer(val);
    ui->liste_citoyens->setModel(citoyen.afficher());
}

void MainWindow::on_chercher_citoyen_textChanged(const QString &arg1)
{
    Citoyen citoyen;
    ui->liste_citoyens->setModel(citoyen.chercher(ui->chercher_citoyen->text()));
}

void MainWindow::on_trier_citoyens_clicked()
{
    Citoyen citoyen;
   // ui->liste_missions->setModel(c.trier());
    QSqlQueryModel * model =new QSqlQueryModel();

  if(ui->radioButton_3->isChecked())
  model = citoyen.trier();

 else if(ui->radioButton_4->isChecked())
    model=citoyen.trier_down();

  else
      model=citoyen.afficher();

   ui->liste_citoyens->setModel(model);
}

/*void MainWindow::on_chercher_citoyen_cursorPositionChanged(int arg1, int arg2)
{

}*/



void MainWindow::on_pb_send_clicked()
{
    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);

    smtp.setUser("awaseynilaye.sylla@esprit.tn");
    smtp.setPassword("770474156Sylla");

    MimeMessage message;

    EmailAddress sender("awaseynilaye.sylla@esprit.tn", "Police Station");
    message.setSender(&sender);

    EmailAddress to(ui->le_to->text(), "  to ");
    message.addRecipient(&to);

    message.setSubject( ui->le_object->text());

    MimeText text;
    text.setText(ui->te_message->toPlainText());

    message.addPart(&text);

        if (!smtp.connectToHost()) {
            qDebug() << "Failed to connect to host!" << endl;
        }

        if (!smtp.login()) {
            qDebug() << "Failed to login!" << endl;
        }

        if (!smtp.sendMail(message)) {
            qDebug() << "Failed to send mail!" << endl;
        }

    smtp.quit();

}

void MainWindow::on_modifier_citoyen_clicked()
{
    Citoyen citoyen;
    QString val=ui->liste_citoyens->model()->data(ui->liste_citoyens->model()->index(ui->liste_citoyens->selectionModel()->currentIndex().row(),0)).toString();
    citoyen.getCitoyen(val);
    ui->id_citoyen_modif->setText(QString::number(citoyen.getId()));
    ui->cin_input_modif->setText(QString::number(citoyen.getCin()));
    ui->nom_input_modif->setText(citoyen.getNom());
    ui->prenom_input_modif->setText(citoyen.getPrenom());
    ui->age_input_modif->setText(QString::number(citoyen.getAge()));
    ui->CitoyenTab->setCurrentIndex(2);

}

void MainWindow::on_confirmer_modif_citoyen_clicked()
{
    Citoyen citoyen(ui->id_citoyen_modif->text().toInt(),ui->cin_input_modif->text().toInt(),ui->nom_input_modif->text(),ui->prenom_input_modif->text(),ui->age_input_modif->text().toInt());
    citoyen.supprimer(ui->id_citoyen_modif->text());
    citoyen.ajouter();
   ui->liste_citoyens->setModel(citoyen.afficher());
}
void MainWindow::update_label1()  {
    data=A.read_from_arduino();
    if (data =="4")
      ui->label_13->setText("ATTENTION INCENDIE!!");
    else if  (data =="5")
      ui->label_13->setText("PAS D'INCENDIE");

}

void MainWindow::on_pushButton_7_clicked()
{
    {
        QString cin=ui->cin->text();
        QString nomr=ui->nomr->text();
        QString prenomr=ui->prenomr->text();
        QString adresser=ui->adresser->text();
        QString telr=ui->telr->text();
        QString datere=ui->datere->text();
        QString recl=ui->plainTextEdit->toPlainText();


        reclamation f(cin,nomr,prenomr,adresser,telr,datere,recl);
        bool test=f.ajouter();
        if(test)
        {
            ui->tableView_3->setModel(tempreclamation.afficher());
            QMessageBox::information(nullptr,QObject::tr("Ajout"),
                                     QObject::tr("Ajout avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);

      }
        else
        {

           QMessageBox::critical(nullptr,QObject::tr("Ajout"),
                                     QObject::tr("Ajout echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
        }
    }
}


void MainWindow::on_pushButton_8_clicked()
{
    QString cin=ui->cin->text();
    QString nomr=ui->nomr->text();
    QString prenomr=ui->prenomr->text();
    QString adresser=ui->adresser->text();
    QString telr=ui->telr->text();
    QString datere=ui->datere->text();
    QString recl=ui->plainTextEdit->toPlainText();

    reclamation f(cin,nomr,prenomr,adresser,telr,datere,recl);
bool test=f.modifier(cin);
    if(test)
    {
        ui->tableView_3->setModel(tempreclamation.afficher());
        QMessageBox::information(nullptr,QObject::tr("modifier"),
                                 QObject::tr("modifier avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);

}
}

void MainWindow::on_pushButton_25_clicked()
{
    QString cin =ui->rech_4->text();
       ui->tableView_3->setModel(tempreclamation.recherche(cin));
}

void MainWindow::on_pushButton_26_clicked()
{
    QPdfWriter pdf("D:/qtproject/documents et services/pdfreclamation.pdf");
                      QPainter painter(&pdf);
                     int i = 4000;
                          painter.setPen(Qt::darkGray);
                          painter.setFont(QFont("Roboto", 25));
                          painter.drawText(950,1100,"Liste Des Reclamations");
                          painter.setPen(Qt::black);
                          painter.setFont(QFont("Arial", 15));
                         // painter.drawText(1100,2000,afficheDC);
                          painter.drawRect(100,100,7300,2600);
                          //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("logo.png"));
                          painter.drawRect(0,3000,9600,500);
                          painter.setFont(QFont("Arial", 9));
                          painter.drawText(200,3300,"cin");
                          painter.drawText(1200,3300,"nomr");
                          painter.drawText(2600,3300,"prenomr");
                          painter.drawText(4000,3300,"adresser");
                          painter.drawText(5400,3300,"telr");
                          painter.drawText(7000,3300,"recl");

                          QSqlQuery query;
                          query.prepare("select * from reclamation");
                          query.exec();
                          while (query.next())
                          {
                              painter.drawText(200,i,query.value(0).toString());
                              painter.drawText(1300,i,query.value(1).toString());
                              painter.drawText(2600,i,query.value(2).toString());
                              painter.drawText(3900,i,query.value(3).toString());
                              painter.drawText(5500,i,query.value(4).toString());
                              painter.drawText(6900,i,query.value(5).toString());





                             i = i + 500;
                          }
}

void MainWindow::on_pushButton_32_clicked()
{
    QPrinter rd;
       QPrintDialog d(&rd,this);
       d.setWindowTitle("imprimer reclamation");
       //d.addEnableOption(QAbstractPrintDialog::PrinSelection);
       d.addEnabledOption(QAbstractPrintDialog::PrintSelection);
       if(d.exec()!=QDialog::Accepted)
           return;
}



void MainWindow::on_pushButton_9_clicked()
{
    QString cin=ui->deleterec->text();
    bool test=tempreclamation.supprimer(cin);
    if(test){

        ui->tableView_3->setModel(tempreclamation.afficher());
        QMessageBox::information(nullptr,QObject::tr("suppression"),
                                 QObject::tr("suppression avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("suppression"),
                                 QObject::tr("suppression echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_27_clicked()
{
     ui->tableView_3->setModel(tempreclamation.trier());
}

void MainWindow::on_pushButton_28_clicked()
{
    ui->tableView_3->setModel(tempreclamation.trierdec());
}

void MainWindow::on_pushButton_21_clicked()
{
    {
        QString idcer=ui->idcer->text();
        QString nomcer=ui->nomcit->text();
        QString prenomcer=ui->prencit->text();
        QString nompere=ui->prenp->text();
        QString datesor=ui->datesort->text();
        QString adresseres=ui->adrres->text();


        certificat f(idcer,nomcer,prenomcer,nompere,datesor,adresseres);
        bool test=f.ajouter();
        if(test)
        {
            ui->tableView_4->setModel(tempcertif.afficher());
            QMessageBox::information(nullptr,QObject::tr("Ajout"),
                                     QObject::tr("Ajout avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);

      }
        else
        {

           QMessageBox::critical(nullptr,QObject::tr("Ajout"),
                                     QObject::tr("Ajout echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QString idc=ui->idcin->text();
    QString nomc=ui->line1->text();
    QString prenomc=ui->prenomcin->text();
    QString datec=ui->datecin->text();
    QString lieuc=ui->lieuc->text();
    QString adressec=ui->adressecin->text();
    QString metierc=ui->metiercin->text();
    QString sexe=ui->comboBox->currentText();
    ajoutercin f(idc,nomc,prenomc,datec,lieuc,adressec,metierc,sexe);
bool test=f.modifier(idc);
    if(test)
    {
        ui->tableView->setModel(hajoutercin.afficher());
        QMessageBox::information(nullptr,QObject::tr("modifier"),
                                 QObject::tr("modifier avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);



  }
    else
        QMessageBox::critical(nullptr,QObject::tr("modifier"),
                                 QObject::tr("modifier echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_2_clicked()
{
    notification n;
    {
        QString idc=ui->idcin->text();
        QString nomc=ui->line1->text();
        QString prenomc=ui->prenomcin->text();
        QString datec=ui->datecin->text();
        QString lieuc=ui->lieuc->text();
        QString adressec=ui->adressecin->text();
        QString metierc=ui->metiercin->text();
        QString sexe=ui->comboBox->currentText();

        ajoutercin f(idc,nomc,prenomc,datec,lieuc,adressec,metierc,sexe);
        bool test=f.ajouter();
        if(test)
        {
            n.setPopupText("cin a été ajouté");
                    n.show();
            ui->tableView->setModel(hajoutercin.afficher());
            QMessageBox::information(nullptr,QObject::tr("Ajout"),
                                     QObject::tr("Ajout avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);

      }
        else
        {

           QMessageBox::critical(nullptr,QObject::tr("Ajout"),
                                     QObject::tr("Ajout echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
        }
    }
}

void MainWindow::on_pushButton_11_clicked()
{
    QString idp =ui->rech_2->text();
       ui->tableView_2->setModel(temppassport.recherche(idp));
}

void MainWindow::on_pushButton_35_clicked()
{
    QPdfWriter pdf("D:/qtproject/documents et services/pdfdocumentcin.pdf");
                      QPainter painter(&pdf);
                     int i = 4000;
                          painter.setPen(Qt::darkGray);
                          painter.setFont(QFont("Roboto", 25));
                          painter.drawText(950,1100,"Liste Des carte identité");
                          painter.setPen(Qt::black);
                          painter.setFont(QFont("Arial", 15));
                         // painter.drawText(1100,2000,afficheDC);
                          painter.drawRect(100,100,7300,2600);
                          //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/Helmi/Documents/Gestion_achats/logo.png"));
                          painter.drawRect(0,3000,9600,500);
                          painter.setFont(QFont("Arial", 9));
                          painter.drawText(200,3300,"idc");
                          painter.drawText(1200,3300,"nomc");
                          painter.drawText(2600,3300,"prenomc");
                          painter.drawText(4000,3300,"datec");
                          painter.drawText(5400,3300,"adressec");
                          painter.drawText(7000,3300,"metierc");
                          painter.drawText(8400,3300,"sexe");

                          QSqlQuery query;
                          query.prepare("select * from documentcin");
                          query.exec();
                          while (query.next())
                          {
                              painter.drawText(200,i,query.value(0).toString());
                              painter.drawText(1300,i,query.value(1).toString());
                              painter.drawText(2600,i,query.value(2).toString());
                              painter.drawText(3900,i,query.value(3).toString());
                              painter.drawText(5500,i,query.value(4).toString());
                              painter.drawText(6900,i,query.value(5).toString());
                              painter.drawText(8300,i,query.value(6).toString());





                             i = i + 500;
                          }
}

void MainWindow::on_pushButton_36_clicked()
{
    QPrinter rd;
       QPrintDialog d(&rd,this);
       d.setWindowTitle("imprimer cin");
       d.addEnabledOption(QAbstractPrintDialog::PrintSelection);
       if(d.exec()!=QDialog::Accepted)
           return;
}

void MainWindow::on_pushButton_10_clicked()
{
    QString idc=ui->lineEdit_2->text();
    bool test=hajoutercin.supprimer(idc);
    if(test){

        ui->tableView->setModel(hajoutercin.afficher());
        QMessageBox::information(nullptr,QObject::tr("suppression"),
                                 QObject::tr("suppression avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("suppression"),
                                 QObject::tr("suppression echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_37_clicked()
{
     ui->tableView->setModel(hajoutercin.trier());
}

void MainWindow::on_pushButton_38_clicked()
{
      ui->tableView->setModel(hajoutercin.trierdec());
}

void MainWindow::on_pushButton_4_clicked()
{
    {
        QString idp=ui->idp->text();
        QString cinp=ui->cinp->text();
        QString nomp=ui->nomp->text();
        QString prenomp=ui->prenomp->text();
        QString datep=ui->datep->text();
        QString adressep=ui->adressep->text();
        QString metierp=ui->metierp->text();

        passeport f(idp,cinp,nomp,prenomp,datep,adressep,metierp);
        bool test=f.ajouter();
        if(test)
        {
            ui->tableView_2->setModel(temppassport.afficher());
            QMessageBox::information(nullptr,QObject::tr("Ajout"),
                                     QObject::tr("Ajout avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);

      }
        else
        {

           QMessageBox::critical(nullptr,QObject::tr("Ajout"),
                                     QObject::tr("Ajout echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
        }
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    QString idp=ui->idp->text();
    QString cinp=ui->cinp->text();
    QString nomp=ui->nomp->text();
    QString prenomp=ui->prenomp->text();
    QString datep=ui->datep->text();
    QString adressep=ui->adressep->text();
    QString metierp=ui->metierp->text();

    passeport f(idp,cinp,nomp,prenomp,datep,adressep,metierp);
bool test=f.modifier(idp);
    if(test)
    {
        ui->tableView_2->setModel(temppassport.afficher());
        QMessageBox::information(nullptr,QObject::tr("modifier"),
                                 QObject::tr("modifier avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);



  }
    else
        QMessageBox::critical(nullptr,QObject::tr("modifier"),
                                 QObject::tr("modifier echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_18_clicked()
{
    QString idp=ui->iddelete->text();
    bool test=temppassport.supprimer(idp);
    if(test){

        ui->tableView_2->setModel(temppassport.afficher());
        QMessageBox::information(nullptr,QObject::tr("suppression"),
                                 QObject::tr("suppression avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("suppression"),
                                 QObject::tr("suppression echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_15_clicked()
{
    QString idp =ui->rech_2->text();
       ui->tableView_2->setModel(temppassport.recherche(idp));
}

/*void MainWindow::on_pushButton_16_clicked()
{
    QPdfWriter pdf("C:/Users/awasylla/3D Objects/ProjetFINAL/MOMO/pdfpasseport.pdf");
                      QPainter painter(&pdf);
                     int i = 4000;
                          painter.setPen(Qt::darkGray);
                          painter.setFont(QFont("Roboto", 25));
                          painter.drawText(950,1100,"Liste Des Passeports");
                          painter.setPen(Qt::black);
                          painter.setFont(QFont("Arial", 15));
                         // painter.drawText(1100,2000,afficheDC);
                          painter.drawRect(100,100,7300,2600);
                          //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/Helmi/Documents/Gestion_achats/logo.png"));
                          painter.drawRect(0,3000,9600,500);
                          painter.setFont(QFont("Arial", 9));
                          painter.drawText(200,3300,"idp");
                          painter.drawText(1200,3300,"cinp");
                          painter.drawText(2600,3300,"nomp");
                          painter.drawText(4000,3300,"prenomp");
                          painter.drawText(5400,3300,"datep");
                          painter.drawText(7000,3300,"adressep");
                          painter.drawText(8400,3300,"metierp");

                          QSqlQuery query;
                          query.prepare("select * from passeportdoc");
                          query.exec();
                          while (query.next())
                          {
                              painter.drawText(200,i,query.value(0).toString());
                              painter.drawText(1300,i,query.value(1).toString());
                              painter.drawText(2600,i,query.value(2).toString());
                              painter.drawText(3900,i,query.value(3).toString());
                              painter.drawText(5500,i,query.value(4).toString());
                              painter.drawText(6900,i,query.value(5).toString());
                              painter.drawText(8300,i,query.value(6).toString());





                             i = i + 500;
                          }*/


/*void MainWindow::on_pushButton_17_clicked()
{
    QPrinter rd;
       QPrintDialog d(&rd,this);
       d.setWindowTitle("imprimer passeport");
       //d.addEnableOption(QAbstractPrintDialog::PrinSelection);
       d.addEnabledOption(QAbstractPrintDialog::PrintSelection);
       if(d.exec()!=QDialog::Accepted)
           return;
}*/

void MainWindow::on_pushButton_19_clicked()
{
    ui->tableView_2->setModel(temppassport.trier());

}

void MainWindow::on_pushButton_20_clicked()
{
     ui->tableView_2->setModel(temppassport.trierdec());
}

void MainWindow::on_pushButton_22_clicked()
{
    QString idcer=ui->idcer->text();
    QString nomcer=ui->nomcit->text();
    QString prenomcer=ui->prencit->text();
    QString nompere=ui->prenp->text();
    QString datesor=ui->datesort->text();
    QString adresseres=ui->adrres->text();

    certificat f(idcer,nomcer,prenomcer,nompere,datesor,adresseres);
bool test=f.modifier(idcer);
    if(test)
    {
        ui->tableView_4->setModel(tempcertif.afficher());
        QMessageBox::information(nullptr,QObject::tr("modifier"),
                                 QObject::tr("modifier avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);

}
}

void MainWindow::on_pushButton_23_clicked()
{

    QString idcer =ui->rech_3->text();
       ui->tableView_4->setModel(tempcertif.recherche(idcer));
}

void MainWindow::on_pushButton_24_clicked()
{

    QPdfWriter pdf("C:/Users/awasylla/3D Objects/ProjetFINAL/MOMO/pdfcertificats.pdf");
                      QPainter painter(&pdf);
                     int i = 4000;
                          painter.setPen(Qt::darkGray);
                          painter.setFont(QFont("Roboto", 25));
                          painter.drawText(950,1100,"Liste Des Certificats De Residence");
                          painter.setPen(Qt::black);
                          painter.setFont(QFont("Arial", 15));
                         // painter.drawText(1100,2000,afficheDC);
                          painter.drawRect(100,100,7300,2600);
                          //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/Helmi/Documents/Gestion_achats/logo.png"));
                          painter.drawRect(0,3000,9600,500);
                          painter.setFont(QFont("Arial", 9));
                          painter.drawText(200,3300,"idcer");
                          painter.drawText(1200,3300,"nomcer");
                          painter.drawText(2600,3300,"prenomcer");
                          painter.drawText(4000,3300,"nompere");
                          painter.drawText(5400,3300,"datesor");
                          painter.drawText(7000,3300,"adresseres");

                          QSqlQuery query;
                          query.prepare("select * from certificat");
                          query.exec();
                          while (query.next())
                          {
                              painter.drawText(200,i,query.value(0).toString());
                              painter.drawText(1300,i,query.value(1).toString());
                              painter.drawText(2600,i,query.value(2).toString());
                              painter.drawText(3900,i,query.value(3).toString());
                              painter.drawText(5500,i,query.value(4).toString());
                              painter.drawText(6900,i,query.value(5).toString());





                             i = i + 500;
                          }
}

void MainWindow::on_pushButton_29_clicked()
{

    QPrinter rd;
       QPrintDialog d(&rd,this);
       d.setWindowTitle("imprimer certificat");
       //d.addEnableOption(QAbstractPrintDialog::PrinSelection);
       d.addEnabledOption(QAbstractPrintDialog::PrintSelection);
       if(d.exec()!=QDialog::Accepted)
           return;
}

void MainWindow::on_pushButton_30_clicked()
{
    QString idcer=ui->deletecer->text();
    bool test=tempcertif.supprimer(idcer);
    if(test){

        ui->tableView_4->setModel(tempcertif.afficher());
        QMessageBox::information(nullptr,QObject::tr("suppression"),
                                 QObject::tr("suppression avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("suppression"),
                                 QObject::tr("suppression echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_31_clicked()
{
     ui->tableView_4->setModel(tempcertif.trier());
}

void MainWindow::on_pushButton_33_clicked()
{
     ui->tableView_4->setModel(tempcertif.trierdec());
}

void MainWindow::on_tableView_4_activated(const QModelIndex &index)
{
    QString idcer=ui->tableView_4->model()->data(index).toString();
              QSqlQuery query;
              query.prepare("select * from certificat where idcer LIKE '"+idcer+"%' or nomcer LIKE '"+idcer+"%' or prenomcer LIKE '"+idcer+"%' or nompere LIKE '"+idcer+"%' or datesor LIKE '"+idcer+"%' or adresseres LIKE '"+idcer+"%'");
              if(query.exec())
              {
                while(query.next())
                {
                    ui->idcer->setText(query.value(0).toString());
                    ui->nomcit->setText(query.value(1).toString());
                    ui->prencit->setText(query.value(2).toString());
                     //ui->datecin->setDate(query.value(3).toString());
                     ui->prenp->setText(query.value(4).toString());
                     ui->adrres->setText(query.value(5).toString());
                     //ui->datere->setText(query.value(5).toString());
                     //ui->plainTextEdit->toPlainText(query.value(6).toString());



                }
              }
                else
                {

                    //QMessageBox::critical(this,tr("error::"),query.lastError().text());
                  QMessageBox::critical(nullptr, QObject::tr("error"),
                              QObject::tr("error.\n""Click Cancel to exit."), QMessageBox::Cancel);
              }
}

void MainWindow::on_tableView_3_activated(const QModelIndex &index)
{
    QString cin=ui->tableView->model()->data(index).toString();
              QSqlQuery query;
              query.prepare("select * from reclamation where cin LIKE '"+cin+"%' or nomr LIKE '"+cin+"%' or prenomr LIKE '"+cin+"%' or adresser LIKE '"+cin+"%' or telr LIKE '"+cin+"%' or dater LIKE '"+cin+"%'or recl LIKE '"+cin+"%'");
              if(query.exec())
              {
                while(query.next())
                {
                    ui->cin->setText(query.value(0).toString());
                    ui->nomr->setText(query.value(1).toString());
                    ui->prenomr->setText(query.value(2).toString());
                     //ui->datecin->setDate(query.value(3).toString());
                     ui->adresser->setText(query.value(4).toString());
                     ui->telr->setText(query.value(5).toString());
                     //ui->datere->setText(query.value(5).toString());
                     //ui->plainTextEdit->toPlainText(query.value(6).toString());



                }
              }
                else
                {

                    //QMessageBox::critical(this,tr("error::"),query.lastError().text());
                  QMessageBox::critical(nullptr, QObject::tr("error"),
                              QObject::tr("error.\n""Click Cancel to exit."), QMessageBox::Cancel);
              }
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString idc=ui->tableView->model()->data(index).toString();
          QSqlQuery query;
          query.prepare("select * from documentcin where idc LIKE '"+idc+"%' or nomc LIKE '"+idc+"%' or prenomc LIKE '"+idc+"%' or datec LIKE '"+idc+"%' or lieuc LIKE '"+idc+"%' or adressec LIKE '"+idc+"%' or metierc LIKE '"+idc+"%'or sexe LIKE '"+idc+"%'");
          if(query.exec())
          {
            while(query.next())
            {
                ui->idcin->setText(query.value(0).toString());
                ui->line1->setText(query.value(1).toString());
                ui->prenomcin->setText(query.value(2).toString());
                 //ui->datecin->setDate(query.value(3).toString());
                ui->lieuc->setText(query.value(4).toString());
                 ui->adressecin->setText(query.value(5).toString());
                 ui->metiercin->setText(query.value(6).toString());

            }
          }
            else
            {

                //QMessageBox::critical(this,tr("error::"),query.lastError().text());
              QMessageBox::critical(nullptr, QObject::tr("error"),
                          QObject::tr("error.\n""Click Cancel to exit."), QMessageBox::Cancel);
          }
}

void MainWindow::on_tableView_2_activated(const QModelIndex &index)
{
    QString idp=ui->tableView_2->model()->data(index).toString();
          QSqlQuery query;
          query.prepare("select * from passeportdoc where idp LIKE '"+idp+"%' or cinp LIKE '"+idp+"%' or nomp LIKE '"+idp+"%' or prenomp LIKE '"+idp+"%' or datep LIKE '"+idp+"%' or adressep LIKE '"+idp+"%'or metierp LIKE '"+idp+"%'");
          if(query.exec())
          {
            while(query.next())
            {
                ui->idp->setText(query.value(0).toString());
                ui->cinp->setText(query.value(1).toString());
                ui->nomp->setText(query.value(2).toString());
                ui->prenomp->setText(query.value(3).toString());
                 //ui->datecin->setDate(query.value(3).toString());
                ui->adressep->setText(query.value(4).toString());
                ui->metierp->setText(query.value(5).toString());

            }
          }
            else
            {

                //QMessageBox::critical(this,tr("error::"),query.lastError().text());
              QMessageBox::critical(nullptr, QObject::tr("error"),
                          QObject::tr("error.\n""Click Cancel to exit."), QMessageBox::Cancel);
          }
}

void MainWindow::on_pushButton_6_clicked()
{
   admin a;
     ui->affiche->setModel(a.afficher());
     ui->StackedMission->setCurrentIndex(6);
}

void MainWindow::on_pushButton_12_clicked()
{
    admin a(ui->lineEdit_cin->text(),ui->lineEdit_prenom->text(),ui->lineEdit_nom->text(),ui->lineEdit_adresse->text());
       bool test= a.ajouter();




       if (test)
       {
           ui->affiche->setModel(temptadmin.afficher());//actualisation taa afficher
                   QMessageBox::information(nullptr,QObject::tr("ok"),
                                            QObject::tr("ajout succful .\n"),
                           QMessageBox::Cancel);
               }

               else
                   QMessageBox::critical(nullptr,QObject::tr("ajout not open"),
                                           QObject::tr("click cancel to exist"),
                                           QMessageBox::Cancel);



        ui->affiche->setModel(temptadmin.afficher());
}

void MainWindow::on_pushButton_39_clicked()
{
    QString cin=ui->lineEdit_cin->text();
        QString prenom=ui->lineEdit_prenom->text();
        QString nom=ui->lineEdit_nom->text();
        QString adresse=ui->lineEdit_adresse->text();

        admin f(cin,prenom,nom,adresse);
    bool test=f.modifier(cin );
        if(test)
        {
            ui->affiche->setModel(temptadmin.afficher());
            QMessageBox::information(nullptr,QObject::tr("modifier"),
                                     QObject::tr("modifier avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);

    }
}

void MainWindow::on_pushButton_40_clicked()
{
    QString cin=ui->lineEdit_3->text();
        bool test=temptadmin.supprimer(cin);
        if(test){

            ui->affiche->setModel(temptadmin.afficher());
            QMessageBox::information(nullptr,QObject::tr("suppression"),
                                     QObject::tr("suppression avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);
        }
        else {
            QMessageBox::critical(nullptr,QObject::tr("suppression"),
                                     QObject::tr("suppression echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
        }
}

void MainWindow::on_pushButton_13_clicked()
{
    ui->affiche->setModel(temptadmin.trier());
}

void MainWindow::on_pushButton_14_clicked()
{
     ui->affiche->setModel(temptadmin.trierdec());
}

void MainWindow::on_pushButton_34_clicked()
{
    QPdfWriter pdf("C:/Users/21629/Documents/amir/pdfdocumentcin.pdf");
                          QPainter painter(&pdf);
                         int i = 4000;
                              painter.setPen(Qt::blue);
                              painter.setFont(QFont("Arial", 25));
                              painter.drawText(950,1100,"Liste Des detenus");
                              painter.setPen(Qt::red);
                              painter.setFont(QFont("Arial", 15));
                             // painter.drawText(1100,2000,afficheDC);
                              painter.drawRect(100,100,7300,2600);
                              //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/Helmi/Documents/Gestion_achats/logo.png"));
                              painter.drawRect(0,3000,9600,500);
                              painter.setFont(QFont("Arial", 9));
                              painter.drawText(200,3300,"cin");
                              painter.drawText(1200,3300,"prenom");
                              painter.drawText(2600,3300,"nom");
                              painter.drawText(4000,3300,"adresse");

                              QSqlQuery query;
                              query.prepare("select * from detenu");
                              query.exec();
                              while (query.next())
                              {
                                  painter.drawText(200,i,query.value(0).toString());
                                  painter.drawText(1300,i,query.value(1).toString());
                                  painter.drawText(2600,i,query.value(2).toString());
                                  painter.drawText(3900,i,query.value(3).toString());





                                 i = i + 500;
                              }
}

void MainWindow::on_pushButton_41_clicked()
{
    cellule c;
      ui->affichec->setModel(c.afficher());
      ui->StackedMission->setCurrentIndex(8);
}

void MainWindow::on_pushButton_42_clicked()
{
   cellule c(ui->lineEdit_num->text(),ui->dateline1->text(),ui->dateline2->text(),ui->lineEdit_dis->text());
       bool test= c.ajouter();




       if (test)
       {
           ui->affichec->setModel(tempcellule.afficher());//actualisation taa afficher
                   QMessageBox::information(nullptr,QObject::tr("ok"),
                                            QObject::tr("ajout succful .\n"),
                           QMessageBox::Cancel);
               }

               else
                   QMessageBox::critical(nullptr,QObject::tr("ajout not open"),
                                           QObject::tr("click cancel to exist"),
                                           QMessageBox::Cancel);



        ui->affichec->setModel(tempcellule.afficher());
}

void MainWindow::on_pushButton_43_clicked()
{
   QPdfWriter pdf("C:/Users/21629/Documents/amir/pdg.pdf");
                          QPainter painter(&pdf);
                         int i = 4000;
                              painter.setPen(Qt::blue);
                              painter.setFont(QFont("Arial", 25));
                              painter.drawText(950,1100,"Liste Des cellules");
                              painter.setPen(Qt::red);
                              painter.setFont(QFont("Arial", 15));
                             // painter.drawText(1100,2000,afficheDC);
                              painter.drawRect(100,100,7300,2600);
                              //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/Helmi/Documents/Gestion_achats/logo.png"));
                              painter.drawRect(0,3000,9600,500);
                              painter.setFont(QFont("Arial", 9));
                              painter.drawText(200,3300,"num");
                              painter.drawText(1200,3300,"dateen");
                              painter.drawText(2600,3300,"datesp");
                              painter.drawText(4000,3300,"dispo");

                              QSqlQuery query;
                              query.prepare("select * from cellule");
                              query.exec();
                              while (query.next())
                              {
                                  painter.drawText(200,i,query.value(0).toString());
                                  painter.drawText(1300,i,query.value(1).toString());
                                  painter.drawText(2600,i,query.value(2).toString());
                                  painter.drawText(3900,i,query.value(3).toString());





                                 i = i + 500;
                              }
}

void MainWindow::on_pushButton_44_clicked()
{

    QString num=ui->lineEdit_num->text();
    QString dateen=ui->dateline1->text();
    QString dateso=ui->dateline2->text();
    QString dispo=ui->lineEdit_dis->text();

    cellule c(num,dateen,dateso,dispo);
bool test=c.modifier(num);
    if(test)
    {
        ui->affichec->setModel(tempcellule.afficher());
        QMessageBox::information(nullptr,QObject::tr("modifier"),
                                 QObject::tr("modifier avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);

}


}

void MainWindow::on_pushButton_45_clicked()
{
    QString num=ui->lineEdit_7->text();
        bool test=tempcellule.supprimer(num);
        if(test){

            ui->affichec->setModel(tempcellule.afficher());
            QMessageBox::information(nullptr,QObject::tr("suppression"),
                                     QObject::tr("suppression avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);
        }
        else {
            QMessageBox::critical(nullptr,QObject::tr("suppression"),
                                     QObject::tr("suppression echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
        }

}

void MainWindow::myfunction()
{
    QTime time=QTime::currentTime();
    QString time_text=time.toString("hh : mm : ss");
    ui->label_62->setText(time_text);
}

void MainWindow::on_pushButton_46_clicked()
{
    budget b;
      ui->tableView_5->setModel(b.afficher());
      ui->StackedMission->setCurrentIndex(1);
}

void MainWindow::on_pushButton_47_clicked()
{
    {
        QString numr=ui->lineEdit_4->text();
        QString dater=ui->dateEdit->text();
        QString sommer=ui->lineEdit_5->text();
        budget f(numr,dater,sommer);
        bool test=f.ajouter();
        if(test)
        {
            ui->tableView_5->setModel(tempbudget.afficher());
            QMessageBox::information(nullptr,QObject::tr("Ajout"),
                                     QObject::tr("Ajout avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);

      }
        else
        {

           QMessageBox::critical(nullptr,QObject::tr("Ajout"),
                                     QObject::tr("Ajout echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
        }
    }
}

void MainWindow::on_pushButton_48_clicked()
{
    QString numr=ui->lineEdit_4->text();
    QString dater=ui->dateEdit->text();
    QString sommer=ui->lineEdit_5->text();

budget f(numr,dater,sommer);
bool test=f.modifier(numr);
if(test)
{
ui->tableView_5->setModel(tempbudget.afficher());
QMessageBox::information(nullptr,QObject::tr("modifier"),
                         QObject::tr("modifier avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);



}
else
QMessageBox::critical(nullptr,QObject::tr("modifier"),
                         QObject::tr("modifier echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_51_clicked()
{
    QString numr=ui->lineEdit_9->text();
    bool test=tempbudget.supprimer(numr);
    if(test){

        ui->tableView_5->setModel(tempbudget.afficher());
        QMessageBox::information(nullptr,QObject::tr("suppression"),
                                 QObject::tr("suppression avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("suppression"),
                                 QObject::tr("suppression echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_49_clicked()
{
    ui->tableView_5->setModel(tempbudget.trier());
}

void MainWindow::on_pushButton_50_clicked()
{
    ui->tableView_5->setModel(tempbudget.trierdec());
}

void MainWindow::on_pushButton_52_clicked()
{
    Agent a;
      ui->tableView_agent->setModel(a.afficher());
      ui->StackedMission->setCurrentIndex(2);
}

void MainWindow::on_pushButton_53_clicked()
{
    {
        QString numm=ui->lineEdit_10->text();
        QString datem=ui->dateEdit_2->text();
        QString typem=ui->lineEdit_11->text();
        maintenance f(numm,datem,typem);
        bool test=f.ajouter();
        if(test)
        {
            ui->tableView_6->setModel(tempmaintenance.afficher());
            QMessageBox::information(nullptr,QObject::tr("Ajout"),
                                     QObject::tr("Ajout avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);

      }
        else
        {

           QMessageBox::critical(nullptr,QObject::tr("Ajout"),
                                     QObject::tr("Ajout echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
        }
    }
}

void MainWindow::on_pushButton_54_clicked()
{

    QString numm=ui->lineEdit_10->text();
    QString datem=ui->dateEdit_2->text();
    QString typem=ui->lineEdit_11->text();

maintenance f(numm,datem,typem);
bool test=f.modifier(numm);
if(test)
{
ui->tableView_6->setModel(tempmaintenance.afficher());
QMessageBox::information(nullptr,QObject::tr("modifier"),
                         QObject::tr("modifier avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);



}
else
QMessageBox::critical(nullptr,QObject::tr("modifier"),
                         QObject::tr("modifier echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_55_clicked()
{
    QString numm=ui->lineEdit_12->text();
    bool test=tempmaintenance.supprimer(numm);
    if(test){

        ui->tableView_6->setModel(tempmaintenance.afficher());
        QMessageBox::information(nullptr,QObject::tr("suppression"),
                                 QObject::tr("suppression avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
    else {
        QMessageBox::critical(nullptr,QObject::tr("suppression"),
                                 QObject::tr("suppression echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_pushButton_56_clicked()
{
    maintenance::printPDF(ui->tableView_6);
    QMessageBox::information(nullptr, QObject::tr("PDF Saved"),
                      QObject::tr("PDF file saved as maintenance.pdf"), QMessageBox::Ok);
}

void MainWindow::on_tableView_agent_doubleClicked(const QModelIndex &index)
{
    /*if(ui->tableView_agent->model()->data(index).toString()[0]>'0' && ui->tableView_agent->model()->data(index).toString()[0]<'9' )
    {
        ui->Cin_agent_2->setText(ui->tableView_agent->model()->data(index).toString());
        ui->Cin_agent_3->setText(ui->tableView_agent->model()->data(index).toString());
    }*/
}

void MainWindow::on_pushButton_57_clicked()
{
    ui->StackedMission->setCurrentIndex(0);
}

void MainWindow::on_pushButton_58_clicked()
{
     ui->StackedMission->setCurrentIndex(0);
}

void MainWindow::on_pushButton_59_clicked()
{
    ui->StackedMission->setCurrentIndex(0);
}

void MainWindow::on_pushButton_60_clicked()
{
    ui->StackedMission->setCurrentIndex(0);
}

void MainWindow::on_pushButton_61_clicked()
{
    ui->StackedMission->setCurrentIndex(0);
}

void MainWindow::on_pushButton_62_clicked()
{
    ui->StackedMission->setCurrentIndex(0);
}

void MainWindow::on_pushButton_63_clicked()
{
    ui->StackedMission->setCurrentIndex(0);
}

void MainWindow::on_pushButton_64_clicked()
{
    ui->StackedMission->setCurrentIndex(0);
}

void MainWindow::on_pushButton_65_clicked()
{
    SmtpClient smtp("smtp.gmail.com", 465, SmtpClient::SslConnection);
                      smtp.setUser("smartpoli015@gmail.com");
                      smtp.setPassword("blackopps3");
                      MimeMessage message;
                      message.setSender(new EmailAddress("smartpoli015@gmail.com", "smart police"));
                      QString emaiil =ui->lineEdit_14->text();
                      message.addRecipient(new EmailAddress(emaiil, ""));
                      message.setSubject("client informations");
                      MimeText text;
                      QString emaill = ui->plainTextEdit_2->toPlainText();
                      text.setText(emaill);
                      message.addPart(&text);
                      smtp.connectToHost();
                      smtp.login();
                      if(smtp.sendMail(message))
                      {
                          QMessageBox::information(this, "PAS D'ERREUR", "Envoyé");
                      }
                      else
                      {
                          QMessageBox::critical(this, "ERREUR", "Non Envoyé (probleme de connexion)");
                      }
                      smtp.quit();
}



void MainWindow::on_rechercher_agent_textChanged(const QString &arg1)
{
    ui->tableView_agent->setModel(A1.rechercher(arg1));
}

void MainWindow::on_TRIER_clicked()
{

}

void MainWindow::on_Trier_cin_2_clicked()
{
    ui->tableView_agent->setModel(A1.trier_Cin());
}

void MainWindow::on_Trier_nom_2_clicked()
{
    ui->tableView_agent->setModel(A1.trier_Nom());
}

void MainWindow::on_radioButton_7_clicked()
{
    ui->tableView_agent->setModel(A1.trier_Permon());
}

void MainWindow::on_TRIER_3_clicked()
{
    int Cin= ui->lineEdit_29->text().toInt();
    bool test=A1.Supprimer(Cin);
    if(test)
    {
        ui->tableView_agent->setModel(A1.afficher());
        QMessageBox::information(nullptr,QObject::tr("Agent supprime"),QObject::tr("Agent supprime avec succes.\n""Cliquez Cancel to exit."),QMessageBox::Cancel);

    }
}

void MainWindow::on_Ajouter_agent_clicked()
{
    int Cin=ui->Cin_agent->text().toInt();
    QString Nom=ui->Nom_agent->text();
    QString Prenom=ui->Prenom_agent->text();
    QString Date=ui->dateEdit_agent->text();
if ((Cin!=NULL)&&(Nom!=NULL)&&(Prenom!=""))
{
    Agent A(Cin,Date,Nom,Prenom);

    bool test=A.Ajouter();
    if(test)
    {
        ui->tableView_agent->setModel(A.afficher());
        QMessageBox::information(nullptr,QObject::tr("Ajouter un Agent"),QObject::tr("Agent ajouter avec succes.\n""Cliquez Cancel to exit."),QMessageBox::Ok);
        ui->Cin_agent->clear();ui->Nom_agent->clear();ui->Prenom_agent->clear();
    }
    else
        QMessageBox::information(nullptr,QObject::tr("Ajouter un Agent"),QObject::tr("Agent non ajouter.\n""Cliquez Cancel to exit."),QMessageBox::Cancel);
}
}

void MainWindow::on_TRIER_2_clicked()
{

    int Cin=ui->lineEdit_30->text().toInt();
    QString Nom=ui->lineEdit_31->text();
    QString Prenom=ui->lineEdit_32->text();
    QString Date=ui->dateEdit_5->text();

     Agent A(Cin,Date,Nom,Prenom);
     bool test=A.Modifier(Cin);
     if(test)
     {
          ui->tableView_agent->setModel(A.afficher());
         QMessageBox::information(nullptr,QObject::tr("Modifier un Agent"),QObject::tr("Agent Modifier avec succes.\n""Cliquez Cancel to exit."),QMessageBox::Cancel);

     }
     else
         QMessageBox::information(nullptr,QObject::tr("Modifier un Agent"),QObject::tr("Agent non Modifier.\n""Cliquez Cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_pushButton_134_clicked()
{
    arme a;
      ui->tableView_14->setModel(a.afficher());
      ui->StackedMission->setCurrentIndex(7);
}

void MainWindow::on_lineEdit_33_textChanged(const QString &arg1)
{
    ui->tableView_13->setModel(C.rechercher(arg1));
}

void MainWindow::on_pushButton_131_clicked()
{
    int Id= ui->lineEdit_34->text().toInt();
    bool test=C.Supprimer(Id);
    if(test)
    {
         ui->tableView_13->setModel(C.afficher());
        QMessageBox::information(nullptr,QObject::tr("Categories supprime"),QObject::tr("Categories supprime avec succes.\n""Cliquez Cancel to exit."),QMessageBox::Cancel);
    }
}

void MainWindow::on_radioButton_11_clicked()
{
    ui->tableView_13->setModel(C.trier_ID());
}

void MainWindow::on_radioButton_12_clicked()
{
  ui->tableView_13->setModel(C.trier_Poste());
}

void MainWindow::on_radioButton_13_clicked()
{
    ui->tableView_13->setModel(C.trier_Grade());
}

void MainWindow::on_pushButton_132_clicked()
{
    int Id=ui->lineEdit_35->text().toInt();
    int Note=ui->lineEdit_38->text().toInt();
     QString Poste=ui->comboBox_5->currentText();
     QString Grade=ui->comboBox_6->currentText();

     Categories C(Id,Poste,Grade,Note);
     bool test=C.Modifier(Id);
     if(test)
     {
          ui->tableView_13->setModel(C.afficher());
         QMessageBox::information(nullptr,QObject::tr("Modifier une Categories"),QObject::tr("Categories Modifier avec succes.\n""Cliquez Cancel to exit."),QMessageBox::Cancel);
     }
     else
         QMessageBox::information(nullptr,QObject::tr("Modifier une Categories"),QObject::tr("Categories non Modifier.\n""Cliquez Cancel to exit."),QMessageBox::Cancel);
}

void MainWindow::on_pushButton_133_clicked()
{
    int Id=ui->lineEdit_39->text().toInt();
    int Note=ui->lineEdit_42->text().toInt();
     QString Poste=ui->comboBox_4->currentText();
     QString Grade=ui->comboBox_3->currentText();

    if ((Id!=NULL && Note>=0 && Note<=20 ))
     {

        Categories C(Id,Poste,Grade,Note);
        bool test=C.Ajouter();
        if(test)
        {
             ui->tableView_13->setModel(C.afficher());
            QMessageBox::information(nullptr,QObject::tr("Ajouter une Categories"),QObject::tr("Categories ajouter avec succes.\n""Cliquez Cancel to exit."),QMessageBox::Cancel);

        }
        else
            QMessageBox::information(nullptr,QObject::tr("Ajouter une Categories"),QObject::tr("Categories non ajouter.\n""Cliquez Cancel to exit."),QMessageBox::Cancel);

    }
}

void MainWindow::on_pushButton_135_clicked()
{
    C.CREATION_PDF();
}

void MainWindow::on_pushButton_138_clicked()
{
   /* vehicule a(ui->lineEdit_36->text(),ui->lineEdit_37->text(),ui->lineEdit_40->text());
       bool test= a.ajouter();




       if (test)
       {
           ui->tableView_14->setModel(tempvehicule.afficher());//actualisation taa afficher
                   QMessageBox::information(nullptr,QObject::tr("ok"),
                                            QObject::tr("ajout succful .\n"),
                           QMessageBox::Cancel);
               }

               else
                   QMessageBox::critical(nullptr,QObject::tr("ajout not open"),
                                           QObject::tr("click cancel to exist"),
                                           QMessageBox::Cancel);



        ui->tableView_14->setModel(tempvehicule.afficher());*/
    QString nom=ui->lineEdit_36->text();
     QString type=ui->lineEdit_37->text();
      QString num=ui->lineEdit_40->text();


    vehicule c(nom,type,num);


    bool test=c.ajouter();
    if(test)
    {
        ui->tableView_14->setModel(tempvehicule.afficher());
        QMessageBox::information(nullptr,QObject::tr("Ajouter"),QObject::tr("Agent ajouter avec succes.\n""Cliquez Cancel to exit."),QMessageBox::Ok);

    }
    else
        QMessageBox::information(nullptr,QObject::tr("Ajouter"),QObject::tr("Agent non ajouter.\n""Cliquez Cancel to exit."),QMessageBox::Cancel);
}


void MainWindow::on_pushButton_136_clicked()
{QString nom=ui->lineEdit_44->text();
    QString type=ui->lineEdit_45->text();
    QString num=ui->lineEdit_46->text();

    vehicule f(nom,type,num);
bool test=f.modifier(num );
    if(test)
    {
        ui->tableView_14->setModel(tempvehicule.afficher());
        QMessageBox::information(nullptr,QObject::tr("modifier"),
                                 QObject::tr("modifier avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);

}

}

void MainWindow::on_pushButton_137_clicked()
{
    QString num=ui->lineEdit_43->text();
        bool test=tempvehicule.supprimer(num);
        if(test){

            ui->tableView_14->setModel(tempvehicule.afficher());
            QMessageBox::information(nullptr,QObject::tr("suppression"),
                                     QObject::tr("suppression avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);
        }
        else {
            QMessageBox::critical(nullptr,QObject::tr("suppression"),
                                     QObject::tr("suppression echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
        }
}

void MainWindow::on_pushButton_141_clicked()
{
    arme c(ui->lineEdit_44->text(),ui->lineEdit_45->text(),ui->lineEdit_46->text());
       bool test= c.ajouter();




       if (test)
       {
           ui->tableView_15->setModel(temparme.afficher());//actualisation taa afficher
                   QMessageBox::information(nullptr,QObject::tr("ok"),
                                            QObject::tr("ajout succful .\n"),
                           QMessageBox::Cancel);
               }

               else
                   QMessageBox::critical(nullptr,QObject::tr("ajout not open"),
                                           QObject::tr("click cancel to exist"),
                                           QMessageBox::Cancel);



        ui->tableView_15->setModel(temparme.afficher());
}

void MainWindow::on_pushButton_142_clicked()
{

    QString nom1=ui->lineEdit_44->text();
    QString type1=ui->lineEdit_45->text();
    QString numero1=ui->lineEdit_46->text();

    arme c(nom1,type1,numero1);
bool test=c.modifier(numero1);
    if(test)
    {
        ui->tableView_15->setModel(temparme.afficher());
        QMessageBox::information(nullptr,QObject::tr("modifier"),
                                 QObject::tr("modifier avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);

}
}

void MainWindow::on_pushButton_143_clicked()
{
    QString num1=ui->lineEdit_48->text();
        bool test=temparme.supprimer(num1);
        if(test){

            ui->tableView_15->setModel(temparme.afficher());
            QMessageBox::information(nullptr,QObject::tr("suppression"),
                                     QObject::tr("suppression avec succès.\n""Click Cancel to exit."),QMessageBox::Cancel);
        }
        else {
            QMessageBox::critical(nullptr,QObject::tr("suppression"),
                                     QObject::tr("suppression echoue.\n""Click Cancel to exit."),QMessageBox::Cancel);
        }
}

void MainWindow::on_pushButton_144_clicked()
{
    QPdfWriter pdf("C:/pdf/pdg.pdf");
                          QPainter painter(&pdf);
                         int i = 4000;
                              painter.setPen(Qt::blue);
                              painter.setFont(QFont("Arial", 25));
                              painter.drawText(950,1100,"Liste Des cellules");
                              painter.setPen(Qt::red);
                              painter.setFont(QFont("Arial", 15));
                             // painter.drawText(1100,2000,afficheDC);
                              painter.drawRect(100,100,7300,2600);
                              //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/Helmi/Documents/Gestion_achats/logo.png"));
                              painter.drawRect(0,3000,9600,500);
                              painter.setFont(QFont("Arial", 9));
                              painter.drawText(200,3300,"nom1");
                              painter.drawText(1200,3300,"type1");
                              painter.drawText(2600,3300,"numero1");


                              QSqlQuery query;
                              query.prepare("select * from arme");
                              query.exec();
                              while (query.next())
                              {
                                  painter.drawText(200,i,query.value(0).toString());
                                  painter.drawText(1300,i,query.value(1).toString());
                                  painter.drawText(2600,i,query.value(2).toString());





                                 i = i + 500;
                              }
}

void MainWindow::on_pushButton_145_clicked()
{
   ui->StackedMission->setCurrentIndex(0);
}


void MainWindow::on_radioButton_5_clicked()
{
    if(ui->radioButton_5->isChecked())
    {
       ui->numero_ajout->setText(tr("Number"));
       ui->type_ajout->setText(tr("Type"));
       ui->description_ajout->setText(tr("Description"));
        ui->btn_confirmer_ajout->setText(tr("ADD"));

       ui->radioButton_5->setText(tr("anglaise"));

    }
    else
    {
        ui->numero_ajout->setText(tr("numero"));
        ui->type_ajout->setText(tr("Type"));
        ui->description_ajout->setText(tr("Description"));
        ui->btn_confirmer_ajout->setText(tr("Ajouter"));
    ui->radioButton_5->setText(tr("français"));
    }
}

void MainWindow::on_radioButton_6_clicked()
{

    if(ui->radioButton_6->isChecked())
    {
       ui->numero_input_modif->setText(tr("Number"));
       ui->type_input_modif->setText(tr("Type"));
       ui->description_input_modif->setText(tr("Description"));
        ui->btn_confirmer_modif->setText(tr("Update"));

       ui->radioButton_6->setText(tr("anglaise"));

    }
    else
    {
        ui->numero_input_modif->setText(tr("Numero"));
        ui->type_input_modif->setText(tr("Type"));
        ui->description_input_modif->setText(tr("Description"));
        ui->btn_confirmer_modif->setText(tr("Modifier"));
    ui->radioButton_6->setText(tr("français"));
    }
}

void MainWindow::on_pushButton_66_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                               tr("Excel Files (*.xls)"));
               if (fileName.isEmpty())
                   return;

               ExportExcelObject obj(fileName, "mydata", ui->tableView_2);

               obj.addField(0, "colum1", "char(20)");
               obj.addField(1, "colum2", "char(20)");
               obj.addField(2, "colum3", "char(20)");
               obj.addField(3, "colum4", "char(20)");
               obj.addField(4, "colum5", "char(20)");
               obj.addField(5, "colum6", "char(20)");
               obj.addField(6, "colum7", "char(20)");


               int retVal = obj.export2Excel();

               if( retVal > 0)
               {

                   QMessageBox::information(this, tr("Done"),
                                            QString(tr("passeport exported!")).arg(retVal)
                                            );
               }
}

void MainWindow::on_translate_clicked()
{
    if(ui->translate->isChecked())
            {
               ui->label_31->setText(tr("Name"));
               ui->label_32->setText(tr("Last name"));
               ui->label_33->setText(tr("Birthdat"));
               ui->label_34->setText(tr("Work"));
               ui->label_35->setText(tr("Address"));
               ui->pushButton_4->setText(tr("add"));
               ui->pushButton_5->setText(tr("Update"));
               ui->pushButton_18->setText(tr("Delete"));
               ui->pushButton_15->setText(tr("Search"));
               //ui->pushButton_16->setText(tr("PDF Export"));
               ui->pushButton_17->setText(tr("Print"));
               ui->label_23->setText(tr("Name"));
               ui->label_24->setText(tr("Last name"));
               ui->label_25->setText(tr("Birthdate"));
               ui->label_27->setText(tr("Place of bith"));
               ui->label_28->setText(tr("Work"));
               ui->label_29->setText(tr("Address"));
               ui->label_21->setText(tr("Sex"));
               ui->translate->setText(tr("français"));

            }
            else
            {
            ui->label_7->setText(tr("Nom"));
            ui->label_8->setText(tr("prenom"));
            ui->label_9->setText(tr("date naissance"));
            ui->label_10->setText(tr("metier"));
            ui->label_11->setText(tr("adresse"));
            ui->pushButton_4->setText(tr("Ajouter"));
            ui->pushButton_5->setText(tr("Modifier"));
            ui->pushButton_6->setText(tr("Supprimer"));
            ui->pushButton_12->setText(tr("Recherche"));
            ui->pushButton_22->setText(tr("Exporter PDF"));
            ui->pushButton_32->setText(tr("Imprimer"));
            ui->label->setText(tr("Nom"));
            ui->translate->setText(tr("Anglais"));
            }

}
