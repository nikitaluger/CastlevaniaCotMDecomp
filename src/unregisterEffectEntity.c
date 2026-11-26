extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 sub_080C364C(s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 sub_08014A04(void *, s32, s32, s32);
extern void sub_08014B1C(void *, void *, s32, s32);
extern void sub_08014DB4(void *, void *, s32, s32);
extern void sub_08027A4C(void *, s32, s32 *, s32 *);

extern s32 D_08671BFC[];
extern s32 gMainObjTimerCallback[];

struct S_02025FF0_174C { u8 _0[0x174C]; u32 v174C; u32 v1750; };
extern struct S_02025FF0_174C gMainWorkspace;

void sub_08029020(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 a0 = *(s32 *)(self + 0x38);
    u8 *r5 = *(u8 **)(self + 0x3C);
    u8 *r1 = r5 + 0x34;
    u8 *r6 = r5 + 0x48;
    s32 *lit;
    s32 v;
    s32 t;

    setAnimationFrame(a0, r1, 0, 1);
    lit = D_08671BFC;
    v = sub_080C364C(*(s32 *)(r6 + 8) << 16, 0x50);
    v = sub_080C31E0(v + 0x4000, *lit);
    *(s32 *)(r5 + 0xC) = (v << 4) + *(s32 *)(r6 + 4);
    t = *(s32 *)(r5 + 0x50);
    *(s32 *)(r5 + 0x50) = t + 1;
    if (t > 0x50) {
        *(s32 *)(r6 + 8) = 0;
    }
}

// Unregisters this entity from the graphics manager's 5-slot table (unless
// the flag at +0x64 is set) by clearing its matching entry.
void unregisterEffectEntity(void *entity)
{
    if (!(1 & *(u16 *)((u8 *)entity + 0x64)))
    {
        u32 *slotTable = *(u32 **)(*(u8 **)((u8 *)entity + 0x8C) + 0x3C);
        u32 zero = 0;
        u32 *slot = slotTable + 0x1A;
        s32 i = 4;
        do
        {
            if (*slot == (u32)entity)
                *slot = zero;
            slot++;
        } while (--i >= 0);
    }
}

void sub_0802754C(void *arg0) {
    s32 sp4;
    s32 sp8;
    void *temp_r5;

    temp_r5 = *(void **)((u8 *)arg0 + 0x3C);
    sub_08027A4C(arg0, *(s32 *)((u8 *)temp_r5 + 0x50), &sp4, &sp8);
    if (sub_08014A04(temp_r5, sp4, sp8, 0xC0000) == 1) {
        s32 *lit;
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = 0;
        lit = gMainObjTimerCallback;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *lit);
        return;
    }
    sub_08014B1C(temp_r5, (u8 *)temp_r5 + 0x74, sp4, sp8);
}

void sub_080274F0(void *arg0) {
    void *temp_r4;
    temp_r4 = *(void **)((u8 *)arg0 + 0x3C);
    sub_08014DB4(temp_r4, (u8 *)temp_r4 + 0x74, gMainWorkspace.v174C, gMainWorkspace.v1750);
    if (4 & *(u16 *)((u8 *)temp_r4 + 0x8C)) {
        s32 *lit;
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = 0;
        lit = gMainObjTimerCallback;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *lit);
    }
}
