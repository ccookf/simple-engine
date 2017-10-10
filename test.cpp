#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>

int main()
{
	if (!sf::Shader::isAvailable()) std::cout << "No shaders!\n";
	else std::cout << "Starting.\n";

	sf::RenderTexture rtex;
	rtex.create(800, 600);

	std::cout << "Creating shader.\n";
	
	sf::Shader shader;
	shader.loadFromFile("assets/multiply-light.frag", sf::Shader::Fragment);
	shader.setUniform("lightmap", rtex.getTexture());
	shader.setUniform("strength", 1.0f);

	std::cout << "Done.\n";

	return 0;
}
