struct S_02025FF0 { u8 _0[0x174C]; u32 field_0x174C; };
extern struct S_02025FF0 gMainWorkspace;
extern u32 D_08102EEC[];
extern u32 gMainObjTimerCallbacks;
extern s32 getAngleFromDelta(s32, s32);
extern void setFacingDirection(s32, s32);
extern s32 divideInt(s32, s32);
extern void playSound(s32);
extern s32 sub_080C31E0(void *, s32);
extern s32 sub_080C31E4(void *, void *, s32);

void sub_080BA9EC(u8 *self) {
    u8 *r5;
    u8 *ptr;
    u8 *r9;
    
    s32 __repair_r4_2;
    s32 r0, r1, r2, r3;
    volatile s32 sp0, sp4, sp8, spC, sp10;
    s32 r6;
    s32 r8;

    ptr = *(u8 **)(self + 0x3C);
    r9 = ptr + 0x48;
    r5 = (u8 *)(*(u32 *)(self + 0x4C));

    if (*(s32 *)(r9 + 0x64) != 0) {
        setFacingDirection((s32)r5, *(s32 *)(ptr + 0x08));
    }
    r5 += 0x35;

    {
        s32 r4_arm;
        s32 t = *(s32 *)(r9 + 0x4C) & 1;
        r2 = (s32)D_08102EEC;
        r0 = r2 + (t << 3);
        r0 = *(s32 *)r0;
        r4_arm = (s8)r5[0];
        r3 = r0;
        r3 = r3 * r4_arm;
        r0 = *(s32 *)(ptr + 0x08);
        r3 = r0 + r3;
        r2 = r2 + 0x04;
        r1 = (t << 3) + r2;
        r2 = *(s32 *)(ptr + 0x0C);
        r0 = *(s32 *)r1;
        r2 = r2 + r0;
        r1 = (s32)&gMainWorkspace;
        r0 = 0x174C;
        r1 = r1 + r0;
        r0 = r4_arm;
        r0 = r0 << 1;
        r0 = r0 + r4_arm;
        r0 = r0 << 21;
        r1 = *(s32 *)r1;
        r0 = r1 - r0;
        sp0 = r0;
        r1 = (s8)r5[0];
        r0 = -1;
        if (r1 != r0) goto path_B;
        r0 = 0x009FFFFF;
        r1 = sp0;
        if (r1 <= r0) {
            r6 = 0xA00000;
            sp0 = r6;
            goto done_clamp;
        }
        r0 = sp0;
        if (r0 <= r3) goto done_clamp;
        goto set_r3;
    path_B:
        r0 = 0x1600000;
        r1 = sp0;
        if (r1 > r0) {
            sp0 = r0;
            goto done_clamp;
        }
        r4_arm = sp0;
        if (r4_arm >= r3) goto done_clamp;
    set_r3:
        sp0 = r3;
    done_clamp:
        ;
    }

    r0 = (s8)r5[0];
    r1 = r0 << 23;
    __repair_r4_2 = sp0;
    r1 = __repair_r4_2 + r1;
    sp4 = r1;
    r0 = r0 << 22;
    r1 = __repair_r4_2;
    r0 = r0 + r1;
    r6 = (s32)r9;
    *(s32 *)(r6 + 0x54) = r0;
    r0 = r1 - r3;
    r1 = sp0;
    r5 = 0x1E00000;
    r5 = r5 - r2;
    r1 = r5;
    sp10 = r3;
    r0 = getAngleFromDelta(r0, r1);
    r6 = r0;
    __repair_r4_2 = 0x4000;
    r6 = __repair_r4_2 - r6;
    r2 = 0xFFFF;
    r8 = r2;
    r6 = r6 & r2;
    sp8 = r6;
    r3 = sp10;
    r0 = r1 - r3;
    r1 = sp4;
    r1 = r5;
    r0 = getAngleFromDelta(r0, r1);
    __repair_r4_2 = __repair_r4_2 - r0;
    r2 = r8;
    r2 = r2 & __repair_r4_2;
    spC = r2;
    __repair_r4_2 = sp8;
    r0 = r2 - __repair_r4_2;
    r1 = 0x4B;
    r0 = divideInt(r0, r1);
    r1 = (s32)r9;
    *(s32 *)(r1 + 0x50) = r0;
    *(s32 *)(r1 + 0x58) = r6;
    r0 = 0x1A8;
    playSound(r0);

    *(u8 *)((s16)*(s16 *)(self + 0x22) * 2 + (u32)self + 0x19) = 0;
    {
        u32 *cb = (u32 *)0x08671BB0;
        u8 *q = self + 0x18;
        sub_080C31E4(q, self + 0x22, *cb);
        *(u8 *)((s16)*(s16 *)(self + 0x22) * 2 + (u32)self + 0x19) += 1;
        q += (s16)*(s16 *)(self + 0x22) * 2;
        { u8 b = *q;
          sub_080C31E0(self, *(u32 *)(*(u32 *)(self + 0x14) + b * 4)); }
    }
}
