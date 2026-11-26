extern void *sub_0805FAEC(void *, s32);

/* Game-state block; +0x1870 is the head of the effect-object list. */
struct GameState { u8 _0[0x1870]; u32 effectList; };
extern struct GameState gMainWorkspace;

/* Spawn effect object kind 0x195 on the current effect list at world position
 * (x, y); its position lives at +0x4C/+0x5C. */
void sub_080A56A8(s32 arg0, s32 arg1) {
    void *r = sub_0805FAEC((void *)gMainWorkspace.effectList, 0x195);
    if (r != 0) {
        *(s32 *)((u8 *)r + 0x4C) = arg0;
        *(s32 *)((u8 *)r + 0x5C) = arg1;
    }
}
