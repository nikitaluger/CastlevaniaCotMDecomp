void sub_08011368(void *, void *, s32, s32);
void sub_080C31E0(void *, void *);
s32 sub_08023F34(s32, s32, s32);
void sub_080C31E4(void *, void *, void *);
extern void *D_08671BB0;

void sub_0802349C(void *arg0) {
    u8 *obj = arg0;
    u8 new_var;
    s32 off;
    sub_08011368(*(void **)(obj + 0x38), (u8 *)*(void **)(obj + 0x3C) + 0x34, 0, 0);
    *(u32 *)(obj + 0x14) = 0x0866D8B0;
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) + 1;
    ((u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2))[0x19]++;
    off = (*(s16 *)(obj + 0x22)) * 2;
    new_var = 0x18;
    sub_080C31E0(arg0, (void *)((u32 *)*(u32 **)(obj + 0x14))[((u8 *)(new_var + obj))[off]]);
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) - 1;
}

void sub_080235C0(void *arg0) {
    s32 var_r3;
    void **var_r2;
    void *temp_r1;

    var_r2 = (void **)(*(u32 *)((u8 *)arg0 + 0x3C) + 0x70);
    var_r3 = 9;
    do {
        temp_r1 = *var_r2;
        if (temp_r1 != NULL) {
            *(u16 *)((u8 *)temp_r1 + 0x6C) = (u16)(*(u16 *)((u8 *)temp_r1 + 0x6C) | 2);
            *var_r2 = NULL;
        }
        var_r2 += 1;
        var_r3 -= 1;
    } while (var_r3 >= 0);
}

void sub_08023A7C(void *arg0) {
    u8 *obj = arg0;
    void *r1 = *(void **)(obj + 0x3C);
    u8 *r5 = (u8 *)r1 + 0x48;
    *((u8 *)*(void **)((u8 *)r1 + 0x28) + 1) = 0;
    *((u8 *)*(void **)(r5 + 4) + 1) = 0;
    if (sub_08023F34(*(s32 *)((u8 *)r1 + 8), *(s32 *)((u8 *)r1 + 0xC), 1) == 0) {
        sub_080C31E0(arg0, *(void **)(obj + 0x24));
        return;
    }
    *(u16 *)(r5 + 2) = 9;
    *((u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2) + 0x19) = 0;
    sub_080C31E4(obj + 0x18, obj + 0x22, D_08671BB0);
}

void sub_08023B3C(void *arg0) {
    u8 *obj = arg0;
    void *r1 = *(void **)(obj + 0x3C);
    u8 *r4 = (u8 *)r1 + 0x34;
    u8 *r3;
    u8 *r2;
    r3 = *(u8 **)((u8 *)r1 + 0x28);
    r3[1] &= 0xFB;
    r2 = *(u8 **)((u8 *)r1 + 0x4C);
    r2[1] &= 0xFE;
    if (r4[0] & 2) {
        sub_080C31E0(arg0, *(void **)(obj + 0x24));
    }
}
