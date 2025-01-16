#include "maintenance.h"


maintenance::maintenance()
{
numm="";
datem="";
typem="";
}
maintenance::maintenance(QString n,QString d,QString t)
{
    numm=n;
    datem=d;
    typem=t;
}

bool maintenance::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO maintenance (numm,datem,typem)"
                  "VALUES(:numm, :datem, :typem)");
    query.bindValue(":numm",numm);
    query.bindValue(":datem",datem);
    query.bindValue(":typem",typem);
    return query.exec();
}
QSqlQueryModel *maintenance::afficher(){

    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from maintenance");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("numero"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("type"));
   return model;
}
bool maintenance::supprimer(QString numm){

    QSqlQuery query;
    query.prepare("delete from maintenance where numm = :numm");
    query.bindValue(":numm",numm);
    return query.exec();
}
bool maintenance::modifier(QString numm){
    QSqlQuery query;
    query.prepare("update maintenance set typem= :typem where numm = :numm ");
    query.bindValue(":numm",numm);
    query.bindValue(":typem",typem);
    return query.exec();


}
//recherche
QSqlQueryModel * maintenance::chercher(QString r)
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT * FROM maintenance WHERE numm like ('%"+r+"%') or datem like ('%"+r+"%') or typem like ('%"+r+"%') ");
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("numero"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("date"));
    model->setHeaderData(2,Qt::Horizontal, QObject::tr("type"));
     return model;
}
//imprimer
void maintenance::printPDF(QTableView * tableView_2)
{
    QPixmap pix(tableView_2->size());
      QPainter painter(&pix);
      tableView_2->render(&painter);
      painter.end();
      QPrinter printer(QPrinter::HighResolution);
      printer.setOrientation(QPrinter::Landscape);
      printer.setOutputFormat(QPrinter::PdfFormat);
      printer.setPaperSize(QPrinter::A4);
      printer.setOutputFileName("congé.pdf"); // will be in build folder

      painter.begin(&printer);
      double xscale = printer.pageRect().width() / double(pix.width());
      double yscale = printer.pageRect().height() / double(pix.height());
      double scale = qMin(xscale, yscale);
      painter.translate(printer.paperRect().x() + printer.pageRect().width() / 2,
                        printer.paperRect().y() + printer.pageRect().height() / 2);
      painter.scale(scale, scale);
      painter.translate(-tableView_2->width() / 2, -tableView_2->height() / 2);
      painter.drawPixmap(0, 0, pix);

    QTextDocument doc;

    doc.setHtml("");
    doc.drawContents(&painter);

      painter.end();

}

