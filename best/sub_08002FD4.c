extern u8 D_0300291C;
extern void *D_08671BE4;
extern void *D_08671BE8;
extern void *D_08671BEC;
extern void *D_08671BF0;
extern void *D_08671BF4;
extern void *D_08671BFC;

extern u8 *D_03002E34;
extern u16 D_0300269C;
extern u16 D_03002914;
extern u32 D_03002694;
extern s32 D_03002698;
extern s32 D_030026A4;
extern u16 D_030026A8;
extern s32 D_030026AC;
extern s32 D_030026B0;
extern u32 D_030026B4;
extern u32 D_030026BC;
extern u32 D_03002700;
extern u8 *D_03002918;
extern u8 *D_03002E30;
extern u32 D_03002930[];
extern void *D_03002936;
extern void *D_03002D30;
extern u32 D_03000C80;
extern u32 *D_03000C84;
extern u32 *D_030026C0;

void *sub_080C31DC(void *);
s32 sub_080C31E0(s32, void *);
void sub_080C31E4(void *, s32, void *);
s32 sub_080C2F20(s32, s32);
void sub_080C2F30(void *, void *, s32, s32);

struct Entity {
    u16 unk00;
    u16 unk02;
    s16 unk04;
    s16 unk06;
    u16 unk08;
    u16 unk0A;
    s16 unk0C;
    s16 unk0E;
    u16 unk10;
    u16 unk12;
    s32 x;
    s32 y;
    s32 z;
    s16 screenX;
    s16 screenY;
    u8 pad24[6];
    u8 flags2A;
    u8 unk2B;
};

