struct S_02025FF0_ab { u8 _0x000[0x1868]; s32 v1868; u8 _pad[0x1874 - 0x186C]; s32 v1874; };
extern struct S_02025FF0_ab gMainWorkspace;
void *spawnBudgetedEffect(s32, s32);

/* Spawns a type-0x207 object under the given root and fills in its position,
 * timer pair and three extra init fields. */
void *sub_0808E348(s32 x, s32 y, s32 heading, s32 param8C, s32 param9C, u16 duration, u16 timer) {
    void *object = spawnBudgetedEffect(gMainWorkspace.v1874, 0x207);
    if (object == NULL) return NULL;
    *(s32 *)((u8 *)object + 0x4C) = x;
    *(s32 *)((u8 *)object + 0x5C) = y;
    {
        u8 *p = (u8 *)object + 0x6C;
        *(u16 *)p = timer;
        p += 8;
        *(u16 *)p = duration;
    }
    *(s32 *)((u8 *)object + 0x7C) = heading;
    *(s32 *)((u8 *)object + 0x8C) = param8C;
    *(s32 *)((u8 *)object + 0x9C) = param9C;
    return object;
}
