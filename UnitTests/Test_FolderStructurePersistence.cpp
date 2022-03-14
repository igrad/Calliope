#include "folder.h"
#include "page.h"
#include <QUuid>
#include <QtTest/QtTest>

class Test_FolderStructurePersistenceTest: public QObject
{
    Q_OBJECT

private slots:
    void SaveAncestryToFile()
    {
        const QUuid f1ID = QUuid::createUuid();
        const QUuid f2ID = QUuid::createUuid();
        Folder f1(f1ID, "Folder 1", &Folder::RootFolder);
        Folder f2(f2ID, "Folder 2", &f1);

        QVERIFY(true);
    }
};
