#ifndef MAIN_MENU_SCENE_H
#define MAIN_MENU_SCENE_H

#include "scene_manager.h"

class MainMenuScene : public Scene {
	SFW_OBJECT(MainMenuScene, Scene);

public:
	explicit MainMenuScene(SceneManager &p_scene_manager);
	~MainMenuScene() override = default;

	void render() override;

private:
	SceneManager &scene_manager;
};

#endif
