extern void sub_080BB940(void *a, void *b);
extern void sub_080BB984(void *a, void *b);
extern void sub_080BBB60(void *a);
extern void sub_0801165C(void *a, s32 b);
extern void sub_080BE8D0(s32 a, s32 b);
extern void sub_080BB898(void *a);
extern void sub_080C31E4(void *a, void *b, s32 c);

/* Script-step callback: updates the companion's AI state and integrates its
 * motion, then ramps a control value up to 0x10000 and writes it to a target
 * object; once saturated it resets the step and redirects the script. */
void sub_080BB204(u8 *arg0)
{
    u8 *scriptState = *(u8 **)(arg0 + 0x3C);
    u8 *control = scriptState + 0x48;
    u8 *targetObj = *(u8 **)(arg0 + 0x4C);

    if (*(u8 *)(targetObj + 0x25) != 2)
        sub_080BB940(scriptState, targetObj);
    else
        sub_080BB984(scriptState, control);

    sub_080BBB60(scriptState);
    sub_0801165C(scriptState, 0);

    *(s32 *)(control + 0x40) += 0x600;
    if (*(s32 *)(control + 0x40) > 0x10000)
        *(s32 *)(control + 0x40) = 0x10000;

    sub_080BE8D0(*(s32 *)(control + 0x34), *(s32 *)(control + 0x40));

    if (*(s32 *)(control + 0x40) == 0x10000) {
        sub_080BB898(control);
        *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = 0;
        {
            s32 *lit = (s32 *)0x08671BB0;
            sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *lit);
        }
    }
}
