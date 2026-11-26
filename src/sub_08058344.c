extern s32 gMainObjTimerCallback;

s32 sub_08005820(s32);
s32 sub_0800583C(s32);
void sub_08014848(s32, s32, s32, s32, s32, s32);
void sub_08058D60(s32, s32, s32, s32, s32, s32);
void sub_080C31E4(u8 *, u8 *, s32);
u8 sub_080C389C(u8, s32);

/* Spawns an attack from the entity's hitbox sub-object according to its slot
 * state (taken mod 6): state 1 fires a burst through sub_08014848, state 2
 * creates a projectile through sub_08058D60; the slot counter is reset once it
 * passes 60. */
void sub_08058344(u8 *self)
{
    s32 zero;
    u8 *obj;

    obj = *(u8 **)(self + 0x3C);
    zero = 0;
    *(s32 *)(obj + 0x10) = zero;
    *(s32 *)(obj + 0x14) = 0x8000;

    if (sub_080C389C(*(self + *(s16 *)(self + 0x22) * 2 + 0x19), 6) == 1)
    {
        sub_08014848(1, 1, *(s32 *)(obj + 8), *(s32 *)(obj + 0x0C) + 0x80000, 0xE0000, 0x80000);
    }

    if (sub_080C389C(*(self + *(s16 *)(self + 0x22) * 2 + 0x19), 6) == 2)
    {
        s32 spawnX;
        s32 spawnY;
        s32 velX;
        s32 velY;

        spawnX = *(s32 *)(obj + 8) + sub_0800583C(0xA0000);
        spawnY = *(s32 *)(obj + 0x0C) + sub_08005820(0x40000) + 0x180000;
        velX = sub_0800583C(0x20000);
        velY = sub_0800583C(0x20000) + 0xFFFF8000;
        sub_08058D60(spawnX, spawnY, velX, velY, (s32)(s16)sub_08005820(4), 1);
    }

    {
        s32 slotOff;
        u8 *slot;
        s32 *argTable;

        slotOff = (*(s16 *)(self + 0x22)) * 2;
        slot = (u8 *)(slotOff + (s32)self);
        if (*(slot + 0x19) > 0x3C)
        {
            *(slot + 0x19) = (u8)zero;
            argTable = &gMainObjTimerCallback;
            sub_080C31E4(self + 0x18, self + 0x22, *argTable);
        }
    }
}
