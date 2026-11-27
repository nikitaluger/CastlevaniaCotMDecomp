extern void sub_08011EE8(void *, s32, s32);
extern void stepAnimationTrack(void *, void *);
extern void *spawnBudgetedEffect(s32, s32);
extern s32 sub_0800583C(s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E4(void *, void *, void *);

struct S_02025FF0_1870 { u8 _0[0x1870]; u32 v; };
extern struct S_02025FF0_1870 gMainWorkspace;
extern s32 D_02027860;
extern u32 gScriptStepCallbackTable;

/* Spawns the entity's particle bursts: a directional one keyed to the script
 * counter, and, when state flags 5 are set, a two-particle burst plus a sound. */
void sub_0803CEA4(u8 *self) {
    u8 *body;
    u8 *comp;
    u8 *parent;
    void *particle;
    s32 *poolPtr;
    u8 *scriptBase;
    u8 *scriptIdx;

    parent = *(u8 **)(self + 0x38);
    comp = *(u8 **)(self + 0x3C);
    body = comp + 0x34;

    sub_08011EE8(comp, 0x16C1, 0);
    stepAnimationTrack(parent, body);

    if ((*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) & 3) == 0) {
        particle = spawnBudgetedEffect((s32)gMainWorkspace.v, 0xFD);
        if (particle != 0) {
            s32 x = *(s32 *)(comp + 8);
            if (*(u16 *)(parent + 2) & 0x10)
                *(s32 *)((u8 *)particle + 0x4C) = x + 0xFFF70000;
            else
                *(s32 *)((u8 *)particle + 0x4C) = x + 0x90000;
            *(s32 *)((u8 *)particle + 0x5C) = *(s32 *)(comp + 0xC) + sub_0800583C(0x40000);
            *(s32 *)((u8 *)particle + 0x6C) = sub_0800583C(0x1000) + 0x7000;
            *(s32 *)((u8 *)particle + 0x7C) = (-(s32)((*(u16 *)(parent + 2) & 0x10) != 0) >> 31) & 0x8000;
            *(u8 *)((u8 *)particle + 0x8C) = 7;
        }
    }

    if (*(u16 *)(comp + 2) & 5) {
        u32 i;
        s32 param;

        setAnimationFrame(parent, body, 0x11, 0);
        i = 0;
        scriptBase = self + 0x18;
        scriptIdx = self + 0x22;
        poolPtr = &D_02027860;
        param = 0xB000;
        for (i = 0; i <= 1; i++) {
            particle = spawnBudgetedEffect(*poolPtr, 0xFD);
            if (particle != 0) {
                *(s32 *)((u8 *)particle + 0x4C) = *(s32 *)(comp + 8);
                *(s32 *)((u8 *)particle + 0x5C) = *(s32 *)(comp + 0xC);
                *(s32 *)((u8 *)particle + 0x6C) = 0x14000;
                *(s32 *)((u8 *)particle + 0x7C) = param;
                *(u8 *)((u8 *)particle + 0x8C) = 0x10;
            }
            param += 0x2000;
        }

        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            u32 *sound = &gScriptStepCallbackTable;
            sub_080C31E4(scriptBase, scriptIdx, (void *)*sound);
        }
    }
}
