void stepAnimationTrack(s32, void *);
void advanceMotion(void *, s32);

/* Step the entity's animation and integrate its motion; once the current script
 * step counter reaches 0x78, set bit 0 of the work record. */
void sub_080B20D0(void *entity) {
    s32 sprite = *(s32 *)((u8 *)entity + 0x38);
    u16 *work = *(u16 **)((u8 *)entity + 0x3C);
    u16 one = 1;
    stepAnimationTrack(sprite, (u8 *)work + 0x34);
    advanceMotion(work, 0);
    if (*(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) == 0x78) {
        *work = one | *work;
    }
}
