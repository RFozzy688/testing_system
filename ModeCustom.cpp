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

            Load load(obj.GetCurrentTest());
            load.LoadTest(questions);
            load.CloseFile();

            Testing();
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

    }

}
