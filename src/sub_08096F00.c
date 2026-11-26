void sub_08005E80(s32);
void sub_080C31E8(void *, void *, s32, s32);
void sub_0809C510(s32, s32, s32);
void sub_080C31E4(void *, void *, s32);

void sub_08096D64(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 *r1 = *(s32 **)(self + 0x3C);
    if (*(u8 *)(r1 + 0x18) & 2) {
        s32 zero = 0;
        *(u16 *)(r1 + 0x14) = zero;
        sub_08005E80(0x1B8);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        {
            s32 *lit = (s32 *)0x08671BD0;
            sub_080C31E8(self + 0x18, self + 0x22, 1, *lit);
        }
    }
}

/* The player's 16.16 fixed-point position, recorded every frame. */
struct PlayerPosition {
    u8 _0x000[0x1728];
    s32 playerX;
    s32 playerY;
};
extern struct PlayerPosition gMainWorkspace;

/* Returns 1 while the player is within 32 px horizontally and 56 px
 * vertically of the object's work position (work+0x0C/+0x10), else 0. */
s32 sub_08096F00(void *arg0) {
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    if (gMainWorkspace.playerX >= *(s32 *)(work + 0x0C) + (s32)0xFFE00000 &&
        gMainWorkspace.playerX <= *(s32 *)(work + 0x0C) + 0x200000 &&
        gMainWorkspace.playerY >= *(s32 *)(work + 0x10) + (s32)0xFFC80000 &&
        gMainWorkspace.playerY <= *(s32 *)(work + 0x10) + 0x380000) {
        return 1;
    }
    return 0;
}

void sub_08099E2C(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *r4 = *(u8 **)(self + 0x3C) + 0x48;
    u16 v;
    u32 shifted;
    sub_0809C510(*(s32 *)(r4 + 0x08), *(s32 *)(r4 + 0x18), 2);
    v = *(u16 *)(r4 + 0x24) - 0x80;
    *(u16 *)(r4 + 0x24) = v;
    shifted = v << 16;
    if (shifted == 0xD8000000) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *lit = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *lit);
        }
    }
}
