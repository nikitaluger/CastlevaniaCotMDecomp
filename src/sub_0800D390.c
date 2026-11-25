extern void sub_08005E80(s32);
extern void sub_08006210(void);
extern void sub_0800EB44(u16, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

struct S_020278D0 {
    u8 _0[0x64];
    u8 chosenValue;
    u8 _65[3];
    s8 selection;
};
extern struct S_020278D0 D_020278D0;

struct S_02021E90 {
    u8 _0[0x146C];
    u16 actionButtons;
    u8 _2[0x1470 - 0x146E];
    u16 dirButtons;
};
extern struct S_02021E90 D_02021E90;

extern u8 D_080CAFF8[];
extern u8 D_080CB002[];
extern u32 D_08671BD8[];

/* Handle menu-selection input: move the five-way cursor with the direction
 * bits, play a sound and redraw when it changes, then dispatch the confirm or
 * cancel callback. */
void sub_0800D390(void *obj)
{
    s32 oldSelection;
    u16 dirButtons;
    u16 actionButtons;
    u32 buttonBits;

    oldSelection = D_020278D0.selection;
    dirButtons = D_02021E90.dirButtons;
    {
        u32 bothDirs = 0xC0;

        bothDirs &= dirButtons;
        if (bothDirs != 0xC0) {
            u32 dirMinus = 0x40;

            dirMinus &= dirButtons;
            if (dirMinus != 0) D_020278D0.selection--;
            {
                u16 dirButtons2 = D_02021E90.dirButtons;
                u32 dirPlus = 0x80;

                dirPlus &= dirButtons2;
                if (dirPlus != 0) D_020278D0.selection++;
            }
            if (D_020278D0.selection < 0) D_020278D0.selection = 4;
            if (D_020278D0.selection > 4) D_020278D0.selection = 0;
        }
    }
    if (oldSelection != D_020278D0.selection) {
        u8 *gfxTable;
        s32 selection;

        sub_08005E80(0x14E);
        gfxTable = D_080CAFF8;
        selection = D_020278D0.selection;
        sub_0800EB44(*(u16 *)(gfxTable + selection * 2), 2, 0xFC0);
    }
    actionButtons = D_02021E90.actionButtons;
    buttonBits = 0xA;
    buttonBits &= actionButtons;
    if (buttonBits != 0) {
        sub_08005E80(0x14F);
        sub_08006210();
        *(u8 *)((u8 *)obj + *(s16 *)((u8 *)obj + 0x22) * 2 + 0x17) = 0;
        {
            u32 *callbackTbl = D_08671BD8;

            sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, 0x10, callbackTbl[0]);
        }
        return;
    }
    {
        u32 confirmBit = 0x01;

        confirmBit &= actionButtons;
        if (confirmBit != 0) {
            sub_08005E80(0x13B);
            D_020278D0.chosenValue = D_080CB002[D_020278D0.selection];
            *(u8 *)((u8 *)obj + *(s16 *)((u8 *)obj + 0x22) * 2 + 0x17) = buttonBits;
            {
                u32 *callbackTbl2 = D_08671BD8;

                sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, 0xE, callbackTbl2[0]);
            }
        }
    }
}
