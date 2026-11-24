#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#include "sfw.h"

#include "main_menu_scene.h"
#include "scene_manager.h"

class GameApplication : public Application {
	SFW_OBJECT(GameApplication, Application);

public:
	GameApplication() {
		Renderer::initialize();
		GUI::initialize();
		scene_manager.change_scene(Ref<Scene>(memnew(MainMenuScene(scene_manager))));
	}

	~GameApplication() override {
		scene_manager.clear_scene();
		GUI::destroy();
		Renderer::destroy();
	}

	void input_event(const Ref<InputEvent> &event) override {
		scene_manager.input_event(event);
	}

	void update(float delta) override {
		scene_manager.update(delta);
	}

	void render() override {
		scene_manager.render();
	}

	SceneManager &get_scene_manager() {
		return scene_manager;
	}

private:
	SceneManager scene_manager;
};

#endif