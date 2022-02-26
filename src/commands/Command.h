#pragma once
#include <string>
#include <vector>
#include <map>

namespace psgui::commands {
	class Command {
		protected:
			std::string id;

		public:
			Command(std::string id): id(id){}
			virtual ~Command(){}

			std::string getId() {return this->id;}
			virtual bool execute(std::vector<std::string> args = {}) = 0;
			virtual std::string getHelp() = 0;
	};
}
