extern u8 D_02025FF0[];

/* Return the current actor's state byte at actor+0x9C; the actor pointer is
 * held in the workspace at +0x1724. */
u8 sub_0806DDF4(void) {
    u32 off = 0x1724;
    u8 *actorSlot = D_02025FF0;
    actorSlot = actorSlot + off;
    return *(u8*)(*(u32*)actorSlot + 0x9C);
}
