#pragma once

#include <vector>

#include "scene.h"
#include "../ecs/ecs.h"
#include "../mesh/mesh.h"
#include "../objects/player.h"
#include "../ecs/components/components.h"
#include "../ui/components/crosshair.h"
#include "../objects/room/room.h"
#include "../objects/room/wall/wall.h"


class DefaultScene : public Scene
{
public:
	DefaultScene(unsigned int id, Renderer* p_renderer) : Scene(id, p_renderer){}

	void LoadScene()
	{
		this->p_main_shader = new Shader("Assets/Shaders/shader.vert", "Assets/Shaders/shader.frag");
		this->p_main_camera = new Camera();

		Room* r = new Room(glm::vec3(5.0f, 0.0f, 5.0f), 20.0f, 15.0f, 20.0f);
		AddGameObject(r);

		//Player
		//--------------------------------------------------------
		Player* p = new Player("player", p_main_camera, glm::vec3(0.0f, 3.0f, 0.0f));
		AddGameObject(p);

		p_ui = new UI("Assets/Shaders/shaderUI.vert", "Assets/Shaders/shaderUI.frag");
		CrossHair* ch = new CrossHair(p_renderer);
		p_ui->AddUIComponent("crosshair", ch);
	}
};