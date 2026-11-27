extern u8 gMainWorkspace[];

extern s32 stepDelayTimer(void *, void *);
extern s32 checkGlobalStateChange(void *, void *, void *);
extern s32 sub_0806D588(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s32 divInt32(s32, s32);

typedef struct { s32 v; } Field_s32;
typedef struct { u16 v; } Field_u16;
void sub_08074654(void *arg0) {
    void *r9 = *(void **)((u8 *)arg0 + 0x6C);
    void *r7 = (u8 *)r9 + 4;
    void *r5 = *(void **)((u8 *)arg0 + 0x38);
    void *r6;
    s32 r4;
    s32 a, b;
    s32 zero;
    s32 *p;
    s32 *p2;

    if (checkGlobalStateChange(arg0, r5, r7) != 0) {
        return;
    }

    {
        s32 v = *(u16 *)((u8 *)r5 + 4) - 0x10;
        zero = 0;
        (((Field_u16 *) ((u8 *)r5 + 4))->v) = v;
    }
    (((Field_u16 *) ((u8 *)r5 + 6))->v) -= 0x10;
    stepDelayTimer((u8 *)r9 + 0x20, r5);
    r6 = *(void **)((u8 *)r7 + 0x4C);

    if (*(u8 *)((u8 *)r6 + 1) != *(u8 *)((u8 *)r9 + 0x54)) {
        *(u8 *)((u8 *)*(void **)((u8 *)r7 + 0x2C) + 1) = zero;
        *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = zero;
        p = (s32 *)0x08671BD0;
        sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 4, *p);
        return;
    }

    a = *(s32 *)((u8 *)r6 + 0x0C);
    b = *(s32 *)((u8 *)r9 + 4);
    b = b + divInt32(a - b, 0x14);
    (((Field_s32 *) ((u8 *)r9 + 4))->v) = b;
    a = *(s32 *)((u8 *)r6 + 0x10);
    b = *(s32 *)((u8 *)r7 + 4);
    b = b + divInt32(a - b, 0x14);
    (((Field_s32 *) ((u8 *)r7 + 4))->v) = b;

    sub_0806D588(r5, r7);

    if (*(s16 *)((u8 *)r5 + 4) == 0x100) {
        *(u8 *)((u8 *)*(void **)((u8 *)r7 + 0x2C) + 1) = (u8)(gMainWorkspace[0x1510] & 1);
        *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = zero;
        p2 = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *p2);
    }

    if (gMainWorkspace[0x173A] == 0x1C || (gMainWorkspace[0x14ED] == 0 && *(u32 *)(gMainWorkspace + 0x10) != 0)) {
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
    }
}
