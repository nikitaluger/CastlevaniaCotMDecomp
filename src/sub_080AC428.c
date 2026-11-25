void sub_0808BBAC(s32, s32, s32);
void sub_0808D0A4(s32);
void sub_08005E80(s32);
void sub_080C31E4(void *, void *, s32);

/* Scene transition: paint the backdrop white, queue the (1, 8, 1) palette/fade
 * request, play sound effect 0x10 and song 0x17E, then clear the script action
 * byte and dispatch the next handler. */
void sub_080AC428(void *self) {
    s32 *handlerTable;
    *((s16 *) 0x05000000) = 0x7FFF;
    sub_0808BBAC(1, 8, 1);
    sub_0808D0A4(0x10);
    sub_08005E80(0x17E);
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) self) + 0x22))) * 2) + self)) + 0x19)) = 0;
    handlerTable = (s32 *) 0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
}
