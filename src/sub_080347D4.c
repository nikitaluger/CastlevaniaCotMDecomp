extern s32 stepAnimationTrack(s32, void *);
extern s32 advanceMotion(void *, s32);

/* Advance the sub-object's animation by one step, then move it by its
 * velocity with zero added gravity. */
void sub_080347D4(void *arg0) {
    s32 sprite = *(s32 *)((s8 *)arg0 + 0x38);
    void *sub = *(void **)((s8 *)arg0 + 0x3C);
    stepAnimationTrack(sprite, (s8 *)sub + 0x34);
    advanceMotion(sub, 0);
}

extern void sub_08015974(void);
extern void unlinkAndFreeObject(void);
extern void sub_08016678(void *);
extern void sub_080C31E0(void *, s32);

void sub_0803443C(void *arg0) {
    void *r4 = *(void **)((s8 *)arg0 + 0x3C);
    void *r6 = (s8 *)r4 + 0x48;
    if (*(s32 *)((s8 *)r4 + 0x28) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)((s8 *)r6 + 0x0C) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)((s8 *)r4 + 0x2C) != 0) {
        sub_08015974();
    }
    sub_08016678(arg0);
    sub_080C31E0(arg0, *(s32 *)((s8 *)r4 + 0x24));
}

extern void sub_080C31E4(void *, void *, s32);
extern u32 gScriptStepCallbackTable;

void sub_080350F0(void *arg0) {
    void *r1 = *(void **)((s8 *)arg0 + 0x3C);
    void *r5;
    r1 = *(void **)((s8 *)arg0 + 0x3C);
    *(s32 *)((s8 *)r1 + 0x4C) = *(s32 *)((s8 *)arg0 + 0x6C);
    *(s32 *)((s8 *)r1 + 0x48) = 0x60000;
    *(u8 *)((s8 *)arg0 + (s32)(s16)((u16 *)arg0)[0x11] * 2 + 0x19) = 0;
    sub_080C31E4((s8 *)arg0 + 0x18, (s8 *)arg0 + 0x22, gScriptStepCallbackTable);
    *(u8 *)((s8 *)arg0 + (s32)(s16)((u16 *)arg0)[0x11] * 2 + 0x19) += 1;
    r5 = (s8 *)arg0 + (s32)(s16)((u16 *)arg0)[0x11] * 2;
    sub_080C31E0(arg0, *(u32 *)((u8 *)*(u32 *)((s8 *)arg0 + 0x14) + *(u8 *)r5 * 4));
}

extern s32 sub_080146D0(void *, s32, s32);

void sub_08035150(void *arg0) {
    void *r5 = *(void **)((s8 *)arg0 + 0x3C);
    s32 v;
    stepAnimationTrack(*(s32 *)((s8 *)arg0 + 0x38), (s8 *)r5 + 0x34);
    sub_080146D0(r5, *(s32 *)((s8 *)r5 + 0x4C), *(s32 *)((s8 *)r5 + 0x48));
    advanceMotion(r5, 0);
    v = *(s32 *)((s8 *)r5 + 0x48) + 0xFFFF0000;
    *(s32 *)((s8 *)r5 + 0x48) = v;
    if (v > 0) {
        return;
    }
    *(s32 *)((s8 *)r5 + 0x48) = 0;
    *(u8 *)((s8 *)arg0 + (s32)(s16)((u16 *)arg0)[0x11] * 2 + 0x19) = 0;
    sub_080C31E4((s8 *)arg0 + 0x18, (s8 *)arg0 + 0x22, gScriptStepCallbackTable);
}
