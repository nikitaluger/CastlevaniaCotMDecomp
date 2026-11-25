void sub_080113A8(void *, void *);
void sub_0801165C(void *, s32);
s32 sub_08013B5C(void *, void *);
s32 sub_0805F9B4(s32, s32);
void sub_080C31E0(void *, void *);

extern u8 D_0866DBB4[];
extern u8 D_02021E90[];
extern u8 D_02025FF0[];

struct Target { u8 unk0; u8 hitFlags; };

/* Entity script update: mark the linked target's hit flag, run one script
 * command, then write the camera-relative position back to the parent. */
void sub_0802E100(u8 *self) {
    u8 *parent;
    u8 *comp;
    u8 *body;
    struct Target *target;
    u32 deltaX;
    u32 deltaY;
    u32 idx2;

    parent = *(u8 **)(self + 0x38);
    comp = *(u8 **)(self + 0x3C);
    body = comp + 0x34;
    target = *(struct Target **)(comp + 0x28);
    target->hitFlags |= 1;

    if (sub_0805F9B4(*(s32 *)(comp + 8), *(s32 *)(comp + 0xC)) == 1) {
        sub_080C31E0(self, *(void **)(self + 0x24));
        return;
    }

    if (sub_08013B5C(parent, comp) == 0) {
        *(u32 *)(self + 0x14) = (u32)D_0866DBB4;
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
        {
            u8 *p2 = (u8 *)((s32)*(s16 *)(self + 0x22) * 2 + (s32)self);
            *(u8 *)(p2 + 0x19) = *(u8 *)(p2 + 0x19) + 1;
        }
        {
            s32 idx = *(s16 *)(self + 0x22) * 2;
            u8 *base18 = self + 0x18;
            u32 b = *(u8 *)(base18 + idx);
            sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + b * 4));
        }
        *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;

        if ((*(u16 *)(self + 2) & 0x8000) == 0) {
            sub_080113A8(parent, body);
            sub_0801165C(comp, 0);
        } else {
            return;
        }
    }

    *(u16 *)(*(u8 **)(comp + 0x28) + 0x14) = 0;
    {
        u8 *pt = D_02021E90;
        u8 *pb = D_02025FF0;
        u8 *pt1;
        u32 idx;
        u32 tableVal;
        pb += 0x18A8;
        idx = (((u32) (*pb)) + 1) << 6;
        pt1 = pt + 0x1278;
        tableVal = *((u32 *) (pt1 + idx));
        deltaX = tableVal;
        *((u32 *) (parent + 0x14)) = (*((u32 *) (comp + 0x08))) - ((deltaX + 0x8000) & 0xFFFF0000);
        idx2 = (1 + ((u32) (*pb))) << 6;
        idx = idx2;
        pt += 0x127C;
        tableVal = (deltaY = *((u32 *) (pt + idx)));
        *((u32 *) (parent + 0x18)) = (*((u32 *) (comp + 0x0C))) - ((tableVal + 0xFFFF8000) & 0xFFFF0000);
    }
}
