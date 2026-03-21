////// GARLIC V0.1.0 (2026-03-21)

#pragma once
#include <stdlib.h>
#include "raylib.h"

typedef struct GarlicTexture {
    const char* filename;
    float width;
    float height;
    Texture2D tex;
} GarlicTexture;

extern GarlicTexture TEXTURES[];

void load_textures(unsigned int n);
void unload_textures(unsigned int n);
Texture2D* getp_texture(unsigned int idx);

static Texture2D _load_texture_resize(GarlicTexture* gt);
