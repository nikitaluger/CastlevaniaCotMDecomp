extern void *sub_08016190(void);
extern void sub_0806D2D0(void *a);
extern s16 sub_0806D62C(u16, s32);
extern void sub_08003A6C(void *a, s32 b, s32 c);
extern void sub_080C31E0(void *a, s32 b);
extern void sub_080C31E4(void *a, void *b, s32 c);
extern void sub_0808449C(void);

struct S_02025FF0 {
    u8 _0[0x14EF];
    u8 b14EF;
    u8 _1[0x1510 - 0x14F0];
    u8 b1510;
    u8 _2[0x174C - 0x1511];
    u32 f174C;
    u32 f1750;
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
    u32 f00;
    u32 f04;
    u8 _1[0x18-0x08];
    u32 f18;
    u8 _2[0x2C-0x1C];
    struct Child78 *f2C;
    u32 f30, f34, f38, f3C;
};

/* Allocates and initialises a single child effect for the owner's sprite,
 * sets its state/visibility from global flags, then records the action. */
void sub_0807710C(u8 *owner) {
    u8 *basePtr = *(u8 **)(owner + 0x6C);
    u8 *sprite = *(u8 **)(owner + 0x38);
    struct Parent5 *state = (struct Parent5 *)(basePtr + 4);
    u8 *dataBase = D_02025368;
    struct Child78 *child = sub_08016190();
    u16 flipFlag;
    u8 *attackLog;
    u8 flagByte;

    state->f2C = child;
    if (child == NULL) {
        sub_0806D2D0(owner);
        return;
    }
    state->f30 = 0;
    state->f34 = 0;
    state->f38 = 0;
    state->f3C = 0;

    child->f1 = D_02025FF0.b1510 & 1;
    state->f2C->f2 = 2;
    state->f2C->f3 = 8;
    state->f2C->f4 = dataBase[0xC1 << 2];
    state->f2C->f6 = 6;
    state->f2C->f8 = 6;
    state->f2C->fA = 0;
    state->f2C->fC = 0;
    state->f2C->fE = sub_0806D62C(*(u16 *)(dataBase + 0x2E2), 0x3F);
    state->f2C->f16 = 5;
    state->f2C->f18 = 0x4D;
    state->f2C->f10 = (u32)sprite;

    state->f18 = *(u32 *)(owner + 0x24);
    *(u32 *)(owner + 0x24) = (u32)sub_0808449C;
    flagByte = D_02025FF0.b14EF;
    *(u8 *)(basePtr + 0x55) = flagByte;
    *(u32 *)(sprite + 0x24) = 0x084D24D8;

    sub_08003A6C(basePtr + 0x20, 0, 0x084D271C);

    {
        s32 baseX = D_02025FF0.f174C;
        flipFlag = *(u16 *)(sprite + 2) & 0x10;
        if (flipFlag) {
            baseX += 0xFFF40000;
        } else {
            baseX += 0xC0000;
        }
        state->f00 = baseX;
    }
    state->f04 = D_02025FF0.f1750 + 0xFFF00000;

    {
        s32 mask;
        flipFlag = *(u16 *)(sprite + 2) & 0x10;
        mask = 0x20000;
        if (flipFlag) {
            mask = 0xFFFE0000;
        }
        *(s32 *)((u8 *)state + 8) = mask;
    }
    *(s32 *)((u8 *)state + 0xC) = 0xFFFC0000;

    *((u8 *)((s16)*(s16 *)(owner + 0x22) * 2 + (u32)owner) + 0x19) = 0;
    {
        s32 *cmdTable = (s32 *)0x08671BB0;
        attackLog = owner + 0x18;
        sub_080C31E4(attackLog, owner + 0x22, *cmdTable);
    }
    {
        u8 *entryPtr = (u8 *)((s16)*(s16 *)(owner + 0x22) * 2 + (u32)owner);
        *(u8 *)(entryPtr + 0x19) = (u8)(*(u8 *)(entryPtr + 0x19) + 1);
    }
    {
        u8 *entryPtr = attackLog + (s16)*(s16 *)(owner + 0x22) * 2;
        sub_080C31E0(owner, *(u32 *)((u32)(*entryPtr) * 4 + *(u32 *)(owner + 0x14)));
    }
}
