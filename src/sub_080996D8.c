struct S_02025FF0
{
    u8 _0[0x174C];
    u32 targetX; /* 0x174C */
    u32 targetY; /* 0x1750 */
};
extern struct S_02025FF0 gMainWorkspace;
extern u32 gTrigFuncPtr;
extern u32 gScriptStepCallbackTable;
s32 sub_08005910(s32, s32);
void sub_08005E80(s32);
void setObjectAnimation(void *, void *, s32, s32);
void sub_08011EE8(void *, s32, s32);
void sub_080148D8(void *, s32);
void sub_0809C4E0(s32, s32);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Enemy script dispatch: set facing and base velocity, run the movement
   helper for low script IDs, and aim a shot at the player for script ID 0x3C. */
void sub_080996D8(void *arg0)
{
    void *self = arg0;
    void *mainObj = *((void **) (((u8 *) self) + 0x38));
    void *base = *((void **) (((u8 *) self) + 0x3C));
    void *p34 = (void *) (((u8 *) base) + 0x34);
    void *p48 = (void *) (((u8 *) base) + 0x48);
    sub_080148D8(mainObj, *((s32 *) (((u8 *) base) + 0x08)));
    {
        s32 velX;
        if ((*((u16 *) (((u8 *) mainObj) + 0x02))) & 0x10)
        {
            velX = (s32) 0xFFFF8000;
        }
        else
        {
            velX = 0x8000;
        }
        *((s32 *) (((u8 *) base) + 0x10)) = velX;
    }
    {
        s16 idx = *((s16 *) (((u8 *) self) + 0x22));
        u8 cmd = *((u8 *) ((((u8 *) self) + (idx * 2)) + 0x19));
        if (cmd <= 9)
        {
            sub_08011EE8(base, 0x16C1, 0);
        }
    }
    {
        s16 idx = *((s16 *) (((u8 *) self) + 0x22));
        u8 cmd = *((u8 *) ((((u8 *) self) + (idx * 2)) + 0x19));
        if (cmd == 0x28)
        {
            sub_0809C4E0(*((s32 *) (((u8 *) p48) + 0x08)), 1);
        }
    }
    {
        s16 idx = *((s16 *) (((u8 *) self) + 0x22));
        u8 cmd = *((u8 *) ((((u8 *) self) + (idx * 2)) + 0x19));
        if (cmd == 0x3C)
        {
            s32 angle;
            angle = sub_08005910(gMainWorkspace.targetY - (*((s32 *) (((u8 *) base) + 0x0C))), gMainWorkspace.targetX - (*((s32 *) (((u8 *) base) + 0x08))));
            {
                u32 scaled = (u32) (angle + 0xFFFF5FFF);
                if (scaled <= 0x3FFE)
                {
                    if ((*((u16 *) (((u8 *) mainObj) + 0x02))) & 0x10)
                    {
                        angle = 0xE000;
                    }
                    else
                    {
                        angle = 0xA000;
                    }
                }
            }
            {
                u32 *angleFunc = &gTrigFuncPtr;
                *((s32 *) (((u8 *) base) + 0x10)) = (s32) ((sub_080C31E0(angle + 0x4000, *angleFunc) >> 8) << 11);
                *((s32 *) (((u8 *) base) + 0x14)) = (s32) ((sub_080C31E0(angle, *angleFunc) >> 8) << 11);
            }
            setObjectAnimation(mainObj, p34, 0x26, 0);
            sub_08005E80(0x164);
            *((u8 *) ((((u8 *) self) + ((*((s16 *) (((u8 *) self) + 0x22))) * 2)) + 0x19)) = 0;
            {
                u32 *cmdTable = &gScriptStepCallbackTable;
                sub_080C31E4(((u8 *) self) + 0x18, ((u8 *) self) + 0x22, *cmdTable);
            }
        }
    }
}
