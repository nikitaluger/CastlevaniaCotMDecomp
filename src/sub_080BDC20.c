extern s32 sub_08013B5C(void *, void *);
extern void sub_08098428(s32);
extern void sub_080984C4(s32);
extern void sub_080C31E0(void *, s32);

struct ScriptState { u8 pad[0x18]; u8 handlers[8]; };

/* Dispatches the current script step when display handling is idle, then
 * applies a palette effect whenever the entity's state byte or its linked
 * data pointer changes. */
void sub_080BDC20(void *arg0)
{
    s16 step;
    u8 handler;
    u8 *newState;
    u8 *oldState;
    u8 stateValue;
    s32 *handlerTable;

    if (sub_08013B5C(*(void **)((u8 *)arg0 + 0x38), *(void **)((u8 *)arg0 + 0x3C)) == 0) {
        *(u32 *)((u8 *)arg0 + 0x14) = 0x08670738;
        *(u16 *)((u8 *)arg0 + 0x22) += 1;
        step = *(s16 *)((u8 *)arg0 + 0x22);
        *(u8 *)((u8 *)arg0 + step * 2 + 0x19) += 1;
        step = *(s16 *)((u8 *)arg0 + 0x22);
        handler = ((struct ScriptState *)arg0)->handlers[step * 2];
        handlerTable = *(s32 **)((u8 *)arg0 + 0x14);
        sub_080C31E0(arg0, handlerTable[handler]);
        *(u16 *)((u8 *)arg0 + 0x22) -= 1;
    }
    newState = (u8 *)arg0 + 0x54;
    oldState = (u8 *)arg0 + 0x50;
    stateValue = *oldState;
    if (*(s8 *)newState != *(s8 *)oldState || *(s32 *)((u8 *)arg0 + 0x6C) != *(s32 *)((u8 *)arg0 + 0x5C)) {
        *newState = stateValue;
        handlerTable = *(s32 **)((u8 *)arg0 + 0x5C);
        *(s32 **)((u8 *)arg0 + 0x6C) = handlerTable;
        switch (*(s8 *)oldState) {
        case 0:
            sub_08098428(0x11);
            sub_080984C4(0);
            break;
        case 1:
            sub_08098428(0x15);
            sub_080984C4(4);
            break;
        case 2:
            sub_08098428(0x1F);
            sub_080984C4(6);
            break;
        }
    }
}
