#include "main_menu_scene.h"
#include "game_scene.h"

MainMenuScene::MainMenuScene(SceneManager &p_scene_manager) :
		scene_manager(p_scene_manager) {
	Ref<Image> image;
	image.instance();

	image->load_from_file("assets/wallpaper/wallpaper01_rgba.png");

	background.instance();
	background->create_from_image(image);
}

void MainMenuScene::render() {
	Renderer *renderer = Renderer::get_singleton();

	renderer->clear_screen(Color(0, 0, 0, 1));
	renderer->camera_2d_projection_set_to_window();

	glDisable(GL_FRAMEBUFFER_SRGB);

	renderer->draw_texture(
		background,
		Rect2(0, 0, 1920, 1080)
	);

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

	if (ImGui::Button("Start", ImVec2(-1.0f, 44.0f))) {
		scene_manager.change_scene(Ref<Scene>(memnew(GameScene(scene_manager))));
	}
	if (ImGui::Button("Exit", ImVec2(-1.0f, 44.0f))) {
		Application::get_singleton()->running = false;
	}

	ImGui::End();

	GUI::render();
}