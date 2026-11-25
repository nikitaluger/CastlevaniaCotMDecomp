extern void sub_08011368(void *, void *, s32, s32);
extern s32 sub_080B9824(s32);
extern void sub_080C31E4(void *, void *, s32);

/* Actor step: when the actor's flag is set, clear a sprite rendering flag;
 * then, once the linked object's 0x4C byte is clear, start animation 0x0A,
 * set the work value to 0x400000, clear the script step and dispatch. */
void sub_080B837C(void *actor) {
    void *self;
    void *sprite;
    void *work;
    void *anim;
    s16 idx;
    s32 *handlerTable;
    u8 *flagByte;

    self = actor;
    sprite = *((void **)((s8 *)self + 0x38));
    work = *((void **)((s8 *)self + 0x3C));
    anim = work + 0x34;

    if (*((u8 *)((s8 *)self + 0x4C)) != 0) {
        flagByte = (u8 *)sprite + 0x2A;
        *flagByte = *flagByte & 0xBF;
    }
    if (sub_080B9824(*((s32 *)((s8 *)work + 0x48))) != 0) {
        sub_08011368(sprite, anim, 0x0A, 0);
        *((s32 *)((s8 *)work + 0x08)) = 0x400000;
        idx = *((s16 *)((s8 *)self + 0x22));
        *((u8 *)((s8 *)self + idx * 2 + 0x19)) = 0;
        handlerTable = (s32 *)0x08671BB0;
        sub_080C31E4((s8 *)self + 0x18, (s8 *)self + 0x22, *handlerTable);
    }
}
