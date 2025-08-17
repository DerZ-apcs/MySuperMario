#pragma once
#include <unordered_map>
#include "Command.h"
#include "raylib.h"
#include <vector>
#include "Character.h"

struct KeyBinding {
	int key;
	InputType type;
	Command* command;
};

class InputHandler {
	std::vector<KeyBinding> bindings;
	Command* defaultCommand = nullptr;
public:
	void bindKey(int key, InputType type ,Command* command) {
		bindings.push_back({ key, type, command });
	}
	// set a default command for "no input"
	void setDefaultCommand(Command* command) {
		defaultCommand = command;
	}
	void handleInput(Character& character) {
		bool anyTriggered = false;
		for (auto& binding : bindings) {
			bool triggered = false;
			switch (binding.type) {
				case InputType::Press: triggered = IsKeyPressed(binding.key); break;
				case InputType::Down: triggered = IsKeyDown(binding.key); break;
				case InputType::Release: triggered = IsKeyReleased(binding.key); break;
			}
			if (triggered) {
				binding.command->execute(character);
				anyTriggered = true;
			}
		}
		if (!anyTriggered && defaultCommand) {
			defaultCommand->execute(character);
		}
	}
};