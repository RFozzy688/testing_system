#include "TestManagement.h"

void TestManagement::ClearScreen(COORD pos)
{
    DWORD count;
    DWORD cellCount;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    cellCount = 100;

    /* Fill the entire buffer with spaces */
    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', cellCount, pos, &count)) return;

    /* Move the cursor home */
    SetConsoleCursorPosition(hConsole, pos);
}

void TestManagement::LoadingTestsTree(map<string, vector<string>>& paths, const string& current_path)
{
    for (const auto file : filesystem::directory_iterator(current_path))
    {
        if (filesystem::is_directory(file))
        {
            tests.clear();
            chapter = file.path().string();

            LoadingTestsTree(paths, file.path().string());

            pair<string, vector<string>> element(chapter, tests);
            paths.insert(element);
        }
        else
        {
            tests.push_back(file.path().string());
        }
    }
}

void TestManagement::PrintTestsTree()
{
    int countChapter = 1;
    int countTest = 1;

    cout << "\n ������ ������:\n";

    for (auto it_chapters : testsTree)
    {
        cout << " ������: \n";
        cout << "  " << countChapter++ << ". " << it_chapters.first.substr(it_chapters.first.rfind("\\") + 1) << endl;
        cout << " �����:\n";

        for (auto it_tests : it_chapters.second)
        {
            int start = it_tests.rfind("\\") + 1;
            int end = it_tests.rfind(".");
            cout << "   " << countTest++ << ". " << it_tests.substr(start, end - start) << endl;
        }

        countTest = 1;
    }
}

void TestManagement::PrintChapter()
{
    int count = 1;

    for (auto it : testsTree)
    {
        cout << " " << count++ << ". " << it.first.substr(it.first.rfind("\\") + 1) << endl;
    }
}

int TestManagement::PrintMenuCreateTest()
{
    system("cls");

    cout << "\n ������� ����\n";
    cout << "\n 1 - ������� ������ | 2 - ������� ������������\n";
    cout << " > ";

    int key = _getch();

    cin.ignore(cin.rdbuf()->in_avail()); // ������� ����� ����� �� ������ ��������

    return key;
}

void TestManagement::CreateChapter()
{
    while (true)
    {
        system("cls");

        string newChapter;

        cout << "\n ������� ����\n";
        cout << "\n �������� �������: ";
        getline(cin, newChapter);

        if (IsChapter(newChapter))
        {
            cout << " ������ " + newChapter + " ����������.\n";
            cout << " ������� ���� � ���� �������?(y/n)";
            int key = _getch();

            if (key == 'y')
            {
                chapter = rootCatalog + "\\" + newChapter;
                break;
            }
            else
            {
                continue;
            }
        }
        else
        {
            chapter.clear();
            chapter = rootCatalog + "\\" + newChapter;

            tests.clear();
            pair<string, vector<string>> element(chapter, tests);
            testsTree.insert(element);

            filesystem::create_directories(chapter);
            break;
        }
    }
}

void TestManagement::CreateTest()
{
    int count = 1;
    Question testQuestion;

    questions.clear();

    while (true)
    {
        system("cls");

        cout << endl;
        cout << count++ << ". ������: ";
        getline(cin, testQuestion.question);
        cout << "\n 1 - �����: ";
        getline(cin, testQuestion.answer_1);
        cout << " 2 - �����: ";
        getline(cin, testQuestion.answer_2);
        cout << " 3 - �����: ";
        getline(cin, testQuestion.answer_3);
        cout << " 4 - �����: ";
        getline(cin, testQuestion.answer_4);
        cout << " ����� ����������� ������: ";
        cin >> testQuestion.trueAnswer;

        questions.push_back(testQuestion);

        cout << "\n ����������?(y/n): ";
        int key = _getch();

        cin.ignore(cin.rdbuf()->in_avail()); // ������� ����� ����� �� ������ ��������

        if (key == 'n')
        {
            break;
        }
    }

    cout << "\n ���������?(y/n): ";
    int key = _getch();

    cin.ignore(cin.rdbuf()->in_avail()); // ������� ����� ����� �� ������ ��������

    if (key == 'y')
    {
        map<string, vector<string>>::iterator iter = testsTree.find(chapter);

        Save save(iter->second.back());
        save.SaveTest(questions);
        save.CloseFile();
    }
}

