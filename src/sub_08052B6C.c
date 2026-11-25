extern void sub_080C31E0(void *, void *);
extern void sub_080144D8(void *, void *);
extern void sub_080144FC(void *, void *);

/* Run one step of an actor's script: prepare its sprite, switch to the
 * 0x0866E674 command table, advance the script index (and that step's
 * repeat byte), dispatch the step's handler through the command table,
 * restore the index, then finish the sprite update. */
void sub_08052B6C(void *actor) {
    u8 *obj = (u8 *)actor;
    u8 scriptBase;
    s32 stepOffset;
    void *sprite = *(void **)(obj + 0x38);
    sub_080144D8(actor, sprite);
    *(u32 *)(obj + 0x14) = 0x0866E674;
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) + 1;
    ((u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2))[0x19]++;
    stepOffset = (*(s16 *)(obj + 0x22)) * 2;
    scriptBase = 0x18;
    sub_080C31E0(actor, (void *)((u32 *)*(u32 **)(obj + 0x14))[((u8 *)(scriptBase + obj))[stepOffset]]);
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) - 1;
    sub_080144FC(actor, sprite);
}
