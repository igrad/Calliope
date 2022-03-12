#include <page.h>
#include <QtTest/QtTest>

namespace
{
    const std::string TESTSTRING = "test string";
}

class Test_PageSaveAndLoad: public QObject
{
    Q_OBJECT

private slots:
    void SaveToFile()
    {
        Page page("z_test_page");

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
        Page page("z_test_page");

        page.SetData(TESTSTRING);
        page.SaveToFile();

        Page loadedPage("z_test_page");
        page.SetData("");

        page.LoadFromFile();
        QVERIFY(page.GetData() == TESTSTRING);
    }
};