void sub_08002FD4(void)
{
    s32 sp00, sp04, sp08, sp0C, sp10, sp14, sp18, sp1C;
    s32 v;
    u32 i;
    struct Entity *ent;
    u32 idx;
    void **pfc;

    if (D_0300291C & 1)
        return;

    sub_080C31DC(D_08671BE4);

    ent = (struct Entity *)D_03002E34;
    pfc = &D_08671BFC;

    v = sub_080C31E0(D_0300269C + 0x4000, *pfc);
    if (v < 0) v += 3;
    sp00 = v >> 2;
    v = -sub_080C31E0(D_0300269C, *pfc);
    if (v < 0) v += 3;
    sp04 = v >> 2;

    {
        s32 a = sub_080C31E0(D_03002914, *pfc);
        s32 b = sub_080C31E0(D_0300269C, *pfc);
        s32 t = (a / 2) * b;
        if (t < 0) t += 0x1FFFF;
        sp08 = t >> 17;
    }

    v = sub_080C31E0(D_03002914 + 0x4000, *pfc);
    if (v < 0) v += 3;
    sp0C = v >> 2;

    {
        s32 a = sub_080C31E0(D_03002914, *pfc);
        s32 b = sub_080C31E0(D_0300269C + 0x4000, *pfc);
        s32 t = (a / 2) * b;
        if (t < 0) t += 0x1FFFF;
        sp10 = t >> 17;
    }

    {
        s32 a = sub_080C31E0(D_03002914 + 0x4000, *pfc);
        s32 b = sub_080C31E0(D_0300269C, *pfc);
        s32 t = (a / 2) * b;
        if (t < 0) t += 0x1FFFF;
        sp14 = t >> 17;
    }

    v = -sub_080C31E0(D_03002914, *pfc);
    if (v < 0) v += 3;
    sp18 = v >> 2;

    {
        s32 a = sub_080C31E0(D_03002914 + 0x4000, *pfc);
        s32 b = sub_080C31E0(D_0300269C + 0x4000, *pfc);
        s32 t = (a / 2) * b;
        if (t < 0) t += 0x1FFFF;
        sp1C = t >> 17;
    }

    idx = 0;
    for (i = 0; i < D_03002694; i++, ent++, idx++)
    {
        u8 flags = ent->flags2A;
        if ((flags & 0xC0) != 0xC0)
            continue;

        if (flags & 0x20)
        {
            s32 rx, ry, rz;
            s32 px, py;
            s32 depth;
            s32 scrX, scrY;

            rx = ent->x - D_030026B0;
            if (rx < 0) rx += 0xFFFF;
            rx >>= 16;
            ry = ent->y - D_03002698;
            if (ry < 0) ry += 0xFFFF;
            ry >>= 16;
            rz = ent->z - D_030026AC;
            if (rz < 0) rz += 0xFFFF;
            rz >>= 16;

            depth = rx * sp14 + ry * sp18 + rz * sp1C;
            if (depth < 0) depth += 0x3FFF;
            depth >>= 14;
            if ((u32)(depth - 0x80) > 0x1F80)
                continue;

            px = rx * sp00 + ry * 0 + rz * sp04;
            if (px < 0) px += 0x3FFF;
            px >>= 14;
            py = rx * sp08 + ry * sp0C + rz * sp10;
            if (py < 0) py += 0x3FFF;
            py >>= 14;

            scrX = (s32)(D_03002918 + 0x78) - sub_080C2F20(px << 8, depth);
            scrY = (s32)(D_03002E30 + 0x50) - sub_080C2F20(py << 8, depth);

            if ((u32)(scrX + 0x3F) > 0x16E)
                continue;
            if (scrY <= -0x40 || scrY > 0xDF)
                continue;

            {
                u32 packed = ((ent->unk00 & 0x0C00) << 8) | (idx << 24);
                packed |= ((u16)depth & 0xFFFF) << 2;
                packed |= (ent->unk2B & 3);
                sub_080C31E0(packed, D_08671BE8);
            }

            ent->screenX = scrX;
            ent->screenY = scrY;
            {
                s32 t = ent->unk04 * depth;
                if (t < 0) t += 0xFF;
                ent->unk0C = t >> 8;
            }
            {
                s32 t = ent->unk06 * depth;
                if (t < 0) t += 0xFF;
                ent->unk0E = t >> 8;
            }
            ent->unk10 = D_030026A8 + ent->unk08;
        }
        else if (flags & 0x08)
        {
            s32 sx, sy;
            s32 ex, ey;
            ex = ent->x;
            if (ex < 0) ex += 0xFFFF;
            sx = ex >> 16;
            ey = ent->y;
            if (ey < 0) ey += 0xFFFF;
            sy = ey >> 16;
            if ((u32)(sx + 0xFF) <= 0x2EE && sy > -0x100 && sy <= 0x19F)
            {
                if (ent->z > 0)
                {
                    u32 packed = ((ent->unk00 & 0x0C00) << 8) | (idx << 24);
                    packed |= ((u32)ent->z & 0xFFFF) << 2;
                    packed |= (ent->unk2B & 3);
                    sub_080C31E0(packed, D_08671BE8);
                }
                else
                {
                    sub_080C31E4(ent, ent->z & 0xF, D_08671BEC);
                }
                ent->screenX = sx;
                ent->screenY = sy;
                *(u32 *)&ent->unk0C = *(u32 *)&ent->unk04;
                *(u32 *)&ent->unk10 = *(u32 *)&ent->unk08;
            }
        }
        else
        {
            s32 sx, sy;
            s32 ex, ey;
            ex = ent->x - *(s32 *)D_03000C84;
            if (ex < 0) ex += 0xFFFF;
            sx = ex >> 16;
            ey = ent->y - *(s32 *)D_030026A4;
            if (ey < 0) ey += 0xFFFF;
            sy = ey >> 16;
            if ((u32)(sx + 0xFF) <= 0x2EE && sy > -0x100 && sy <= 0x19F)
            {
                if (ent->z > 0)
                {
                    u32 packed = ((ent->unk00 & 0x0C00) << 8) | (idx << 24);
                    packed |= ((u32)ent->z & 0xFFFF) << 2;
                    packed |= (ent->unk2B & 3);
                    sub_080C31E0(packed, D_08671BE8);
                }
                else
                {
                    sub_080C31E4(ent, ent->z & 0xF, D_08671BEC);
                }
                ent->screenX = sx;
                ent->screenY = sy;
                *(u32 *)&ent->unk0C = *(u32 *)&ent->unk04;
                *(u32 *)&ent->unk10 = *(u32 *)&ent->unk08;
            }
        }
    }

    sub_080C31DC(D_08671BF0);
    D_030026B4 = 0;
    D_03000C80 = 0;

    for (i = 0; i < 16; i++)
    {
        u32 *node = ((u32 **)D_030026C0)[i];
        if ((u32)node > 1)
        {
            while ((u32)node > 1)
            {
                sub_080C31E0(node[0], D_08671BF4);
                if (D_030026B4 > 0x7F)
                    goto done;
                node = (u32 *)node[1];
            }
        }
        else if ((u32)node == 1)
        {
            u8 *arr = (u8 *)D_03002700;
            u32 n = D_030026BC;
            u32 j;
            u8 *p = arr + n * 4;
            for (j = 0; j < n; j++)
            {
                struct Entity *e = (struct Entity *)(D_03002E34 + p[3] * 0x2C);
                sub_080C31E0((s32)e, D_08671BF4);
                if (D_030026B4 > 0x7F)
                    goto done;
                p -= 4;
            }
        }
    }

done:
    {
        u32 b4 = D_030026B4;
        if (b4 <= 0x7F)
        {
            u8 *p = (u8 *)D_03002930 + b4 * 8 + 1;
            while (b4 <= 0x7F)
            {
                *p = (*p & 0xFC) | 2;
                p += 8;
                b4++;
            }
        }
        if (D_03000C80 != 0)
            sub_080C2F30(D_03002D30, D_03002936, D_03000C80, 8);
    }
}
