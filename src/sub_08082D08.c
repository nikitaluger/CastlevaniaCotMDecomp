extern void *allocEffectPart(void);            /* allocate a part object from the free pool */
extern void sub_0806D2D0(void *);           /* abort/cleanup this object */
extern s16 sub_0806D62C(u16, s32);          /* compute a 16-bit scaled value */
extern void sub_08003A6C(s32, s32, s32);    /* initialise a small control struct */
extern s32 _call_via_r1(u8 *, s32);         /* call the handler in r1 */
extern s32 _call_via_r2(u8 *, u8 *, s32);   /* call the handler in r2 */

struct S02564A { u16 f0; };
extern struct S02564A D_0202564A;
extern u8 D_0202566C;
struct S25FF0 { u8 _0[0x1510]; u8 f1510; };
extern struct S25FF0 gMainWorkspace;
extern u32 D_080E5E18;                      /* 16-entry fixed-point value table */
extern u32 gMainObjTimerCallback;                      /* step-script operation */

struct Part {                               /* one of the two sub-objects */
    u8 _0, f1, f2, f3;
    u16 f4, f6, f8, fA, fC, fE;
    u32 f10;
    u16 f14, f16, f18;
    u8 _1A[0x24 - 0x1A];
    u32 f24;
};
struct PartState {                          /* header holding both parts and their state */
    u8 _0[8];
    s32 f8, fC;
    u8 _10[0x18-0x10];
    u32 f18;
    u8 _1C[0x2C-0x1C];
    struct Part *partA;
    struct Part *partB;
    s32 f34, f38, f3C;
};
struct InitObj {                            /* object being initialised */
    u8 _0[0x14]; u32 f14; u8 _18[0x22-0x18]; s16 f22;
    u32 f24; u8 _28[0x38-0x28]; void *f38; u8 _3C[0x6C-0x3C]; u32 f6C;
    u8 _70[0x9C-0x70]; s32 f9C;
};
struct StepByte { u8 _0[0x19]; u8 f19; };

/* Initialises a two-part object: allocates and configures both parts, sets up its
   control header and step data, then runs the first step of its script. */
void sub_08082D08(struct InitObj *obj) {
    s32 header;
    struct PartState *state;
    void *target;
    s32 x, y, q, rem, off, val;
    s16 step;
    u8 byteVal;
    u32 *base;
    u32 *tbl;
    u8 *hb;
    u32 *lit;
    u8 *ptr;

    header = obj->f6C;
    state = (struct PartState *)(header + 4);
    target = obj->f38;
    if (((state->partA = (struct Part *)allocEffectPart()) == NULL) ||
        ((state->partB = (struct Part *)allocEffectPart()) == NULL)) {
        sub_0806D2D0(obj);
        return;
    }

    state->f34 = 0;
    state->f38 = 0;
    state->f3C = 0;

    state->partA->f1 = 1 & gMainWorkspace.f1510;
    state->partA->f2 = 2;
    state->partA->f3 = 8;
    state->partA->f4 = D_0202566C;
    state->partA->f6 = 6;
    state->partA->f8 = 0x0F;
    state->partA->fA = 0xFFFB;
    state->partA->fC = 0x16;
    state->partA->fE = sub_0806D62C(D_0202564A.f0, 0x84);
    state->partA->f16 = 0x1E;
    state->partA->f18 = 0x79;
    state->partA->f10 = (u32)target;

    state->partB->f1 = 1 & gMainWorkspace.f1510;
    state->partB->f2 = 2;
    state->partB->f3 = 8;
    state->partB->f4 = D_0202566C;
    state->partB->f6 = 6;
    state->partB->f8 = 0x13;
    state->partB->fA = 3;
    state->partB->fC = 0xFFF3;
    state->partB->fE = sub_0806D62C(D_0202564A.f0, 0x70);
    state->partB->f16 = 0x1E;
    state->partB->f18 = 0x79;
    state->partB->f10 = (u32)target;

    state->f18 = (u32)obj->f24;
    obj->f24 = 0x0808449D;
    ((struct Part *)target)->f24 = 0x084F7FF4;
    sub_08003A6C(header + 0x20, 0, 0x084F8024);

    base = &D_080E5E18;
    x = obj->f9C;
    y = x;
    if (x < 0) y += 0x0F;
    q = y >> 4;
    rem = x - (q << 4);
    off = rem << 2;
    val = *(s32 *)((u8 *)base + off);
    *(u32 *)((u8 *)target + 0x14) = val;

    *(u32 *)((u8 *)target + 0x18) = 0xFFC00000;
    state->f8 = 0xFFFB0000;
    state->fC = 0x00140000;

    step = *(s16 *)((u8*)obj + 0x22);
    ((struct StepByte *)((u8*)obj + step*2))->f19 = 0;
    lit = (u32*)0x08671BB0;
    hb = (u8*)obj + 0x18;
    _call_via_r2(hb, (u8*)obj + 0x22, *lit);
    step = *(s16 *)((u8*)obj + 0x22);
    ((struct StepByte *)((u8*)obj + step*2))->f19 += 1;
    step = *(s16 *)((u8*)obj + 0x22);
    ptr = hb;
    ptr += step * 2;
    byteVal = *ptr;
    tbl = *(u32 **)((u8*)obj + 0x14);
    _call_via_r1((u8*)obj, (s32)tbl[byteVal]);
}
