void *sub_08016190(void);
void sub_0806D2D0(void *);
u16 sub_0806D62C(u16, u16);
void sub_08003A6C(void *, s32, u32);
s32 sub_080C36E4(s32, s32);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, u32);
extern void sub_0808449C(void);

struct S_02025FF0 { u8 _0[0x1510]; u8 b1510; };
extern struct S_02025FF0 D_02025FF0;
extern u8 D_02025368[];

struct Child81 {
    u8 f0, f1, f2, f3;
    u16 f4, f6, f8, fA, fC, fE;
    u32 f10;
    u8 _14[2];
    u16 f16, f18;
};
struct Parent7 {
    u8 _0[0x18];
    u32 f18;
    u8 _1C[0x10];
    struct Child81 *f2C;
    u32 f30, f34, f38, f3C;
};

void sub_08081178(u8 *arg0) {
    u8 *groupBase = *(u8 **)(arg0 + 0x6C);
    struct Parent7 *group = (struct Parent7 *)(groupBase + 4);
    u8 *sprite = *(u8 **)(arg0 + 0x38);
    u8 *params = D_02025368;
    u8 *p9C;
    u32 *rec;
    u32 *tblA;
    u32 *tblB;
    struct Child81 *spawn;
    s32 idx;
    u32 *g;

    spawn = (struct Child81 *)sub_08016190();
    group->f2C = spawn;
    if (spawn == NULL) {
        sub_0806D2D0(arg0);
        return;
    }
    group->f30 = 0;
    group->f34 = 0;
    group->f38 = 0;
    group->f3C = 0;

    p9C = arg0 + 0x9C;
    rec = (u32 *)(0x080E5BB8 + ((*(u32 *)p9C & 1) << 3));

    spawn->f1 = 1 & D_02025FF0.b1510;
    group->f2C->f2 = 2;
    group->f2C->f3 = 8;
    group->f2C->f4 = params[0xC1 << 2];
    group->f2C->f6 = 0x0E;
    group->f2C->f8 = 0x0E;
    group->f2C->fA = 0;
    group->f2C->fC = 0;
    group->f2C->fE = sub_0806D62C(*(u16 *)(params + 0x2E2), *(u16 *)rec);
    group->f2C->f16 = 0x1E;
    group->f2C->f18 = 0x70;
    group->f2C->f10 = (u32)sprite;

    group->f18 = *(u32 *)(arg0 + 0x24);
    *(u32 *)(arg0 + 0x24) = (u32)&sub_0808449C;
    *(u32 *)(sprite + 0x24) = 0x084F0914;

    sub_08003A6C(groupBase + 0x20, 0, rec[1]);

    tblA = (u32 *)0x080E5B6C;
    idx = sub_080C36E4(*(s32 *)p9C, 0x0C);
    *(u32 *)(sprite + 0x14) = tblA[idx];

    tblB = (u32 *)0x080E5B9C;
    idx = sub_080C36E4(*(s32 *)p9C, 0x07);
    *(u32 *)(sprite + 0x18) = tblB[idx];

    *(u8 *)((s16)*(s16 *)(arg0 + 0x22) * 2 + (u32)arg0 + 0x19) = 0;

    g = (u32 *)0x08671BB0;
    {
        u8 *p = arg0 + 0x18;
        sub_080C31E4(p, arg0 + 0x22, *g);
        *(u8 *)((s16)*(s16 *)(arg0 + 0x22) * 2 + (u32)arg0 + 0x19) += 1;
        p += (s16)*(s16 *)(arg0 + 0x22) * 2;
        sub_080C31E0(arg0, *(s32 *)((u32)(*p) * 4 + *(u32 *)(arg0 + 0x14)));
    }
}
