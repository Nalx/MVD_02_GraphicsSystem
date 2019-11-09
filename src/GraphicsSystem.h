#pragma once
#include "includes.h"
#include "Shader.h"
#include "Components.h"
#include "Texture.h"
#include <vector>
#include <unordered_map>

struct Geometry {
	GLuint vao;
	GLuint num_tris;
};

struct Material {
	std::string name;
	GLuint shader_id;
	lm::vec3 diffuse_color;
	lm::vec3 specular_color;
	float shininess;
	GLint diffuse_texture;

	Material() {
		shader_id = 0;
		diffuse_color = lm::vec3(1.0f, 1.0f, 1.0f);
		specular_color = lm::vec3(1.0f, 1.0f, 1.0f);
		shininess = 30.0f;
		diffuse_texture = -1;
	}
	//TODO:
	// - add properties here
	// - add constructor with default properties

	// hint: ONLY store simple data (floats, ints, vec3s etc)
	// do NOT store pointers to data
};


class GraphicsSystem {
public:
	//destructor frees Shader objects
	~GraphicsSystem();

	//init and update are mandatory for all systems
	void init();
	void update(float dt);

	//load and get shader into/from private unordered_map
	int loadShader(std::string name, std::string vs_path, std::string fs_path);
	int getShaderProgram(std::string name);

	//loads a texture and returns the OpenGL texture id
	GLuint loadTexture(std::string path);

	//TODO - change this (see description in cpp file)
	int createPlaneGeometry();
	int GraphicsSystem::createGeometryFromOBJ();
	//TODO: - implement this
	int createBaseMaterial();

	//TODO 
	// - delete this!
	GLuint temp_texture;

	Material& getMaterial(int index) {
		if (index > materials_.size())
			std::cout << "wrong material index";
		return materials_[index];
	}	
	Geometry& getGeometry(int index) {
		if (index > geometries_.size())
			std::cout << "wrong geometries index";
		return geometries_[index];
	}

private:
	//dictionary of shaders
	std::unordered_map<std::string, Shader*> shaders_;
	std::vector<Geometry> geometries_;
	std::vector<Material> materials_;

	//TODO:
	// - create *private* storage vectors for Geometries and Materials
	// - and *public* methods for adding removing data to them
	


	//rendering
	GLuint current_program_;
	void renderMeshComponent_(Mesh& comp);
};
