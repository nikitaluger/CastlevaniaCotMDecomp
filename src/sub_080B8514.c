extern void freeMotionTracker(void);
extern void unlinkAndFreeObject(void);
extern void sub_08016678(void *);
extern void sub_080C31E0(void *, s32);
extern void stepAnimationTrack(void *, void *);
extern void sub_08042130(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Tear down the entity's attached sub-objects, then re-dispatch its command
 * script from the current command's handler entry. */
void sub_080B8514(void *arg0) {
    void *res = *(void **)((u8 *)arg0 + 0x3C);
    void *aux = (u8 *)res + 0x48;
    if (*(s32 *)((u8 *)res + 0x28) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)((u8 *)aux + 4) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)((u8 *)res + 0x2C) != 0) {
        freeMotionTracker();
    }
    sub_08016678(arg0);
    sub_080C31E0(arg0, *(s32 *)((u8 *)res + 0x24));
}

void sub_08042078(void *arg0) {
    void *r4 = *(void **)((u8 *)arg0 + 0x38);
    void *r0p = *(void **)((u8 *)arg0 + 0x3C);
    void *r5 = (u8 *)r0p + 0x34;
    void *r7 = (u8 *)r0p + 0x48;
    stepAnimationTrack(r4, r5);
    sub_08042130(r7, r4);
    if (2 & *(u8 *)r5) {
        *(u8 *)((u8 *)*(void **)((u8 *)r7 + 4) + 1) = 0;
        *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *pd = (s32 *)0x08671BD0;
            sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 2, *pd);
        }
    }
}

void sub_080428B8(void *arg0) {
    s32 *var_r4;
    s32 var_r5;
    void *temp_r6;
    temp_r6 = *(void **)((u8 *)arg0 + 0x3C);
    if (*(s32 *)((u8 *)temp_r6 + 0x28) != 0) {
        unlinkAndFreeObject();
    }
    if (*(s32 *)((u8 *)temp_r6 + 0x2C) != 0) {
        freeMotionTracker();
    }
    var_r4 = (s32 *)((u8 *)temp_r6 + 0x50);
    var_r5 = 1;
    do {
        if (*var_r4 != 0) {
            unlinkAndFreeObject();
        }
        var_r4 += 4;
        var_r5 -= 1;
    } while (var_r5 >= 0);
    sub_08016678(arg0);
    sub_080C31E0(arg0, *(s32 *)((u8 *)temp_r6 + 0x24));
}

void sub_08042900(void *arg0, void *arg1) {
    u16 v = *(u16 *)((u8 *)arg0 + 0x28);
    u16 *src = (u16 *)0x080CF4FC;
    switch (v) {
    case 0x0C:
        src = (u16 *)((u8 *)src + 8);
        break;
    case 0x10:
        src = (u16 *)((u8 *)src + 0x10);
        break;
    case 0x14:
    case 0x1C:
        src = (u16 *)0x080CF514;
        break;
    }
    *(u16 *)((u8 *)*(void **)((u8 *)arg1 + 0x28) + 6) = src[0];
    *(u16 *)((u8 *)*(void **)((u8 *)arg1 + 0x28) + 8) = src[1];
    *(u16 *)((u8 *)*(void **)((u8 *)arg1 + 0x28) + 0xA) = src[2];
    *(u16 *)((u8 *)*(void **)((u8 *)arg1 + 0x28) + 0xC) = src[3];
}
