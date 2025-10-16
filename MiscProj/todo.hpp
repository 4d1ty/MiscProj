#pragma once
#include <vector>
#include <string>

#include "SimpleFile.hpp"


// Type alias
using todos_t = std::vector<std::string>;

///<summary>
/// Aditya Mini Console To - Do.
///</summary>
class TodoApp {
private:
	/// <summary>
	/// Todo entries in the memory
	/// </summary>
	todos_t todos;
	/// <summary>
	/// Creates a SimpleFile object associated with the file "store.txt".
	/// </summary>
	SimpleFile store;
	void load();
	void save();
public:

	TodoApp();

	/// <summary>
	/// Starts the interactive TODO list application, displaying options and processing user commands.
	/// </summary>
	void start();
	
	/// <summary>
	/// Add a todo to the bottom for the vector todos
	/// </summary>
	/// <param name="todo"></param>
	void addTodo(const std::string&);
	
	/// <summary>
	/// Removes the todo from the todos via the idx
	/// </summary>
	/// <param name="todos"></param>
	/// <param name="idx"></param>
	void removeTodo(int const);
	
	/// <summary>
	/// Lists all the todos in the entry
	/// </summary>
	/// <param name="todos"></param>
	void listTodo();
};

