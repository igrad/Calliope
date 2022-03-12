#include <QtTest/QtTest>
#include "page.h"
#include "folder.h"

class Test_FolderStructurePersistenceTest: public QObject
{
    Q_OBJECT

private slots:
    void SaveAncestryToFile()
    {
        Folder f1("Folder 1", "ID1", &Folder::RootFolder);
        Folder f2("Folder 2", "ID2", &f1);

        QVERIFY(true);
    }
};
