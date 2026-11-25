extern s32 sub_08014114(s32, s32, s32, s32, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s32 D_08671BD0[];

/* Attack-step update: clear the sub-object's active flag and the sprite's 0x40
 * flag, tick down the step timer; on expiry zero the velocity and, if the
 * target's position (widened by +/-0x12, +/-0x0A) has left the screen, reset
 * the script step and run command table entry 0. */
void sub_080942B0(void *arg0)
{
    u8 *entity = (u8 *)arg0;
    u8 *sprite = *(u8 **)(entity + 0x38);
    u8 *work = *(u8 **)(entity + 0x3C);
    u8 *action = work + 0x34; /* action state: +4 sub-object, +8 velocity, +0xC timer */
    s32 zero;
    u8 *subObj;
    s32 *cmdTable;

    subObj = *(u8 **)(action + 4);
    zero = 0;
    subObj[1] = zero;
    *(u8 *)(sprite + 0x2A) &= 0xBF;

    *(u16 *)(action + 0x0C) = *(u16 *)(action + 0x0C) - 1;
    if ((s16)*(u16 *)(action + 0x0C) <= 0) {
        *(u16 *)(action + 0x0C) = zero;
        if (sub_08014114(*(s32 *)(work + 8), *(s32 *)(work + 0x0C), -0x12, 0x12, -0x0A, 0x0A) == 0) {
            *(s32 *)(action + 8) = zero;
            *(u8 *)(entity + (*(s16 *)(entity + 0x22) * 2) + 0x19) = zero;
            cmdTable = D_08671BD0;
            sub_080C31E8(entity + 0x18, entity + 0x22, 0, cmdTable[0]);
        }
    }
}
