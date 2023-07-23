#include <iostream>
#include "Game_Manager.h"

//Вывод игровых правил на экран
void print_rules();

//Функция main реализует главное меню игры
//(запускает игровую сессию, показывает правила, закрывает игру)
int main()
{
    while (true)
    {
        std::cout << "\n\n_____GAME__MENU____________________\n\n";
        std::cout << "(Enter one of the provided numbers)\n\n";
        std::cout << "1 - PLAY!\n\n";
        std::cout << "2 - RULES?\n\n";
        std::cout << "3 - CLOSE GAME.\n\n";
        size_t command = 0;
        while (true)
        {
            std::cin >> command;
            if (!std::cin.good())
            {
                std::cin.clear();
                std::cin.ignore(200000, '\n');
                std::cout << "Unknown command!\n";
            }
            else
                break;
        }
        switch (command)
        {
        case 1:                                            //Запуск игровой сессии
        {
            game_Manager game;
            game.start();
            break;
        }

        case 2:                                            //Вывод правил
        {
            print_rules();
            break;
        }

        case 3:                                            //Выход из игры
            return 0;

        default:
        {
            std::cout << "Unknown command!\n";
            continue;
            break;
        }
        }
    }
}
void print_rules()
{
    std::cout << "_____RULES_______________\n";
    std::cout << "(In progress)\n";
}
