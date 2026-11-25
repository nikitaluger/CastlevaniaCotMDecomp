s32 sub_0809295C(void) {
    if (*(s16 *)0x020279E8 == 0xE) {
        return 0;
    }
    return -1;
}

s32 sub_08005E80(s32);
void sub_080C31E4(void *, void *, s32);
/* When the work area's state flag is 1, play sound 0x1B5, copy the flag into
 * the adjacent field, clear the entity's script-step counter and advance its
 * command script via the shared advance callback. */
void sub_08092704(void *entity) {
    s32 state;
    void *work;
    u8 zero;
    work = *(void **)((u8 *)entity + 0x3C);
    state = *(s16 *)((u8 *)work + 0xE);
    if (state == 1) {
        sub_08005E80(0x1B5);
        zero = 0;
        *(s16 *)((u8 *)work + 0xC) = state;
        ((u8 *)((u8 *)entity + (*(s16 *)((u8 *)entity + 0x22)) * 2))[0x19] = zero;
        {
            s32 *advanceCb;
            advanceCb = (s32 *)0x08671BB0;
            sub_080C31E4(entity + 0x18, entity + 0x22, *advanceCb);
        }
    }
}

s32 sub_080923C0(void) {
    if (*(s16 *)0x020279E8 == 1) {
        return 0;
    }
    return -1;
}

s32 sub_080160A0(s32, s32, s32, s32, void *);
void sub_08092374(void *arg0, void *arg1) {
    s32 temp_r2;
    u16 temp_r1;
    void *temp_r3;
    temp_r3 = *(void **)((s8 *)arg0 + 0x3C);
    if (1 & *(u16 *)((s8 *)arg1 + 2)) {
        if (8 & *(u16 *)((s8 *)arg1 + 0)) {
            *(s16 *)((s8 *)temp_r3 + 0xE) = 1;
        }
        temp_r1 = *(u16 *)((s8 *)arg1 + 2);
        if (1 & temp_r1) {
            *(u16 *)((s8 *)arg1 + 2) = (u16)(0x400 | temp_r1);
        }
    }
    temp_r2 = *(s32 *)((s8 *)temp_r3 + 4);
    sub_080160A0(temp_r2, *(s32 *)((s8 *)temp_r3 + 0x10), temp_r2, *(s32 *)((s8 *)temp_r3 + 0x14), arg1);
}
