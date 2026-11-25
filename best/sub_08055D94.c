extern void *sub_0800355C(void);
extern s32 sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern void sub_080141F8(void *, void *, void *, void *, s32);
extern void sub_0801131C(void *, void *, s32);
extern void *sub_08016190(void);
extern void *sub_0805FB24(void *, s32);
extern void sub_08056B30(void *, s32, void *, s32, s32);
extern void sub_08016664(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_08014290(void);

extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern u8 D_080CD400[];
extern u8 D_080CFB88[];
extern u8 D_080CFBA8[];
extern u32 D_08671BB0[];

struct E {
    u8 _0; u8 f1; u8 f2; u8 f3;
    u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE;
    u32 f10;
};
struct P {
    u8 _0[8];
    u32 f08; u32 f0C;
    u8 _10[0x0C];
    s16 f1C;
    u8 _1E[0x0A];
    struct E *f28;
};
struct TBL { u16 f0; u16 f2; u16 f4; u8 _6[0x0E]; };
extern struct TBL D_080CB2B8[];

void sub_08055D94(u8 *arg0) {
    void *vAC;
    u8 *obj;
    struct P *p;
    u8 *q;
    u8 *p48;
    u8 *tab;
    struct E *e;
    u8 *tmp;
    u8 *pt, *pb, *base1, *base2;
    u32 idx;

    vAC = *(void **)(arg0 + 0xAC);
    obj = sub_0800355C();
    if (obj == NULL) goto fail;
    *(void **)(arg0 + 0x38) = obj;
    sub_0800168C(arg0, 0, 0x64, 0);
    if (*(u32 *)(arg0 + 0x3C) == 0) goto fail;
    *(u32 *)(obj + 0x1C) = 0x80000009;
    p = *(struct P **)(arg0 + 0x3C);
    q = (u8 *)p + 0x34;
    p48 = (u8 *)p + 0x48;
    sub_08014288(arg0, (u8 *)p, (void *)sub_08014290);
    sub_080141F8(arg0, obj, (u8 *)p, vAC, 0x0F);
    sub_0801131C(obj, q, (s32)D_080CD400 + *(s16 *)((u8 *)p + 0x1C) * 0xC);
    tab = D_080CFB88;
    e = sub_08016190();
    p->f28 = e;
    if (e == NULL) goto fail;

    e->f1 = 5;
    p->f28->f2 = 8;
    p->f28->f3 = 1;
    p->f28->f4 = D_080CB2B8[*(s16 *)((u8 *)p + 0x1C)].f0;
    p->f28->f6 = *(u16 *)(tab + 0);
    p->f28->f8 = *(u16 *)(tab + 2);
    p->f28->fA = *(u16 *)(tab + 4);
    p->f28->fC = *(u16 *)(tab + 6);
    p->f28->fE = D_080CB2B8[*(s16 *)((u8 *)p + 0x1C)].f4;
    p->f28->f10 = (u32)obj;

    tmp = sub_0805FB24(arg0, 0x159);
    if (tmp == NULL) goto fail;
    *(u32 *)(tmp + 0x4C) = *(u32 *)((u8 *)p + 0x08);
    *(u32 *)(tmp + 0x5C) = *(u32 *)((u8 *)p + 0x0C);
    tmp = sub_0805FB24(arg0, 0x15A);
    if (tmp == NULL) goto fail;
    *(u32 *)(tmp + 0x4C) = *(u32 *)((u8 *)p + 0x08);
    *(u32 *)(tmp + 0x5C) = *(u32 *)((u8 *)p + 0x0C);
    tmp = sub_0805FB24(arg0, 0x15B);
    if (tmp == NULL) goto fail;
    goto body;

fail:
    sub_080C31E0(arg0, *(void **)(arg0 + 0x24));
    return;

body:
    *(u32 *)(tmp + 0x4C) = *(u32 *)((u8 *)p + 0x08);
    *(u32 *)(tmp + 0x5C) = *(u32 *)((u8 *)p + 0x0C);

    sub_08056B30(p48, 6, D_080CFBA8, 4, 4);

    pt = D_02021E90;
    pb = D_02025FF0;
    pb += 0x18A8;
    idx = ((u32)*pb + 1) * 0x40;
    base1 = pt + 0x1278;
    *(u32 *)(obj + 0x14) = *(u32 *)((u8 *)p + 0x08) - ((*(u32 *)(base1 + idx) + 0x8000) & 0xFFFF0000);
    idx = ((u32)*pb + 1) * 0x40;
    base2 = pt + 0x127C;
    *(u32 *)(obj + 0x18) = *(u32 *)((u8 *)p + 0x0C) - ((*(u32 *)(base2 + idx) + 0xFFFF8000) & 0xFFFF0000);

    sub_08016664(arg0, 0);
    {
        u16 h = *(u16 *)(arg0 + 2);
        h |= 0x1000;
        *(u16 *)(arg0 + 2) = h;
    }
    *(u8 *)((u32)(*(s16 *)(arg0 + 0x22) * 2) + (u32)arg0 + 0x19) = 0;
    {
        u32 *wp = (u32 *)D_08671BB0;
        u8 *p18 = arg0 + 0x18;
        sub_080C31E4(p18, arg0 + 0x22, *wp);
        {
            u8 *q2 = (u8 *)((u32)(*(s16 *)(arg0 + 0x22) * 2) + (u32)arg0 + 0x19);
            *q2 = (u8)(*q2 + 1);
            q2 = p18;
            q2 += *(s16 *)(arg0 + 0x22) * 2;
            {
                u8 c = *q2;
                void *fn = ((void **)*(void **)(arg0 + 0x14))[c];
                sub_080C31E0(arg0, fn);
            }
        }
    }
}
