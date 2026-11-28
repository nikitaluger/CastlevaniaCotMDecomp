s32 getSpriteFacingSign(void *);
void spawnVariant2Effect(s32, s32, s32);
void sub_080C31E0(void *, void *);

/* Spawn effect 0x203 to the side of this entity (which side depends on the
 * facing bit in its graphics header) and slightly below it, then run the
 * entity's current state handler. */
void sub_0805ADD4(void *arg0)
{
    void *work;
    void *gfx;

    gfx = *(void **)((u8 *)arg0 + 0x38);
    work = *(void **)((u8 *)arg0 + 0x3C);
    if (getSpriteFacingSign(gfx) < 0) {
        spawnVariant2Effect(*(s32 *)((u8 *)work + 8) + 0xFFF90000, *(s32 *)((u8 *)work + 0xC) + 0xA0000, 8);
    } else {
        spawnVariant2Effect(*(s32 *)((u8 *)work + 8) + 0x70000, *(s32 *)((u8 *)work + 0xC) + 0xA0000, 8);
    }
    sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
}
