extern void sub_080C31E4(void *a, void *b, s32 c);

extern s32 gMainObjTimerCallback[];

/* Count down the timer in the object's extra state; when it expires, advance
 * the object's command script. */
void sub_08072218(void *obj)
{
    u8 *p = (u8 *)obj;
    u8 *state = *(u8 **)(p + 0x6C) + 4;
    s32 remaining = *(s32 *)(state + 0x2C) - 1;
    *(s32 *)(state + 0x2C) = remaining;
    if (remaining == 0)
    {
        *(u8 *)(p + (*(s16 *)(p + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *nv = gMainObjTimerCallback;
            sub_080C31E4(p + 0x18, p + 0x22, *nv);
        }
    }
}
