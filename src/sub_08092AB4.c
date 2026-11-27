/* Entity attack update: when the current animation frame registers a hit, sets
 * the parent's hit flag, spawns contact effects along the entity's body, plays
 * a sound and starts a script step; then dispatches the current step handler. */
extern s32 sub_08007EA8(u16);
extern void sub_0800479C(void *, s32, s32, u16);
extern void sub_08005E80(s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void sub_080C31E0(void *, void *);

extern s32 sScriptStepCallbacks;
extern u8 D_0866FA00;
extern u8 gTilemapPages[];
extern u8 gMainWorkspace[];

void sub_08092AB4(void *entity)
{
    u16 *flags;
    void *motion;
    s32 zero;

    flags = *(u16 **)((u8 *)entity + 0xAC);
    motion = *(void **)((u8 *)entity + 0x3C);

    if (*(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x1A) != 1) {
        if (sub_08007EA8(*(u16 *)((u8 *)*(void **)((u8 *)motion + 0x08) + 4)) != 0) {
            u32 oldFlags;
            u32 newFlags;
            oldFlags = *flags;
            newFlags = 4;
            zero = 0;
            newFlags |= oldFlags;
            *flags = (u16)newFlags;

            sub_0800479C(gTilemapPages + (gMainWorkspace[0x18A8] << 6),
                         *(s32 *)motion >> 0x15,
                         (*(s32 *)((u8 *)motion + 4) - 0x100000) >> 0x15,
                         *(u16 *)((u8 *)*(void **)((u8 *)motion + 0x08) + 0));

            sub_0800479C(gTilemapPages + (gMainWorkspace[0x18A8] << 6),
                         *(s32 *)motion >> 0x15,
                         (*(s32 *)((u8 *)motion + 4) + 0x100000) >> 0x15,
                         *(u16 *)((u8 *)*(void **)((u8 *)motion + 0x08) + 2));

            sub_08005E80(0x79);

            *(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x1B) = (u8)zero;
            {
                s32 *scriptTable = &sScriptStepCallbacks;
                sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 1, *scriptTable);
            }
        }
    }

    *(void **)((u8 *)entity + 0x14) = (void *)&D_0866FA00;
    *(s16 *)((u8 *)entity + 0x22) += 1;

    {
        s16 stepIndex = *(s16 *)((u8 *)entity + 0x22);
        *(u8 *)((u8 *)entity + stepIndex * 2 + 0x19) += 1;
    }

    {
        s16 stepIndex = *(s16 *)((u8 *)entity + 0x22);
        s32 stepOffset;
        u8 *stepTable;
        u8 stepByte;
        stepOffset = stepIndex * 2;
        stepTable = (u8 *)entity + 0x18;
        stepTable = stepTable + stepOffset;
        stepByte = *stepTable;
        sub_080C31E0(entity, *(void **)(*(u8 **)((u8 *)entity + 0x14) + stepByte * 4));
    }

    *(s16 *)((u8 *)entity + 0x22) -= 1;
}
