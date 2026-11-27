extern s32 scaleByRandom(s32);
extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 sub_08014900(s32);
extern s32 sub_0801491C(s32);
extern void sub_080149A4(s32, void *, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *gScriptStepCallbacks;

/* Updates an enemy object: advances its sprite animation, checks player
 * proximity on a timer and despawns through a callback when close, and on a
 * second timer reverses its horizontal velocity toward a patrol target. */
void sub_0802D014(u8 *object) {
    s32 sprite = *(s32 *)(object + 0x38);
    u8 *data = *(u8 **)(object + 0x3C);
    u8 *pose = data + 0x34;
    u8 *ctrl = data + 0x48;
    s32 playerCheckTimer;
    s32 turnTimer;
    s32 delay;
    s32 newVelX;
    s32 xPos, targetX;

    sub_080149A4(sprite, data, data + 0x50, 0x28, 0x3C);
    setAnimationFrame(sprite, pose, 0, 1);

    playerCheckTimer = *(u16 *)(ctrl + 0x0C);
    playerCheckTimer = playerCheckTimer - 1;
    *(u16 *)(ctrl + 0x0C) = playerCheckTimer;
    if ((playerCheckTimer << 16) <= 0) {
        *(u16 *)(ctrl + 0x0C) = scaleByRandom(0x29) + 0x3C;
        if (sub_08014900(*(s32 *)(data + 0x08)) <= 0x680000 &&
            sub_0801491C(*(s32 *)(data + 0x0C)) <= 0x400000) {
            *(u8 *)(object + (*(s16 *)(object + 0x22)) * 2 + 0x19) = 0;
            { void **callbackPtr = &gScriptStepCallbacks;
              sub_080C31E8(object + 0x18, object + 0x22, 1, *callbackPtr); }
            return;
        }
        delay = *(s16 *)(ctrl + 0x0C);
        if (delay < 0) delay += 3;
        *(u16 *)(ctrl + 0x0C) = delay >> 2;
    }
    turnTimer = *(u16 *)(ctrl + 0x0A);
    turnTimer = turnTimer - 1;
    *(u16 *)(ctrl + 0x0A) = turnTimer;
    if ((turnTimer << 16) <= 0) {
        *(u16 *)(ctrl + 0x0A) = scaleByRandom(0x0C) + 0x0B;
        xPos = *(s32 *)(data + 0x08);
        targetX = *(s32 *)(ctrl + 0x00);
        newVelX = 0xD000;
        if (xPos > targetX) {
            newVelX = (s32)0xFFFF3000;
        }
        *(s32 *)(data + 0x10) = newVelX;
    }
}
