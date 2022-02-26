#pragma once
#include "CommandWindow.h"

namespace psgui::commands {
	class HelpCommand: public Command {
		std::map<std::string,Command*>* commands;
		public:
		HelpCommand(std::map<std::string,Command*>* commands): Command("help") {
			this->commands = commands;
		}

		bool execute(std::vector<std::string> args = {}) {
			if(args.size() > 1) {
				CommandWindow::addError("help command does not take parameters");
				return false;
			}
			CommandWindow::addOutput("List of commands:");
			for(auto command: *this->commands) {
				CommandWindow::addOutput(command.second->getHelp());
			}
			return true;
		}
		std::string getHelp() {
			return this->id + ": displays help text";
		};

	};
}
