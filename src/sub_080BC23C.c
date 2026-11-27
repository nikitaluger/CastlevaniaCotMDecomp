s32 advanceAnimTrack(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Advance the object's sprite animation; when the animation reports its flip
 * flag (bit 1 at work+0x34), reset the held value at +0x5C, clear this step's
 * progress byte and advance the script. */
void sub_080BC23C(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *anim = *(void **)(self + 0x38);
    void *work = *(void **)(self + 0x3C);
    advanceAnimTrack(anim, (u8 *)work + 0x34);
    if (*(u8 *)((u8 *)work + 0x34) & 2) {
        *(s32 *)(self + 0x5C) = 0;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *stepTable = (s32 *)0x08671BC0;
            sub_080C31E4(self + 0x18, self + 0x22, *stepTable);
        }
    }
}
