#include "game_scene.h"

GameScene::GameScene() {
	state = GameState::MainMenu;

	Renderer::initialize();
	GUI::initialize();
}

GameScene::~GameScene() {
	GUI::destroy();
	Renderer::destroy();
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

	if(state == GameState::GameOver) {
		ImGui::TextUnformatted("A jatek veget ert!");
		if(ImGui::Button("Vissza a fomenube", ImVec2(-1.0f, 44.0f))){
			state = GameState::MainMenu;
		}
		if (ImGui::Button("Exit", ImVec2(-1.0f, 44.0f))) {
			Application::get_singleton()->running = false;
		}
	}
	else if (state == GameState::Playing) {
		ImGui::TextUnformatted("A jatek elindult!");
		if (ImGui::Button("Vissza a fomenube", ImVec2(-1.0f, 44.0f))) {
			state = GameState::MainMenu;
		}
		if(ImGui::Button("Jatek vege", ImVec2(-1.0f, 44.0f))){
			state = GameState::GameOver;
		}
	} else {
		if (ImGui::Button("Start", ImVec2(-1.0f, 44.0f))) {
			state = GameState::Playing;
		}
		if(ImGui::Button("Jatek vege", ImVec2(-1.0f, 44.0f))){
			state = GameState::GameOver;
		}
		if (ImGui::Button("Exit", ImVec2(-1.0f, 44.0f))) {
			Application::get_singleton()->running = false;
		}
	}

	ImGui::End();

	GUI::render();
}