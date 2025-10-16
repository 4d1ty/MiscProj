#include <iostream>
#include <string>
#include <vector>
#include "todo.hpp"
#include "utils.hpp"

TodoApp::TodoApp() : store{ "store.txt" } { this->load(); }

void TodoApp::start() {
	std::cout << "AMCTD" << "\n";
	std::cout << "=====" << "\n";
	std::cout <<
		"OPTIONS:\n"
		" - [A]DD TODO <TEXT>\n"
		" - [L]IST TODO\n"
		" - [R]EMOVE TODO <IDX>\n"
		" - [S]AVE\n"
		" - [H]ELP\n"
		" - [Q]UIT\n"

		<< "\n";
	std::string prompt;
	bool isRunning = true;
	while (isRunning) {
		std::cout << "> ";
		std::getline(std::cin, prompt);
		if (prompt.empty()) std::cout << "[ERROR] PROMPT IS EMPTY\n";
		switch (tolower(prompt[0])) {
		case 'a':
		{
			this->addTodo(prompt.substr(2));
			break;
		}
		case 'r':
		{
			this->removeTodo(atoi(prompt.substr(2).c_str()));
			break;
		}
		case 'l':
		{
			this->listTodo();
			break;
		}
		case 's':
		{
			this->save();
			std::cout << "[SUCCESS] SAVED\n";
			break;
		}
		case 'h':
		{
			std::cout <<
				"OPTIONS:\n"
				" - [A]DD TODO <TEXT>\n"
				" - [L]IST TODO\n"
				" - [R]EMOVE TODO <IDX>\n"
				" - [R]EMOVE TODO <IDX>\n"
				" - [H]ELP\n"
				" - [Q]UIT\n"

				<< "\n";
			break;
		}
		case 'q':
		{
			this->save();
			isRunning = false;
			std::cout << "[SUCCESS] GOODBYE";
			break;
		}
		default:
		{
			std::cout << "[ERROR] UNKNOWN COMMAND\n";
		}
		}
	}
}


void TodoApp::addTodo(const std::string& todo) {
	if (todo.size() > 0) {
		todos.push_back(todo);
		std::cout << "[SUCCESS] TODO ADDED\n";
	}
	else {
		std::cout << "[ERROR] TEXT CANNOT BE EMPTY\n";
	}
}

void TodoApp::removeTodo(int const idx) {
	if (idx >= 0 && idx < todos.size()) {
		todos.erase(todos.begin() + idx);
		std::cout << "[SUCCESS] TODO REMOVED\n";

	}
	else {
		std::cout << "[ERROR] OUT OF BOUNDS IDX\n";
	}
}

void TodoApp::listTodo() {
	if (todos.size()) {

		for (int idx = 0; idx < todos.size(); idx++)
		{
			std::cout << "[" << idx << "] " << todos.at(idx) << "\n";
		}
	}
	else {
		std::cout << "[WARN] NO TODOS\n";
	}
}

void TodoApp::load() {
	auto linesOpt = this->store.readLines();
	if (linesOpt != std::nullopt) {
		todos = *linesOpt;
	}
}

void TodoApp::save() {
	this->store.clear();
	this->store.writeList(this->todos);
}