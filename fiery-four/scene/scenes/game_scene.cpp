#include "game_scene.h"
#include "main_menu_scene.h"
#include "pause_menu_scene.h"

GameScene::GameScene(SceneManager &p_scene_manager) :
		scene_manager(p_scene_manager) {
}

void GameScene::input_event(const Ref<InputEvent> &p_event) {
	Ref<InputEventKey> key = p_event;
	if (key.is_valid() && key->is_pressed() && !key->is_echo() && key->get_scancode() == KEY_P) {
		scene_manager.pause_game(Ref<Scene>(memnew(PauseMenuScene(scene_manager))));
	}
}

void GameScene::update(float p_delta) {
	elapsed_seconds += AppWindow::get_singleton()->get_delta();
	RLogger::print_message(String::num(AppWindow::get_singleton()->get_delta());
}

void GameScene::render() {
	Renderer::get_singleton()->clear_screen(Color(0.08f, 0.08f, 0.12f));

	GUI::new_frame();

	ImGuiIO &io = ImGui::GetIO();
	ImGui::SetNextWindowPos(
			ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f),
			ImGuiCond_Always,
			ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(360.0f, 220.0f), ImGuiCond_Always);
	ImGui::Begin("Fiery Four", NULL, ImGuiWindowFlags_NoSavedSettings);

	ImGui::TextUnformatted("FIERY FOUR");
	ImGui::Separator();
	ImGui::Text("Jatekido: %02d:%02d",
			static_cast<int>(elapsed_seconds) / 60,
			static_cast<int>(elapsed_seconds) % 60);
	ImGui::TextUnformatted("Nyomd meg a P gombot a szunethez.");

	if (ImGui::Button("Szunet", ImVec2(-1.0f, 44.0f))) {
		scene_manager.pause_game(Ref<Scene>(memnew(PauseMenuScene(scene_manager))));
	}
	if (ImGui::Button("Vissza a fomenube", ImVec2(-1.0f, 44.0f))) {
		scene_manager.change_scene(Ref<Scene>(memnew(MainMenuScene(scene_manager))));
	}

	ImGui::End();

	GUI::render();
}
