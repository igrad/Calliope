#include <page.h>
#include <QtTest/QtTest>

namespace
{
    static std::string TESTSTRING = "test string";
}

class Test_PageSaveAndLoad: public QObject
{
    Q_OBJECT

private slots:
    void SaveToFile()
    {
        QUuid pageID = QUuid::createUuid();
        Page page(pageID, "z_test_page.md", nullptr);

        page.SetData(TESTSTRING);
        page.SaveToFile();

        page.SetData("");
        QVERIFY(page.GetData() == "");

        page.LoadFromFile();
        QVERIFY(page.GetData() == TESTSTRING);

        page.DeleteFile();
    }

    void LoadFromFile()
    {
        QUuid pageID = QUuid::createUuid();
        Page page(pageID, "z_test_page.md", nullptr);

        page.SetData(TESTSTRING);
        page.SaveToFile();

        Page loadedPage(pageID, "z_test_page.md", nullptr);
        loadedPage.SetData("");

        loadedPage.LoadFromFile();
        QVERIFY(loadedPage.GetData() == TESTSTRING);

        page.DeleteFile();
        loadedPage.DeleteFile();
    }

    void DeleteFile()
    {
        QUuid pageID = QUuid::createUuid();
        Page page(pageID, "z_test_page.md", nullptr);

        QVERIFY(page.DeleteFile() == true);
    }
};
