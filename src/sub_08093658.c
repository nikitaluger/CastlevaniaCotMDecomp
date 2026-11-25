void sub_08005E80(s32 songId);
void sub_080C31E4(void *, void *, s32);
extern u8 D_08100818[];
extern u8 D_081007D0[];

/* Animation-script step: show the sprite frame given by the 6-byte frame
 * table entry for the current frame index; on the script's last frame,
 * reload the frame timer, play sound 0x1B1, clear the substep counter and
 * pop the state stack. */
void sub_08093658(void *obj) {
    void *sprite = *(void **)((u8 *)obj + 0x38);
    void *anim = *(void **)((u8 *)obj + 0x3C);
    u8 *frame = (u8 *)anim + 0x34;
    u8 *frameTable;
    frameTable = D_081007D0;
    *(u16 *)((u8 *)sprite + 0x28) = *(u16 *)&frameTable[*(u32 *)(frame) * 6];
    if (*(s32 *)(frame + 8) == 1) {
        *(u16 *)(frame + 0x0C) = 0x14;
        sub_08005E80(0x1B1);
        *(u8 *)((u8 *)obj + (*(s16 *)((u8 *)obj + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *popState = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)obj + 0x18, (u8 *)obj + 0x22, *popState);
        }
    }
}
