#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "admin.h"
#include "mission.h"
#include "vehicule.h"
#include "arme.h"
#include "classe.h"
#include "maintenance.h"
#include "citoyen.h"
#include "categories.h"
#include<reclamation.h>
#include "cellule.h"
#include "budget.h"
#include "agent.h"
#include <QMainWindow>
#include "QSystemTrayIcon"
#include <QDebug>
#include <QTimer>
#include<certificat.h>
#include<passeport.h>
#include<ajoutercin.h>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QFileInfo>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QLabel>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QMovie>
#include <QPainter>
#include <QPdfWriter>
#include <QPropertyAnimation>
#include <QSqlDatabase>
#include "arduino.h"
#include <QTimer>
#include <QUrl>
#include <QWidget>
#include <QtSql>
#include <QSound>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_mission_clicked();

    void on_btn_citoyen_clicked();

    void on_btn_confirmer_ajout_clicked();

    void on_pushButton_clicked();

    void on_chercherMission_textChanged(const QString &arg1);

    void on_supprimerMission_clicked();

    void on_btn_confirmer_modif_clicked();

    void on_modifierMission_clicked();

    void on_trierMission_clicked();

    void on_imprimerMission_clicked();

    void on_confirmer_ajout_citoyen_clicked();

    void on_supprimer_citoyen_clicked();



    void on_chercher_citoyen_textChanged(const QString &arg1);

    void on_trier_citoyens_clicked();

    void on_modifier_citoyen_clicked();

    void on_pb_send_clicked();

    void on_confirmer_modif_citoyen_clicked();
    void update_label1();

    void on_pushButton_7_clicked();



    void on_pushButton_8_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_32_clicked();



    void on_pushButton_9_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_35_clicked();

    void on_pushButton_36_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_37_clicked();

    void on_pushButton_38_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_15_clicked();





    void on_pushButton_19_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_33_clicked();

    void on_tableView_4_activated(const QModelIndex &index);

    void on_tableView_3_activated(const QModelIndex &index);

    void on_tableView_activated(const QModelIndex &index);

    void on_tableView_2_activated(const QModelIndex &index);

    void on_pushButton_6_clicked();



    void on_pushButton_12_clicked();

    void on_pushButton_39_clicked();

    void on_pushButton_40_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_41_clicked();

    void on_pushButton_42_clicked();

    void on_pushButton_43_clicked();

    void on_pushButton_44_clicked();

    void on_pushButton_45_clicked();
    void on_pushButton_46_clicked();

    void on_pushButton_47_clicked();

    void on_pushButton_48_clicked();

    void on_pushButton_51_clicked();

    void on_pushButton_49_clicked();

    void on_pushButton_50_clicked();

    void on_pushButton_52_clicked();

    void on_pushButton_53_clicked();

    void on_pushButton_54_clicked();

    void on_pushButton_55_clicked();

    void on_pushButton_56_clicked();

    void on_tableView_agent_doubleClicked(const QModelIndex &index);

    void on_pushButton_57_clicked();

    void on_pushButton_58_clicked();

    void on_pushButton_59_clicked();

    void on_pushButton_60_clicked();

    void on_pushButton_61_clicked();

    void on_pushButton_62_clicked();

    void on_pushButton_63_clicked();

    void on_pushButton_64_clicked();

    void on_pushButton_65_clicked();


    void on_rechercher_agent_textChanged(const QString &arg1);

    void on_TRIER_clicked();

    void on_Trier_cin_2_clicked();

    void on_Trier_nom_2_clicked();

    void on_radioButton_7_clicked();

    void on_TRIER_3_clicked();

    void on_Ajouter_agent_clicked();

    void on_TRIER_2_clicked();

    void on_pushButton_134_clicked();

    void on_lineEdit_33_textChanged(const QString &arg1);

    void on_pushButton_131_clicked();

    void on_radioButton_11_clicked();

    void on_radioButton_12_clicked();

    void on_radioButton_13_clicked();

    void on_pushButton_132_clicked();

    void on_pushButton_133_clicked();

    void on_pushButton_135_clicked();

    void on_pushButton_138_clicked();

    void on_pushButton_136_clicked();

    void on_pushButton_137_clicked();

    void on_pushButton_141_clicked();

    void on_pushButton_142_clicked();

    void on_pushButton_143_clicked();

    void on_pushButton_144_clicked();

    void on_pushButton_145_clicked();



    void on_radioButton_5_clicked();

    void on_radioButton_6_clicked();

    void on_pushButton_66_clicked();

    void on_translate_clicked();



public slots:
    void myfunction();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QSystemTrayIcon *notifyicon;
     QMediaPlayer *player;
     QByteArray data;
     Arduino A;
     int x=0;
     ajoutercin hajoutercin;
     passeport temppassport;
     certificat tempcertif;
     reclamation tempreclamation;
      admin temptadmin;
       cellule tempcellule;
        budget tempbudget;
        Agent A1,tmpA;
           maintenance tempmaintenance;
           Categories C,tmpC;
           vehicule tempvehicule;
           arme temparme;
           QSound *son;
           QSqlQuery qry;

};
#endif // MAINWINDOW_H
