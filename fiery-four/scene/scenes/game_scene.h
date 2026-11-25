
#ifndef GAME_SCENE_H
#define GAME_SCENE_H

#include "../../common/Coords.h"
#include "../../common/Room.h"
#include "../../mapgen/map_generator.h"
#include "../../sfw.h"
#include "../scene_manager.h"

class GameScene : public Scene
{
	SFW_OBJECT(GameScene, Scene);

public:
	explicit GameScene(SceneManager &p_scene_manager);

	void input_event(const Ref<InputEvent> &p_event) override;
	void update(float p_delta) override;
	void render() override;

private:
	SceneManager &scene_manager;

	unsigned int seed;
	MapGenerator map_generator;

	HashMap<Coords, Room, Coords> map;

	Ref<Font> font;


	Coords current_coords{0, 0};

	float elapsed_seconds = 0.0f;

	void enter_room(Coords coords);
	bool move_to(Direction dir);
};

#endif
