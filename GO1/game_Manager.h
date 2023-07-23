#pragma once
#include <iostream>
#include "Board.h"
#include "Pair.h"

class game_Manager
{
private:
	bool player1_pass = false;
	bool player2_pass = false;

	size_t step_count = 0;

	Board board;

	int alpha = INT16_MIN;
	int beta = INT16_MAX;
	int max_level = 3;
	Pair best_step;
public:
	game_Manager()
	{}    
	void start()
	{
		while (!(player1_pass && player2_pass))
		{
			new_step();
		}
		int result = board.calc_result();
		if (result + 5 > 0)
			std::cout << "AI win with score: " << result + 5 << "!\n";
		else if (result + 5 < 0)
			std::cout << "Player win with score: " << ((result + 5) * -1) << "!\n";
		else
			std::cout << "Пame ended in a draw!\n";

		return;
	}

	void new_step()
	{
		if ((step_count % 2) == 0)   //0 - игрок-человек   1 - игрок-компьютер
			player_step();
		else
			bot_step();
		step_count++;
	}

	void player_step()
	{
		board.update_avaliable_step(1);
		player1_pass = false;
		board.print();

		int i, j;
		while (true)
		{
			print_step_ui();
			while (true)
			{
				std::cin >> i;
				if (!std::cin.good() || i < 0 || i > 10)
				{
					std::cin.clear();
					std::cin.ignore(200000, '\n');
					std::cout << "Uncorrect value, try again!\n";
				}
				else
					break;
			}
			while (true)
			{
				std::cin >> j;
				if (!std::cin.good() || j < 0 || j > 10)
				{
					std::cin.clear();
					std::cin.ignore(200000, '\n');
					std::cout << "Uncorrect value, try again!\n";
				}
				else
					break;
			}
			//Выход из игры      
			if (i == 10 && j == 10)
			{
				exit(0);
			}
			//Пасс   
			else if (i == 0 && j == 0)
			{
				player1_pass = true;
				return;
			}
			//Поставить камень
			else
			{
				if (board.chek_step_avaliable(i - 1, j - 1))
				{
					board.step(i - 1, j - 1, 1);
					break;
				}
				else
				{
					std::cout << "You cant step into this cell\n";
					continue;
				}
			}
		}
	}


	void bot_step()
	{
		board.update_bord_score();
		board.update_avaliable_step(2);
		AlphaBeta(board, 0, alpha, beta);
		board.step(best_step.firts, best_step.second, 2);

		if (best_step.firts == 0 && best_step.second == 0)
		{
			std::cout << "Bot pass!\n";
			return;
		}
	}

	int AlphaBeta(Board board, int level, int alpha, int beta)
	{
		if (level == 0)
		{
			if (board.avaliable_step.empty())               //Если у бота нет ходов
			{
				best_step.firts = 0;
				best_step.second = 0;
				player2_pass = true;
				return 0;
			}
			if (player1_pass == true && (board.calc_result() + 5 > 0))   //Если бот может выйграть закончив игру
			{
				best_step.firts = 0;
				best_step.second = 0;
				player2_pass = true;
				return 0;
			}

		}
		if (level == max_level)
		{
			return board.get_score();
		}
		int max_min_eval;

		if (level % 2 == 0)       // n принадлежит уровню max
		{
			max_min_eval = INT16_MIN;
			for (size_t i = 0; i < board.avaliable_step.size(); i++)
			{
				if (beta < alpha)
					break;
				if (max_min_eval >= beta)
					break;
				Board fake_board(board);
				fake_board.step(board.avaliable_step[i].firts, board.avaliable_step[i].second, 2);
				int max_min = AlphaBeta(fake_board, level + 1, alpha, beta);
				if (level == 0 && max_min > max_min_eval)
				{
					best_step.firts = board.avaliable_step[i].firts;
					best_step.second = board.avaliable_step[i].second;
				}
				max_min_eval = std::max(max_min_eval, max_min);
				alpha = std::max(max_min_eval, alpha);
			}
		}
		else                   // n принадлежит уровню min
		{
			max_min_eval = INT16_MAX;
			board.update_avaliable_step(1);
			for (size_t i = 0; i < board.avaliable_step.size(); i++)
			{
				if (beta < alpha)
					break;
				if (max_min_eval <= alpha)
					break;
				Board fake_board(board);
				fake_board.step(board.avaliable_step[i].firts, board.avaliable_step[i].second, 1);

				int max_min = AlphaBeta(fake_board, level + 1, alpha, beta);

				max_min_eval = std::min(max_min_eval, max_min);
				beta = std::min(max_min_eval, beta);
			}
		}
		return max_min_eval;
	}
	void print_step_ui()
	{
		std::cout << "Your turn!\n";
		std::cout << "(Enter step coords in format x[enter]y[enter], enter 0[enter]0[enter] if you want pass, if you want close game enter 10[enter]10[enter]\n";
	}
};
