struct S_02025358 { u8 _[0x0C]; u8 flag; };
extern struct S_02025358 D_02025358;
extern s32 gScriptStepCallbackTable;
extern s32 gMenuScriptCallback;
void *createChildObject(void *, s32);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E8(void *, void *, s32, s32);

/* Branch on a global mode flag: either jump to an alternate script table, or
 * spawn a helper and advance this actor's script. */
void sub_08010B74(void *actor)
{
    u8 mode = D_02025358.flag;
    if (mode != 0) {
        *(u8 *)((u8 *)actor + (*(s16 *)((u8 *)actor + 0x22)) * 2 + 0x17) = 0;
        {
            s32 *altTable = (s32 *)0x08671BD8;
            sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, 0, *altTable);
        }
    } else {
        createChildObject(actor, 0x1F);
        *(u8 *)((u8 *)actor + (*(s16 *)((u8 *)actor + 0x22)) * 2 + 0x19) = mode;
        {
            s32 *scriptTable = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)actor + 0x18, (u8 *)actor + 0x22, *scriptTable);
        }
        {
            u8 *stepFlagPtr = (u8 *)((u32)(*(s16 *)((u8 *)actor + 0x22)) * 2 + (u32)actor);
            stepFlagPtr[0x19] = (u8)(stepFlagPtr[0x19] + 1);
        }
        {
            s32 actionOffset = (*(s16 *)((u8 *)actor + 0x22)) * 2;
            u8 *actionList = (u8 *)actor + 0x18;
            u8 actionId = *(actionList + actionOffset);
            u8 **stepHandlers = *(u8 **)((u8 *)actor + 0x14);
            sub_080C31E0(actor, (s32)stepHandlers[actionId]);
        }
    }
}
