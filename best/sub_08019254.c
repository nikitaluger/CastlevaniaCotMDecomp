extern u16 gKind55EffectLayerAttrs[];
extern u16 D_080CE5D8[];
extern u16 D_080CE5E0[];

struct Node { u8 pad[0x28]; u8 * volatile field28; };

void sub_08019254(void *arg0, void *arg1) {
    u16 *tbl = gKind55EffectLayerAttrs;
    struct Node *o = *(struct Node **)((u8 *)arg0 + 0x3C);
    u16 val = *(u16 *)((u8 *)arg1 + 0x28);
    switch (val - 0x32) {
    case 0:
    case 1:
        *(u8 *)(o->field28 + 1) = 0;
        break;
    case 9:
        tbl = D_080CE5D8;
        break;
    case 2:
    case 4:
        tbl = D_080CE5E0;
        break;
    }
    *(u16 *)(o->field28 + 6) = tbl[0];
    *(u16 *)(o->field28 + 8) = tbl[1];
    *(u16 *)(o->field28 + 0xA) = tbl[2];
    *(u16 *)(o->field28 + 0xC) = tbl[3];
}