bool TestManagement::IsChapter(string str)
{
    string newChapter = rootCatalog + "\\" + str;
    map<string, vector<string>>::iterator iter = testsTree.find(newChapter);

    if (iter != testsTree.end())
    {
        return true;
    } 
    else
    {
        return false;
    }
    
}

void TestManagement::AddTestToMap(string nameTest)
{
    string fullNameTest;

    map<string, vector<string>>::iterator iter = testsTree.find(chapter);
    fullNameTest = chapter + "\\" + nameTest + ".txt";
    iter->second.push_back(fullNameTest);
}

string TestManagement::InputNameTest()
{
    string nameTest;

    while (true)
    {
        system("cls");

        cout << "\n ������� ����\n";
        cout << "\n �������� �����: ";
        getline(cin, nameTest);

        if (!IsNameTest(nameTest))
        {
            break;
        } 
    }

    return nameTest;
}

bool TestManagement::IsNameTest(string nameTest)
{
    string fullNameTest;
    map<string, vector<string>>::iterator iter = testsTree.find(chapter);
    fullNameTest = chapter + "\\" + nameTest + ".txt";

    if (!iter->second.empty())
    {
        for (auto it : iter->second)
        {
            if (it == fullNameTest)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    } 
    else
    {
        return false;
    }
}

void TestManagement::ChoiceChapter()
{
    int number;
    string nameChapter;
    COORD pos;

    while (true)
    {
        pos.X = 0;
        pos.Y = 7;
        SetConsoleCursorPosition(hConsole, pos);

        PrintChapter();

        pos.X = 0;
        pos.Y = 3;
        SetConsoleCursorPosition(hConsole, pos);

        cout << " ����� �������: ";
        cin >> number;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            continue;
        }

        --number;

        if (number >= 0 && number < testsTree.size())
        {
            int index = 0;

            for (auto it : testsTree)
            {
                if (number == index)
                {
                    chapter = it.first;
                    break;
                }

                index++;
            }

            break;
        }
    }

    cin.ignore(cin.rdbuf()->in_avail()); // ������� ����� ����� �� ������ ��������
}

void TestManagement::ChoiceTest()
{
    int numberChapter;
    //int numberTest;
    COORD pos;

    cout << "\n ����� �������: ";

    while (true)
    {
        while (true)
        {
            cin >> numberChapter;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                pos.X = 16;
                pos.Y = 3;
                ClearScreen(pos);
                SetConsoleCursorPosition(hConsole, pos);
                continue;
            }
            else
            {
                break;
            }
        }

        --numberChapter;

        if (numberChapter >= 0 && numberChapter < testsTree.size())
        {
            int index = 0;

            for (auto it : testsTree)
            {
                if (numberChapter == index)
                {
                    chapter = it.first;
                    break;
                }

                index++;
            }
        }
        else
        {
            pos.X = 16;
            pos.Y = 3;
            ClearScreen(pos);
            SetConsoleCursorPosition(hConsole, pos);
            continue;
        }

        cout << " ����� �����: ";
        while (true)
        {
            cin >> numberTest;

            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                pos.X = 14;
                pos.Y = 4;
                ClearScreen(pos);
                SetConsoleCursorPosition(hConsole, pos);
                continue;
            }
            else
            {
                break;
            }
        }

        map<string, vector<string>>::iterator iter = testsTree.find(chapter);
        --numberTest;

        if (numberTest >= 0 && numberTest < iter->second.size())
        {
            currentTest = iter->second[numberTest];
            break;
        }
        else
        {
            pos.X = 0;
            pos.Y = 4;
            ClearScreen(pos);
            pos.X = 16;
            pos.Y = 3;
            ClearScreen(pos);
            SetConsoleCursorPosition(hConsole, pos);
            continue;
        }
    }
}

