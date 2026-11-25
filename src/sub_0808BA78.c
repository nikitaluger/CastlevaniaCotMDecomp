void sub_0808BBE0(void *, s32);
void sub_0808BA9C(void);
void sub_08062118(void);

/* Reloads the current room's presentation: reads the active scene id from global
 * state, sets up that scene's sprite/VRAM assets, advances the effect timer, then
 * redraws the status HUD. */
void sub_0808BA78(void *obj) {
    extern u32 D_02025FF0[];
    u32 sceneIdOff = 0x1890;
    s32 sceneId = *(s32 *)((u8 *)D_02025FF0 + sceneIdOff);
    sub_0808BBE0(obj, sceneId);
    sub_0808BA9C();
    sub_08062118();
}
