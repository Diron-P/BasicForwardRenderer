#pragma once

#include <string>
#include <vector>
#include "Shader.hpp"

using namespace std;

struct Vertex {
    Oblivion::Math::Vector3 Position;
    Oblivion::Math::Vector3 Normal;
    Oblivion::Math::Vector2D TexCoords;
    // tangent
    Oblivion::Math::Vector3 Tangent;
    // bitangent
    Oblivion::Math::Vector3 Bitangent;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};

class Mesh {
public:
    /* Mesh Data */
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    /* Constructor */
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);

    /* Functions */
    void Draw(Shader shader);

private:
    /* Render data */
    unsigned int VAO, VBO, EBO;

    /* Functions */
    void setupMesh();
};