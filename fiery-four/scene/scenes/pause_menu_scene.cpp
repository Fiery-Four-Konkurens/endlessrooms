#include "pause_menu_scene.h"
#include "main_menu_scene.h"

PauseMenuScene::PauseMenuScene(SceneManager &p_scene_manager) :
		scene_manager(p_scene_manager) {
}

void PauseMenuScene::input_event(const Ref<InputEvent> &p_event) {
	Ref<InputEventKey> key = p_event;
	if (key.is_valid() && key->is_pressed() && !key->is_echo() && key->get_scancode() == KEY_P) {
		scene_manager.resume_game();
	}
}

void PauseMenuScene::render() {
	Renderer::get_singleton()->clear_screen(Color(0.08f, 0.08f, 0.12f));

	GUI::new_frame();

	ImGuiIO &io = ImGui::GetIO();
	ImGui::SetNextWindowPos(
			ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y * 0.5f),
			ImGuiCond_Always,
			ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(360.0f, 220.0f), ImGuiCond_Always);
	ImGui::Begin("Fiery Four - Szunet", NULL, ImGuiWindowFlags_NoSavedSettings);

	ImGui::TextUnformatted("Jatek szuneteltetve");
	ImGui::Separator();

	if (ImGui::Button("Folytatas", ImVec2(-1.0f, 44.0f))) {
		scene_manager.resume_game();
	}
	if (ImGui::Button("Vissza a fomenube", ImVec2(-1.0f, 44.0f))) {
		scene_manager.change_scene(Ref<Scene>(memnew(MainMenuScene(scene_manager))));
	}

	ImGui::End();

	GUI::render();
}
