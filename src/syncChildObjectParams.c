struct S338F0 { u8 pad[0x30]; u8 * volatile f30; };
struct O338F0 {
    u8 pad0[0x4C];
    u32 f4C;
    u8 pad1[0x5C - 0x50];
    u32 f5C;
    u8 pad2[0x6C - 0x60];
    u16 f6C;
    u8 pad3[0x74 - 0x6E];
    u16 f74;
    u8 pad4[0x7C - 0x76];
    u8 f7C;
    u8 pad5[0x80 - 0x7D];
    u8 f80;
    u8 pad6[0x84 - 0x81];
    u8 f84;
};
/* Copies state and position data from the two source buffers into the object
 * referenced by owner->f30, then sets a flag byte from the owner's frame state. */
void syncChildObjectParams(u8 *owner, u8 *source, u8 *params)
{
    struct S338F0 *self;
    u8 *target;
    u8 *paramPtr;
    unsigned long long one;
    u8 *statePtr;
    self = (struct S338F0 *) owner;
    paramPtr = params + 0;
    one = 1;
    target = self->f30;
    if (target == 0) return;
    *((u8 *) (target + 0x80)) = one;
    ((struct O338F0 *) self->f30)->f84 = *((u8 *) (params + 2)) & 0x10;
    *((u32 *) (self->f30 + 0x4C)) = *((u32 *) (source + 8));
    *((u32 *) (self->f30 + 0x5C)) = *((u32 *) (source + 0xC));
    ((struct O338F0 *) self->f30)->f6C = *((u16 *) paramPtr);
    ((struct O338F0 *) self->f30)->f74 = *((u16 *) (params + 2));
    statePtr = (u8 *) ((((u32) *((s16 *) (((u8 *) owner) + 0x22))) * 2) + (u32) owner);
    if (statePtr[0x1A] == 4)
        *((u8 *) (self->f30 + 0x7C)) = one;
    else
        *((u8 *) (self->f30 + 0x7C)) = 0;
}
