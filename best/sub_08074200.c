struct S_02025FF0 {
    u8 _0[0x14F8]; s32 f14F8; u8 _1[0x14]; u8 f1510; u8 _2[0x217]; s32 f1728; s32 f172C;
};
extern struct S_02025FF0 gMainWorkspace;
extern u8 gGameStatus[];
extern s32 D_080E4C98[];
extern void *allocEffectPart(void);
extern void sub_0806D2D0(void *);
extern s16 sub_0806D62C(u16, s32);
extern void sub_08003A6C(void *, s32, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_0808449C(void);
extern void *gMainObjTimerCallback;
struct E { u8 _0, f1, f2, f3; u16 f4, f6, f8, fA, fC, fE; u8 _10[6]; u16 f16, f18; };
struct Q { s32 f0, f4, f8, fC; u8 _10[8]; void *f18; u8 _1C[0x10]; struct E *f2C; s32 f30, f34, f38, f3C; };
static inline u8 and1(u8 b){ u32 m = 1; m &= b; return (u8)m; }

void sub_08074200(u8 *arg0) {
    u8 *g; u8 *a; struct Q *q; u8 *base; struct S_02025FF0 *d; s32 idx, counter; u8 *t2; u32 zero; struct E *child;
    u8 *script; u16 flip;
    g = *(u8 **)(arg0 + 0x6C);
    a = *(u8 **)(arg0 + 0x38);
    q = (struct Q *)(g + 4);
    base = gGameStatus;
    child = allocEffectPart();
    q->f2C = child;
    if (child == NULL) { sub_0806D2D0(arg0); return; }
    zero = 0;
    q->f30 = zero; q->f34 = zero; q->f38 = zero; q->f3C = zero;
    d = &gMainWorkspace;
    child->f1 = and1(d->f1510);
    q->f2C->f2 = 2;
    q->f2C->f3 = 8;
    q->f2C->f4 = *(u8 *)(base + 0x304);
    q->f2C->f6 = 8;
    q->f2C->f8 = 8;
    q->f2C->fA = zero;
    q->f2C->fC = zero;
    q->f2C->fE = sub_0806D62C(*(u16 *)(base + 0x2E2), 0x20);
    q->f2C->f16 = 0xF;
    q->f2C->f18 = 0x26;
    *(u8 **)((u8 *)q->f2C + 0x10) = a;
    q->f18 = *(void **)(arg0 + 0x24);
    *(void **)(arg0 + 0x24) = sub_0808449C;
    *(u32 *)(a + 0x24) = 0x08489960;
    sub_08003A6C(g + 0x20, 0, (void *)0x08489B94);
    counter = d->f14F8;
    a = (u8 *)D_080E4C98 + (counter << 4);
    counter++;
    d->f14F8 = counter;
    if (counter > 4) d->f14F8 = zero;
    idx = d->f1728;
    t2 = *(u8 **)(arg0 + 0x28);
    flip = *(u16 *)(*(u8 **)(t2 + 0x38) + 2);
    if (flip & 0x10) q->f0 = idx - ((s32 *)a)[0];
    else q->f0 = idx + ((s32 *)a)[0];
    q->f4 = gMainWorkspace.f172C + ((s32 *)a)[1];
    { s32 v3 = ((s32 *)a)[2];
      flip = *(u16 *)(*(u8 **)(t2 + 0x38) + 2);
      if (flip & 0x10) v3 = -v3;
      q->f8 = v3; }
    q->fC = ((s32 *)a)[3];
    *(u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0 + 0x19) = 0;
    { s32 *cmdTable = (s32 *)0x08671BB0;
      script = arg0 + 0x18;
      sub_080C31E4(script, arg0 + 0x22, (s32)*cmdTable); }
    *(u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0 + 0x19) += 1;
    { u8 *p = script + (u32)(*(s16 *)(arg0 + 0x22)) * 2;
      sub_080C31E0(arg0, *(void **)(*(u8 **)(arg0 + 0x14) + *(u8 *)p * 4)); }
}
