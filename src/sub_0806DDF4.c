extern u8 gMainWorkspace[];

/* Return the current actor's state byte at actor+0x9C; the actor pointer is
 * held in the workspace at +0x1724. */
u8 sub_0806DDF4(void) {
    u32 off = 0x1724;
    u8 *actorSlot = gMainWorkspace;
    actorSlot = actorSlot + off;
    return *(u8*)(*(u32*)actorSlot + 0x9C);
}
