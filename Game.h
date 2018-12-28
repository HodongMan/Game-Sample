#pragma once

#include <SDL.h>

#include "TypeDefine.h"


class Game
{
public:

	Game() noexcept;
	
	bool Initialize() noexcept;

	void MainLoop() noexcept;

	void ShutDown() noexcept;

private:

	void ProcessInput() noexcept;
	void UpdateGame() noexcept;
	void GenerateOutput() noexcept;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;

	int mPaddleDir;

	Vector2 mPaddlePos;
	Vector2 mBallPos;
	Vector2 mBallVel;
};