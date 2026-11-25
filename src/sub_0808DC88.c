extern u32 D_02025FF0[];
extern void *sub_0805FAEC(void *, s32);

/* Spawn effect object 0x204 for the current owner at (x, y), storing the
 * 16-bit param at +0x6C and byte 3 at +0x74; NULL if the pool is full. */
void *sub_0808DC88(s32 x, s32 y, u16 param) {
    s32 px = x;
    s32 py = y;
    s32 pparam = param;
    u32 ownerOff;
    void *owner;
    void *effect;
    s32 scratch;

    ownerOff = 0x1874;
    owner = *(void **)((u8 *)D_02025FF0 + ownerOff);
    scratch = 0x81;
    scratch = scratch << 2;
    effect = sub_0805FAEC(owner, scratch);
    if (effect == 0) return 0;
    *(s32 *)((u8 *)effect + 0x4C) = px;
    *(s32 *)((u8 *)effect + 0x5C) = py;
    owner = (u8 *)effect + 0x6C;
    *(u16 *)owner = (u16)pparam;
    scratch = effect;
    scratch = scratch + 0x74;
    *(u8 *)scratch = 3;
    return effect;
}
