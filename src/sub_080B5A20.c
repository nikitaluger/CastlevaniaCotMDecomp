s32 updateObjectDisplayState(void *, void *);
void syncSpriteToWorldPosition(void *, void *);
void stepAnimationTrack(s32, void *);
void advanceMotion(void *, s32);
void sub_080146D0(void *, s32, s32);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

struct S_B53B8 {
    u8 _00[0x14];
    u32 field_14;
    u8 _18[0x0A];
    s16 field_22;
    u8 _24[0x14];
    u32 field_38;
    u32 field_3C;
};

void sub_080B53B8(struct S_B53B8 *arg0) {
    void *r5 = (void *)arg0->field_38;
    if (updateObjectDisplayState(r5, (void *)arg0->field_3C) == 0) {
        arg0->field_14 = 0x0867040C;
        arg0->field_22 += 1;
        *((u8 *)(((u8 *)arg0) + (arg0->field_22 * 2) + 0x19)) += 1;
        sub_080C31E0(arg0, *(void **)((*(u8 *)(((u8 *)arg0) + 0x18 + (arg0->field_22 * 2)) * 4) + arg0->field_14));
        arg0->field_22 -= 1;
    }
    syncSpriteToWorldPosition(arg0, r5);
}

void sub_080B59C0(void *arg0) {
    s32 temp_r5 = *(s32 *)((u8 *)arg0 + 0x3C);
    s32 temp_r0;
    stepAnimationTrack(*(s32 *)((u8 *)arg0 + 0x38), temp_r5 + 0x34);
    temp_r0 = *(s32 *)((u8 *)arg0 + 0x6C) + 0xFFFFF000;
    *(s32 *)((u8 *)arg0 + 0x6C) = temp_r0;
    if (temp_r0 <= 0) {
        *(s32 *)((u8 *)arg0 + 0x6C) = 0;
    }
    sub_080146D0((void *)temp_r5, *(s32 *)((u8 *)arg0 + 0x7C), *(s32 *)((u8 *)arg0 + 0x6C));
    advanceMotion((void *)temp_r5, 0);
    if (*(s32 *)((u8 *)arg0 + 0x6C) == 0) {
        s32 idx = *(s16 *)((u8 *)arg0 + 0x22);
        *(u8 *)((u8 *)arg0 + idx * 2 + 0x19) = 0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *(s32 *)0x08671BB0);
    }
}

/* Run one step of the entity's command script; command 8 clears the current
 * command byte and reloads the script from the default command table. */
void sub_080B5A20(void *arg0) {
    u8 *obj = (u8 *)arg0;
    s32 *lit;
    stepAnimationTrack(*(s32 *)(obj + 0x38), (u8 *)*(void **)(obj + 0x3C) + 0x34);
    if (*(u8 *)(obj + (*(s16 *)(obj + 0x22) * 2) + 0x19) == 8) {
        *(u8 *)(obj + (*(s16 *)(obj + 0x22) * 2) + 0x19) = 0;
        lit = (s32 *)0x08671BB0;
        sub_080C31E4(obj + 0x18, obj + 0x22, *lit);
    }
}

void sub_080B5ACC(void *arg0) {
    s32 temp_r5 = *(s32 *)((u8 *)arg0 + 0x3C);
    s32 temp_r0;
    stepAnimationTrack(*(s32 *)((u8 *)arg0 + 0x38), temp_r5 + 0x34);
    temp_r0 = *(s32 *)((u8 *)arg0 + 0x6C) + 0x800;
    *(s32 *)((u8 *)arg0 + 0x6C) = temp_r0;
    if (temp_r0 > 0x17FFF) {
        *(s32 *)((u8 *)arg0 + 0x6C) = 0x18000;
    }
    sub_080146D0((void *)temp_r5, *(s32 *)((u8 *)arg0 + 0x7C), *(s32 *)((u8 *)arg0 + 0x6C));
    advanceMotion((void *)temp_r5, 0);
}
