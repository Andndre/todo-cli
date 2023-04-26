#include <ncurses.h>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <cerrno>
#include "todo.h"

TodoApp::TodoApp()
{
	initscr();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	init_pair(5, COLOR_BLACK, COLOR_YELLOW);
	loadData();
}
TodoApp::~TodoApp()
{
	saveData();
	endwin();
}

void TodoApp::run()
{
	draw();
	while (!stopped)
	{
		input = getch();
		draw();
	}
}

void TodoApp::draw()
{
	clear();
	if (editingTodo == -1)
		normalModeAction();
	else
		editModeAction();
	drawTodos();
	refresh();
}

void TodoApp::normalModeAction()
{
	switch (input)
	{
	case 'A':
		if (todos.size() > 0 && editingTodo == -1)
		{
			if (selectedTodo == 0)
				selectedTodo = todos.size() - 1;
			else
				selectedTodo--;
		}
		break;
	case 'B':
		if (todos.size() > 0 && editingTodo == -1)
		{
			selectedTodo++;
			if (selectedTodo >= (int)todos.size())
				selectedTodo = 0;
		}
		break;
	case 'd':
		if (editingTodo == -1 && todos.size() > 0)
			todos.erase(todos.begin() + selectedTodo);
		break;
	case '\n':
	case 'x':
	case ' ':
		if (editingTodo == -1)
			todos[selectedTodo].done = !todos[selectedTodo].done;
		break;
	case 'e':
		if (todos.size() > 0)
			editingTodo = selectedTodo;
		break;
	case 'n':
		todos.push_back(Todo{"New Todo", false});
		selectedTodo = todos.size() - 1;
		editingTodo = selectedTodo;
		break;
	case 'q':
		stopped = true;
		return;
	}
}

void TodoApp::editModeAction()
{
	switch (input)
	{
	case '\n':
		editingTodo = -1;
		break;
	case 8: // CTRL + BACKSPACE
		do
		{
			if (!todos[editingTodo].text.empty())
				todos[editingTodo].text.pop_back();
		} while (!todos[editingTodo].text.empty() &&
						 todos[editingTodo].text.back() != ' ');
		break;
	case 127: // BACKSPACE
	case KEY_BACKSPACE:
		if (todos[editingTodo].text.size() > 0)
			todos[editingTodo].text.pop_back();
		break;
	default:
		todos[editingTodo].text += input;
	}
}

void TodoApp::drawTodos()
{
	char done = ' ';

	attron(COLOR_PAIR(4));
	if (todos.size())
	{
		printw("All your todos:\n");
		for (size_t i = 0; i < todos.size(); i++)
		{
			done = todos[i].done ? 'X' : ' ';

			if (i == (size_t)selectedTodo)
				attron(COLOR_PAIR(5));
			else
				attroff(COLOR_PAIR(5));

			printw("[%c] %s\n", done, todos[i].text.c_str());
		}
	}
	else
		printw("No todos!\n");

	attroff(COLOR_PAIR(4));
	attroff(COLOR_PAIR(5));

	attron(COLOR_PAIR(3));
	printw("\nENTER\t toggle done\n");
	printw("n\t create new Todo\n");
	printw("d\t delete Todo\n");
	printw("e\t edit Todo\n");
	printw("q\t quit\n\n");
	attroff(COLOR_PAIR(3));

	attron(COLOR_PAIR(2));
	if (editingTodo == -1)
		printw("NORMAL MODE");
	else
		printw("EDIT MODE");
	attroff(COLOR_PAIR(2));
}

void TodoApp::loadData()
{
	std::ifstream file("data/todos.todo");
	if (file.is_open())
	{
		std::string line;
		while (std::getline(file, line))
		{
			std::string done = line.substr(0, 1);
			todos.push_back(Todo{
					line.substr(2),
					strcmp(done.c_str(), "1") == 0});
		}
		file.close();
	}
	else
	{
		printf("Could not open todos.todo\n");
		saveData();
	}
}

void TodoApp::saveData()
{
	std::ofstream file("data/todos.todo", std::ios::out | std::ios::trunc);
	if (file.is_open())
	{
		for (size_t i = 0; i < todos.size(); i++)
		{
			if (todos[i].done)
				file << "1";
			else
				file << "0";
			file << ':' << todos[i].text << std::endl;
		}
		file.close();
	}
	else
	{
		printf("Could not open todos.todo:\n\t%s\n", strerror(errno));
		exit(1);
	}
}
