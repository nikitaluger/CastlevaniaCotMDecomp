s32 randomSignedOffset(s32);
void sub_080AAB04(s32, s32, s32);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Spawn a child actor at a script-selected position while the script flag's
 * low bits are clear; when the flag reaches 0x30, clear it, raise a script
 * event, bump the counter and dispatch the script's handler. */
void sub_080A7F78(void *actor)
{
    u8 *self = (u8 *)actor;
    u8 *state = *(u8 **)(self + 0x3C);
    u8 *work = state + 0x48;
    s32 spawnPos;

    if ((*(u8 *)((u8 *)self + (*(s16 *)(self + 0x22)) * 2 + 0x19) & 1) == 0)
    {
        if (*(u8 *)((u8 *)self + (*(s16 *)(self + 0x22)) * 2 + 0x19) & 2)
        {
            spawnPos = *(s32 *)(state + 0x08) + randomSignedOffset(0x200000);
        }
        else
        {
            spawnPos = *(s32 *)(self + 0x5C) + randomSignedOffset(0x400000);
        }
        sub_080AAB04(*(s32 *)(work + 0x138), spawnPos, 0x1E00000);
    }

    if (*(u8 *)((u8 *)self + (*(s16 *)(self + 0x22)) * 2 + 0x19) == 0x30)
    {
        *(u8 *)((u8 *)self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *eventPtr = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *eventPtr);
        }
        {
            u8 *scriptPtr = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            scriptPtr[0x19] = (u8)(scriptPtr[0x19] + 1);
        }
        {
            s32 scriptOffset = (*(s16 *)(self + 0x22)) * 2;
            u8 *scriptData = (u8 *)self + 0x18;
            u8 handlerIndex = *(scriptData + scriptOffset);
            u8 **handlerTable = *(u8 **)((u8 *)self + 0x14);
            sub_080C31E0(self, (void *)handlerTable[handlerIndex]);
        }
    }
}
