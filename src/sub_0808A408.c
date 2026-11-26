extern void sub_08003740(s32, s32);
extern void sub_08003A6C(s32, s32, s32);
extern void sub_0806D588(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 gMainObjTimerCallback[];
extern u8 gMainWorkspace[];

/* Tick a mover's attached animation: when the global mode word (+0x1C) is 1,
 * start the sub-script at mover+0x20 on its frame data and switch the mode word
 * to 0x10, advancing the outer script; then step the sub-script and copy the
 * mover's world position into the sprite's screen position. */
void sub_0808A408(void *entity) {
    u8 *self = (u8 *)entity;
    u8 *mover = *(u8 **)(self + 0x6C);
    u8 *pos = mover + 4;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *gameState = gMainWorkspace;
    s32 *scriptTable;
    if (*(s32 *)(gameState + 0x1C) == 1) {
        sub_08003A6C((s32)(mover + 0x20), 0, (s32)0x08502D64);
        *(s32 *)(gameState + 0x1C) = 0x10;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
    }
    sub_08003740((s32)(mover + 0x20), sprite);
    sub_0806D588(sprite, (s32)pos);
}
