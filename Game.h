#pragma once

#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>

class Ship;

class Game
{
public:
	Game();
	bool initialize();
	void runLoop();
	void shutdown();

	void addActor(class Actor* actor);
	void removeActor(class Actor* actor);

	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);

	SDL_Texture* getTexture(const std::string& fileName);

private:
	void processInput();
	void updateGame();
	void generateOutput();
	void loadData();
	void unloadData();

	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::vector<class Actor*> mActors;
	
	std::vector<class Actor*> mPendingActors;

	std::vector<class SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;
	
	bool mUpdatingActors;

	class Ship* mShip;
};