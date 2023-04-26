#pragma once

#include <iostream>
#include <vector>

struct Todo
{
	std::string text;
	bool done;
};

class TodoApp
{
public:
	std::vector<Todo> todos;

public:
	TodoApp();
	~TodoApp();
	void run();

private:
	unsigned short input;
	unsigned short selectedTodo = 0;
	short editingTodo = -1;
	bool stopped = false;

private:
	void draw();
	void normalModeAction();
	void editModeAction();
	void drawTodos();
	void loadData();
	void saveData();
};