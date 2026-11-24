#ifndef PAUSE_MENU_SCENE_H
#define PAUSE_MENU_SCENE_H

#include "../scene_manager.h"

class PauseMenuScene : public Scene {
	SFW_OBJECT(PauseMenuScene, Scene);

public:
	explicit PauseMenuScene(SceneManager &p_scene_manager);

	void input_event(const Ref<InputEvent> &p_event) override;
	void render() override;

private:
	SceneManager &scene_manager;
};

#endif
