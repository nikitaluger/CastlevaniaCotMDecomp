extern s32 sub_080B9834(s32 a, u8 b, s32 c, s32 d, s32 e);
extern void sub_080C31E4(void *a, void *b, s32 c);

/* Script-step callback: on every fourth step past 0x10, spawns a projectile
 * ahead of the companion (offset by its facing direction) with an incrementing
 * counter; at step 0x90 it resets the step and redirects the script. */
void sub_080B8000(u8 *self)
{
    u8 *companion = *(u8 **)(self + 0x38);
    u8 *scriptState = *(u8 **)(self + 0x3C);
    u8 *control = scriptState + 0x48;
    s32 spawnX;
    s32 spawnY;

    u8 step = *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19);
    if ((step & 3) == 0 && step > 0x10) {
        u16 facingBit = *(u16 *)(companion + 2) & 0x10;
        s32 direction = -1;
        if (facingBit) {
            direction = 1;
        }
        spawnX = *(s32 *)(scriptState + 8) - (direction << 20);
        spawnY = *(s32 *)(scriptState + 0xC) + 0xFFE80000;
        sub_080B9834(1, *(u8 *)(control + 9), spawnX, spawnY, direction);
        *(u8 *)(control + 9) = *(u8 *)(control + 9) + 1;
    }

    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x90) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *pScriptTable = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *pScriptTable);
        }
    }
}
