void sub_080113A8(void *, void *);
void sub_0801165C(void *, u32);
s32 sub_08013B5C(void *, void *);
s32 sub_0805F9B4(s32, s32);
void sub_080C31E0(void *, s32);
void sub_080C31E8(void *, void *, s32, s32);
struct Target { u8 unk0; u8 hitFlags; u8 pad[0x12]; u16 stateFlags; };
struct Comp { u16 flags; };
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u32 D_08671BDC;
extern u32 D_0866E55C;

/* Entity script update: refresh the linked target's flags, run one script
 * command from the script table, then write the camera-relative position back. */
void sub_0804ECBC(void *self) {
    void *parent;
    void *comp;
    void *body;
    struct Comp *compFlags;
    struct Target *target;

    parent = *(void **)((u8 *)self + 0x38);
    comp = *(void **)((u8 *)self + 0x3C);
    body = (u8 *)comp + 0x34;
    compFlags = (struct Comp *)comp;
    target = *(struct Target **)((u8 *)comp + 0x28);
    target->hitFlags |= 1;

    if (sub_0805F9B4(*(s32 *)((u8 *)comp + 8), *(s32 *)((u8 *)comp + 0xC)) == 1) {
        sub_080C31E0(self, *(s32 *)((u8 *)self + 0x24));
        return;
    }

    target = *(struct Target **)((u8 *)comp + 0x28);
    if (target->stateFlags & 1) {
        compFlags->flags |= 1;
    }

    if (compFlags->flags & 1) {
        target = *(struct Target **)((u8 *)comp + 0x28);
        target->hitFlags &= 0xFB;
        if (*((u8 *)self + *(s16 *)((u8 *)self + 0x22) * 2 + 0x1A) != 1) {
            u32 *sound;
            *((u8 *)self + *(s16 *)((u8 *)self + 0x22) * 2 + 0x1B) = 0;
            sound = &D_08671BDC;
            sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 1, *sound);
        }
    }

    if (sub_08013B5C(parent, comp) == 0) {
        *(u32 *)((u8 *)self + 0x14) = (u32)&D_0866E55C;
        *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) + 1;
        {
            u8 *script = (u8 *)((s16)(*(u16 *)((u8 *)self + 0x22)) * 2 + (u32)self);
            script[0x19] = script[0x19] + 1;
        }
        {
            s32 idx = (s16)(*(u16 *)((u8 *)self + 0x22)) * 2;
            u8 *q = (u8 *)self;
            u8 cmd;
            q += 0x18;
            q += idx;
            cmd = *q;
            sub_080C31E0(self, *(s32 *)(*(u32 *)((u8 *)self + 0x14) + (u32)(cmd * 4)));
        }
        *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) - 1;
        if (*(u16 *)((u8 *)self + 2) & 0x8000) {
            return;
        }
        sub_080113A8(parent, body);
        sub_0801165C(comp, 0);
    }

    {
        struct Target *t;
        u8 *pt;
        u8 *pb;
        u32 idx;
        u8 *p1;
        u8 *p2;
        t = *(struct Target **)((u8 *)comp + 0x28);
        t->stateFlags = 0;
        pt = gCameraState;
        pb = gMainWorkspace;
        pb += 0x18A8;
        idx = ((u32)*pb + 1) * 0x40;
        p1 = pt + 0x1278;
        *(u32 *)((u8 *)parent + 0x14) = *(u32 *)((u8 *)comp + 8) - ((*(s32 *)(p1 + idx) + 0x8000) & 0xFFFF0000);
        idx = ((u32)*pb + 1) * 0x40;
        p2 = pt + 0x127C;
        *(u32 *)((u8 *)parent + 0x18) = *(u32 *)((u8 *)comp + 0xC) - ((*(s32 *)(p2 + idx) + 0xFFFF8000) & 0xFFFF0000);
    }
}
