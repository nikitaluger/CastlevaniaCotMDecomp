/* Entity action: a random timer triggers sounds/effects, a target flag selects
 * the facing direction, an animation-id table is checked, and horizontal
 * velocity is mirrored based on position thresholds. */
s32 sub_080057F8(void);
void sub_0809C5F4(s32);
void sub_0809C4E0(s32, s32);
void sub_0809C5E4(s32);
void sub_08011EE8(void *, s32, s32);
void setSpriteFlipForDirection(void *, s32);

void sub_0809A610(void *entity)
{
    void *target = *((void **)((u8 *)entity + 0x38));
    u8 *state = *((u8 **)((u8 *)entity + 0x3C));
    u8 *anim = state + 0x34;
    u8 *ctrl = state + 0x48;
    u8 *counter;
    s32 v0, v1;
    
    if ((sub_080057F8() & 0xFF) == 0)
    {
        sub_0809C5F4(*((s32 *)(ctrl + 0x14)));
    }
    
    counter = state + 0x69;
    v0 = *counter;
    if (v0 != 0)
    {
        v0 = v0 - 1;
        *counter = v0;
        if ((v0 << 0x18) == 0)
        {
            sub_0809C4E0(*((s32 *)(ctrl + 0x08)), 0);
        }
    }
    else if ((sub_080057F8() & 0x7F) == 0)
    {
        *counter = 0x10;
        sub_0809C4E0(*((s32 *)(ctrl + 0x08)), 1);
        sub_0809C5E4(*((s32 *)(ctrl + 0x08)));
    }
    
    if ((sub_080057F8() & 0x7F) == 0)
    {
        sub_0809C5E4(*((s32 *)(ctrl + 0x08)));
    }
    
    v1 = *((u16 *)((u8 *)target + 0x02));
    v0 = v1 & 0x10;
    if (v0 != 0)
    {
        v1 = 0x8000;
    }
    else
    {
        v1 = 0xFFFF8000;
    }
    *((s32 *)(state + 0x10)) = v1;
    *((s32 *)(state + 0x14)) = 0;
    
    v1 = *((s32 *)(anim + 0x08));
    v0 = *((s16 *)(anim + 0x0E));
    v0 = v0 + *((u8 *)(anim + 0x01));
    v1 = *((s32 *)v1);  // dereference HERE (after v0 += anim[1])
    v0 = v0 << 2;
    v0 = v0 + v1;
    v0 = v0 - 4;
    v0 = *((u16 *)(v0 + 0x02));
    
    if (v0 != 0 && v0 != 0x25)
    {
        sub_08011EE8(state, 0x16C1, 0);
    }
    
    v1 = *((s32 *)(state + 0x10));
    setSpriteFlipForDirection(target, v1);
    
    v1 = *((s32 *)(state + 0x08));
    if (v1 <= 0x3FFFFF)
    {
        v0 = *((s32 *)(state + 0x10));
        if (v0 < 0)
            v0 = -v0;
        *((s32 *)(state + 0x10)) = v0;
    }
    
    v1 = *((s32 *)(state + 0x08));  // force reload
    if (v1 > 0x1C00000)
    {
        v0 = *((s32 *)(state + 0x10));
        if (v0 < 0)
            v0 = -v0;
        v0 = -v0;
        *((s32 *)(state + 0x10)) = v0;
    }
}
