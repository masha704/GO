#pragma once
#include "Cell.h"
#include "my_Vector.h"
#include "Pair.h"
#include <iostream>

class Board
{
private:
	Cell cur_board[9][9];
	Cell chek_avaliable_steps[9][9];
	Cell prev_board[9][9];
	long int board_score = 0;
	int game_score = 0;
public:
	my_Vector<Pair> avaliable_step;

	bool chek_step_avaliable(size_t i, size_t j) {
		for (size_t _i = 0; _i < avaliable_step.size(); _i++) {
			if (i == avaliable_step[_i].firts && j == avaliable_step[_i].second) return true;
		}
		return false;
	}

	bool update_avaliable_step(size_t who_step) {
		avaliable_step.clear();
		for (size_t i = 0; i < 9; i++) {
			for (size_t j = 0; j < 9; j++) {
				if (cur_board[i][j].get_stat() != 0) continue;
				for (size_t k = 0; k < 9; k++) {
					for (size_t l = 0; l < 9; l++) {
						chek_avaliable_steps[k][l].set_status(cur_board[k][l].get_stat());
					}
				}
				chek_avaliable_steps[i][j].set_status(who_step);
				update_check(who_step);

				int count = 0;
				for (size_t k = 0; k < 9; k++) {
					for (size_t l = 0; l < 9; l++) {
						if (chek_avaliable_steps[k][l].get_stat() != prev_board[k][l].get_stat())
							break;
						if (chek_avaliable_steps[k][l].get_stat() == prev_board[k][l].get_stat())
							count++;
					}
				}

				if (count == 81) continue;
				for (size_t k = 0; k < 9; k++)
				{
					for (size_t l = 0; l < 9; l++)
					{
						chek_avaliable_steps[k][l].set_status(cur_board[k][l].get_stat());
					}
				}
				chek_avaliable_steps[i][j].set_status(who_step);
				update_check(who_step);
				if (chek_avaliable_steps[i][j].get_stat() == 0) continue;
				avaliable_step.push_back(Pair(i, j));
			}
		}
		return !avaliable_step.empty();
	}

	void update_check(int who_step) {
		my_Vector<Pair> surround_cells;
		if (who_step == 1) {
			for (size_t i = 0; i < 9; i++)
			{
				for (size_t j = 0; j < 9; j++) {
					if (chek_avaliable_steps[i][j].get_stat() == 2) {
						surround_cells.clear();
						check_surround_group(i, j, 2, 0, &surround_cells, true);
					}
				}
			}

			for (size_t i= 0; i < 9; i++) {
				for (size_t j = 0; j < 9; j++) {
					if (chek_avaliable_steps[i][j].get_stat() == 1) {
						surround_cells.clear();
						check_surround_group(i, j, 1, 0, &surround_cells, true);
					}
				}
			}
		}
		else {
			for (size_t i = 0; i < 9; i++) {
				for (size_t j = 0; j < 9; j++) {
					if (chek_avaliable_steps[i][j].get_stat() == 1)
					{
						surround_cells.clear();
						check_surround_group(i, j, 1, 0, &surround_cells, true);
					}
				}
				for (size_t i = 0; i < 9; i++)
				{
					for (size_t j = 0; j < 9; j++)
					{
						if (chek_avaliable_steps[i][j].get_stat() == 2)
						{
							surround_cells.clear();
							check_surround_group(i, j, 2, 0, &surround_cells, true);
						}
					}
				}
			}
		}
	}

