void sub_0801165C(void *, s32);
u16 divideInt(s32, s32);
void setAnimationFrame(void *, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Pulsating effect update: integrates its position and drives the sprite's Y
 * scale with a triangle wave over its 30-frame lifetime; after that it switches
 * to animation 0x0B and advances the script. */
void sub_080AE77C(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *sprite = *(u8 **)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *anim = work + 0x34;
    s32 *scriptHandlers;
    u8 *stepBase;
    s16 stepIndex;
    sub_0801165C(work, 0);
    stepIndex = *(s16 *)(self + 0x22);
    stepBase = (u8 *)((s32)stepIndex * 2 + (s32)self);
    if (*(u8 *)(stepBase + 0x19) <= 0x0F) {
        *(u16 *)(sprite + 6) = divideInt(0xF00, *(u8 *)(stepBase + 0x19) + 0x0F);
    } else {
        *(u16 *)(sprite + 6) = divideInt(0xF00, 0x2D - *(u8 *)(stepBase + 0x19));
    }
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x1E) {
        setAnimationFrame(sprite, anim, 0x0B, 0);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptHandlers = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptHandlers);
    }
}
