////// GARLIC V0.1.0 (2026-03-22)
////// IMPORTANT: read Considerations in README.md

#pragma once
#include <stdlib.h>
#include "raylib.h"

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// GRAPHICS ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

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


////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// AUDIO /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

typedef struct SoundEffect {
    const char* path_sfx;
    Sound sound;
} SoundEffect;

extern SoundEffect SOUND_EFFECTS[];
extern bool SOUND_SFX_ON;

void load_sound_effects(unsigned int n);
void unload_sound_effects(unsigned int n);
void play_sfx(unsigned int idx);
void play_sfx_random(unsigned int idx, unsigned int n_variants); // assumes n consecutive variants for a SFX


////////////////////////////////////////////////////////////////////////////////
