#include "testmanager.h"

std::map<std::string, UnitTest*> UnitTest::AllTests;



UnitTest::UnitTest(std::string m_testName)
    : testName(m_testName)
{
    UnitTest::AllTests[m_testName] = this;
}

UnitTest::~UnitTest()
{
    UnitTest::AllTests.erase(UnitTest::AllTests.find(testName));
}


bool UnitTest::Run()
{
    try
    {
        return TestBody();
    }
    catch (const std::exception &exception)
    {
        std::cout << testName << ": test threw exception: " << exception.what() << std::endl;
        return false;
    }
}



void UnitTest::RunTests()
{
    std::map<std::string, UnitTest*>::iterator test;
    for(test = AllTests.begin(); test != AllTests.end(); test++)
    {
        test->second->Run();
    }
}
