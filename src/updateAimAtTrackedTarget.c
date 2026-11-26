extern void sub_080160A0(s32, s32, s32, s32, void *);

/* Aims a character's weapon at the point tracked in its work block
 * (work+0x48: target x/y at +0x14/+0x18, "aim started" flag at +0x1C).
 * While bit 0x1000 of the controller flag halfword is held it either starts
 * the aim on the first frame (via sub_080160A0, which fills the controller's
 * output vector at +0x1C) or, once started, turns the stored aim into a
 * release vector (zero velocity, character-to-target delta); otherwise it
 * keeps updating the aim. */
void updateAimAtTrackedTarget(void *entity, void *controller)
{
    u8 *work = *(u8 **)((u8 *)entity + 0x3C);
    u8 *aim = work + 0x48;

    if (*(u16 *)controller & 0x1000)
    {
        if (*(s16 *)(aim + 0x1C) == 0)
        {
            *(s16 *)(aim + 0x1C) = 1;
            sub_080160A0(*(s32 *)(work + 8), *(s32 *)(work + 0xC),
                         *(s32 *)(aim + 0x14), *(s32 *)(aim + 0x18), controller);
        }
        else
        {
            u8 *vec = *(u8 **)((u8 *)controller + 0x1C);
            u16 flags = *(u16 *)((u8 *)controller + 2);
            s32 zero = 0;
            u8 *out;
            *(u16 *)vec = flags;
            out = *(u8 *volatile *)((u8 *)controller + 0x1C);
            *(s32 *)(out + 4) = zero;
            *(s32 *)(out + 8) = zero;
            *(s32 *)(out + 0xC) = *(s32 *)(work + 8) - *(s32 *)(aim + 0x14);
            *(s32 *)(out + 0x10) = *(s32 *)(work + 0xC) - *(s32 *)(aim + 0x18);
        }
    }
    else
    {
        sub_080160A0(*(s32 *)(work + 8), *(s32 *)(work + 0xC),
                     *(s32 *)(aim + 0x14), *(s32 *)(aim + 0x18), controller);
    }
}
