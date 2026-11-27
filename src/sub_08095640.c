extern s32 sub_08007EA8(u16);
extern void sub_0800479C(u8 *, s32, s32, u16);
extern void sub_08005E80(s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void sub_080C31E0(void *, s32);

extern u8 gTilemapPages[];
extern u8 gMainWorkspace[];
extern s32 sScriptStepCallbacks;

/*
 * Entity attack update: when the current animation frame registers a hit, sets
 * the parent's hit flag, spawns contact effects along the entity's body, plays
 * a sound and starts a script step; then dispatches the current step handler.
 */
void sub_08095640(u8 *entity)
{
    u16 *flags;
    u8 *motion;
    s32 zero;

    flags = *(u16 **)(entity + 0xAC);
    motion = *(u8 **)(entity + 0x3C);

    if (*(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x1A) != 1) {
        if (sub_08007EA8(*(u16 *)(*(u8 **)(motion + 8) + 6)) != 0) {
            u32 oldFlags;
            u32 newFlags;
            oldFlags = *flags;
            newFlags = 4;
            zero = 0;
            newFlags |= oldFlags;
            *flags = (u16)newFlags;

            sub_0800479C(gTilemapPages + (gMainWorkspace[0x18A8] << 6),
                         *(s32 *)motion >> 0x15,
                         (*(s32 *)(motion + 4) + (s32)0xFFF00000) >> 0x15,
                         *(u16 *)(*(u8 **)(motion + 8) + 0));

            sub_0800479C(gTilemapPages + (gMainWorkspace[0x18A8] << 6),
                         *(s32 *)motion >> 0x15,
                         (*(s32 *)(motion + 4) + 0x100000) >> 0x15,
                         *(u16 *)(*(u8 **)(motion + 8) + 2));

            sub_0800479C(gTilemapPages + (gMainWorkspace[0x18A8] << 6),
                         *(s32 *)motion >> 0x15,
                         (*(s32 *)(motion + 4) + 0x300000) >> 0x15,
                         *(u16 *)(*(u8 **)(motion + 8) + 4));

            sub_08005E80(0x79);

            *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x1B) = (u8)zero;
            {
                s32 *scriptTable = &sScriptStepCallbacks;
                sub_080C31E8(entity + 0x18, entity + 0x22, 1, *scriptTable);
            }
        }
    }

    *(u32 *)(entity + 0x14) = 0x0866FAD0;
    *(u16 *)(entity + 0x22) += 1;

    {
        s16 stepIndex = *(s16 *)(entity + 0x22);
        *(u8 *)(entity + stepIndex * 2 + 0x19) += 1;
    }

    {
        s16 stepIndex = *(s16 *)(entity + 0x22);
        s32 stepOffset;
        u8 *stepTable;
        u8 stepByte;
        stepOffset = stepIndex * 2;
        stepTable = entity + 0x18;
        stepTable = stepTable + stepOffset;
        stepByte = *stepTable;
        sub_080C31E0(entity, *(s32 *)(*(u8 **)(entity + 0x14) + stepByte * 4));
    }

    *(u16 *)(entity + 0x22) -= 1;
}
