#ifndef TESTMANAGER_H
#define TESTMANAGER_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>


class UnitTest
{
public:
    UnitTest(std::string m_testName);
    ~UnitTest();

    bool Run();
    virtual bool TestBody() = 0;

    std::string testName;

    // Static members
    static void RunTests();

    static std::map<std::string, UnitTest*> AllTests;
};

#endif // TESTMANAGER_H
