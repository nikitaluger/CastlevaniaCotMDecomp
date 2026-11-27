extern void setAnimationFrame(s32, void *, s32, s32);
extern void updateFollowPath(void *, void *, s32, s32);

struct S_02025FF0_174C { u8 _0[0x174C]; u32 a; u32 b; };
extern struct S_02025FF0_174C gMainWorkspace;

/* Play pose 14 and steer the follow path at body+0x50 toward the global
 * target point; when the path hits its turn limit (dirFlags bit 2), flag the
 * motion state as complete. */
void sub_08022708(void *arg0)
{
    s32 sprite = *(s32 *)((u8 *)arg0 + 0x38);
    u8 *body = *(u8 **)((u8 *)arg0 + 0x3C);
    void *anim = body + 0x34;
    u8 *motion = body + 0x48;

    setAnimationFrame(sprite, anim, 0xE, 1);
    updateFollowPath(body, body + 0x50, gMainWorkspace.a, gMainWorkspace.b);
    if (4 & *(u16 *)(motion + 0x20))
        *(u16 *)motion = 1;
}
