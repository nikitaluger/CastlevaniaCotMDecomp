s32 scaleByRandom(s32 bound);
s32 setAnimationFrame(s32 sprite, void *animData, s32 anim, s32 flag);
s32 getSpriteFacingSign(void *sprite);
s32 sub_08053678(s32 x, s32 y);

/* Entity updater: plays animation 0 and counts down the timer at work+0x48;
 * when it expires with the right animation state, spawns three objects at fixed
 * offsets from the entity (mirrored by facing) and restarts with a random delay. */
void sub_08053000(void *arg0) {
    s32 sprite;
    u8 *work;
    u8 *animData;
    u8 *timer;
    s32 remaining;
    u8 *offsetTable;
    u8 *offset;
    s32 x, y;

    sprite = *(s32 *)((u8 *)arg0 + 0x38);
    work = *(u8 **)((u8 *)arg0 + 0x3C);
    animData = work + 0x34;
    timer = work + 0x48;
    setAnimationFrame(sprite, animData, 0, 1);
    remaining = *(u16 *)timer;
    remaining = remaining - 1;
    *(u16 *)timer = (u16)remaining;
    if ((s32)(remaining << 16) > 0) return;
    *(u16 *)timer = 0;
    if (*(u8 *)(animData + 1) != 3) return;
    if (*(s32 *)(animData + 4) != 1) return;

    offsetTable = (u8 *)0x080CFAE8;
    offset = offsetTable;
    do {
        if (getSpriteFacingSign((void *)sprite) < 0) {
            x = *(s32 *)(work + 8) + (((s16 *)offset)[0] << 16);
            y = *(s32 *)(work + 0xC) + (((s16 *)offset)[1] << 16);
        } else {
            x = *(s32 *)(work + 8) - (((s16 *)offset)[0] << 16);
            y = *(s32 *)(work + 0xC) - (((s16 *)offset)[1] << 16);
        }
        sub_08053678(x, y);
        offset += 4;
    } while ((s32)offset <= (s32)(offsetTable + 8));
    *(u16 *)timer = (u16)(scaleByRandom(0x79) + 0xF0);
}
