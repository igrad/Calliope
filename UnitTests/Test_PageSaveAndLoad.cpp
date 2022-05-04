#include "page.h"
#include <QtTest/QtTest>

namespace
{
    static std::string TESTSTRING = "test string";
}

class Test_PageSaveAndLoad: public QObject
{
    Q_OBJECT

private slots:
    void saveToFile()
    {
        QUuid pageID = QUuid::createUuid();
        Page page(pageID, "z_test_page.md", nullptr);

        page.setData(TESTSTRING);
        page.saveToFile();

        page.setData("");
        QVERIFY(page.getData() == "");

        page.loadFromFile();
        QVERIFY(page.getData() == TESTSTRING);

        page.deleteFile();
    }

    void loadFromFile()
    {
        QUuid pageID = QUuid::createUuid();
        Page page(pageID, "z_test_page.md", nullptr);

        page.setData(TESTSTRING);
        page.saveToFile();

        Page loadedPage(pageID, "z_test_page.md", nullptr);
        loadedPage.setData("");

        loadedPage.loadFromFile();
        QVERIFY(loadedPage.getData() == TESTSTRING);

        page.deleteFile();
        loadedPage.deleteFile();
    }

    void deleteFile()
    {
        QUuid pageID = QUuid::createUuid();
        Page page(pageID, "z_test_page.md", nullptr);

        QVERIFY(page.deleteFile() == true);
    }
};
