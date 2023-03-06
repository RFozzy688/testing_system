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

    cout << "\n Дерево тестов:\n";

    for (auto it_chapters : testsTree)
    {
        cout << " Раздел: \n";
        cout << "  " << countChapter++ << ". " << it_chapters.first.substr(it_chapters.first.rfind("\\") + 1) << endl;
        cout << " Тесты:\n";

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

    cout << "\n Создать тест\n";
    cout << "\n 1 - Создать раздел | 2 - Выбрать существующий\n";
    cout << " > ";

    int key = _getch();

    cin.ignore(cin.rdbuf()->in_avail()); // очищаем поток ввода от лишних символов

    return key;
}

void TestManagement::CreateChapter()
{
    while (true)
    {
        system("cls");

        string newChapter;

        cout << "\n Создать тест\n";
        cout << "\n Название раздела: ";
        getline(cin, newChapter);

        if (IsChapter(newChapter))
        {
            cout << " Раздел " + newChapter + " существует.\n";
            cout << " Создать тест в этом разделе?(y/n)";
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
        cout << count++ << ". Вопрос: ";
        getline(cin, testQuestion.question);
        cout << "\n 1 - Ответ: ";
        getline(cin, testQuestion.answer_1);
        cout << " 2 - Ответ: ";
        getline(cin, testQuestion.answer_2);
        cout << " 3 - Ответ: ";
        getline(cin, testQuestion.answer_3);
        cout << " 4 - Ответ: ";
        getline(cin, testQuestion.answer_4);
        cout << " Номер правильного ответа: ";
        cin >> testQuestion.trueAnswer;

        questions.push_back(testQuestion);

        cout << "\n Продолжить?(y/n): ";
        int key = _getch();

        cin.ignore(cin.rdbuf()->in_avail()); // очищаем поток ввода от лишних символов

        if (key == 'n')
        {
            break;
        }
    }

    cout << "\n Сохранить?(y/n): ";
    int key = _getch();

    cin.ignore(cin.rdbuf()->in_avail()); // очищаем поток ввода от лишних символов

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

        cout << "\n Создать тест\n";
        cout << "\n Название теста: ";
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

        cout << " Номер раздела: ";
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

    cin.ignore(cin.rdbuf()->in_avail()); // очищаем поток ввода от лишних символов
}

void TestManagement::ChoiceTest()
{
    int numberChapter;
    //int numberTest;
    COORD pos;

    cout << "\n Номер раздела: ";

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

        cout << " Номер теста: ";
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

        cout << "\n Удаление теста\n";

        ChoiceTest();
        map<string, vector<string>>::iterator iter_map = testsTree.find(chapter);
        vector<string>::iterator iter_vec = iter_map->second.begin() + numberTest;

        filesystem::remove(*iter_vec);
        iter_map->second.erase(iter_vec);

        system("cls");

        cout << "\n Тест удален\n";

        pos.X = 0;
        pos.Y = 7;
        SetConsoleCursorPosition(hConsole, pos);

        PrintTestsTree();

        pos.X = 0;
        pos.Y = 6;
        SetConsoleCursorPosition(hConsole, pos);

        cout << " Продолжить удаление?(y/n): ";
        int key = _getch();
        cin.ignore(cin.rdbuf()->in_avail()); // очищаем поток ввода от лишних символов

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

        cout << "\n Удаление раздела\n";

        ChoiceChapter();
        map<string, vector<string>>::iterator iter = testsTree.find(chapter);

        filesystem::remove_all(iter->first);
        testsTree.erase(iter);
        chapter.clear();

        system("cls");

        cout << "\n Раздел удален\n";

        pos.X = 0;
        pos.Y = 7;
        SetConsoleCursorPosition(hConsole, pos);

        PrintChapter();

        pos.X = 0;
        pos.Y = 4;
        SetConsoleCursorPosition(hConsole, pos);

        cout << " Продолжить удаление?(y/n): ";
        int key = _getch();
        cin.ignore(cin.rdbuf()->in_avail()); // очищаем поток ввода от лишних символов

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

    cout << "\n Управление тестами\n";
    cout << "\n 1 - Создать тест | 2 - Редактировать тест | 3 - Удалить тест | 4 - Удалить категорию";
    cout << "\n 5 - Пароль | 6 - Адрес | 7 - Телефон | Esc - Выход\n";
    cout << " > ";

    int key = _getch();

    cin.ignore(cin.rdbuf()->in_avail()); // очищаем поток ввода от лишних символов

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
                    cout << "\n Создать тест\n";
                    ChoiceChapter();
                    AddTestToMap(InputNameTest());
                    CreateTest();
                    break;
                }
            }
            break;
        }
        case 50: // 2 
        {
            
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
        case 53: // 5
        {

            break;
        }
        case 54: // 6
        {
   
            break;
        }
        case 55: // 7
        {

            break;
        }
        default:
            break;
    }
}
