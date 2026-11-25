extern u32 D_0866D968[];

/* Push a handler frame: install the state table at 0x14, advance the frame
 * depth at 0x22, bump this frame's counter and dispatch to the handler
 * picked by the frame's entry byte. */
void sub_08025B94(void *obj)
{
    u8 *o = (u8 *)obj;
    s16 depth;
    u8 handler;

    *(u32 *)(o + 0x14) = (u32)D_0866D968;
    *(u16 *)(o + 0x22) += 1;

    depth = *(s16 *)(o + 0x22);
    *(u8 *)(o + 0x19 + depth * 2) += 1;

    depth = *(s16 *)(o + 0x22);
    {
        s32 off = depth * 2;
        u8 *addr = o;
        addr += 0x18;
        addr = addr + off;
        handler = *addr;
    }

    ((void (**)(void *))*(u32 *)(o + 0x14))[handler](obj);

    *(u16 *)(o + 0x22) -= 1;
}
