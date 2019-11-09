//  This file contains the definitions of an entity, and all the different types of component
//  At the end is a *definition of std::tuple data type 'ComponentArrays' which contains an std::vector for  
//  each of the different component types. An instance of ComponentArrays is declared in the 
//  EntityComponentStore class, which is a global variable

//    TO ADD A NEW COMPONENT TYPE:
//    - define it as a sub-class of Component
//    - add it to the ComponentArrays tuple
//    - add it as a subtemplate of typetoint() and increment 'result' variable
//    - increment NUM_TYPE_COMPONENTS
//
#pragma once
#include "includes.h"
#include "Texture.h"
#include <vector>

/**** COMPONENTS ****/

//Component (base class)
// - owner: id of Entity which owns the instance of the component
struct Component {
    int owner;
};

// Transform Component
// - inherits a mat4 which represents a model matrix
// - parent: id of Transform which represents this component's parent
struct Transform : public Component, public lm::mat4 {
	int parent = -1;
	lm::mat4 getGlobalMatrix(std::vector<Transform>& transforms) {
		if (parent != -1) {
			return transforms.at(parent).getGlobalMatrix(transforms) * *this;
		}
		else return *this;
	}
};

// Mesh Component

struct Mesh : public Component {
	
	//TODO:
	// - change the mesh component so that it references 
	//   a material as well as a geometry
	
	int geometry;
	int material;
};

/**** COMPONENT STORAGE ****/

//add new component type vectors here to store them in *ECS*
typedef std::tuple<
std::vector<Transform>,
std::vector<Mesh>
> ComponentArrays;

//way of mapping different types to an integer value i.e.
//the index within ComponentArrays
template< typename T >
struct type2int{};
template<> struct type2int<Transform> { enum { result = 0 }; };
template<> struct type2int<Mesh> { enum { result = 1 }; };

const int NUM_TYPE_COMPONENTS = 2;

/**** ENTITY ****/

struct Entity {
    //name is used to store entity
    std::string name;
    //array of handles into ECM component arrays
    int components[NUM_TYPE_COMPONENTS];
    //sets active or not
    bool active = true;
    Entity() {
        for (int i = 0; i < NUM_TYPE_COMPONENTS; i++) { components[i] = -1;}
    }
    Entity(std::string a_name) : name(a_name) {
        for (int i = 0; i < NUM_TYPE_COMPONENTS; i++) { components[i] = -1;}
    }
};

