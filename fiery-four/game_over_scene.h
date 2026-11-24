#ifndef GAME_OVER_SCENE_H
#define GAME_OVER_SCENE_H

#include "scene_manager.h"

class GameOverScene : public Scene {
	SFW_OBJECT(GameOverScene, Scene);

public:
	explicit GameOverScene(SceneManager &p_scene_manager);

	void render() override;

private:
	SceneManager &scene_manager;
};

#endif 