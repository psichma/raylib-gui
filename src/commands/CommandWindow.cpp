#include "CommandWindow.h"
#include "raylib.h"
#include "HelpCommand.h"

namespace psgui::commands {
	std::vector<CommandWindow::OutputEntry> CommandWindow::output = std::vector<CommandWindow::OutputEntry>();
	CommandWindow::CommandWindow(unsigned int width) {
		this->state = State::CLOSED;
		this->max_height = 200;
		this->movement_speed = 1000.f;
		this->current_text = "";
		this->cmd_history_cursor = 0;
		this->window_width = width;

		this->window.setPosition({0.f,0.f});
		this->window.setSize({(float)this->window_width,0.f});
		this->window.setFillColor({ 130, 130, 130, 90 });
		this->addCommand(new HelpCommand(&this->commands));
	}
	CommandWindow::~CommandWindow() {
		for(auto cmd : this->commands) delete cmd.second;
	}

	void CommandWindow::open() {
		if(this->state == State::OPEN) return;
		if(this->state != State::OPENING) this->state = State::OPENING;
	}

	void CommandWindow::close() {
		if(this->state == State::CLOSED) return;
		if(this->state != State::CLOSING) this->state = State::CLOSING;
	}

	void CommandWindow::toggle() {
		if(this->state == State::OPEN || this->state == State::OPENING) this->close();
		else if(this->state == State::CLOSED || this->state == State::CLOSING) this->open();
	}

	void CommandWindow::update() {
		float current_size = this->window.getHeight();
		if(this->state == State::OPENING) {
			current_size += movement_speed * GetFrameTime();
			if(current_size >= max_height) {
				current_size = max_height;
				state = State::OPEN;
			}
			this->window.setHeight(current_size);
		}
		if(state == State::CLOSING) {
			current_size -= movement_speed * GetFrameTime();
			if(current_size <= 0){
				current_size = 0;
				state = State::CLOSED;
			}
			this->window.setHeight(current_size);
		}
		if(this->hasFocus()) {
			// if mouse out of window and clicked, close
			if(IsMouseButtonReleased(0)) {
				Vector2 mouse = GetMousePosition();
				if(mouse.y > this->window.getHeight()) {
					this->close();
					return;
				}
			}

			if(IsKeyPressed(KEY_ESCAPE)) {
				this->close();
				this->current_text.clear();
			}
			if(IsKeyReleased(KEY_BACKSPACE)) {
				if(!this->current_text.empty())
					this->current_text.erase(this->current_text.size() - 1);
			}
			if(IsKeyReleased(KEY_ENTER)) {
				this->applyCommand(this->current_text);
				this->current_text.clear();
			}

			size_t cmd_history_size = cmd_history.size();

			if(IsKeyReleased(KEY_UP) && cmd_history_size != 0) {
				if(this->cmd_history_cursor != 0) {
					this->cmd_history_cursor--;
				}
				this->current_text = cmd_history[cmd_history_cursor];
			}

			if(IsKeyReleased(KEY_DOWN) && this->cmd_history_cursor < cmd_history_size) {
				this->cmd_history_cursor++;
				if(this->cmd_history_cursor >= cmd_history_size) {
					this->cmd_history_cursor = cmd_history_size - 1;
				}
				this->current_text = cmd_history[cmd_history_cursor];
			}

			char c = GetCharPressed();
			if(c != 0) {
				this->current_text += c;
			}

		}

	}

	void CommandWindow::addCommand(Command* command) {
		this->commands.insert(std::pair<std::string,Command*>(command->getId(), command));
	}

	void CommandWindow::applyCommand(std::string command) {
		CommandWindow::addOutput(command);
		if(command == "") return;
		this->cmd_history.push_back(command);
		this->cmd_history_cursor = cmd_history.size();


		std::vector<std::string> args;
		int max_tries = 20;
		int tries = 0;
		while(true){
			size_t space_pos  = command.find(' ');
			if(space_pos == std::string::npos) {
				if(command != " ")
					args.push_back(command);
				break;
			}
			args.push_back(command.substr(0, space_pos));
			command.erase(0, space_pos + 1);
			tries++;
			if(tries >= max_tries) {
				CommandWindow::addError("could not parse command and arguments..");
				return;
			}
		};

		std::string cmd = args[0];


		// simple build int commands
		if(cmd == "clear") {
			this->output.clear();
			return;
		}

		if(cmd == "exit") {
			this->close();
			return;
		}

		// find command and execute
		if(this->commands.find(cmd) != this->commands.end()) {
			if(!this->commands[cmd]->execute(args)) {
				CommandWindow::addError("command failed");
			}
		}
		else {
			CommandWindow::addError("ERROR: command \'" + args[0] + "\' does not exist");
		}
	}

	void CommandWindow::addOutput(std::string output_str, Color color) {
		CommandWindow::output.push_back(OutputEntry(output_str, color));
	}

	void CommandWindow::addError(std::string error_str) {
		CommandWindow::addOutput(error_str, RED);
	}

	void CommandWindow::addSuccess(std::string success_str) {
		CommandWindow::addOutput(success_str, LIME);
	}

	void CommandWindow::render() const {
		float current_size = this->window.getHeight();
		if(current_size > 0) {
			this->window.render();
			//DrawRectangle(0, 0, WINDOW_WIDTH, current_size, { 130, 130, 130, 90 });

			// render output
			int outidx = 0;
			for(int i = CommandWindow::output.size() - 1; i >= 0; i--) {
				OutputEntry e = CommandWindow::output[i];
				float target_y = current_size - (30 * (outidx++ + 1));
				if(target_y < -30) break;
				DrawText(e.text.c_str(), 0, target_y, 30, e.color);
			}

			// render textwindow
			float text_window_size = 30;
			DrawRectangle(0, current_size, this->window_width, text_window_size, {255,0,0,90});
			DrawText(current_text.c_str(), 0, current_size, 30, RAYWHITE);
		}
	}
}
