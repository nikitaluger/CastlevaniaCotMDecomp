struct S_03000830 { u8 _[4]; u16 f04; u16 f06; };
s32 sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);

#define IDLE_DISPLAY 0x3F52
#define COUNT_START  0x10

/* Actor countdown script step: publish the work's countdown byte and its
 * complement to the timer display register; when it reaches COUNT_START,
 * blank the display, advance the script and switch state, else increment it. */
void sub_0800A358(void *actor)
{
    void *work = *(void **)((u8 *)actor + 0x3C);
    struct S_03000830 *timerDisplay = (struct S_03000830 *)0x03000830;
    u8 countdown;
    u8 countdownNow;
    u16 idleValue = IDLE_DISPLAY;

    timerDisplay->f04 = idleValue;
    countdown = *(u8 *)((u8 *)work + 0x637);
    timerDisplay->f06 = countdown | ((COUNT_START - countdown) << 8);

    countdownNow = *(volatile u8 *)((u8 *)work + 0x637);
    if (countdownNow == COUNT_START) {
        timerDisplay->f04 = 0;
        *(u8 *)((u8 *)actor + (*(s16 *)((u8 *)actor + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *nextScriptTable = (s32 *)0x08671BB0;
            sub_080C31E4(actor + 0x18, actor + 0x22, *nextScriptTable);
        }
        {
            u8 *scriptBytePtr = (u8 *)((u32)(*(s16 *)((u8 *)actor + 0x22)) * 2 + (u32)actor);
            scriptBytePtr[0x19] = (u8)(scriptBytePtr[0x19] + 1);
        }
        {
            s32 scriptIndex = (*(s16 *)((u8 *)actor + 0x22)) * 2;
            u8 *scriptBase = (u8 *)actor + 0x18;
            u8 scriptByte = *(scriptBase + scriptIndex);
            u8 **stateTable = *(u8 **)((u8 *)actor + 0x14);
            sub_080C31E0(actor, (s32)stateTable[scriptByte]);
        }
    } else {
        *(u8 *)((u8 *)work + 0x637) = (u8)(countdownNow + 1);
    }
}
