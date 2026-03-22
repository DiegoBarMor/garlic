# GARLIC
**GARLIC** (GUI Applications with RayLib In C) is a simple framework fo making GUI applications in C.

# Considerations
When using garlic's functions, the following data must be initialized statically somewhere in the source files. If they're not needed, they can be initialized as an empty array.
```c
GarlicTexture TEXTURES[]; // used by load_textures(), unload_textures(), getp_texture()
SoundEffect SOUND_EFFECTS[]; // used by load_sound_effects(), unload_sound_effects(), play_sfx(), play_sfx_random()
BGMusic BGM_TRACKS[]; // used by load_bg_music(), unload_bg_music(), play_sfx(), getp_bg_music()
```
