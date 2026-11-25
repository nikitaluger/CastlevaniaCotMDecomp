extern s32 sub_080C31E0(s32, s32);
extern void *D_08671BFC;

/* Size the attached child object to 7x7 and set its two offset fields from the
 * object's position scaled by the current scaling routine. */
void sub_08059320(void *arg0) {
    u8 *attached = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *state = attached + 0x48;
    u16 *sizeTable = (u16 *)0x080CFD78;
    void **scaleFunc;
    s32 scaled;
    u16 *child;

    *(u16 *)(*(u8 **)(attached + 0x28) + 6) = sizeTable[0];
    *(u16 *)(*(u8 * volatile *)(attached + 0x28) + 8) = sizeTable[1];

    scaleFunc = &D_08671BFC;
    scaled = sub_080C31E0(*(s32 *)(state + 8) + 0x4000, (s32)*scaleFunc);
    child = *(u16 **)(attached + 0x28);
    if (scaled < 0) scaled += 0x3FFF;
    child[5] = sizeTable[2] - (s16)(scaled >> 14);

    scaled = sub_080C31E0(*(s32 *)(state + 8), (s32)*scaleFunc);
    child = *(u16 **)(attached + 0x28);
    if (scaled < 0) scaled += 0x3FFF;
    child[6] = sizeTable[3] - (s16)(scaled >> 14);
}
