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
	TodoApp();
	~TodoApp();
	void run();

private:
	std::vector<Todo> todos;
	unsigned short input;
	unsigned short selectedTodo = 0;
	short editingTodo = -1;
	bool stopped = false;

private:
	void draw();
	void normalModeAction();
	void editModeAction();
	void drawTodos();
};