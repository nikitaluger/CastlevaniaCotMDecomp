extern u8 gTilemapPages[];

extern s32 checkGlobalStateChange(void *, void *, void *);
extern void startEffectTimer(void *, s32, void *);
extern void playSound(s32);
extern s32 getTileTerrainB(u32, s32);
extern void *spawnEntity(s32, s32, s32, s32);
extern void sub_0806D330(void *, void *);
extern void stepDelayTimer(void *);
extern void setSpriteScreenPosition(void *, void *);
extern void _call_via_r1(u32, u32);
extern void _call_via_r2(u32, u32, u32);
extern s32 gMainObjTimerCallbacks;

struct G78534 {
    u8 pad0[0x10];
    u32 w10;
    u8 pad14[0x14D9];
    u8 b14ED;
    u8 pad14EE[0x24C];
    u8 b173A;
    u8 pad173B[0x16D];
    u8 b18A8;
    u8 pad18A9[0x19];
    u16 h18C2;
};
extern struct G78534 gMainWorkspace;

static inline u32 andOne(u16 v)
{
    u32 m = 1;
    m &= v;
    return m;
}

void sub_08078534(u8 *self)
{
    s32 r2;
    u16 *r8;
    u8 *r4;
    u8 *r5;
    u8 *base20;
    void *new;
    
    
    s32 rr;

    r4 = *(u8 **)(self + 0x6C);
    r8 = *(u16 **)(self + 0x38);
    r5 = r4 + 4;

    if (checkGlobalStateChange(self, r8, r5) != 0) return;

    *(s32 *)(r5 + 0xC) += 0x4000;
    if (*(s32 *)(r5 + 0xC) > 0x80000) *(s32 *)(r5 + 0xC) = 0x80000;

    *(s32 *)(r4 + 4) += *(s32 *)(r5 + 8);
    r2 = *(s32 *)(r5 + 4) + *(s32 *)(r5 + 0xC);
    *(s32 *)(r5 + 4) = r2;

    r2 = andOne(*(u16 *)(*(u8 **)(r5 + 0x2C) + 0x14));
    rr = 0;
    if (!r2) {
        rr = getTileTerrainB((gMainWorkspace.b18A8 << 6) + (u32)gTilemapPages,
                          *(s32 *)(r4 + 4)) << 0x10;
    }
    base20 = r4 + 0x20;
    if (r2 || rr != 0) {
        r4 += 0x20;
        startEffectTimer(r4, 0, (void *)0x084D96AC);
        *(u16 *)(*(u8 **)(r5 + 0x2C) + 6) = 0xA;
        *(u16 *)(*(u8 **)(r5 + 0x2C) + 8) = 0xA;
        playSound(0x144);
        for (r2 = 0; r2 <= 7; r2++) {
            new = spawnEntity(*(s32 *)(self + 0x28), 0x46, 0xA, 0x12);
            if (new != NULL) {
                *(u32 *)((u8 *)new + 0x7C) = *(u32 *)(r4 + 4 - 0x20 + 0x20);
                *(u32 *)((u8 *)new + 0x8C) = *(u32 *)(r5 + 4);
                *(u32 *)((u8 *)new + 0x9C) = r2;
            }
        }
        *((u8 *)((s16)*(s16 *)(self + 0x22) * 2 + (u32)self) + 0x19) = 0;
        _call_via_r2((u32)(self + 0x18), (u32)(self + 0x22), (u32)gMainObjTimerCallbacks);
    }

    *r8 = gMainWorkspace.h18C2;
    stepDelayTimer(base20);
    do { do { do { setSpriteScreenPosition(r8, r5); } while (0); } while (0); } while (0);
    if (gMainWorkspace.b173A == 0x1C ||
        (gMainWorkspace.b14ED == 0 && gMainWorkspace.w10 != 0)) {
        _call_via_r1((u32)self, *(u32 *)(self + 0x24));
        return;
    }
    sub_0806D330(self, r8);
}
