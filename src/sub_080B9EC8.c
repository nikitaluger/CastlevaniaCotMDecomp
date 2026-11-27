extern void setAttachedObjectMode(void *, s32, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Clears the entity's target flag through setAttachedObjectMode, resets its current
 * script slot, then dispatches the next script step. */
void sub_080B9EC8(void *arg0) {
    u8 *entity = (u8 *)arg0;
    void *work = *(void **)(entity + 0x3C);
    setAttachedObjectMode(*(void **)((u8 *)work + 0x68), 0, work);
    *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = 0;
    {
        s32 *scriptArg = (s32 *)0x08671BB0;
        sub_080C31E4(entity + 0x18, entity + 0x22, *scriptArg);
    }
}
