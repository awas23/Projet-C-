#ifndef ARME_H
#define ARME_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
class arme
{
public:
    arme();
    arme(QString,QString,QString);
    void setnm1(QString nm1);
    void setty1(QString ty1);
    void setnum1(QString num1);
    QString get_nm1();
    QString get_ty1();
    QString get_num1();

    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool modifier(QString num1);
    void genererPDF();




private:
    QString nm1, ty1, num1;

};

#endif // ARME_H
