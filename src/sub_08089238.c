void sub_08003740(void *, void *);
void sub_08003A6C(void *, s32, void *);
void sub_0806D588(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Update a falling object: mirror its Y into the game state, drop one pixel
 * per frame, and once it is low enough run the cutscene script and switch
 * game mode. */
void sub_08089238(void *arg0)
{
    u8 *entity = (u8 *)arg0;
    u8 *work = *(u8 **)(entity + 0x6C);
    u8 *pos = work + 4;
    u8 *obj = *(u8 **)(entity + 0x38);
    u8 *game = (u8 *)0x02025FF0;

    *(s32 *)(game + 0x38) = *(s32 *)(obj + 0x14);
    *(s32 *)(work + 4) += 0x10000;

    if (*(s32 *)(obj + 0x14) > 0x67FFFF)
    {
        s32 *litp;
        sub_08003A6C(work + 0x20, 0, (void *)0x08500D48);
        *(s32 *)(game + 0x1C) = 2;
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = 0;
        litp = (s32 *)0x08671BB0;
        sub_080C31E4(entity + 0x18, entity + 0x22, *litp);
    }

    sub_08003740(work + 0x20, obj);
    sub_0806D588(obj, pos);
}
