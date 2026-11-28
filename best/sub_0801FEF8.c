extern void setAnimationFrame(s32, void *, u16, u8);
extern void _call_via_r1(void *, void *);
extern void *spawnBudgetedEffect(s32, s32);
extern s32 randomSignedOffset(s32);
extern s32 scaleByRandom(s32);
extern u8 gMainWorkspace[];

void sub_0801FEF8(void *self) {
    void *obj;
    u8 *work;
    u8 *r4;
    u8 *w48;
    s32 v_1;
    s32 v_2;
    
    s32 v_4;
s32 __repair_phase_v_4;
    s32 r1;
    s32 off;
  s32 hoisted_const;

    obj = *(void **)((u8 *)self + 0x38);
    work = *(u8 **)((u8 *)self + 0x3C);
    r4 = work + 0x34;
    w48 = work + 0x48;
    *(s32 *)(work + 0x14) = 0;
    *(s32 *)(work + 0x10) = 0;
    setAnimationFrame((s32)obj, r4, 0x19, 0);
    if (r4[0] & 2) {
        _call_via_r1(self, *(void **)((u8 *)self + 0x24));
        return;
    }
    if (--*(s32 *)(w48 + 8) < 0) {
        *(s32 *)(w48 + 8) = 0;
        return;
    }
    off = 0x1870;
    r4 = spawnBudgetedEffect(*(s32 *)((u8 *)gMainWorkspace + off), 0x9A);
    if (r4 == 0) {
        return;
    }

    r1 = randomSignedOffset(10);
    v_1 = *(s32 *)(work + 8);
    if (v_1 < 0) {
        v_1 += 0xFFFF;
    }
    v_2 = (v_1 >> 16) + r1;
    *(s16 *)(r4 + 0x4C) = (s16)v_2;

    r1 = randomSignedOffset(10);
    v_1 = *(s32 *)(work + 0xC);
    if (v_1 < 0) {
        v_1 += 0xFFFF;
    }
    __repair_phase_v_4 = (v_1 >> 16) + r1;
    *(s16 *)(r4 + 0x54) = (s16)__repair_phase_v_4;

    if (*(u16 *)((u8 *)self + 0x5C) & 2) {
        v_4 = *(s32 *)(w48 + 8) - 1;
    } else {
        v_4 = *(s32 *)(w48 + 8) - 2;
    }
    *(s32 *)(r4 + 0x6C) = v_4 << 15;
    *(s32 *)(r4 + 0x7C) = 0x8000 - scaleByRandom(0x80 << 10);

    hoisted_const = 1;
    switch (*(s32 *)(w48 + 8) % 2) {
    case 0:
        *(u16 *)(r4 + 0x5C) = 0x80 << 1;
        break;
    case 1:
        *(u16 *)(r4 + 0x5C) = (0x80 << 2) + (hoisted_const - 1);
        break;
    }
}
