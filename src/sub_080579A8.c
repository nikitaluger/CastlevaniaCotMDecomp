extern void sub_080C31E0(void *, void *);
extern u32 D_080CFD20[];
struct S2_080579A8 { u8 pad[2]; u16 f2; };

/* Set up a moving effect object: copy its start/target coordinates, take the
 * velocity for its direction from the table (mirrored by its facing sign), set
 * the owner's facing bit and jump to the movement handler. */
void sub_080579A8(void *arg0p)
{
    u8 *self = (u8 *)arg0p;
    u8 *owner = *(u8 **)(self + 0x38);
    u32 *moveState = *(u32 **)(self + 0x3C);
    u8 *facing = self;
    facing += 0x80;
    if (*(s8 *)facing > 0) {
        ((struct S2_080579A8 *)owner)->f2 |= 0x10;
    }
    moveState[0] = *(u32 *)(self + 0x5C);
    moveState[1] = *(u32 *)(self + 0x6C);
    {
        u8 *velocityTable = (u8 *)D_080CFD20;
        u8 *dirIndex = self;
        s32 entryOffset;
        dirIndex += 0x7C;
        moveState[2] = *(u32 *)(velocityTable + *dirIndex * 8) * *(s8 *)facing;
        entryOffset = *dirIndex * 8;
        velocityTable += 4;
        moveState[3] = *(u32 *)(velocityTable + entryOffset);
    }
    *(u32 *)(self + 0x14) = 0x08057A0D;
    *(u16 *)(self + 0x22) = 1;
    sub_080C31E0(self, (void *)0x08057A0D);
}
