#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "sfw.h"

enum class GameState{
	MainMenu,
	Playing,
	GameOver
};

class GameScene : public Scene {
	SFW_OBJECT(GameScene, Scene);

public:
	GameScene();
	~GameScene() override;

	void render() override;

private:
	GameState state;
};

#endif
