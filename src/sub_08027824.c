extern s32 sub_080C31E0(s32, s32);
extern s32 sub_08026C7C(s32, s32, s16, s16, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Places the entity at a position derived from a trig-table lookup (angle at
 * fx+8), then, when flag 0x20 is set, fires a projectile and plays a sound. */
void sub_08027824(u8 *self) {
    s32 scaledSin, scaledCos;
    s32 rawA, rawB;
    s32 angle;
    s32 offsetX, offsetY, cosB, sinB, newY;
    u8 *comp = *(u8 **)(self + 0x3C);
    u8 *fx = comp + 0x48;
    s32 *trigTable;

    angle = *(u16 *)(fx + 8);
    trigTable = (s32 *)0x08671BFC;
    rawA = sub_080C31E0(angle + 0x4000, *trigTable);
    if (rawA < 0) rawA += 0x7FF;
    scaledSin = rawA >> 0xB;
    rawB = sub_080C31E0(angle, *trigTable);
    if (rawB < 0) rawB += 0xFFF;
    scaledCos = rawB >> 0xC;

    offsetX = (sub_080C31E0(*(u16 *)(*(u8 **)(fx + 0x58) + 4) + 0x4000, *trigTable) * 8) + *(s32 *)(fx + 0x5C);
    offsetY = (sub_080C31E0(*(u16 *)(*(u8 **)(fx + 0x58) + 4), *trigTable) * 8) + *(s32 *)(fx + 0x60);
    cosB = sub_080C31E0(*(u16 *)(*(u8 **)(fx + 0x58) + 2) + 0x4000, *trigTable);
    *(s32 *)(comp + 8) = (scaledSin * cosB) - (sub_080C31E0(*(u16 *)(*(u8 **)(fx + 0x58) + 2), *trigTable) * scaledCos) + offsetX;
    sinB = sub_080C31E0(*(u16 *)(*(u8 **)(fx + 0x58) + 2), *trigTable);
    newY = (scaledSin * sinB) + (sub_080C31E0(*(u16 *)(*(u8 **)(fx + 0x58) + 2) + 0x4000, *trigTable) * scaledCos) + offsetY;
    *(s32 *)(comp + 0xC) = newY;

    if (0x20 & *(u16 *)(self + 0x64)) {
        sub_08026C7C(*(s32 *)(comp + 8), newY, *(s16 *)(fx + 0x18), *(s16 *)(fx + 0x22), *(s16 *)(comp + 0x1C));
        {
            void *owner = *(void **)(self + 0x30);
            if (owner != NULL) {
                sub_080C31E0((s32)owner, *(s32 *)((u8 *)owner + 0x24));
            }
        }
        {
            u8 *script = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            *(u8 *)(script + 0x17) = 0;
        }
        {
            s32 *soundTab = (s32 *)0x08671BD8;
            sub_080C31E8(self + 0x18, self + 0x22, 1, *soundTab);
        }
    }
}
