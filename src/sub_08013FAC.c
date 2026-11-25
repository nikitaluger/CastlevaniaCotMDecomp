/* Countdown timer at +0x1E: when it expires, free the attached object at
 * +0x2C (sub_08015974), clear the pointer and clear flag 0x0004 in the
 * flags word at +0. */
void sub_08013FAC(void *obj)
{
    int remaining;
    remaining = *(u16 *)((char *)obj + 0x1E) - 1;
    *(u16 *)((char *)obj + 0x1E) = (u16)remaining;
    if ((s32)(remaining << 16) <= 0) {
        if (*(void **)((char *)obj + 0x2C) != 0) {
            sub_08015974();
            *(void **)((char *)obj + 0x2C) = 0;
        }
        *(u16 *)obj = (u16)(0xFFFB & *(u16 *)obj);
    }
}
