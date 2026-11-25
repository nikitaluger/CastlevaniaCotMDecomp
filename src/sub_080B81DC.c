extern s32 sub_08005E80(s32);
extern void sub_080B9834(s32, s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Fire a projectile in the facing direction at two script steps: play a
 * sound, spawn the child object at an offset from the actor's body, then
 * dispatch the follow-up script when the step byte reaches 0x3C. */
void sub_080B81DC(u8 *self) {
    u8 *owner;
    u8 *body;
    s32 direction;
    s32 spawnX;
    s32 dirFlag;
    u8 step;

    owner = *(u8 **)(self + 0x38);
    body = *(u8 **)(self + 0x3C);
    dirFlag = *(u16 *)(owner + 2) & 0x10;
    direction = -1;
    if (dirFlag) {
        direction = 1;
    }
    spawnX = *(s32 *)(body + 8) - (direction << 20);

    step = *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19);
    if (step == 8) {
        sub_08005E80(0x184);
        sub_080B9834(2, 0, spawnX, *(s32 *)(body + 0xC) + (s32)0xFFE40000, direction);
    } else if (step == 0x28) {
        sub_08005E80(0x184);
        sub_080B9834(2, 0, spawnX, *(s32 *)(body + 0xC) + (s32)0xFFF80000, direction);
    }

    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x3C) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *nv = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *nv);
        }
    }
}
