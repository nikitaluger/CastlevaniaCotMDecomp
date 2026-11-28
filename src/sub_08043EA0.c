extern void setAnimationFrame(void *, void *, s32, s32);
extern void stepAnimationTrack(void *, void *);
extern void *spawnBudgetedEffect(s32, s32);
extern void _call_via_r3(void *, void *, s32, void *);

struct S_02025FF0_1870 { u8 _0[0x1870]; u32 v; };
extern struct S_02025FF0_1870 gMainWorkspace;
extern u32 gScriptStepCallbacks;

void sub_08043EA0(u8 *script) {
    u8 *sprite;
    u8 *work;
    u8 *animTrack;
    u8 *dest;
    void *particle;
    s32 worldX;
    s32 off;
    s32 t;
    s32 zero;
    u8 nextId;
    u32 *callback;
    zero = 0;

    do { do { do { sprite = *(u8 **)(script + 0x38); } while (0); } while (0); } while (0);
    do { do { do { work = *(u8 **)(script + 0x3C); } while (0); } while (0); } while (0);
    animTrack = 0x34 + work;
    dest = work + 0x48;

    setAnimationFrame(sprite, animTrack, 2, 0);
    stepAnimationTrack(sprite, animTrack);

    if (dest[1] == 0 && *(u16 *)(sprite + 0x28) == 0xA) {
        dest[1] = 1;
        particle = spawnBudgetedEffect((s32)gMainWorkspace.v, 0x119);
        if (particle != 0) {
            do { nextId = *(u8 *)(script + 0x4C); } while (0);
            *(u8 *)((u8 *)particle + 0x4C) = nextId;
            worldX = *(s32 *)(work + 8);
            *(s32 *)((u8 *)particle + 0x5C) = worldX + ((*(u16 *)(sprite + 2) & 0x10) ? (0xA0 << 13) : -0x140000);
            *(s32 *)((u8 *)particle + 0x6C) = *(s32 *)(work + 0xC) - 0x130000;
            if ((*(u16 *)(sprite + 2) & 0x10) != 0)
                off = 0xC0 << 10;
            else
                off = -0x30000;
            *(s32 *)((u8 *)particle + 0x7C) = off;
        }
    }

    if (*animTrack & 2) {
        t = dest[0] - 1;
        zero = 0;
        dest[0] = t;
        if ((t << 24) == 0) {
            *(u8 *)(script + *(s16 *)(script + 0x22) * 2 + 0x19) = zero;
            callback = &gScriptStepCallbacks;
            _call_via_r3(script + 0x18, script + 0x22, 0, (void *)*callback);
        } else {
            dest[1] = 0;
            setObjectAnimationFrame(sprite, animTrack, 2, 0);
        }
    }
}
