extern u8 D_08100860[];
void sub_080C31E4(void *, void *, s32);

/* Animation-script step: set the sprite frame from the 10-byte-per-entry
 * table D_08100860 using the current frame index, reset the frame timer at
 * frame+0xC from the linked object's value, clear the step's progress byte
 * and advance the script. */
void sub_08094668(void *obj) {
    void *sprite = *(void **)((u8 *)obj + 0x38);
    u8 *target = *(void **)((u8 *)obj + 0xAC);
    u8 *frame = *(u8 **)((u8 *)obj + 0x3C) + 0x34;
    u8 *frameTable = D_08100860;
    u16 frameValue;
    u16 duration;
    u32 zero;
    frameValue = *(u16 *)&frameTable[*(u32 *)(frame) * 10];
    zero = 0;
    *(u16 *)((u8 *)sprite + 0x28) = frameValue;
    duration = *(u16 *)((u8 *)*(u32 *)(target + 4) + 6);
    *(u16 *)(frame + 0x0C) = (u16)(duration * 12 + 0x5A);
    *(u8 *)((u8 *)obj + (*(s16 *)((u8 *)obj + 0x22)) * 2 + 0x19) = zero;
    { s32 *advanceFn = (s32 *)0x08671BB0; sub_080C31E4((u8 *)obj + 0x18, (u8 *)obj + 0x22, *advanceFn); }
}
