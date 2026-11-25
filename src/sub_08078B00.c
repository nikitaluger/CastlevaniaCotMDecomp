extern void *sub_08016190(void);
extern void sub_0806D2D0(void *);
extern s16 sub_0806D62C(u16, s32);
extern void sub_08003A6C(void *, s32, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void sub_0808449C(void);

struct S_02025FF0 {
    u8 _0[0x14EF];
    u8 b14EF;
    u8 _1[0x1510 - 0x14F0];
    u8 b1510;
    u8 _2[0x1728 - 0x1511];
    u32 f1728;
    u32 f172C;
};
extern struct S_02025FF0 D_02025FF0;
extern u8 D_02025368[];

struct Child78 {
    u8 f0, f1, f2, f3;
    u16 f4, f6, f8, fA, fC, fE;
    u32 f10;
    u8 _14[2];
    u16 f16, f18;
};
struct Parent5 {
    u8 _0[4];
    u32 f04;
    u8 _1[0x18-0x08];
    u32 f18;
    u8 _2[0x2C-0x1C];
    struct Child78 *f2C;
    u32 f30, f34, f38, f3C;
    u32 f40;
    u8 _44[8];
    u32 f4C;
    u32 f50;
    u32 f54;
};

/* Creates a child object for this entity: allocates and fills a Child78
 * record from global tables, installs a new update callback, and advances
 * the entity's control slot to the next jump-table entry. */
void sub_08078B00(u8 *entity) {
    u8 *parent = *(u8 **)(entity + 0x6C);
    struct Parent5 *state = (struct Parent5 *)(parent + 4);
    u8 *sprite = *(u8 **)(entity + 0x38);
    u8 *dataTable = D_02025368;
    struct Child78 *child = sub_08016190();
    u16 flag;
    u32 v;
    u32 *callbackSlot;
    u8 *ctrlBase;
    u8 b;

    state->f2C = child;
    if (child == NULL) {
        sub_0806D2D0(entity);
        return;
    }
    state->f30 = 0;
    state->f34 = 0;
    state->f38 = 0;
    state->f3C = 0;

    child->f1 = D_02025FF0.b1510 & 1;
    state->f2C->f2 = 2;
    state->f2C->f3 = 8;
    state->f2C->f4 = dataTable[0xC1 << 2];
    state->f2C->f6 = 6;
    state->f2C->f8 = 6;
    state->f2C->fA = 0;
    state->f2C->fC = 0;
    state->f2C->fE = sub_0806D62C(*(u16 *)(dataTable + 0x2E2), 0x47);
    state->f2C->f16 = 5;
    state->f2C->f18 = 0x55;
    state->f2C->f10 = (u32)sprite;

    state->f18 = *(u32 *)(entity + 0x24);
    *(u32 *)(entity + 0x24) = (u32)sub_0808449C;
    b = D_02025FF0.b14EF;
    *(u8 *)(parent + 0x55) = b;
    *(u32 *)(sprite + 0x24) = 0x084D99AC;

    sub_08003A6C(parent + 0x20, 0, (void *)0x084D9A04);

    *(u32 *)(parent + 4) = D_02025FF0.f1728;
    state->f04 = D_02025FF0.f172C + 0xFFEC0000;

    state->f54 = 4;

    flag = *(u16 *)(sprite + 2) & 0x10;
    v = 0x40000;
    if (flag != 0) {
        v = 0xFFFC0000;
    }
    *(u32 *)((u8 *)state + 8) = v;
    *(u32 *)((u8 *)state + 0xC) = 0xFFFC0000;

    *((u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity) + 0x19) = 0;
    callbackSlot = (u32 *)0x08671BB0;
    ctrlBase = entity + 0x18;
    sub_080C31E4(ctrlBase, entity + 0x22, *callbackSlot);
    {
        u8 *desc = (u8 *)((s16)*(s16 *)(entity + 0x22) * 2 + (u32)entity);
        *(u8 *)(desc + 0x19) = (u8)(*(u8 *)(desc + 0x19) + 1);
    }
    {
        u8 *p = ctrlBase + (s16)*(s16 *)(entity + 0x22) * 2;
        sub_080C31E0(entity, *(u32 *)((u32)(*p) * 4 + *(u32 *)(entity + 0x14)));
    }
}
