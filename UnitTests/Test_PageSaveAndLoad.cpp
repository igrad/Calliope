#include <QtTest/QtTest>
#include <page.h>

class Test_PageSaveAndLoad: public QObject
{
    Q_OBJECT

private slots:
    void SaveToFile()
    {
        const std::string testString = "test string";
        Page page("z_test_page");
        FileManager fm;

        page.SetData(testString);

        try {
            fm.SavePageToFile(page);

            page.SetData("");

            fm.LoadPageFromFile(page);
            QVERIFY(page.GetData() == testString);

            fm.DeleteFile(page);
        }  catch (...) {
            QFAIL("Failed to save page to file");
        }
    }

    void LoadFromFile()
    {
        const std::string testString = "test string";
        Page page("z_test_page");
        FileManager fm;

        page.SetData(testString);
        fm.SavePageToFile(page);

        try {
            Page loadedPage("z_test_page");
            page.SetData("");

            fm.LoadPageFromFile(page);
            QVERIFY(page.GetData() == testString);
        }  catch (...) {
            QFAIL("Failed to save page to file");
        }
    }
};
