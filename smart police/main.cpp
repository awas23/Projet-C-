#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include "QDebug"

int main(int argc, char *argv[])
{
    Connection c;
    QApplication a(argc, argv);
    MainWindow w;
    if(c.ouvrirconnexion())
          {

             w.show();
             qDebug()<<"CNX CAVA";

          }
          else {
              qDebug()<<"ERREUR CNX";
          }
    return a.exec();
}
