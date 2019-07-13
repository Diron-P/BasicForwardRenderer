#pragma once

#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma = false);

class Model {
public:
    bool gammaCorrection;
    /* Constructor */
    Model(string& path, bool gamma = false);

    /* Functions */
    void Draw(Shader shader);

private:
    /* Model data */
    vector<Mesh> meshes;
    vector<Texture> textures_loaded;
    string directory;

    /* Functions */
    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};
