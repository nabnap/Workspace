#ifndef JSONMANAGER_H
#define JSONMANAGER_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QVector>
#include <QUrl>
class JsonManager
{
public:
    JsonManager(QString file);
    QJsonDocument *loadDocument(QString *file = nullptr);
    bool saveDocument(QJsonDocument *saveDoc);
    QVector<QUrl*> getSessionUrls(QString *session);
    QVector<QString*> getSessions();
    QUrl* getHomepage();


    bool saveBlockSite(QUrl url);
    bool deleteBlockSite(QUrl url);
    bool isBlocked(QUrl url);

    bool saveBookSite(QUrl url);
    bool deleteBookSite(QUrl url);
    bool isBooked(QUrl url);
    QVector<QString*> getBookmarks();

    bool deleteSession(QString *session);
    bool saveSession(QString *session, QVector<QUrl> urls);

    bool saveHomepage(QUrl homepage);
    bool deleteHomepage();
private:
    QString globalFile;
};

#endif // JSONMANAGER_H
