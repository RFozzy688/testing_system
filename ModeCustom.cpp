#include "ModeCustom.h"

void ModeCustom::ClearScreen(COORD pos)
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

ModeCustom::ModeCustom(User* user)
{
    this->user = user;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    userGrade = { };

    Load load(user->GetPathStat());
    load.LoadingUserStat(userStat);
    load.CloseFile();
}

ModeCustom::~ModeCustom()
{
    if (user)
    {
        delete user;
    }
}

void ModeCustom::StartMode()
{
    int key = 0;

    while (key != 27)
    {
        key = PrintMainMenu();

        switch (key)
        {
        case 49: // 1
        {
            TestManagement obj;

            system("cls");

            COORD pos;

            pos.X = 0;
            pos.Y = 6;
            SetConsoleCursorPosition(hConsole, pos);
            obj.PrintTestsTree();

            pos.X = 0;
            pos.Y = 0;
            SetConsoleCursorPosition(hConsole, pos);

            cout << "\n Тестирование\n";

            obj.ChoiceTest();

            fullNameTest = obj.GetCurrentTest();
            fullNameChapter = obj.GetCurrentChapter();
            Load load(fullNameTest);
            load.LoadTest(questions);
            load.CloseFile();

            Testing();
            ResultTest();
            PrintResult();
            UpdateStat();

            Save save(user->GetPathStat());
            save.SavingUserStat(userStat);
            save.CloseFile();
            _getch();
            break;
        }
        case 50: // 2
        {
            break;
        }
        default:
            break;
        }
    }
}

int ModeCustom::PrintMainMenu()
{
    system("cls");

    cout << "\n Режим тестирования\n";
    cout << "\n 1 - Тестирование | 2 - Результаты | Esc - Выход\n";
    cout << " > ";

    int key = _getch();

    cin.ignore(cin.rdbuf()->in_avail()); // очищаем поток ввода от лишних символов

    return key;
}

void ModeCustom::Testing()
{
    int answer;
    int count = 1;
    COORD pos;

    userAnswer.clear();

    for (auto it : questions)
    {
        system("cls");

        int countAnswer = 1;

        cout << endl << count++ << ". Вопрос: " << it.question << endl << endl;
        cout << "  " << countAnswer++ << " " << it.answer_1 << endl;
        cout << "  " << countAnswer++ << " " << it.answer_2 << endl;
        cout << "  " << countAnswer++ << " " << it.answer_3 << endl;
        cout << "  " << countAnswer++ << " " << it.answer_4 << endl << endl;

        cout << " Номер ответа: ";

        while (true)
        {
            cin >> answer;

            if (cin.fail() || answer < 1 || answer > 4)
            {
                cin.clear();
                cin.ignore();

                pos.X = 15;
                pos.Y = 8;
                ClearScreen(pos);
                SetConsoleCursorPosition(hConsole, pos);
                continue;
            }
            else
            {
                break;
            }
        }

        userAnswer.push_back(answer);
    }
}

void ModeCustom::ResultTest()
{
    float countTrueAnswer = 0;
    float countQuestions = questions.size();
    float grade = 0;

    vector<int>::iterator iter_result = userAnswer.begin();

    for (auto it : questions)
    {
        if (it.trueAnswer == *iter_result)
        {
            countTrueAnswer++;
            iter_result++;
        }
    }

    grade = (countTrueAnswer / countQuestions) * 12;
    userGrade.grade = round(grade);
    userGrade.countTrueAnswer = countTrueAnswer;
    userGrade.percentTrueAnswer = (countTrueAnswer / countQuestions) * 100;

    userGrade.nameChapter = fullNameChapter.substr(fullNameChapter.rfind("\\") + 1);

    int start = fullNameTest.rfind("\\") + 1;
    int end = fullNameTest.rfind(".");

    userGrade.nameTest = fullNameTest.substr(start, end - start);
}

void ModeCustom::PrintResult()
{
    system("cls");

    cout << "\n Название категории:            " << userGrade.nameChapter;
    cout << "\n Название теста:                " << userGrade.nameTest;
    cout << "\n Количество правильных ответов: " << userGrade.countTrueAnswer;
    cout << "\n Процент правильных ответов:    " << userGrade.percentTrueAnswer << "%";
    cout << "\n Оценка:                        " << userGrade.grade << endl;
}

void ModeCustom::UpdateStat()
{

    int count = 0;

    if (userStat.empty())
    {
        userStat.push_back(userGrade);
    }
    else
    {
        for (auto it = userStat.begin(); it != userStat.end(); it++)
        {
            if (it->nameChapter == userGrade.nameChapter && it->nameTest == userGrade.nameTest)
            {
                it->countTrueAnswer = userGrade.countTrueAnswer;
                it->percentTrueAnswer = userGrade.percentTrueAnswer;
                it->grade = userGrade.grade;

                break;
            } 

            count++;
        }

        if (count == userStat.size())
        {
            userStat.push_back(userGrade);
        }
    }
}
