#pragma once
class Character;

enum class InputType {
	Press, 
	Down,
	Release
};

class Command {
public:
	virtual ~Command() = default;
	virtual void execute(Character& character) = 0;
};

// concrete command
class MoveLeftCommand : public Command {
public:
	void execute(Character& character) override;
};

class MoveRightCommand : public Command {
public:
	void execute(Character& character) override;
};

class RunFasterCommand : public Command {
public:
	void execute(Character& character) override;
};
class JumpCommand : public Command {
public:
	void execute(Character& character) override;
};

class DuckCommand : public Command {
public:
	void execute(Character& character) override;
};
// throw
class FireCommand : public Command {
public:
	void execute(Character& character) override;
};

class StandingCommand : public Command {
public:
	void execute(Character& character) override;
};

class ShortHopReleaseCommand : public Command {
public:
	void execute(Character& character) override;
};

class ReleaseRunFastCommand : public Command {
public:
	void execute(Character& character) override;
};