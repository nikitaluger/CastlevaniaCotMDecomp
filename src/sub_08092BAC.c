extern u8 D_02025FF0[];

s32 sub_08005820(s32);
s32 sub_0800583C(s32);
void sub_0808DBF8(s32, s32, s32);
void sub_080918B0(s32, s32, s32, s32, s32, s32);
void sub_080C31E0(void *, s32);
s32 sub_080C36E4(s32, s32);

/* Spawn an effect at the owner's position with random jitter and a count-derived
 * speed/angle; hand control back to the script once its state byte exceeds 0x10. */
void sub_08092BAC(void *behav)
{
    s32 posX, posYraw, posY, speed, angle;
    s32 countDiv, halfCount, countMod;
    u32 *counter;
    void *owner;
    s32 count;
    u32 countOff;

    owner = *(void **)((u8 *)behav + 0x3C);
    posX = *(s32 *)owner + (sub_0800583C(0x10000) << 4);
    posYraw = *(s32 *)((u8 *)owner + 4) + (sub_0800583C(0x10000) << 3);
    countOff = 0x1898;
    counter = (u32 *)(D_02025FF0 + countOff);
    halfCount = *(s32 *)counter / 2;
    countMod = halfCount % 4;
    posY = posYraw + ((countMod - 1) << 20);
    speed = sub_08005820(0x2000);
    countDiv = sub_080C36E4(*(s32 *)counter, 5) - 2;
    speed += 0x4000;
    speed *= countDiv;
    angle = 0x8000 - sub_08005820(0x20000);
    count = *(s32 *)counter;
    if (!(count & 1)) {
        sub_080918B0(posX, posY, speed, angle, 0x16C1,
            (s16)(((s32)(count + (s32)((u32)count >> 31)) >> 1) - (((((s32)(count + (s32)((u32)count >> 31)) >> 1) + (s32)((u32)(count + (s32)((u32)count >> 31)) >> 31)) >> 1) << 1) + 1));
    } else {
        sub_0808DBF8(posX, posY, 8);
    }
    {
        s16 scriptIdx = *(s16 *)((u8 *)behav + 0x22);
        u8 stateByte = *((u8 *)behav + scriptIdx * 2 + 0x19);
        if (stateByte > 0x10)
            sub_080C31E0(behav, *(s32 *)((u8 *)behav + 0x24));
    }
}
