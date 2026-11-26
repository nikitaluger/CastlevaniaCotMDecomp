void setObjectAnimation(void *scene, void *anim, s32 animId, s32 flags);

/* One 4-byte entry of an animation's frame table; only its second halfword is read here. */
struct AnimFrame { u8 pad[2]; u16 v; };

/* Start animation 3 with flags 1 on the object, then copy the halfword of the
 * current frame's previous entry into the output object and clear its +0x17 byte. */
void sub_080A1780(void *scene, void *obj, void *out)
{
    s32 *table;
    s32 idx;
    u16 frame;
    s32 zero;

    setObjectAnimation(scene, obj, 3, 1);
    table = *(s32 **)((u8 *)obj + 8);
    idx = *(s16 *)((u8 *)obj + 0xE) + *(u8 *)((u8 *)obj + 1);
    frame = ((struct AnimFrame *)((u8 *)*table + idx * 4 - 4))->v;
    zero = 0;
    *(u16 *)((u8 *)out + 0x14) = frame;
    *(u8 *)((u8 *)out + 0x17) = zero;
}
