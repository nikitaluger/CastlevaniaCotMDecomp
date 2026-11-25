extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void sub_080148D8(s32, s32);
extern void sub_08011368(s32, void *, s32, s32);
extern void sub_08011460(s32, void *, s32);

void sub_080B7EE4(void *arg0) {
    u8 *self = (u8*)arg0;
    if (*(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) == 0x10) {
        s32 *lit;
        *(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x17) = 0;
        lit = (s32*)0x08671BD8;
        sub_080C31E8(self + 0x18, self + 0x22, 1, *lit);
    }
}

void sub_080B7F5C(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *r5 = (u8*)*(void **)(self + 0x3C) + 0x48;
    s32 *lit;
    sub_080148D8(*(s32*)(self + 0x38), *(s32*)((u8*)*(void **)(self + 0x3C) + 8));
    if (*(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) == 4) {
        *(u8*)(r5 + 9) = 0;
        *(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) = 0;
        lit = (s32*)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
}

/* Script-step handler: refresh the sprite's 0x10 flag from the world state,
 * then if this script sub-step has reached 0x10, clear it and advance the script. */
void sub_080B7D64(void *entity) {
    u8 *self = (u8*)entity;
    s32 *advanceCb;
    sub_080148D8(*(s32*)(self + 0x38), *(s32*)((u8*)*(void **)(self + 0x3C) + 8));
    if (*(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) == 0x10) {
        *(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) = 0;
        advanceCb = (s32*)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *advanceCb);
    }
}

void sub_080B8084(void *arg0) {
    u8 *self = (u8*)arg0;
    s32 v38 = *(s32*)(self + 0x38);
    u8 *p3C = *(u8 **)(self + 0x3C);
    u8 *r4 = p3C + 0x34;
    s32 *lit;
    sub_08011368(v38, r4, 6, 0);
    sub_08011460(v38, r4, 0x40000);
    if (*(u8*)r4 & 2) {
        *(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) = 0;
        lit = (s32*)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
}
