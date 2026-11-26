extern void sub_08003A6C(s32, s32, s32);
extern void sub_08005E80(s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);
extern s32 gMainObjTimerCallback[];
struct S_02025FF0_B8 { u8 _0[0x14D8]; u16 f14D8; u8 _1[0x1754 - 0x14DA]; s32 f1754; };
extern struct S_02025FF0_B8 gMainWorkspace;

/* Initializes an entity's visual state: installs its sprite data and graphics
 * attributes, clamps a global counter and loads a palette, then advances the
 * script step and dispatches the matching callback. */
void sub_080886B8(void *arg0) {
    u8 *entity = (u8 *)arg0;
    u8 *state = *(u8 **)(entity + 0x6C);
    u8 *actor = state + 4;
    *(s32 *)(*(u8 **)(entity + 0x38) + 0x24) = (s32)0x08500CA8;
    sub_08003A6C((s32)(state + 0x20), 0, (s32)0x08500D28);
    *(s32 *)(state + 4) = 0x84 << 17;
    *(s32 *)(actor + 4) = 0x80 << 16;
    *(s32 *)(actor + 8) = (s32)0xFFFD0000;
    *(s32 *)(actor + 0x0C) = (s32)0xFFFF0000;
    if (gMainWorkspace.f1754 <= 4) gMainWorkspace.f1754 = 5;
    sub_08005E80(0xD0 << 1);
    gMainWorkspace.f14D8 = 0xFFF5;
    *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = 0;
    {
        s32 *eventPtr = gMainObjTimerCallback;
        sub_080C31E4(entity + 0x18, entity + 0x22, *eventPtr);
    }
    *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) += 1;
    {
        u8 *stepBase = entity + 0x18;
        s16 step = *(s16 *)(entity + 0x22);
        stepBase += step * 2;
        sub_080C31E0(entity, *(s32 *)(*(u32 *)(entity + 0x14) + *stepBase * 4));
    }
}
