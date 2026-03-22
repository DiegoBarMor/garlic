# GARLIC
**GARLIC** (GUI Applications with RayLib In C) is a simple framework fo making GUI applications in C.

# Considerations
When using garlic's functions, the following data must be initialized statically somewhere in the source files:
```c
GarlicTexture TEXTURES[]; // used by load_textures(), unload_textures(), getp_texture()
SoundEffect SOUND_EFFECTS[]; // used by load_sound_effects(), unload_sound_effects(), play_sfx(), play_sfx_random()
bool SOUND_SFX_ON; // used by play_sfx(), play_sfx_random()
```
