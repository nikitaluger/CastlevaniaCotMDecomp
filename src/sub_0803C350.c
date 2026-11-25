extern void *sub_0800355C(void);
extern s32 sub_0800168C(void *, s32, s32, s32);
extern void sub_08014288(void *, void *, void *);
extern void sub_08014290(void);
extern void sub_0803C70C(void *, s32, u32, u32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_08014668(void *, s32);
extern void sub_0801131C(void *, void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern u8 D_080CD400[];
extern u32 D_08671BB0[];

/* Spawns an attack: allocates a sprite and logic state, assigns an animation
 * slot, sets the sprite graphics and world coordinates, and records the attack
 * on its owner. */
void sub_0803C350(u8 *owner)
{
    void *sprite;
    void *logic;
    void *animData;
    s32 animSlot;
    s32 slotCheck;

    sprite = sub_0800355C();
    if (sprite == 0)
        goto fail;

    *(void **)(owner + 0x38) = sprite;
    sub_0800168C(owner, 0, 0x48, 0);

    if (*(u32 *)(owner + 0x3C) == 0)
        goto fail;

    *(u32 *)((u8 *)sprite + 0x1C) = 0x8000000B;
    logic = *(void **)(owner + 0x3C);
    animData = (u8 *)logic + 0x34;
    sub_08014288(owner, logic, (void *)sub_08014290);

    *(u16 *)((u8 *)logic + 0x1C) = 0x24;
    *(u32 *)((u8 *)logic + 0x08) = *(u32 *)(owner + 0x4C);
    *(u32 *)((u8 *)logic + 0x0C) = *(u32 *)(owner + 0x5C);

    sub_0803C70C(logic,
                 *(s8 *)(owner + 0x98),
                 *(u8 *)(owner + 0x90),
                 *(u8 *)(owner + 0x94),
                 *(s32 *)(owner + 0x6C),
                 *(s32 *)(owner + 0x7C));

    animSlot = sub_08013C2C(*(s16 *)((u8 *)logic + 0x1C));
    slotCheck = animSlot;
    *(s16 *)((u8 *)logic + 0x22) = animSlot;
    if ((slotCheck << 16) >= 0)
        goto cont;

fail:
    sub_080C31E0(owner, *(void **)(owner + 0x24));
    return;

cont:
    {
        s16 slotField = *(s16 *)((u8 *)logic + 0x22);
        u32 graphics = (((s32)slotField << 6) + 0x200) | ((u32)(slotCheck + 8) << 12);
        *(u16 *)((u8 *)sprite + 0x00) = (u16)graphics;
    }

    {
        u8 *sceneState = D_02025FF0;
        *(u16 *)((u8 *)sprite + 0x00) |= *(u16 *)(sceneState + 0x18C2);

        sub_08014668(sprite, *(u32 *)((u8 *)logic + 0x10));

        sub_0801131C(sprite, animData, (s32)D_080CD400 + *(s16 *)((u8 *)logic + 0x1C) * 12);

        {
            u8 *pt = D_02021E90;
            u8 *pb = sceneState;
            u8 *base1;
            u8 *base2;
            u32 idx;

            pb += 0x18A8;
            idx = ((u32)*pb + 1) * 0x40;
            base1 = pt + 0x1278;
            *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)logic + 0x08) - ((*(u32 *)(base1 + idx) + 0x8000) & 0xFFFF0000);
            idx = ((u32)*pb + 1) * 0x40;
            base2 = pt + 0x127C;
            *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)logic + 0x0C) - ((*(u32 *)(base2 + idx) + 0xFFFF8000) & 0xFFFF0000);
        }
    }

    *(u16 *)(owner + 0x02) |= 0x1000;
    *(u8 *)((u32)(*(s16 *)(owner + 0x22) * 2) + (u32)owner + 0x19) = 0;

    {
        u32 *cmdTable = (u32 *)D_08671BB0;
        u8 *attackLog = owner + 0x18;
        sub_080C31E4(attackLog, owner + 0x22, *cmdTable);

        {
            u8 *counterPtr = (u8 *)((u32)(*(s16 *)(owner + 0x22) * 2) + (u32)owner + 0x19);
            *counterPtr = (u8)(*counterPtr + 1);
            counterPtr = attackLog;
            counterPtr += *(s16 *)(owner + 0x22) * 2;
            {
                u8 entryCode = *counterPtr;
                sub_080C31E0(owner, *(void **)(*(u32 *)(owner + 0x14) + entryCode * 4));
            }
        }
    }
}
