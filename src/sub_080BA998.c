void sub_080BB984(void *, void *); /* tick the multi-part actor's bob timer */
void sub_080BB9C8(void *);         /* update the attached-part animation */
void sub_080BBA4C(void *);         /* position the attached parts */
void sub_080C31E4(void *, void *, s32);

/* Attached-walk update: step the actor's bob timer and part animation, move the
 * attached parts at step 0x0C, and at step 0x3C clear the step and advance the
 * script. */
void sub_080BA998(void *arg0) {
    void *work = *(void **)((u8 *)arg0 + 0x3C);
    sub_080BB984(work, (u8 *)work + 0x48);
    sub_080BB9C8(arg0);
    if (*(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) == 0x0C)
        sub_080BBA4C(arg0);
    if (*(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) == 0x3C) {
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = 0;
        {
            s32 *scriptTable;
            scriptTable = (s32 *)0x08671BB0;
            sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *scriptTable);
        }
    }
}
