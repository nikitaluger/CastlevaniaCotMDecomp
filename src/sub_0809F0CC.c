s32 sub_08013B5C(void *, void *);
void sub_080A054C(u8, s32, s32);
void sub_080C31E0(void *, void *);

/* Advance this actor: when its kind byte is set, program two graphics-state
 * halfwords; if the display state was not handled, bump the script step and
 * run the handler selected by its command byte, then update the actor's
 * scroll-relative position from its kind and x/y coordinates. */
void sub_0809F0CC(u8 *arg0) {
    u8 *sprite = *(u8 **)(arg0 + 0x38);
    u8 *work = *(u8 **)(arg0 + 0x3C);
    u8 *kind = arg0 + 0x70;
    if (*kind != 0) {
        volatile u16 *p = (volatile u16 *)0x03000830;
        u16 gfxWord0 = 0x3F44;
        p[2] = gfxWord0;
        {
            u16 gfxWord1 = 0x0A06;
            p[3] = gfxWord1;
        }
    }
    if (sub_08013B5C(sprite, work) == 0) {
        s32 stepOffset;
        u8 command;
        u8 *stepPtr;
        *(u32 *)(arg0 + 0x14) = 0x0866FD78;
        *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) + 1;
        stepOffset = *(s16 *)(arg0 + 0x22) * 2;
        *(u8 *)((u32)stepOffset + (u32)arg0 + 0x19) = *(u8 *)((u32)stepOffset + (u32)arg0 + 0x19) + 1;
        stepOffset = *(s16 *)(arg0 + 0x22) * 2;
        stepPtr = arg0;
        stepPtr += 0x18;
        stepPtr += stepOffset;
        command = *stepPtr;
        sub_080C31E0(arg0, *(void **)(command * 4 + *(u32 *)(arg0 + 0x14)));
        *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) - 1;
    }
    sub_080A054C(*kind, *(s32 *)(arg0 + 0x4C), *(s32 *)(arg0 + 0x5C));
}
