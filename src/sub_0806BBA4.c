extern void *gScriptStepCallbacks;
struct WorldFlags { u8 pad[0x146C]; u16 flags; };
extern struct WorldFlags gCameraState;

void sub_0806DD94(void);
s32 setEntityForm(void *, void *, s32);
void sub_08005E80(s32);
void sub_080C31E8(void *, void *, s32, s32);

/*
 * Tests global mode/input flags to decide whether a companion action is allowed;
 * on the go path it masks a state word, triggers an effect and fires the current
 * pose's attack routine from gScriptStepCallbacks.
 */
s32 sub_0806BBA4(void *arg0, void *arg1, void *arg2) {
    u8 *dataTable = (u8 *)0x02025368;
    u8 *gsBase = (u8 *)0x02025FF0;
    u8 mode = gsBase[0x14ED];
    u8 *gsState = gsBase;
    u8 val;
    s16 poseIndex;

    if (mode != 0) {
        if (*(s32 *)(gsState + 0x24) != 0) {
            if ((*(u16 *)(gsState + 0x28) & *(u16 *)(dataTable + 0x3C2)) != 0) goto success;
            goto ret0;
        } else {
            if ((gCameraState.flags & *(u16 *)(dataTable + 0x3C2)) == 0) goto ret0;
        }
success:
        sub_0806DD94();
        return 2;
    }
    if (*(s32 *)(gsState + 0x24) != 0) {
        if ((*(u16 *)(gsState + 0x28) & *(u16 *)(dataTable + 0x3C2)) != 0) goto cont;
        goto ret0;
    } else {
        if ((gCameraState.flags & *(u16 *)(dataTable + 0x3C2)) == 0) goto ret0;
    }
cont:
    val = *(u8 *)(dataTable + 0x2DB);
    if (val == 0 && *(u8 *)(dataTable + *(u8 *)(dataTable + 0x305) + 0x315) != 0 && *(u8 *)(dataTable + *(u8 *)(dataTable + 0x304) + 0x30B) != 0) {
        *(s32 *)(gsState + 0x1848) |= 0x49FE0000;
        setEntityForm(arg1, arg2, 0x35);
        sub_08005E80(0x12C);
        *(s32 *)((u8 *)arg2 + 0x8C) = 1;
        poseIndex = *(s16 *)((u8 *)arg0 + 0x22);
        *((u8 *)arg0 + poseIndex*2 + 0x19) = val;
        {
            u32 *attackTable = (u32 *)0x08671BD0;
            sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 0x1C, *attackTable);
        }
        return 1;
    }
ret0:
    return 0;
}