void TestManagement::DeleteTest()
{
    COORD pos;

    while (true)
    {
        system("cls");

        pos.X = 0;
        pos.Y = 7;
        SetConsoleCursorPosition(hConsole, pos);

        PrintTestsTree();

        pos.X = 0;
        pos.Y = 0;
        SetConsoleCursorPosition(hConsole, pos);

        cout << "\n �������� �����\n";

        ChoiceTest();
        map<string, vector<string>>::iterator iter_map = testsTree.find(chapter);
        vector<string>::iterator iter_vec = iter_map->second.begin() + numberTest;

        filesystem::remove(*iter_vec);
        iter_map->second.erase(iter_vec);

        system("cls");

        cout << "\n ���� ������\n";

        pos.X = 0;
        pos.Y = 7;
        SetConsoleCursorPosition(hConsole, pos);

        PrintTestsTree();

        pos.X = 0;
        pos.Y = 6;
        SetConsoleCursorPosition(hConsole, pos);

        cout << " ���������� ��������?(y/n): ";
        int key = _getch();
        cin.ignore(cin.rdbuf()->in_avail()); // ������� ����� ����� �� ������ ��������

        if (key == 'y')
        {
            continue;
        }
        else
        {
            break;
        }
    } 
}

void TestManagement::DeleteChapter()
{
    COORD pos;

    while (true)
    {
        system("cls");

        cout << "\n �������� �������\n";

        ChoiceChapter();
        map<string, vector<string>>::iterator iter = testsTree.find(chapter);

        filesystem::remove_all(iter->first);
        testsTree.erase(iter);
        chapter.clear();

        system("cls");

        cout << "\n ������ ������\n";

        pos.X = 0;
        pos.Y = 7;
        SetConsoleCursorPosition(hConsole, pos);

        PrintChapter();

        pos.X = 0;
        pos.Y = 4;
        SetConsoleCursorPosition(hConsole, pos);

        cout << " ���������� ��������?(y/n): ";
        int key = _getch();
        cin.ignore(cin.rdbuf()->in_avail()); // ������� ����� ����� �� ������ ��������

        if (key == 'y')
        {
            continue;
        }
        else
        {
            break;
        }
    }
}

void TestManagement::ShowTest()
{
    int countQuestions = 1;
    int countAnswer = 1;

    for (auto it : questions)
    {
        cout << countQuestions++ << ". " << it.question << endl;
        cout << "  " << countAnswer++ << ") " << it.answer_1 << endl;
        cout << "  " << countAnswer++ << ") " << it.answer_2 << endl;
        cout << "  " << countAnswer++ << ") " << it.answer_3 << endl;
        cout << "  " << countAnswer++ << ") " << it.answer_4 << endl;
        cout << "  ���������� �����: " << it.trueAnswer << endl << endl;

        countAnswer = 1;
    }
}

int TestManagement::PrintMenuEditTest()
{
    cout << "\n ������������� ����\n";
    cout << "\n 1 - �������� ������ | 2 - ������� ������ | Esc - �����\n";
    cout << " > ";

    int key = _getch();

    cin.ignore(cin.rdbuf()->in_avail()); // ������� ����� ����� �� ������ ��������

    return key;
}

void TestManagement::DeleteQuestion()
{
    COORD pos;
    int index;

    if (questions.empty())
    {
        cout << "\n\n ��� �������� ��� ��������";
        Sleep(3000);
        return;
    }

    while (true)
    {
        system("cls");

        pos.X = 0;
        pos.Y = 7;
        SetConsoleCursorPosition(hConsole, pos);
        ShowTest();

        pos.X = 0;
        pos.Y = 0;
        SetConsoleCursorPosition(hConsole, pos);

        cout << "\n ������������� ����\n";
        cout << "\n ����� ������� ��� ��������: ";
        cin >> index;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();

            continue;
        }

        index--;

        if (index >= 0 && index < questions.size())
        {
            vector<Question>::iterator iter = questions.begin() + index;
            questions.erase(iter);

            system("cls");

            pos.X = 0;
            pos.Y = 7;
            SetConsoleCursorPosition(hConsole, pos);
            ShowTest();

            pos.X = 0;
            pos.Y = 4;
            SetConsoleCursorPosition(hConsole, pos);

            cout << " ���������� ��������?(y/n): ";
            int key = _getch();
            cin.ignore(cin.rdbuf()->in_avail()); // ������� ����� ����� �� ������ ��������

            if (key == 'y')
            {
                continue;
            }
            else
            {
                break;
            }
        }
    }

}

