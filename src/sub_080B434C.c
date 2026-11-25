extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void sub_080114DC(s32, void *, s32, s32);
extern void sub_08011528(s32, void *);
extern void sub_080148D8(s32, s32);
extern u8 D_02025FF0[];

void sub_080B3C68(void *arg0) {
    u8 *self = (u8*)arg0;
    if (*(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) == 4) {
        s32 *lit;
        *(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) = 0;
        lit = (s32*)0x08671BD0;
        sub_080C31E8(self + 0x18, self + 0x22, 1, *lit);
    }
}

/* Script step handler: when the current slot's command byte is 0xF, clear the
 * slot's flag byte at +0x17 and dispatch the next script command through the
 * command table at 0x08671BD8, using mode 3. */
void sub_080B434C(void *arg0) {
    u8 *obj = (u8*)arg0;
    if (*(u8*)(obj + *(s16*)(obj + 0x22) * 2 + 0x19) == 0xF) {
        s32 *lit;
        *(u8*)(obj + *(s16*)(obj + 0x22) * 2 + 0x17) = 0;
        lit = (s32*)0x08671BD8;
        sub_080C31E8(obj + 0x18, obj + 0x22, 3, *lit);
    }
}

void sub_080B389C(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *p3C = *(u8 **)(self + 0x3C) + 0x48;
    u8 z = 0;
    void *r5;
    const u32 *lit;
    *(u16 *)(p3C + 0x1C) = 0x78;
    *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) = z;
    lit = (const u32 *)0x08671BB0;
    r5 = self + 0x18;
    sub_080C31E4(r5, self + 0x22, *lit);
    *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    r5 = (u8 *)r5 + (s32)*(s16 *)(self + 0x22) * 2;
    sub_080C31E0(arg0, *(u32 *)((u8 *)*(u32 *)(self + 0x14) + *(u8 *)r5 * 4));
}

void sub_080B36F8(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 v38 = *(s32 *)(self + 0x38);
    u8 *p3C = *(u8 **)(self + 0x3C);
    u8 *r5 = p3C + 0x34;
    sub_080114DC(v38, r5, 0, 1);
    sub_08011528(v38, r5);
    sub_080148D8(v38, *(s32 *)(p3C + 8));
    if (*(u32 *)(D_02025FF0 + 0x40) == 1) {
        s32 *lit;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        lit = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
}
