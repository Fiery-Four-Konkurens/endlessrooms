#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "sfw.h"

class SceneManager {
public:
	void change_scene(const Ref<Scene> &p_scene) {
		ERR_FAIL_COND(p_scene.is_null());
		paused_scene.unref();
		current_scene = p_scene;
	}

	void clear_scene() {
		current_scene.unref();
		paused_scene.unref();
	}

	const Ref<Scene> &get_current_scene() const {
		return current_scene;
	}

	void pause_game(const Ref<Scene> &p_scene) {
		ERR_FAIL_COND(p_scene.is_null());
		ERR_FAIL_COND(current_scene.is_null());
		ERR_FAIL_COND(paused_scene.is_valid());
		paused_scene = get_current_scene();
		current_scene = p_scene;
	}

	void resume_game() {
		ERR_FAIL_COND(paused_scene.is_null());
		current_scene = paused_scene;
		paused_scene.unref();
	}

	void input_event(const Ref<InputEvent> &p_event) {
		Ref<Scene> scene = current_scene;
		ERR_FAIL_COND(scene.is_null());
		scene->input_event(p_event);
	}

	void update(float p_delta) {
		Ref<Scene> scene = current_scene;
		ERR_FAIL_COND(scene.is_null());
		scene->update(p_delta);
	}

	void render() {
		Ref<Scene> scene = current_scene;
		ERR_FAIL_COND(scene.is_null());
		scene->render();
	}

private:
	Ref<Scene> current_scene;
	Ref<Scene> paused_scene;
};

#endif