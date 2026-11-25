#include "game_scene.h"
#include "pause_menu_scene.h"
#include "../../common/Random.h"

GameScene::GameScene(SceneManager &p_scene_manager)
	: scene_manager(p_scene_manager),
	  seed(Random::generateWorldSeed()),
	  map_generator(seed) {

	font = Ref<Font>(memnew(Font));
	font->load_default(32.0f);

	Room start{};

	start.right = 1;
	start.left = 1;
	start.up = 1;
	start.down = 1;

	start.enemy_count = 0; // no spawnkill pls

	map.insert(current_coords, start);

	enter_room(current_coords);
}

// Very basic movement.
// TODO actual movement. majd ha lesz player
void GameScene::input_event(const Ref<InputEvent> &p_event) {
	Ref<InputEventKey> key = p_event;

	if (!key.is_valid() || !key->is_pressed() || key->is_echo())
		return;

	switch (key->get_scancode()) {
		case KEY_P:
		case KEY_ESCAPE:
			scene_manager.pause_game(
					Ref<Scene>(memnew(PauseMenuScene(scene_manager))));
			break;

		case KEY_RIGHT:
			move_to(RIGHT);
			break;

		case KEY_LEFT:
			move_to(LEFT);
			break;

		case KEY_UP:
			move_to(UP);
			break;

		case KEY_DOWN:
			move_to(DOWN);
			break;
		default:;
	}
}

void GameScene::update(float p_delta) {
	elapsed_seconds += AppWindow::get_singleton()->get_delta();
}

//TODO actual game render. Jelenlegit minimapként jó lesz felhasználni.
void GameScene::render() {
	Renderer *renderer = Renderer::get_singleton();

	const Color background(0.08f, 0.08f, 0.12f);
	const Color connection_color(0.65f, 0.65f, 0.65f);
	const Color visited_color(0.40f, 0.40f, 0.45f);
	const Color unvisited_color(0.15f, 0.15f, 0.20f);
	const Color current_color(0.15f, 0.55f, 0.30f);
	const Color border_color(0.75f, 0.75f, 0.75f);
	const Color text_color(1.0f, 1.0f, 1.0f);

	renderer->clear_screen(background);

	if (map.empty())
		return;

	const Vector2i size = renderer->get_window_size();

	if (size.x <= 0 || size.y <= 0)
		return;

	renderer->camera_2d_reset();
	renderer->camera_2d_projection_set_to_window();

	renderer->set_depth_buffer_enable(false);
	renderer->set_face_culling(Renderer::FACE_CULLING_OFF);

	// Calculate map boundaries.

	short min_x = current_coords.x;
	short max_x = current_coords.x;
	short min_y = current_coords.y;
	short max_y = current_coords.y;

	for (auto *e = map.front(); e; e = e->next) {
		const Coords &pos = e->key();

		if (pos.x < min_x)
			min_x = pos.x;
		if (pos.x > max_x)
			max_x = pos.x;
		if (pos.y < min_y)
			min_y = pos.y;
		if (pos.y > max_y)
			max_y = pos.y;
	}

	// Fit the map into the window.

	const float columns = max_x - min_x + 1.0f;
	const float rows = max_y - min_y + 1.0f;

	const float spacing_x = size.x * 0.90f / columns;
	const float spacing_y = size.y * 0.90f / rows;

	float spacing = spacing_x < spacing_y
			? spacing_x
			: spacing_y;

	const float room_size = spacing * 0.60f;
	const float line_width = spacing * 0.025f;
	const float border_width = room_size * 0.025f;

	const float origin_x =
			(size.x - (columns - 1) * spacing) / 2.0f;

	const float origin_y =
			(size.y - (rows - 1) * spacing) / 2.0f;

	// Draw connections.

	for (auto *e = map.front(); e; e = e->next) {
		const Coords &pos = e->key();
		const Room &room = e->value();

		const float x =
				origin_x + (pos.x - min_x) * spacing;

		const float y =
				origin_y + (max_y - pos.y) * spacing;

		// Right connection.

		const Room *right =
				map.getptr(pos + Coords{ 1, 0 });

		if (room.right && right && right->left) {
			renderer->draw_rect(
					Rect2(
							x,
							y - line_width / 2.0f,
							spacing,
							line_width),
					connection_color);
		}

		// Upper connection.

		const Room *up =
				map.getptr(pos + Coords{ 0, 1 });

		if (room.up && up && up->down) {
			renderer->draw_rect(
					Rect2(
							x - line_width / 2.0f,
							y - spacing,
							line_width,
							spacing),
					connection_color);
		}
	}

	// Set font scale relative to room size.

	if (font.is_valid())
		font->set_scale(room_size * 0.45f / 32.0f);

	// Draw rooms.

	for (auto *e = map.front(); e; e = e->next) {
		const Coords &pos = e->key();
		const Room &room = e->value();

		const float cx =
				origin_x + (pos.x - min_x) * spacing;

		const float cy =
				origin_y + (max_y - pos.y) * spacing;

		const float x = cx - room_size / 2.0f;
		const float y = cy - room_size / 2.0f;

		const Color start_color(0.85f, 0.65f, 0.15f);

		Color color = room.visited
				? visited_color
				: unvisited_color;

		if (pos == current_coords)
			color = current_color;

		if (pos == Coords{ 0, 0 })
			color = start_color;

		// Room border.

		renderer->draw_rect(
				Rect2(x, y, room_size, room_size),
				border_color);

		// Room interior.

		renderer->draw_rect(
				Rect2(
						x + border_width,
						y + border_width,
						room_size - 2 * border_width,
						room_size - 2 * border_width),
				color);
	}
}

void GameScene::enter_room(Coords coords) {
	const Room *room = map.getptr(coords);

	if (!room)
		return;

	current_coords = coords;

	if (!room->visited) {
		map_generator.generateNeighbours(map, coords);
		map.getptr(current_coords)->visited = 1;
	}
}

bool GameScene::move_to(Direction dir) {
	const Room *room = map.getptr(current_coords);

	if (!room || !room->hasDoor(dir))
		return false;

	Coords next = current_coords;

	switch (dir) {
		case RIGHT:
			++next.x;
			break;
		case LEFT:
			--next.x;
			break;
		case UP:
			++next.y;
			break;
		case DOWN:
			--next.y;
			break;
		default:
			return false;
	}

	const Room *neighbour = map.getptr(next);

	if (!neighbour)
		return false;

	// Check the opposite door as well.
	if (!neighbour->hasDoor(static_cast<Direction>(dir ^ 1)))
		return false;

	enter_room(next);

	return true;
}
