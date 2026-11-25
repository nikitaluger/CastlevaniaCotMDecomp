void sub_080C31E0(void *, s32);

/* Push a script level using the handler table at 0x0866E4AC: clear the
 * animation's motion fields, bump the level index and its repeat counter,
 * dispatch the level's handler, then pop the level again. */
void sub_0804C258(void *arg0) {
    void *anim = *(void **)((s8 *)arg0 + 0x3C);
    *(u32 *)((s8 *)anim + 0x14) = 0;
    *(u32 *)((s8 *)anim + 0x10) = 0;
    *(u32 *)((s8 *)arg0 + 0x14) = 0x0866E4AC;
    (*(s16 *)((s8 *)arg0 + 0x22)) += 1;
    *(u8 *)((s8 *)arg0 + (s16)(*(s16 *)((s8 *)arg0 + 0x22)) * 2 + 0x19) += 1;
    {
        s32 level;
        u8 *levelBytes;
        u8 handlerIndex;
        level = *(s16 *)((s8 *)arg0 + 0x22);
        level = level << 1;
        levelBytes = (u8 *)((s8 *)arg0 + 0x18);
        handlerIndex = *(levelBytes + level);
        sub_080C31E0(arg0, *(u32 *)(handlerIndex * 4 + *(u32 *)((s8 *)arg0 + 0x14)));
    }
    (*(s16 *)((s8 *)arg0 + 0x22)) -= 1;
}
