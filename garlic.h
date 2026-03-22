////// GARLIC V0.1.0 (2026-03-22)
////// IMPORTANT: read Considerations in README.md

#pragma once
#include <stdlib.h>
#include "raylib.h"

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ASSETS ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////// TEXTURES
typedef struct GarlicTexture {
    const char* filename;
    float width;
    float height;
    Texture2D tex;
} GarlicTexture;

extern GarlicTexture TEXTURES[];

void load_textures(unsigned int n);
void unload_textures(unsigned int n);
Texture2D* getp_texture(unsigned int idx); // [TODO]: consider making private and having public "draw_gtexture" functions instead

static Texture2D _load_texture_resize(GarlicTexture* gt);


/////////////////////////////////////////////////////////// SFX
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


/////////////////////////////////////////////////////////// MUSIC
typedef struct BGMusic {
    const char* path_music;
    Music music;
} BGMusic;

extern BGMusic BGM_TRACKS[];
extern bool SOUND_BGM_ON;

void load_bg_music(unsigned int n);
void unload_bg_music(unsigned int n);
Music* getp_bg_music(unsigned int idx);


////////////////////////////////////////////////////////////////////////////////
