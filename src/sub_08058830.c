extern s32 setAnimationFrame(void *, void *, s32, s32);
extern s32 sub_08014EF4(s32);
extern void sub_080C31E4(void *, void *, s32);
extern u32 gMainObjTimerCallback[];

/* Step for a pacing enemy: keep it playing animation 5; when its motion object
 * is flagged (bit 2), give it a random left/right speed (50/50), reset the
 * script slot's counter and advance to the next handler. */
void sub_08058830(void *arg0)
{
    u8 *self = (u8 *)arg0;
    void *parent;
    u8 *motion;
    s16 idx;
    s32 speed;

    parent = *(void **)(self + 0x38);
    motion = *(u8 **)(self + 0x3C);
    setAnimationFrame(parent, motion + 0x34, 5, 1);

    if (*(u16 *)(motion + 2) & 4) {
        if (sub_08014EF4(5000) == 1) {
            speed = 0x2800;
        } else {
            speed = 0xFFFFD800;
        }
        *(s32 *)(motion + 0x10) = speed;

        idx = *(s16 *)(self + 0x22);
        *(u8 *)(self + idx * 2 + 0x19) = 0;
        {
            u32 *pTable = gMainObjTimerCallback;
            sub_080C31E4(self + 0x18, self + 0x22, *pTable);
        }
    }
}
