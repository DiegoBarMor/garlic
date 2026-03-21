////// GARLIC V0.1.0 (2026-03-21)
//// When using garlic's functions, the following data must be
//// initialized statically somewhere in the source files
////    GarlicTexture TEXTURES[]; // used by load_textures(), unload_textures(), getp_texture()

#include "garlic.h"

// -----------------------------------------------------------------------------
void load_textures(unsigned int n) {
    for (GarlicTexture* gt = TEXTURES; gt < TEXTURES + n; gt++)
        gt->tex = _load_texture_resize(gt);
}

// -----------------------------------------------------------------------------
void unload_textures(unsigned int n) {
    for (GarlicTexture* gt = TEXTURES; gt < TEXTURES + n; gt++)
        UnloadTexture(gt->tex);
}

// -----------------------------------------------------------------------------
Texture2D* getp_texture(unsigned int idx) {
    return &TEXTURES[idx].tex;
}

// -----------------------------------------------------------------------------
static Texture2D _load_texture_resize(GarlicTexture* gt) {
    Image img = LoadImage(gt->filename);
    ImageResize(&img, (int)gt->width, (int)gt->height);
    Texture2D tex = LoadTextureFromImage(img);
    UnloadImage(img);
    return tex;
}

// -----------------------------------------------------------------------------
