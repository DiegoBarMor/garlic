////// GARLIC V0.1.0 (2026-03-22)
////// IMPORTANT: read Considerations in README.md

#include "garlic.h"

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////// ASSETS ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////// TEXTURES
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


/////////////////////////////////////////////////////////// SFX
bool SOUND_SFX_ON = true;

// -----------------------------------------------------------------------------
void load_sound_effects(unsigned int n) {
    for (SoundEffect* sfx = SOUND_EFFECTS; sfx < SOUND_EFFECTS + n; sfx++)
        sfx->sound = LoadSound(sfx->path_sfx);
}

// -----------------------------------------------------------------------------
void unload_sound_effects(unsigned int n) {
    for (SoundEffect* sfx = SOUND_EFFECTS; sfx < SOUND_EFFECTS + n; sfx++)
        UnloadSound(sfx->sound);
}

// -----------------------------------------------------------------------------
void play_sfx(unsigned int idx) {
    if (!SOUND_SFX_ON) return;
    PlaySound(SOUND_EFFECTS[idx].sound);
}

// -----------------------------------------------------------------------------
void play_sfx_random(unsigned int idx, unsigned int n_variants) {
    if (!SOUND_SFX_ON) return;
    int choice = GetRandomValue(idx, idx + n_variants - 1);
    PlaySound(SOUND_EFFECTS[choice].sound);
}


/////////////////////////////////////////////////////////// MUSIC
bool SOUND_BGM_ON = true;

// -----------------------------------------------------------------------------
void load_bg_music(unsigned int n) {
    for (BGMusic* bgm = BGM_TRACKS; bgm < BGM_TRACKS + n; bgm++)
        bgm->music = LoadMusicStream(bgm->path_music);
}

// -----------------------------------------------------------------------------
void unload_bg_music(unsigned int n) {
    for (BGMusic* bgm = BGM_TRACKS; bgm < BGM_TRACKS + n; bgm++)
        UnloadMusicStream(bgm->music);
}

// -----------------------------------------------------------------------------
Music* getp_bg_music(unsigned int idx) {
    return &BGM_TRACKS[idx].music;
}


// -----------------------------------------------------------------------------
