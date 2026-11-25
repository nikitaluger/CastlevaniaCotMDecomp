void sub_080BB940(void *, void *); /* drive the partner actor's vertical bob */
s32 sub_08098754(void *);          /* partner reached its finished state */
void sub_080C31E8(void *, void *, s32, s32);

/* Attached-actor check: drive the partner actor's vertical bob and, once the
 * partner reports it is finished, clear this script step's state byte and
 * advance through handler table 0x08671BD8. */
void sub_080BACF0(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *work = *(void **)(self + 0x3C);
    void *partner = *(void **)(self + 0x4C);
    sub_080BB940(work, partner);
    if (sub_08098754(partner) != 0) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = 0;
        {
            s32 *scriptTable;
            scriptTable = (s32 *)0x08671BD8;
            sub_080C31E8(self + 0x18, self + 0x22, 0, *scriptTable);
        }
    }
}
