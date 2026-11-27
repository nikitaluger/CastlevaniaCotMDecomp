s32 randomSignedOffset(s32);
s32 getSpriteFacingSign(s32);
s32 isOutsideCameraBounds(s32, s32);
void sub_0808DBF8(s32, s32, s32);
void sub_080C31E0(void *, s32);

/* When the script step's low flag equals 1, spawn a trail particle a random
 * distance in front of the actor (the sprite's facing sign picks left/right);
 * if the actor leaves the viewport, switch to its off-screen state. */
void sub_08028424(void *arg0)
{
    s32 sprite = *(s32 *)((u8 *)arg0 + 0x38);
    void *work = *(void **)((u8 *)arg0 + 0x3C);
    s32 randX, randY;
    u8 stepFlag;

    stepFlag = *(u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2 + 0x19);
    if ((stepFlag & 7) == 1) {
        randX = randomSignedOffset(0x10000) << 3;
        randY = randomSignedOffset(0x10000) << 3;
        if (getSpriteFacingSign(sprite) < 0) {
            s32 xOff = randX + 0x180000;
            s32 spawnX = *(s32 *)((u8 *)work + 8) + xOff;
            s32 yOff = randY + 0x10000;
            s32 spawnY = *(s32 *)((u8 *)work + 0xC) + yOff;
            sub_0808DBF8(spawnX, spawnY, 8);
        } else {
            s32 xOff = randX + 0xFFE80000;
            s32 spawnX = *(s32 *)((u8 *)work + 8) + xOff;
            s32 yOff = randY + 0x10000;
            s32 spawnY = *(s32 *)((u8 *)work + 0xC) + yOff;
            sub_0808DBF8(spawnX, spawnY, 8);
        }
    }
    if (isOutsideCameraBounds(*(s32 *)((u8 *)work + 8), *(s32 *)((u8 *)work + 0xC)) == 1) {
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
    }
}
