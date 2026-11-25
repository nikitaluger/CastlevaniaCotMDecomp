extern u16 D_080CF9DC[];

/* Selects four groups of parameters from a table based on the source's kind
 * and copies each group into one of the entity's subobjects. */
void sub_0804E470(u8 *entity, u8 *source)
{
    u8 *data;
    u8 *state;
    u16 *tableA;
    u16 *tableB;
    u16 *tableC;
    u16 *tableD;
    s32 kind;

    data = *(u8 **)(entity + 0x3C);
    state = data + 0x48;
    tableA = D_080CF9DC;
    tableB = D_080CF9DC + 12;
    tableC = D_080CF9DC + 16;
    tableD = D_080CF9DC + 20;
    kind = *(u16 *)(source + 0x28);

    switch (kind)
    {
    case 0x0E:
        tableA = D_080CF9DC + 4;
        tableC = tableB + 12;
        tableD = tableB + 16;
        break;
    case 0x14:
        tableC = D_080CF9DC + 32;
        tableD = D_080CF9DC + 36;
        break;
    case 0x1B:
        tableA = D_080CF9DC + 8;
        tableC = tableB + 28;
        tableD = tableB + 32;
        break;
    case 0x23:
        tableA = D_080CF9DC + 8;
        tableC = tableB + 28;
        *(u8 *)(*(u8 **)(state + 0x0C) + 1) = 0;
        break;
    }

    *(u16 *)(*(u8 *volatile *)(data + 0x28) + 6) = tableA[0];
    *(u16 *)(*(u8 *volatile *)(data + 0x28) + 8) = tableA[1];
    *(u16 *)(*(u8 *volatile *)(data + 0x28) + 10) = tableA[2];
    *(u16 *)(*(u8 *volatile *)(data + 0x28) + 12) = tableA[3];

    *(u16 *)(*(u8 *volatile *)(state + 0x10) + 6) = tableB[0];
    *(u16 *)(*(u8 *volatile *)(state + 0x10) + 8) = tableB[1];
    *(u16 *)(*(u8 *volatile *)(state + 0x10) + 10) = tableB[2];
    *(u16 *)(*(u8 *volatile *)(state + 0x10) + 12) = tableB[3];

    *(u16 *)(*(u8 *volatile *)(state + 0x08) + 6) = tableC[0];
    *(u16 *)(*(u8 *volatile *)(state + 0x08) + 8) = tableC[1];
    *(u16 *)(*(u8 *volatile *)(state + 0x08) + 10) = tableC[2];
    *(u16 *)(*(u8 *volatile *)(state + 0x08) + 12) = tableC[3];

    *(u16 *)(*(u8 *volatile *)(state + 0x0C) + 6) = tableD[0];
    *(u16 *)(*(u8 *volatile *)(state + 0x0C) + 8) = tableD[1];
    *(u16 *)(*(u8 *volatile *)(state + 0x0C) + 10) = tableD[2];
    *(u16 *)(*(u8 *volatile *)(state + 0x0C) + 12) = tableD[3];
}
