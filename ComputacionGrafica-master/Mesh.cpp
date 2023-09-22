#include "Mesh.h"

Mesh::Mesh(){}

Mesh::Mesh(char* meshPath) {
    if (!mesh)
    {
        mesh = glmReadOBJ(meshPath);
        if (!mesh)
        {
            exit(0);
        }

        glmScale(mesh, 0.01f);
        glmFacetNormals(mesh);
        glmVertexNormals(mesh, 90.0);
    }
}

Mesh::Mesh(char* meshPath, char* textPath) {
    if (!mesh)
    {
        mesh = glmReadOBJ(meshPath);
        if (!mesh)
        {
            exit(0);
        }

        glmScale(mesh, 0.01f);
        glmFacetNormals(mesh);
        glmVertexNormals(mesh, 90.0);
    }

    glGenTextures(1, &textId);
    glBindTexture(GL_TEXTURE_2D, textId);
    glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    FIBITMAP* bitmap = FreeImage_Load(
        FreeImage_GetFileType("./Textures/moon.jpg", 0),
        "./Textures/moon.jpg"
    );

    FIBITMAP* pImage = FreeImage_ConvertTo32Bits(bitmap);
    int nWidth = FreeImage_GetWidth(pImage);
    int nHeight = FreeImage_GetHeight(pImage);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        nWidth,
        nHeight,
        0,
        GL_BGRA,
        GL_UNSIGNED_BYTE,
        (void*)FreeImage_GetBits(pImage)
    );

    FreeImage_Unload(pImage);

    glEnable(GL_TEXTURE_2D);
}

void Mesh::draw() {
    if (textId == -1) {
        glmDraw(mesh, GLM_SMOOTH | GLM_MATERIAL);
    }
    else {
        glBindTexture(GL_TEXTURE_2D, textId);
        glmDraw(mesh, GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
    }
}