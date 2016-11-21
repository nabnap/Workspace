#ifndef PHONEBOOK_H
#define PHONEBOOK_H
#include <QVector>
#include <QString>
class Entry {
public:
    Entry(){}
    Entry(QString, QString);
    QString getName();
    QString getNumber();
private:
    QString name, number;
};

class Book {
public:
    Book() {}
    void add(QString,QString);
    QVector<Entry> getAll();
    void deleteAtIndex(int);
    /*QVector<Entry> getName(QString);
    Entry getNumber(QString);
    bool deleteName(QString);
    bool deleteNumber(QString);*/
private:
    QVector<Entry> entryVec;
};


#endif // PHONEBOOK_H
