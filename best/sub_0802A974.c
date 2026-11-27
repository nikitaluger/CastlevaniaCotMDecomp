extern s32 isOutsideCameraBounds(s32, s32);
extern s32 sub_08014090(s32);
extern s32 scaleByRandom(s32);
extern s32 sub_08016830(s32);
extern s32 absXFromFocus(s32);
extern void *spawnBudgetedEffect(s32);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern s32 sub_0805F9B4(s32, s32);
extern void *sub_0805FAEC(void *, s32);

void sub_0802A974(void *entity)
{
    u8 *self = (u8 *)entity;
    void *source = *(void **)(self + 0xAC);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *srcObj = *(u8 **)((u8 *)source + 4);
    s32 x, y;
    s32 kind;
    s32 r8;

    x = *(s16 *)srcObj << 16;
    y = *((s16 *)srcObj + 1) << 16;
    if (isOutsideCameraBounds(x, y) == 1) {
        sub_080C31E0(entity, *(void **)(self + 0x24));
        return;
    }

    if (sub_08014090(*(s16 *)work) == 1)
        return;

    *(s16 *)(work + 2) = *(s16 *)(work + 2) - 1;
    if (*(s16 *)(work + 2) > 0)
        return;

    *(s16 *)(work + 2) = (s16)(scaleByRandom(0x3D) + 0xB4);

    kind = *(s16 *)(srcObj + 4);
    switch (kind) {
    case 0xBE:
        r8 = 0xBB;
        break;
    case 0xBF:
        r8 = 0xBC;
        break;
    case 0xC0:
        r8 = 0xBD;
        break;
    default:
        r8 = 0;
        break;
    }

    if (sub_08016830((s16)r8) > 6)
        return;

    {
        s32 ax = *(s16 *)srcObj << 16;
        s32 dist = absXFromFocus(ax);
        if ((u32)(dist + 0xFFC40000) > 0x003C0000) {
            s16 t = *(s16 *)(work + 2);
            if (t < 0) {
                t = (t + 7) >> 3;
                *(s16 *)(work + 2) = t;
            }
            return;
        }
    }

    {
        void *spawned;
        u8 *sp;
        s32 kind2 = *(s16 *)(srcObj + 4);
        s32 sb = 0;

        switch (kind2) {
        case 0xBE:
            spawned = spawnBudgetedEffect(0xBB);
            sb = 0;
            break;
        case 0xBF:
            spawned = spawnBudgetedEffect(0xBC);
            sb = 1;
            break;
        case 0xC0:
            spawned = spawnBudgetedEffect(0xBD);
            sb = 2;
            break;
        default:
            spawned = 0;
            break;
        }

        if (spawned == 0)
            return;

        allocWorkSlot(spawned, 0, 8, 7);
        sp = *(u8 **)((u8 *)spawned + 0x3C);
        if (sp == 0) {
            sub_080C31E0(spawned, *(void **)((u8 *)spawned + 0x24));
            return;
        }

        *(s16 *)sp = 0;
        *(u32 *)(sp + 4) = (u32)(0x08671BB0 + sb * 12);
        {
            s32 sx = *(s16 *)srcObj << 16;
            u32 *cam = (u32 *)0x02025FF0;
            if (sx < cam[0x1728 / 4]) {
                u8 frame = *(u8 *)((u8 *)0x02025FF0 + 0x18A8);
                u32 *scroll = (u32 *)((u8 *)0x02021E90 + 0x1278 + ((frame + 1) << 6));
                *(u32 *)((u8 *)spawned + 0x4C) = scroll[0] + 0x1E8000;
            } else {
                u8 frame = *(u8 *)((u8 *)0x02025FF0 + 0x18A8);
                u32 *scroll = (u32 *)((u8 *)0x02021E90 + 0x1278 + ((frame + 1) << 6));
                *(u32 *)((u8 *)spawned + 0x4C) = scroll[0] - 0x8000;
            }
            *(u32 *)((u8 *)spawned + 0x54) = ((u8 *)0x02021E90)[0x127C] + scaleByRandom(0x5B);
        }
    }
}
