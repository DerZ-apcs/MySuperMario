#include "../include/Command.h"
#include "../include/Character.h"

void MoveLeftCommand::execute(Character& character)
{
	character.RunLeft();
}

void MoveRightCommand::execute(Character& character)
{
	character.RunRight();
}

void JumpCommand::execute(Character& character)
{
	if (character.getState() == ON_GROUND || character.getState() == SINKING)
		character.Jumping();
}

void DuckCommand::execute(Character& character)
{
	if ((character.getState() == ON_GROUND || character.getState() == SINKING) &&
			character.getCharacterType() != MARISA) {
		character.Ducking();
	}
	else {
		character.setDucking(false);
	}
}

void FireCommand::execute(Character& character)
{
	if ((character.getCharacterState() == STATE_FIRE || character.getCharacterState() == STATE_FIRESTAR) 
		&& !character.isDucking()) 
		character.ThrowingFireBalls();
}

void ShortHopReleaseCommand::execute(Character& character)
{
	if (character.getState() == JUMPING && character.getVelY() < 0)
		character.setVelY(character.getVelY() * 0.5f);
}

void StandingCommand::execute(Character& character)
{
	character.Standing();
	character.setDucking(false);
}

void RunFasterCommand::execute(Character& character)
{
	character.RunFast();
}

void ReleaseRunFastCommand::execute(Character& character)
{
	character.ReleaseRunFast();
}