	void update_board(int who_step) {
		my_Vector<Pair> surround_cells;

		if (who_step == 1) {
			for (size_t i = 0; i < 9; i++) {
				for (size_t j = 0; j < 9; j++) {
					if (cur_board[i][j].get_stat() == 2) {
						surround_cells.clear();
						check_surround_group(i, j, 2, 0, &surround_cells, false);
					}
				}
			}
		}
		else
		{
			for (size_t i = 0; i < 9; i++)
			{
				for (size_t j = 0; j < 9; j++)
				{
					if (cur_board[i][j].get_stat() == 1)
					{
						surround_cells.clear();
						check_surround_group(i, j, 1, 0, &surround_cells, false);
					}
				}
			}
		}
	}
	bool check_surround_group(size_t _i, size_t _j, size_t status, size_t level, my_Vector<Pair>* surround_cells, bool check)
	{
		//Если кол-во дыханий больше нуля, группа не снимается с доски
		bool num_of_breeze_more_then_null = false;
		(*surround_cells).push_back(Pair(_i, _j));

		//Перебираем все соседние клетки
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				//Не смежные клетки, сама клетка
				if (i * i == j * j)
					continue;
				int new_x = _i + i;
				int new_y = _j + j;
				//Выход за пределы доски
				if (new_x > 8 || new_x < 0 || new_y > 8 || new_y < 0)
					continue;
				if (check)
				{
					if (chek_avaliable_steps[new_x][new_y].get_stat() == status && !contain(surround_cells, Pair(new_x, new_y)))
					{
						(*surround_cells).push_back(Pair(new_x, new_y));
						if (check_surround_group(new_x, new_y, status, level + 1, surround_cells, check))
							return true;
					}

					if (chek_avaliable_steps[new_x][new_y].get_stat() == 0)
					{
						return true;
					}
				}
				else
				{
					if (cur_board[new_x][new_y].get_stat() == status && !contain(surround_cells, Pair(new_x, new_y)))
					{
						(*surround_cells).push_back(Pair(new_x, new_y));
						if (check_surround_group(new_x, new_y, status, level + 1, surround_cells, check))
							return true;
					}

					if (cur_board[new_x][new_y].get_stat() == 0)
						return true;
				}
			}
		}
		//Снимаем все камни окруженной группы на уровне корня после работы всего алгоритма
		if (check)
		{
			if (level == 0 && !num_of_breeze_more_then_null)
			{
				for (size_t i = 0; i < (*surround_cells).size(); i++)
				{
					chek_avaliable_steps[(*surround_cells)[i].firts][(*surround_cells)[i].second].set_status(0);
				}
			}
		}
		else
		{
			if (level == 0 && !num_of_breeze_more_then_null)
			{
				for (size_t i = 0; i < (*surround_cells).size(); i++)
				{
					cur_board[(*surround_cells)[i].firts][(*surround_cells)[i].second].set_status(0);
				}
			}
		}
		return false;
	}
	bool contain(my_Vector<Pair>* surround_cells, Pair data)
	{
		for (size_t i = 0; i < (*surround_cells).size(); i++)
		{
			if (((*surround_cells)[i].firts == data.firts) && ((*surround_cells)[i].second == data.second))
				return true;
		}
		return false;
	}
	void step(size_t _i, size_t _j, size_t status)
	{
		//Записываем текущее состояние доски как предыдущее(для правила КО)
		for (size_t i = 0; i < 9; i++)
		{
			for (size_t j = 0; j < 9; j++)
			{
				prev_board[i][j].set_status(cur_board[i][j].get_stat());
			}
		}
		//Модифицируем состояние(делаем ход)
		cur_board[_i][_j].set_status(status);
		update_board(status);
	}
	//Вычисление функции оценки
	void update_bord_score()
	{
		//Обнуляем оценку
		board_score = 0;
		size_t status;

		//Перебираем все клетки доски
		for (size_t i = 0; i < 9; i++)
		{
			for (size_t j = 0; j < 9; j++)
			{
				//Получаем статус клетки
				status = cur_board[i][j].get_stat();
				//Смотрим на ее состояние
				switch (status)
				{
				case 0:
				{
					size_t _status;
					if ((i + 1) < 9)
					{
						_status = cur_board[i + 1][j].get_stat();
						if (_status == 1)
							board_score--;
						else if (_status == 2)
							board_score++;
					}
					if ((i - 1) >= 0 && (i - 1) < 9)
					{
						_status = cur_board[i - 1][j].get_stat();
						if (_status == 1)
							board_score--;
						else if (_status == 2)
							board_score++;
					}
					if ((j + 1) < 9)
					{
						_status = cur_board[i][j + 1].get_stat();
						if (_status == 1)
							board_score--;
						else if (_status == 2)
							board_score++;
					}

					if ((j - 1) >= 0 && (j - 1) < 9)
					{
						_status = cur_board[i][j - 1].get_stat();
						if (_status == 1)
							board_score--;
						else if (_status == 2)
							board_score++;
					}
					break;
				}
				case 1:
				{
					board_score -= 4;
					break;
				}
				case 2:
				{
					board_score += 4;
					break;
				}
				}
			}
		}
	}
	int calc_result()
	{
		game_score = 0;
		size_t status;
		int count1 = 0;
		int count2 = 0;
		//Перебираем все клетки доски
		for (size_t i = 0; i < 9; i++)
		{
			for (size_t j = 0; j < 9; j++)
			{
				//Получаем статус клетки
				status = cur_board[i][j].get_stat();
				//Смотрим на ее состояние
				switch (status)
				{
				case 0:
				{
					if ((i + 1) < 9)
					{
						status = cur_board[i + 1][j].get_stat();
						if (status == 1)
							count1++;
						else if (status == 2)
							count2++;
					}

					if ((i - 1) >= 0 && (i - 1) < 9)
					{
						status = cur_board[i - 1][j].get_stat();
						if (status == 1)
							count1++;
						else if (status == 2)
							count2++;
					}

					if ((j + 1) < 9)
					{
						status = cur_board[i][j + 1].get_stat();
						if (status == 1)
							count1++;
						else if (status == 2)
							count2++;
					}

					if ((j - 1) >= 0 && (j - 1) < 9)
					{
						status = cur_board[i][j - 1].get_stat();
						if (status == 1)
							count1++;
						else if (status == 2)
							count2++;
					}

					if (count1 == 4)
						game_score--;

					if (count2 == 4)
						game_score++;

					count1 = 0;
					count2 = 0;

					break;
				}
				case 1:
				{
					game_score -= 1;
					break;
				}
				case 2:
				{
					game_score += 1;
					break;
				}
				}
			}
		}
		return game_score;
	}
	int get_game_score()
	{
		return game_score;
	}
	long int get_score()
	{
		update_bord_score();
		return board_score;
	}
	int get_avail_lenght()
	{
		return avaliable_step.size();
	}
	void print()
	{
		std::cout << "\n\n";
		std::cout << "\x1b[38;5;136m  Y   1   2   3   4   5   6   7   8   9\x1b[0m\n";
		std::cout << "\x1b[38;5;136mX\x1b[0m\n\n";
		size_t status;

		for (size_t i = 0; i < 9; i++)
		{
			std::cout << "\x1b[38;5;136m" << i + 1 << "\x1b[0m" << "     ";
			for (size_t j = 0; j < 9; j++)
			{
				status = cur_board[i][j].get_stat();
				switch (status)
				{
				case 0:
					std::cout << " ";
					break;
				case 1:
					std::cout << "\x1b[38;5;46m\4\x1b[0m";
					break;
				case 2:
					std::cout << "\x1b[38;5;124m\4\x1b[0m";
					break;
				default:
					std::cout << "!";
					break;
				}
				if (j != 8) std::cout << "\x1b[38;5;240m---\x1b[0m";
			}
			std::cout << "\n";
			if (i != 8)  std::cout << "\x1b[38;5;240m      |   |   |   |   |   |   |   |   |\x1b[0m" << std::endl;
		}
	}
	//Конструктор копирования
	Board(Board& another_board)
	{
		board_score = another_board.board_score;
		avaliable_step = another_board.avaliable_step;

		for (size_t i = 0; i < 9; i++)
		{
			for (size_t j = 0; j < 9; j++)
			{
				cur_board[i][j] = another_board.cur_board[i][j];
			}
		}
		for (size_t i = 0; i < 9; i++)
		{
			for (size_t j = 0; j < 9; j++)
			{
				prev_board[i][j] = another_board.prev_board[i][j];
			}
		}
	}

	Board()
	{}
};
