extern void sub_080BB940(s32, s32);
extern void sub_080BE8D0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);

struct GameState { u8 pad[0x10]; s32 mode; };

/* Refreshes the companion object's facing, then ramps the linked blend value up
 * by 0x200 per frame toward 0x10000 (1.0) and writes it to the blend object;
 * when it saturates, switches the game mode to 0x0D, clears the current script
 * action byte and advances the script. */
void sub_080BB600(void *arg0) {
    void *actor;
    void *control;
    s32 max;
    s32 value;
    s16 idx;
    s32 *scriptTable;

    actor = arg0;
    control = *((void **)((s8 *)actor + 0x3C)) + 0x48;

    sub_080BB940(*((s32 *)((s8 *)actor + 0x3C)), *((s32 *)((s8 *)actor + 0x4C)));
    value = *((s32 *)((s8 *)control + 0x40)) + (0x80 << 2);
    *((s32 *)((s8 *)control + 0x40)) = value;
    max = 0x80 << 9;
    if (value > max) {
        *((s32 *)((s8 *)control + 0x40)) = max;
    }
    sub_080BE8D0(*((s32 *)((s8 *)control + 0x34)), *((s32 *)((s8 *)control + 0x40)));
    if (*((s32 *)((s8 *)control + 0x40)) == max) {
        ((struct GameState *)0x02025FF0)->mode = 0x0D;
        idx = *((s16 *)((s8 *)actor + 0x22));
        *((u8 *)((s8 *)actor + idx * 2 + 0x19)) = 0;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4((s8 *)actor + 0x18, (s8 *)actor + 0x22, *scriptTable);
    }
}
