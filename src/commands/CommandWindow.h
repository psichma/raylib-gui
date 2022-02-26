#pragma once
#include <string>
#include <vector>
#include <map>
#include "Command.h"
#include <raylib.h>
#include "../graphics/Rectangle.h"

namespace psgui::commands {
	class CommandWindow {
		private:
			enum State {
				CLOSED = 0,
				OPENING,
				OPEN,
				CLOSING,
			};

			struct OutputEntry {
				std::string text;
				Color color;
				OutputEntry(std::string text, Color color): text(text), color(color){}
			};

			psgui::graphics::Rectangle window;
			psgui::graphics::Rectangle textbox;

			std::string current_text;
			std::map<std::string,psgui::commands::Command*> commands;
			std::vector<std::string> cmd_history;
			size_t cmd_history_cursor;
			static std::vector<OutputEntry> output;
			int window_width;

		public:
			State state;
			int max_height;
			float movement_speed;

			CommandWindow(unsigned int width);
			~CommandWindow();
			void open();
			void close();
			void toggle();
			void update();
			void render() const;
			void addCommand(psgui::commands::Command* command);
			void applyCommand(std::string command);
			static void addOutput(std::string output_str, Color color = RAYWHITE);
			static void addError(std::string error_str);
			static void addSuccess(std::string success_str);

			bool hasFocus() {
				return this->state == State::OPEN;
			}
	};
}
