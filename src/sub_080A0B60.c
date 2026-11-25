void sub_08011528(void *, void *);
s32 sub_0801459C(void *, s32);
void sub_080A1744(void *, void *);
void sub_080C31E4(void *, void *, s32);

struct S_02025FF0_3C {
    u8 pad[0x3C];
    u16 globalFlag;
};
extern struct S_02025FF0_3C D_02025FF0;

/* Actor step: advance the animator script and aim the sprite, then, while a
 * global flag is set, reset the script step and dispatch the handler when the
 * actor is near the player or its wake flag (bit 1) is set. */
void sub_080A0B60(void *actor) {
    void *sprite = *(void **)((u8 *)actor + 0x38);
    void *work = *(void **)((u8 *)actor + 0x3C);
    s32 *handlerTable;

    sub_08011528(sprite, (u8 *)work + 0x34);
    sub_080A1744(sprite, work);
    if (D_02025FF0.globalFlag != 0) {
        if (sub_0801459C(work, 0x600000) != 0 || (*(u16 *)work & 2)) {
            s32 idx = *(s16 *)((u8 *)actor + 0x22);
            *(u8 *)((u8 *)actor + idx * 2 + 0x19) = 0;
            handlerTable = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)actor + 0x18, (u8 *)actor + 0x22, *handlerTable);
        }
    }
}
