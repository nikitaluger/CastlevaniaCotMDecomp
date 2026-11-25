/* Spawns a projectile at two points of a countdown, then re-dispatches the
   entity once its behavior counter reaches 0xF0. */
s32 sub_080988B8(void *, s32);
s32 sub_080BB984(void *, void *);
s32 sub_080BE84C(s32, s32, s8);
void sub_080C31E4(void *, void *, s32);

void sub_080BAEE4(void *arg0) {
    u8 *entity;
    u8 *work;
    u8 *actor;
    u32 fx;
    s32 spawnX;
    u8 *dirPtr;
    s32 *callbackPtr;
    s32 timer;
    s32 yOffset;
    s32 dir;

    entity = (u8 *)arg0;
    work = *(u8 **)(entity + 0x3C);
    fx = (u32)(work + 0x48);
    actor = *(u8 **)(entity + 0x4C);

    sub_080BB984(work, (void *)fx);
    sub_080988B8(actor, *(s32 *)(work + 0x08));
    *(s32 *)(fx + 0x4C) = *(s32 *)(fx + 0x4C) - 1;
    timer = *(s32 *)(fx + 0x4C);
    if (timer != 0) {
        if (timer == 0x14) {
            dirPtr = actor + 0x35;
            dir = (s8)(*(s8 *)(actor + 0x35));
            spawnX = *(s32 *)(work + 0x08) - (u32)(dir * 0x180000);
            yOffset = *(s32 *)(work + 0x0C);
            fx = 0x240000;
            goto block_4;
        }
    } else {
        *(s32 *)(fx + 0x4C) = 0x28;
        dirPtr = actor + 0x35;
        dir = (s8)(*(s8 *)(actor + 0x35));
        spawnX = *(s32 *)(work + 0x08) + (u32)(dir * 0x350000);
        yOffset = *(s32 *)(work + 0x0C);
        fx = 0x230000;
block_4:
        sub_080BE84C(spawnX, yOffset + fx, *(s8 *)dirPtr);
    }
    {
        u8 *counterPtr = (u8 *)((*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        if (counterPtr[0x19] == 0xF0) {
            counterPtr[0x19] = 0;
            callbackPtr = (s32 *)0x08671BB0;
            sub_080C31E4(entity + 0x18, entity + 0x22, *callbackPtr);
        }
    }
}
