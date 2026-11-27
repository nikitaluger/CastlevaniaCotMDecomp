extern s32 sub_080057F8(void);
extern void sub_08005E80(u16);
extern void forceAnimationFrame(s32, u8 *, s32, s32);
extern void setObjectAnimation(s32, u8 *, s32, s32);
extern void sub_08011528(s32, u8 *);
extern void sub_080148D8(s32, s32);
extern void sub_0809A610(void *);
extern void sub_0809C4E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
void sub_080994DC(void *arg0)
{
    s32 sprite;
    int step;
    u8 *anim;
    s32 *posXPtr;
    u8 *state;
    u8 *body;
    s32 counter;
    s32 zero;
    s16 actionIndex;
    u8 *selfAlias;
    u8 *actionByte;
    u8 *counterPtr;
    s32 *callback;

    sprite = *((s32 *) (((u8 *) arg0) + 0x38));
    state = *((u8 **) (((u8 *) arg0) + 0x3C));
 do { anim = state + 0x34; } while (0);
    body = state + 0x48;
    sub_0809A610(arg0);
    sub_08011528(sprite, anim);
    if ((*anim) & 2)
    {
        counterPtr = state + 0x6A;
        counter = (*((u8 *) counterPtr)) + 1;
        zero = 0;
        posXPtr = (s32 *) (state + 8);
        *((u8 *) counterPtr) = counter;
        if ((counter & 0xF) == 2)
        {
            if (counter & 0x80)
            {
                actionIndex = *((s16 *) (((u8 *) arg0) + 0x22));
                actionByte = (u8 *) ((actionIndex * 2) + ((u32) arg0));
                actionByte[0x17] = zero;
                callback = (s32 *) 0x08671BD8;
                sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 3, *callback);
            }
            else
            {
                setObjectAnimation(sprite, anim, 0xF, zero);
                sub_0809C4E0(*((s32 *) (body + 8)), zero);
                step = 2;
                actionIndex = *((s16 *) (((u8 *) arg0) + 0x22));
                actionByte = (u8 *) (((u32) (actionIndex * step)) + ((u32) arg0));
                actionByte[0x19] = zero;
                callback = (s32 *) 0x08671BD0;
                sub_080C31E8((selfAlias = (u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 4, *callback);
            }
        }
        else
            if ((sub_080057F8() & 3) == 0)
            {
                forceAnimationFrame(sprite, anim, zero, zero);
                sub_080148D8(sprite, *posXPtr);
            }
            else
            {
                setObjectAnimation(sprite, anim, 0xF, zero);
                sub_080148D8(sprite, *((s32 *) (state + 8)));
                *((u8 *) (state + 0x69)) = zero;
                sub_0809C4E0(*((s32 *) (body + 8)), zero);
                sub_08005E80(0x165);
                actionIndex = *((s16 *) (((u8 *) arg0) + 0x22));
                actionByte = (u8 *) (((u32) (actionIndex * 2)) + ((u32) arg0));
                actionByte[0x19] = zero;
                callback = (s32 *) 0x08671BB0;
                sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *callback);
            }
    }
}
