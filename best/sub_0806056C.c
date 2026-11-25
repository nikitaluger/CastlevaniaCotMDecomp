extern u8 D_02021E90[];
extern void sub_0805FEB4(u8);
extern void sub_08061048(void);
extern void sub_08061084(void);
extern void sub_080610D0(void);

struct S6C {
    u8 pad0[0x1360];
    u8 f1360;
    u8 pad1[0x1444 - 0x1361];
    u8 f1444;
    u8 pad2[0x1454 - 0x1445];
    u8 *f1454;
    u8 f1458;
    u8 f1459;
    u8 f145A;
    u8 f145B;
    u8 f145C;
    u8 f145D;
    u8 f145E;
    u8 f145F;
    u8 f1460;
    u8 f1461;
    u8 f1462;
    u8 f1463;
    u8 f1464;
    u8 f1465;
    u8 f1466;
    u8 f1467;
    u8 f1468;
    u8 f1469;
    u8 f146A;
};

u32 sub_0806056C(void)
{
    struct S6C *base = (struct S6C *)&D_02021E90;
    u8 *p = base->f1454 + 1;
    u8 cmd;

    if (base->f145C & 2) {
        base->f1444 = p[0] & 0xF;
    } else {
        sub_0805FEB4(p[0] & 0xF);
    }
    cmd = p[0];
    switch (cmd >> 4) {
    case 0:
        base->f1454 = p + 1;
        return 0;
    case 4:
    case 8: {
        u8 v;
        base->f145F = cmd >> 4;
        if (p[0] >> 4 == 4) {
            base->f1360 = 3;
            if (base->f145C & 8) goto skip;
            base->f1461 = 8;
            base->f1465 = 8;
            base->f1463 = 0x38;
            base->f1467 = 0x48;
        } else {
            base->f1360 = 4;
            if (base->f145C & 8) goto skip;
            base->f1461 = 8;
            base->f1465 = 0x58;
            base->f1463 = 0x38;
            base->f1467 = 0x98;
        }
        if (base->f145C & 8) goto skip;
        base->f1469 = 0x3E;
        base->f146A = 0x3F;
    skip:
        v = base->f1458;
        if (v > 0x21) {
            base->f1454 = p + 1;
            return 0;
        }
        base->f1458 = v + 1;
        if ((u8)(v + 1) == 0x22)
            return 2;
        base->f1458 = v + 2;
        return 2;
    }
    case 12: {
        u8 v;
        if (base->f1458 == 0x22) {
            sub_08061048();
            sub_08061084();
            sub_080610D0();
            base->f1460 = 0;
            base->f1464 = 0;
            base->f1462 = 0;
            base->f1466 = 0;
            base->f1461 = 0;
            base->f1465 = 0;
            base->f1463 = 0;
            base->f1467 = 0;
        }
        v = base->f1458;
        if (v != 0) {
            base->f1458 = v - 1;
            if ((u8)(v - 1) == 0)
                return 2;
            base->f1458 = v - 2;
            return 2;
        }
        base->f1360 = v;
        base->f1454 = p + 1;
        return 0;
    }
    case 1: {
        u8 v;
        base->f145F = cmd >> 4;
        base->f1360 = 5;
        v = base->f1458;
        if (v <= 5) {
            base->f1458 = v + 1;
            return 2;
        }
        base->f1454 = p + 1;
        return 0;
    }
    case 2: {
        u8 v = base->f1458;
        if (v != 0) {
            base->f1458 = v - 1;
            return 2;
        }
        base->f1360 = v;
        base->f1454 = p + 1;
        return 0;
    }
    }
}
