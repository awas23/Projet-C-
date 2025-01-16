#include "categories.h"

Categories::Categories()
{
    Id=0;
    Poste="";
    Grade="";
    Note=0;

}
Categories::Categories(int Id, QString Poste, QString Grade, int Note)
{
    this->Id=Id;
    this->Poste=Poste;
    this->Grade=Grade;
    this->Note=Note;
}
bool Categories::Ajouter()
{

    QSqlQuery querry;
    querry.prepare("INSERT INTO Categories(ID,POSTE,GRADE,NOTE)"
                   "VALUES(:Id,:Poste,:Grade,:Note)");
    querry.bindValue(":Id",Id);
    querry.bindValue(":Poste",Poste);
    querry.bindValue(":Grade",Grade);
    querry.bindValue(":Note",Note);

    return querry.exec();
}

QSqlQueryModel* Categories::afficher()

{
    QSqlQueryModel *model= new QSqlQueryModel();

    model->setQuery("select * from CATEGORIES");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Grade"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Note"));
      return model;
}

QSqlQueryModel* Categories::rechercher(QString chaine)
{

    QSqlQueryModel * model=new QSqlQueryModel() ;
    model->setQuery("select * from CATEGORIES where ID LIKE'%"+chaine+"%' OR POSTE LIKE'%"+chaine+"%' OR NOTE LIKE'%"+chaine+"%' ;");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Grade"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Note"));

        return model;


}

QSqlQueryModel * Categories::trier_ID()
{
    // trier nbre
    QSqlQueryModel * model=new QSqlQueryModel() ;
    model->setQuery("select * from CATEGORIES order by ID ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Grade"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Note"));

        return model;
}
QSqlQueryModel * Categories::trier_Poste()
{
    // trier nbre
    QSqlQueryModel * model=new QSqlQueryModel() ;
    model->setQuery("select * from CATEGORIES ORDER BY POSTE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Grade"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Note"));

        return model;
}

QSqlQueryModel * Categories::trier_Grade()
{
    // trier nbre
    QSqlQueryModel * model=new QSqlQueryModel() ;
    model->setQuery("select * from CATEGORIES ORDER BY GRADE");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Poste"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Grade"));
    model->setHeaderData(3, Qt::Horizontal,QObject::tr("Note"));

        return model;
}

bool Categories::Modifier(int Id)
{


    QSqlQuery query,qry;
    QString res= QString::number(Id);
    bool Testquery=false;


    qry.prepare("select * from CATEGORIES where ID=?;");
    qry.addBindValue(Id);
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
            if(Poste!="")
            {
                query.prepare("UPDATE CATEGORIES SET POSTE=? WHERE ID='"+res+"';");
                query.addBindValue(Poste);query.exec();Testquery=true;
            }
            if(Grade!="")
            {
                query.prepare("UPDATE CATEGORIES SET GRADE=? WHERE ID='"+res+"';");
                query.addBindValue(Grade);query.exec();Testquery=true;
            }
            if(Note!=0 && (Note<=20 && Note>=0) )
            {
                query.prepare("UPDATE CATEGORIES SET NOTE=? WHERE ID='"+res+"';");
                query.addBindValue(Note);query.exec();Testquery=true;
            }



        }

    return  Testquery;
}

bool Categories::Supprimer(int Id)
{
QSqlQuery query;
query.prepare("Delete from CATEGORIES where ID = :Id");
query.bindValue(":Id", Id);
return    query.exec();
}

void Categories::CREATION_PDF()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) { fileName.append(".pdf"); }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QSqlQuery q;
    q.prepare("select * from CATEGORIES ");
    q.exec();
    QString pdf="<br> <h1  style='color:red'>tableu des categories  <br></h1>\n <br> <table>  <tr>  <th>ID </th> <th>Poste </th>  <th>Grade </th> <th> Note </th>  " ;


    while ( q.next()) {
pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+"</td>   <td> " + q.value(1).toString() +"</td>   <td>" +q.value(2).toString() +" </td>   <td>"+q.value(3).toString()+"</td>   <td>"+q.value(4).toString()+" </td>";

    }
    doc.setHtml(pdf);
    doc.setPageSize(printer.pageRect().size());
    doc.print(&printer);
}
