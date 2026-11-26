extern u32 D_0866E584[];
extern void setAnimationFrame(void *, void *, s32, s32);

/* Switch this object to the state table at D_0866E584: reset its animation,
 * push a state slot, advance that slot's substep counter, run the new state's
 * handler, then pop the slot. */
void sub_0804F2B8(void *obj)
{
    u8 *o = (u8 *)obj;
    s16 slot;
    u8 state;

    setAnimationFrame(*(void **)(o + 0x38), *(u8 **)(o + 0x3C) + 0x34, 0, 1);

    *(u32 *)(o + 0x14) = (u32)D_0866E584;
    *(u16 *)(o + 0x22) += 1;

    slot = *(s16 *)(o + 0x22);
    *(u8 *)(o + 0x19 + slot * 2) += 1;

    slot = *(s16 *)(o + 0x22);
    {
        s32 off = slot * 2;
        u8 *p = o;
        p += 0x18;
        p = p + off;
        state = *p;
    }

    ((void (**)(void *))*(u32 *)(o + 0x14))[state](obj);

    *(u16 *)(o + 0x22) -= 1;
}
