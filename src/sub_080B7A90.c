void sub_080113A8(s32, void *);
void sub_080148D8(s32, s32);
void sub_080C31E8(void *, void *, s32, s32);

struct S_02025FF0_3C {
    u8 _0[0x3C];
    u16 v;
};
extern struct S_02025FF0_3C D_02025FF0;

/* Refreshes the actor's animation and sprite state; when the global transition
 * flag is set, clears the script action byte and dispatches handler 1 from
 * table D_08671BD0. */
void sub_080B7A90(void *self) {
    u8 *selfBytes = (u8 *)self;
    s32 sprite = *(s32 *)(selfBytes + 0x38);
    void *work = *(void **)(selfBytes + 0x3C);
    sub_080113A8(sprite, (u8 *)work + 0x34);
    sub_080148D8(sprite, *(s32 *)((u8 *)work + 8));
    if (D_02025FF0.v != 0) {
        s32 idx = *(s16 *)(selfBytes + 0x22);
        s32 *handlerTable;
        *(u8 *)(selfBytes + idx * 2 + 0x19) = 0;
        handlerTable = (s32 *)0x08671BD0;
        sub_080C31E8(selfBytes + 0x18, selfBytes + 0x22, 1, *handlerTable);
    }
}
