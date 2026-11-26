s32 sub_08007D7C(s32 map, s32 x, s32 y);
s32 sub_08012A94(s32 x, s32 y, s32 count);
s32 sub_080159BC(s32 x, s32 y, s32 velX, s32 velY, s32 mask, void *out);
extern u8 gMainWorkspace[];
extern u8 D_02023130[];
extern s16 D_080CB278[];

void sub_080119B4(void *entity, s32 b, s32 c, s32 d, s32 e) {
    int flag;
    s32 sp1C = d;
    s32 probe[5];
    s32 r6;
    s32 r8 = 0;
    s32 x = *(s32 *)((u8 *)entity + 8);
    s32 y = *(s32 *)((u8 *)entity + 0xC);
    s32 mask;
    s32 v;
    s32 newX;
    s32 t1, t2;

    *(u16 *)((u8 *)entity + 2) = 0;
    if (*(s32 *)((u8 *)entity + 0x10) == 0) {
        goto D_A0;
    }
    r6 = *(volatile s32 *)((u8 *)entity + 0x10);
    *(volatile s32 *)((u8 *)entity + 0x14) = 0;
    r8 = 0;
    if (!(*(u16 *)((u8 *)entity + 4) & 0x10)) {
        goto C26;
    }
    if (r6 < 0) {
        /* r6 < 0 branch */
        if (sub_080159BC(x - sp1C, y, r6, 0, (mask = *(u16 *)((u8 *)entity + 6) | 0x200), probe) == 1) {
            r6 += probe[1];
            if (*(u16 *)&probe[0] & 1) *(u16 *)((u8 *)entity + 2) |= 0x100;
            if (*(u16 *)&probe[0] & 6) *(u16 *)((u8 *)entity + 2) |= 0x200;
        }
        if (c != 0) {
            if (sub_080159BC(x - sp1C, y - c, r6, 0, (mask = *(u16 *)((u8 *)entity + 6) | 0x300), probe) == 1) {
                r6 += probe[1];
                if (*(u16 *)&probe[0] & 6) *(u16 *)((u8 *)entity + 2) |= 0x200;
                if (*(u16 *)&probe[0] & 8) *(u16 *)((u8 *)entity + 2) |= 0x400;
            }
        }
        if (sub_080159BC(x + e, y, r6, 0, (mask = *(u16 *)((u8 *)entity + 6) | 0x400), probe) == 1 && (*(u16 *)&probe[0] & 1)) {
            *(u16 *)((u8 *)entity + 2) |= 0x100;
        }
        if (c != 0) {
            s32 v_a1;
            s32 mask_a1;
            v_a1 = *(u16 *)((u8 *)entity + 6); mask_a1 = v_a1 | 0x500;
            if (sub_080159BC(x + e, y - c, r6, 0, mask_a1, probe) == 1 && (*(u16 *)&probe[0] & 8)) {
                *(u16 *)((u8 *)entity + 2) |= 0x400;
            }
        }
    } else {
        /* r6 >= 0 branch */
        if (sub_080159BC(x + e, y, r6, 0, (v = *(u16 *)((u8 *)entity + 6) | 0x400), probe) == 1) {
            r6 += probe[1];
            if (*(u16 *)&probe[0] & 1) *(u16 *)((u8 *)entity + 2) |= 0x100;
            if (*(u16 *)&probe[0] & 6) *(u16 *)((u8 *)entity + 2) |= 0x200;
        }
        if (c != 0) {
            mask = *(u16 *)((u8 *)entity + 6) | 0x500;
            if (sub_080159BC(x + e, y - c, r6, 0, mask, probe) == 1) {
                r6 += probe[1];
                if (*(u16 *)&probe[0] & 6) *(u16 *)((u8 *)entity + 2) |= 0x200;
                if (*(u16 *)&probe[0] & 8) *(u16 *)((u8 *)entity + 2) |= 0x400;
            }
        }
        mask = *(u16 *)((u8 *)entity + 6) | 0x200;
        if (sub_080159BC(x - sp1C, y, r6, 0, mask, probe) == 1 && (*(u16 *)&probe[0] & 1)) {
            *(u16 *)((u8 *)entity + 2) |= 0x100;
        }
        if (c != 0) {
            mask = *(u16 *)((u8 *)entity + 6) | 0x300;
            if (sub_080159BC(x - sp1C, y - c, r6, 0, mask, probe) == 1 && (*(u16 *)&probe[0] & 8)) {
                *(u16 *)((u8 *)entity + 2) |= 0x400;
            }
        }
    }

C26:
    {
        s32 map = (s32)D_02023130 + (gMainWorkspace[0x18A8] << 6);
        t1 = sub_08007D7C(map, (x + r6) - sp1C, y + 0x80000);
        if ((D_080CB278[(unsigned short)t1] & 0x0E) || (D_080CB278[sub_08007D7C(map, (x + r6) + e, y + 0x80000)] & 0x0E)) {
            *(u16 *)((u8 *)entity + 2) |= 0x04;
        }
    }
    (void)&newX;
    newX = x + r6;
    if ((x & 0xFFFF0000) == (newX & 0xFFFF0000)) {
        *(s32 *)((u8 *)entity + 8) = newX;
        goto END;
    }
    v = newX + e;
    if (r6 < 0) v = newX - sp1C;
    t1 = sub_08007D7C((s32)D_02023130 + (gMainWorkspace[0x18A8] << 6), v, y);
    if (D_080CB278[(unsigned short)t1] & 0x0A) {
        flag = r6 > 0;
        if (flag) v = (v & 0xFFF80000) + 0xFFFF8000;
        else v = (v & 0xFFF80000) + 0x88000;
    } else {
        t2 = sub_08007D7C((s32)D_02023130 + (gMainWorkspace[0x18A8] << 6), v, y - c);
        if (D_080CB278[(unsigned short)t2] & 0x0A) {
            flag = (v & 0xFFF80000) + 0xFFFF8000;
            if (r6 > 0) v = flag;
            else v = (v & 0xFFF80000) + 0x88000;
            *(u16 *)((u8 *)entity + 2) |= 0x01;
        }
    }
    /* Wait: |=1 should happen on either hit. Need to restructure. */
    goto END;

D_A0:
    {
        s32 r6v = *(s32 *)((u8 *)entity + 0x14);
        r6v += b;
        *(s32 *)((u8 *)entity + 0x14) = r6v;
        if (*(u16 *)((u8 *)entity + 4) & 0x10) {
            mask = *(u16 *)((u8 *)entity + 6) | 0x200;
            sp1C_unused: (void)0;
            /* probe at x - d, y, mask 0x200, velX=0, velY=r6v */
            v = 1;
            if (sub_080159BC(x - sp1C, y, 0, r6v, mask, probe) == v) {
                r6v += probe[2]; /* dy at sp+0x10 = probe[2] */
                if (*(u16 *)&probe[0] & 1) *(u16 *)((u8 *)entity + 2) |= 0x100;
                if (*(u16 *)&probe[0] & 6) *(u16 *)((u8 *)entity + 2) |= 0x200;
            }
            /* probe at x + e, y, mask 0x400 */
            mask = *(u16 *)((u8 *)entity + 6) | 0x400;
            if (sub_080159BC(x + e, y, 0, r6v, mask, probe) == 1) {
                r6v += probe[2];
                if (*(u16 *)&probe[0] & 1) *(u16 *)((u8 *)entity + 2) |= 0x100;
                if (*(u16 *)&probe[0] & 6) *(u16 *)((u8 *)entity + 2) |= 0x200;
                if (*(u16 *)&probe[0] & 8) *(u16 *)((u8 *)entity + 2) |= 0x400;
            }
        } else {
            mask = *(u16 *)((u8 *)entity + 6) | 0x200;
            v = 1;
            if (sub_080159BC(x - sp1C, y, 0, r6v, mask, probe) == v) {
                r6v += probe[2];
                if (*(u16 *)&probe[0] & 1) *(u16 *)((u8 *)entity + 2) |= 0x100;
                if (*(u16 *)&probe[0] & 6) *(u16 *)((u8 *)entity + 2) |= 0x200;
            }
            mask = *(u16 *)((u8 *)entity + 6) | 0x400;
            if (sub_080159BC(x + e, y, 0, r6v, mask, probe) == 1) {
                r6v += probe[2];
                if (*(u16 *)&probe[0] & 1) *(u16 *)((u8 *)entity + 2) |= 0x100;
                if (*(u16 *)&probe[0] & 6) *(u16 *)((u8 *)entity + 2) |= 0x200;
                if (*(u16 *)&probe[0] & 8) *(u16 *)((u8 *)entity + 2) |= 0x400;
            }
        }
        /* x/y update */
        do { {
            s32 dx = x - sp1C;
            s32 r5r = sub_08012A94(dx, y, 2);
            s32 r1r;
            v = x + e;
            r1r = sub_08012A94(v, y, 2);
            if (r1r > r5r) r1r = r5r;
            if (r1r <= r6v) {
                y += r6v;
            } else {
                y += r1r;
                *(u16 *)((u8 *)entity + 2) |= 0x04;
                *(s32 *)((u8 *)entity + 0x14) = 0;
            }
            if (*(u16 *)((u8 *)entity + 2) & 0x100) {
                *(s32 *)((u8 *)entity + 0x14) = 0;
            }
        } } while (0);
        *(s32 *)((u8 *)entity + 0xC) = y;
    }

END:
    return;
}
