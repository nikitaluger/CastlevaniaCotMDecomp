struct S_D { u8 _0[0x10]; u32 f10; u32 f14; u8 _1[4]; u32 f1C; u8 _2[0x1824]; u32 f1844; };
extern struct S_D gMainWorkspace;

void sub_080C31E8(void *, void *, s32, s32);
void sub_080C31E0(void *, void *);
void sub_08087EC4(void *arg0) {
    u8 *p = (u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
    p[0x19] = 0;
    {
        s32 *pd0 = (s32 *)0x08671BD0;
        sub_080C31E8(arg0 + 0x18, arg0 + 0x22, gMainWorkspace.f10 + 1, *pd0);
    }
    p[0x19] = (u8)(p[0x19] + 1);
    {
        u8 **tbl = *(u8 **)((u8 *)arg0 + 0x14);
        s32 idx2 = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
        u8 b = *((u8 *)arg0 + 0x18 + idx2);
        sub_080C31E0(arg0, tbl[b]);
    }
}

void sub_080C31E4(void *, void *, s32);
/* Set the global 0x01000000 flag, clear the entity's current script-step
 * counter, and advance its command script via the shared advance callback. */
void sub_08087DA8(void *entity) {
    gMainWorkspace.f1844 |= 0x01000000;
    *(u8 *)((u8 *)entity + (*(s16 *)((u8 *)entity + 0x22)) * 2 + 0x19) = 0;
    {
        s32 *advanceCb = (s32 *)0x08671BB0;
        sub_080C31E4(entity + 0x18, entity + 0x22, *advanceCb);
    }
}

void startEffectTimer(void *, s32, s32);
void stepDelayTimer(void *, void *);
void sub_08088010(void *arg0) {
    void *p6C = *(void **)((u8 *)arg0 + 0x6C);
    void *p38 = *(void **)((u8 *)arg0 + 0x38);
    if (gMainWorkspace.f14 == 0x11) {
        void *q = (u8 *)p6C + 0x20;
        startEffectTimer(q, 0, 0x085063F8);
        stepDelayTimer(q, p38);
        *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *nv = (s32 *)0x08671BB0;
            sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *nv);
        }
    }
}

void sub_0806D588(void *, void *);
void sub_080881AC(void *arg0) {
    void *p6C = *(void **)((u8 *)arg0 + 0x6C);
    void *q7 = (u8 *)p6C + 4;
    void *p38 = *(void **)((u8 *)arg0 + 0x38);
    u8 zero;
    if (gMainWorkspace.f14 == 0x21) {
        u16 *f = (u16 *)((u8 *)p38 + 2);
        zero = 0;
        *f = (u16)(0x10 | *f);
        gMainWorkspace.f1C = 2;
        *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19) = zero;
        {
            s32 *nv = (s32 *)0x08671BB0;
            sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *nv);
        }
    }
    stepDelayTimer((u8 *)p6C + 0x20, p38);
    sub_0806D588(p38, q7);
}