void TestManagement::AddQuestion()
{
    Question testQuestion;

    questions.clear();

    while (true)
    {
        system("cls");

        cout << endl;
        cout << " ������: ";
        getline(cin, testQuestion.question);
        cout << "\n 1 - �����: ";
        getline(cin, testQuestion.answer_1);
        cout << " 2 - �����: ";
        getline(cin, testQuestion.answer_2);
        cout << " 3 - �����: ";
        getline(cin, testQuestion.answer_3);
        cout << " 4 - �����: ";
        getline(cin, testQuestion.answer_4);
        cout << " ����� ����������� ������: ";
        cin >> testQuestion.trueAnswer;

        questions.push_back(testQuestion);

        cout << "\n ����������?(y/n): ";
        int key = _getch();

        cin.ignore(cin.rdbuf()->in_avail()); // ������� ����� ����� �� ������ ��������

        if (key == 'n')
        {
            break;
        }
    }
}

string TestManagement::GetCurrentTest()
{
    return currentTest;
}

string TestManagement::GetCurrentChapter()
{
    return chapter;
}

TestManagement::TestManagement()
{
    LoadingTestsTree(testsTree, rootCatalog);
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

TestManagement::~TestManagement()
{
}

int TestManagement::PrintMenuTestManagement()
{
    system("cls");

    cout << "\n ���������� �������\n";
    cout << "\n 1 - ������� ���� | 2 - ������������� ���� | 3 - ������� ���� | 4 - ������� ��������� | Esc - �����\n";
    cout << " > ";

    int key = _getch();

    cin.ignore(cin.rdbuf()->in_avail()); // ������� ����� ����� �� ������ ��������

    return key;
}

void TestManagement::StartTestManagement()
{
    int key;

    key = PrintMenuTestManagement();

    switch (key)
    {
        case 49: // 1 Create Test
        {
            int choice = PrintMenuCreateTest();

            switch (choice)
            {
                case 49: // 1
                {
                    CreateChapter();
                    AddTestToMap(InputNameTest());
                    CreateTest();
                    break;
                }
                case 50: // 2
                {
                    system("cls");
                    cout << "\n ������� ����\n";
                    ChoiceChapter();
                    AddTestToMap(InputNameTest());
                    CreateTest();
                    break;
                }
            }
            break;
        }
        case 50: // 2 edit test
        {
            COORD pos;
            int index;

            system("cls");
            cout << "\n ������������� ����";

            pos.X = 0;
            pos.Y = 6;
            SetConsoleCursorPosition(hConsole, pos);
            PrintTestsTree();

            pos.X = 0;
            pos.Y = 2;
            SetConsoleCursorPosition(hConsole, pos);
            ChoiceTest();
            Load load(currentTest);
            load.LoadTest(questions);
            load.CloseFile();

            int key = 0;

            while (key != 27) // esc
            {
                system("cls");

                pos.X = 0;
                pos.Y = 7;
                SetConsoleCursorPosition(hConsole, pos);
                ShowTest();

                pos.X = 0;
                pos.Y = 0;
                SetConsoleCursorPosition(hConsole, pos);
                key = PrintMenuEditTest();

                switch (key)
                {
                    case 49: // 1
                    {
                        AddQuestion();
                        break;
                    }
                    case 50: // 2
                    {
                        DeleteQuestion();
                        break;
                    }
                default:
                    break;
                }
            }

            Save save(currentTest);
            save.SaveTest(questions);
            save.CloseFile();
            break;
        }
        case 51: // 3 Delete Test
        {
            DeleteTest();
            break;
        }
        case 52: // 4 Delete chapter
        {
            DeleteChapter();
            break;
        }
        default:
            break;
    }
}
