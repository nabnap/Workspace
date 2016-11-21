#include "phonebook.h"



//================= Entry =================//
//Entry class declaration

//Entry class definition
//Entry constructor
Entry::Entry(QString ename, QString enumber) {
    name = ename;
    number = enumber;
}
//Returns the name of the entry
QString Entry::getName() {
    return name;
}
//Returns the number of the entry
QString Entry::getNumber() {
    return number;
}
//============================================//





//================= Book =================//
//Book class declaration

//Book class definition
//Returns the entry book entries
QVector<Entry> Book::getAll() {
    return entryVec;
}

void Book::deleteAtIndex(int index){
    entryVec.remove(index);
}

/*
//Delete entry by number
bool Book::deleteNumber(QString n) {
    for (int i = 0; i < entryVec.size(); i++) {
        Entry e = entryVec.at(i);
        if (e.getNumber() == n) {
            entryVec.erase(entryVec.begin() + i);
            return true;
        }
    }
    return false;
}

//Delete entry by name
bool Book::deleteName(QString n) {
    QVector<Entry> tmp;
    bool removed = false;
    for (int i = 0; i < entryVec.size(); i++) {
        Entry e = entryVec.at(i);
        if (e.getName() == n) {
            entryVec.erase(entryVec.begin() + i);
            removed = true;
            i == 0 ? 0 : i--;
        }
    }
    return removed;
}

//Get entry by number
Entry Book::getNumber(QString n) {
    for (Entry e : entryVec) {
        if (e.getNumber() == n) {
            return e;
        }
    }
    return Entry("","");
}

//Get entry by name
QVector<Entry> Book::getName(QString n) {
    QVector<Entry> tmp;
    for (Entry e : entryVec) {
        if (e.getName() == n) {
            tmp.push_back(e);
        }
    }
    return tmp;
}*/

//Add entry to the book vector
void Book::add(QString name, QString number) {
    entryVec.push_back(Entry(name, number));
}
//============================================//
