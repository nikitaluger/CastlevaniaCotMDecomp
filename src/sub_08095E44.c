extern s32 sub_08007EA8(u16);
extern void sub_0800479C(void *, s32, s32, u16);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void sub_080C31E0(void *, void *);

extern s32 D_08671BDC;
extern u8 D_0866FAF4;
extern u8 gTilemapPages[];
extern u8 gMainWorkspace[];

/* Run one script step: when flagged, spawn the entity's tile effects and call
 * the effect hook, then dispatch the step's handler from the script table. */
void sub_08095E44(void *arg0) {
    u16 *flags;
    void *comp;
    s32 zero;

    flags = *(u16 **)((u8 *)arg0 + 0xAC);
    comp = *(void **)((u8 *)arg0 + 0x3C);

    if (*(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x1A) != 1) {
        if (sub_08007EA8(*(u16 *)((u8 *)*(void **)((u8 *)comp + 0x08) + 4)) != 0) {
            u32 v;
            u32 w;
            v = *flags;
            w = 4;
            zero = 0;
            w |= v;
            *flags = (u16)w;

            sub_0800479C(gTilemapPages + (gMainWorkspace[0x18A8] << 6),
                         (*(s32 *)comp + (s32)0xFFF00000) >> 0x15,
                         *(s32 *)((u8 *)comp + 4) >> 0x15,
                         *(u16 *)((u8 *)*(void **)((u8 *)comp + 0x08) + 0));

            sub_0800479C(gTilemapPages + (gMainWorkspace[0x18A8] << 6),
                         (*(s32 *)comp + 0x100000) >> 0x15,
                         *(s32 *)((u8 *)comp + 4) >> 0x15,
                         *(u16 *)((u8 *)*(void **)((u8 *)comp + 0x08) + 2));

            *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x1B) = (u8)zero;
            {
                s32 *hookSlot = &D_08671BDC;
                sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 1, *hookSlot);
            }
        }
    }

    *(void **)((u8 *)arg0 + 0x14) = (void *)&D_0866FAF4;
    *(s16 *)((u8 *)arg0 + 0x22) += 1;

    {
        s16 step = *(s16 *)((u8 *)arg0 + 0x22);
        *(u8 *)((u8 *)arg0 + step * 2 + 0x19) += 1;
    }

    {
        s16 step = *(s16 *)((u8 *)arg0 + 0x22);
        s32 stepOff;
        u8 *script;
        u8 opcode;
        stepOff = step * 2;
        script = (u8 *)arg0 + 0x18;
        script = script + stepOff;
        opcode = *script;
        sub_080C31E0(arg0, *(void **)(*(u8 **)((u8 *)arg0 + 0x14) + opcode * 4));
    }

    *(s16 *)((u8 *)arg0 + 0x22) -= 1;
}
