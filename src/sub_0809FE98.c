void sub_080C31E4(void *, void *, s32);
void sub_080C31E8(void *, void *, s32, s32);
void sub_08097EF4(s32, s32, s32, s32);
void sub_08097F70(s32, s32);

/* Sets the entity's +0x7C mode to 2; if the current script command is 0x14,
 * clears that command slot and re-dispatches the command script. */
void sub_0809FE98(void *entity)
{
    u8 *self = (u8 *)entity;
    *(u8 *)(self + 0x7C) = 2;
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x14) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *scriptArg = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *scriptArg);
        }
    }
}

/* Advances the sprite's u16 counter at +4 by 0x34; once it passes 0x03FF,
 * clears the flag at +0x2A, resets the entity mode and script slot and
 * re-dispatches with argument 0. The counter is mirrored to +6 each time. */
void sub_0809FED0(void *entity)
{
    u8 *self = (u8 *)entity;
    u8 *gfx = *(u8 **)(self + 0x38);
    u16 value = *(u16 *)(gfx + 4) + 0x34;
    *(u16 *)(gfx + 4) = value;
    if ((s32)((u32)value << 16) > 0x03FF0000) {
        *(u8 *)(gfx + 0x2A) &= 0xBF;
        *(u8 *)(self + 0x7C) = 0;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *scriptArg = (s32 *)0x08671BD0;
            sub_080C31E8(self + 0x18, self + 0x22, 0, *scriptArg);
        }
    }
    *(u16 *)(gfx + 6) = *(u16 *)(gfx + 4);
}

/* Decrements the sprite's u16 counter at +4 by 0x1C, clamping it to 0x100;
 * on the clamp the script slot is cleared and re-dispatched. The counter is
 * mirrored to +6 each time. */
void sub_0809FE54(void *entity)
{
    u8 *self = (u8 *)entity;
    u8 *gfx = *(u8 **)(self + 0x38);
    s16 value = *(u16 *)(gfx + 4) - 0x1C;
    *(u16 *)(gfx + 4) = value;
    if ((s32)value <= 0x100) {
        *(u16 *)(gfx + 4) = 0x100;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *scriptArg = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *scriptArg);
        }
    }
    *(u16 *)(gfx + 6) = *(u16 *)(gfx + 4);
}

/* Records variant on the entity, looks up its palette index in the table at
 * 0x0866FDE4, mirrors that index into the global at 0x020279F6, then loads
 * the matching palette data and starts the associated sound. */
void sub_080A0340(void *entity, s8 variant)
{
    u8 *self = (u8 *)entity;
    u16 *variantToPalette = (u16 *)0x0866FDE4;
    s32 index = (u8)variant;
    u16 palette;
    *(u8 *)(self + 0x6C) = variant;
    palette = variantToPalette[index];
    *(u16 *)((u8 *)0x020279F0 + 6) = palette;
    sub_08097EF4(0, *(s32 *)((u8 *)0x080CDAA8 + palette * 0x10), 3, 1);
    sub_08097F70(*(s32 *)((u8 *)0x080CDAA8 + palette * 0x10 + 4), 3);
}
