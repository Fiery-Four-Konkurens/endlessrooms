#include "game_over_scene.h"
#include "main_menu_scene.h"

GameOverScene::GameOverScene(SceneManager &p_scene_manager) :
		scene_manager(p_scene_manager) {
}

void GameOverScene::render() {
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
	ImGui::TextUnformatted("A jatek veget ert!");

	if (ImGui::Button("Vissza a fomenube", ImVec2(-1.0f, 44.0f))) {
		scene_manager.change_scene(Ref<Scene>(memnew(MainMenuScene(scene_manager))));
	}
	if (ImGui::Button("Exit", ImVec2(-1.0f, 44.0f))) {
		Application::get_singleton()->running = false;
	}

	ImGui::End();

	GUI::render();
}
