#include "jsonmanager.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVector>
#include <QUrl>
#include <QFile>
#include <QDebug>
JsonManager::JsonManager(QString file)
{
    globalFile = file;
}

QJsonDocument * JsonManager::loadDocument(QString *file){
    QString lfile = file == nullptr ? globalFile : *file;
    QFile loadFile(lfile);

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return nullptr;
    }
    QByteArray saveData = loadFile.readAll();
    loadFile.close();
    return new QJsonDocument(QJsonDocument::fromJson(saveData));
}
bool JsonManager::saveDocument(QJsonDocument *saveDoc){
    QFile saveFile(globalFile);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    saveFile.write(saveDoc->toJson());
    saveFile.close();
    return true;
}

QVector<QUrl*> JsonManager::getSessionUrls(QString *session){
    QJsonDocument *doc = this->loadDocument(); //Get the document from the global file
    QVector<QUrl*> urls;
    if(doc && session){

        QJsonObject json = doc->object();
        json = json["sessions"].toObject();
        QJsonArray urlArray = json[session->toStdString().c_str()].toArray();
        for (int i = 0; i < urlArray.size(); ++i) {
            //QUrl url = QUrl::fromUserInput(urlArray[i].toString());
            //m_tabWidget->createTab(true, url);
            urls.append(new QUrl(QUrl::fromUserInput(urlArray[i].toString())));
        }

        delete doc;
    }
    return urls;
}
bool JsonManager::deleteHomepage(){
    QJsonDocument *doc = this->loadDocument(); //Get the document from the global file
    if(doc){
        QJsonObject json = doc->object();
        json.remove("homepage");

        QJsonDocument saveDoc(json);
        delete doc;

        return this->saveDocument(&saveDoc);
    }
    return false;
}
bool JsonManager::deleteSession(QString *session){
    QJsonDocument *doc = this->loadDocument(); //Get the document from the global file
    if(doc && session){
        QJsonObject json = doc->object();
        QJsonObject sessions = json["sessions"].toObject();
        sessions.remove(*session);
        json["sessions"] = sessions;

        QJsonDocument saveDoc(json);
        delete doc;
        return this->saveDocument(&saveDoc);
    }
    return false;
}
QVector<QString*> JsonManager::getSessions(){
    QJsonDocument *doc = this->loadDocument(); //Get the document from the global file
    QVector<QString*> sessions;
    if(doc){
        QJsonObject json = doc->object();
        json = json["sessions"].toObject();
        for(QString key : json.keys()){
            sessions.append(new QString(key));
        }

        delete doc;
    }
    return sessions;
}

QVector<QString*> JsonManager::getBookmarks(){
    QJsonDocument *doc = this->loadDocument(); //Get the document from the global file
    QVector<QString*> bookmarks;
    if(doc){
        QJsonObject json = doc->object();
        QJsonArray arr = json["bookmarked"].toArray();
        for(QJsonValue key : arr){
            bookmarks.append(new QString(key.toString()));
        }

        delete doc;
    }
    return bookmarks;
}

QUrl* JsonManager::getHomepage(){
    QJsonDocument *doc = this->loadDocument(); //Get the document from the global file
    if(doc){
        QJsonObject json = doc->object();

        QString home = json["homepage"].toString();
        delete doc;
        if(home.length() > 0)
            return new QUrl(home);
    }
    return nullptr;
}

bool JsonManager::saveHomepage(QUrl homepage){
    //We have a session name to work with
    QJsonDocument *doc = this->loadDocument();

    QJsonObject sessionObject;
    if(doc){
        sessionObject = doc->object();
    }
    sessionObject["homepage"] = homepage.toString();

    QJsonDocument saveDoc(sessionObject);
    return this->saveDocument(&saveDoc);
}

bool JsonManager::saveBookSite(QUrl url){
    QJsonDocument *doc = this->loadDocument();
    QJsonObject object;
    if(doc)
        object = doc->object();
    QJsonArray arr = object["bookmarked"].toArray();
    QJsonValue val(url.toString());
    if(url.isValid() && !arr.contains(val))
        arr.append(url.toString());
    object["bookmarked"] = arr;
    QJsonDocument saveDoc(object);
    return this->saveDocument(&saveDoc);
}
bool JsonManager::deleteBookSite(QUrl url){
    QJsonDocument *doc = this->loadDocument();
    QJsonObject object;
    if(doc)
        object = doc->object();
    QJsonArray arr = object["bookmarked"].toArray();

    if(url.isValid()){
        QJsonValue val(url.toString());
        for(int i = 0; i < arr.size(); i++){
            if(arr.at(i) == val){
                arr.removeAt(i);
                break;
            }
        }
    }

    object["bookmarked"] = arr;
    QJsonDocument saveDoc(object);
    return this->saveDocument(&saveDoc);
}
bool JsonManager::isBooked(QUrl url){
    QJsonDocument *doc = this->loadDocument(); //Get the document from the global file
    if(doc){
        QJsonObject json = doc->object();

        QJsonArray arr = json["bookmarked"].toArray();
        delete doc;
        if(url.isValid()){
            QJsonValue val(url.toString());
            return arr.contains(val);
        }
    }
    return false;
}

bool JsonManager::saveBlockSite(QUrl url){
    QJsonDocument *doc = this->loadDocument();
    QJsonObject object;
    if(doc)
        object = doc->object();
    QJsonArray arr = object["blocked"].toArray();
    QJsonValue val(url.host());
    if(url.isValid() && !url.isRelative() && !url.isLocalFile() && !arr.contains(val))
        arr.append(url.host());
    object["blocked"] = arr;
    QJsonDocument saveDoc(object);
    return this->saveDocument(&saveDoc);
}
bool JsonManager::deleteBlockSite(QUrl url){
    QJsonDocument *doc = this->loadDocument();
    QJsonObject object;
    if(doc)
        object = doc->object();
    QJsonArray arr = object["blocked"].toArray();

    if(url.isValid() && !url.isRelative() && !url.isLocalFile()){
        QJsonValue val(url.host());
        for(int i = 0; i < arr.size(); i++){
            if(arr.at(i) == val){
                arr.removeAt(i);
                break;
            }
        }
    }

    object["blocked"] = arr;
    QJsonDocument saveDoc(object);
    return this->saveDocument(&saveDoc);
}
bool JsonManager::isBlocked(QUrl url){
    QJsonDocument *doc = this->loadDocument(); //Get the document from the global file
    if(doc){
        QJsonObject json = doc->object();

        QJsonArray arr = json["blocked"].toArray();
        delete doc;
        if(url.isValid() && !url.isRelative() && !url.isLocalFile()){
            QJsonValue val(url.host());
            return arr.contains(val);
        }
    }
    return false;
}
bool JsonManager::saveSession(QString *session, QVector<QUrl> urls){

    if(session){
        //We have a session name to work with
        QJsonDocument *doc = this->loadDocument();

        QJsonObject sessionObject;
        if(doc){
            sessionObject = doc->object();
        }
        QJsonObject sessions = sessionObject["sessions"].toObject();

        QJsonArray urlArray;
        for(QUrl url : urls){
            urlArray.append(url.toString());
        }

        sessions[session->toStdString().c_str()] = urlArray;
        sessionObject["sessions"] = sessions;
        QJsonDocument saveDoc(sessionObject);
        return this->saveDocument(&saveDoc);
    }
    return false;
}
