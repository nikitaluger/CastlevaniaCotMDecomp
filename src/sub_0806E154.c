extern u8 gMainWorkspace[];

void _call_via_r1(void *, void *);

/* Clear the actor's entry in the workspace's 32-slot object table (+0x1780,
 * indexed by the slot id at actor+0xAC), then resume the actor's previous
 * update handler saved in its state block at +0x1C. */
void sub_0806E154(void *arg0) {
    void **state = *(void ***)((u8 *)arg0 + 0x6C);
    u8 *workspace = gMainWorkspace;
    u32 tableOff = 0xBC << 5;
    u32 slot = *(u32 *)((u8 *)arg0 + 0xAC);
    *(u32 *)(workspace + tableOff + slot * 4) = 0;
    _call_via_r1(arg0, state[7]);
}
