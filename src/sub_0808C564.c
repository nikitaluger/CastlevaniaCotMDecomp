s32 sub_08003740(void *, void *);
void sub_080C31E4(void *, void *, s32);

struct S_02025FF0 { u8 pad[0x14AC]; s32 state14AC; };
extern struct S_02025FF0 gMainWorkspace;

/* Tick of a grounded actor: when its movement timer has run out, switch the
 * global state to 5, clear the current script step and advance the script. */
void sub_0808C564(void *arg0)
{
    void *mover = *(void **)((u8 *)arg0 + 0x6C);
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    s32 timerDone = sub_08003740((u8 *)mover + 0x20, sprite);
    if (timerDone == 0) {
        gMainWorkspace.state14AC = 5;
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = 0;
        {
            s32 *stepTable = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *stepTable);
        }
    }
}
