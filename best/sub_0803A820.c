void copyPoseAttrs(void *dst, void *src);

void sub_0803A820(void *arg0) {
    u8 *self;
    u8 *sprite;
    u8 *attached;
    u8 *p48;
    u8 *source;
    u16 state;

    u32 zero;
    self = (u8 *)arg0;
    sprite = *(u8 **)(self + 0x38);
    do { attached = *(u8 **)(self + 0x3C); } while (0);
    do { do { do { p48 = attached + 0x48; } while (0); } while (0); } while (0);
    zero = 0;

    if (*(u32 *)(self + 0x2C) != 0 && self[0x80] != 0) {
        s32 step;
        s32 cmd;
        step = *(s16 *)(self + 0x22);
        do { cmd = *(u8 *)(self + step * 2 + 0x19); } while (0);
        switch (cmd & 3) {
        case 0:
            *(u16 *)sprite = (*(u16 *)sprite & 0x0FFF) | 0xD000;
            break;
        case 1:
            *(u16 *)sprite = (*(u16 *)sprite & 0x0FFF) | 0xE000;
            break;
        case 2:
            *(u16 *)sprite = (*(u16 *)sprite & 0x0FFF) | 0xC000;
            break;
        case 3:
            *(u16 *)sprite = (*(u16 *)sprite & 0x0FFF) | 0xF000;
            break;
        }
    } else {
        source = *(u8 **)(*(u8 **)(self + 0x28) + 0x38);
        *(u16 *)sprite = *(u16 *)source;
    }

    source = *(u8 * volatile *)(self + 0x28);
    source = *(u8 * volatile *)(source + 0x38);
    *(u16 *)(sprite + 2) = *(u16 *)(source + 2);
    *(u8 *)(sprite + 0x2A) &= 0xBF;
    *(u8 *)(*(u8 **)(attached + 0x28) + 1) = 0;
    *(u8 *)(*(u8 **)(p48) + 1) = 0;

    state = *(s16 *)(*(u8 **)(*(u8 **)(self + 0x28) + 0x38) + 0x28);
    switch (state) {
    case 0x1A: {
        u8 *pose;
        copyPoseAttrs(*(void **)(attached + 0x28), (pose = (u8 *)0x080CF190));
        copyPoseAttrs(*(void **)(p48), pose + 8);
        state = 0x26;
        break;
    }
    case 0x1E: {
        u8 *pose;
        copyPoseAttrs(*(void **)(attached + 0x28), (pose = (u8 *)0x080CF1A0));
        copyPoseAttrs(*(void **)(p48), pose + 8);
        state = 0x27;
        break;
    }
    case 0x22: {
        u8 *pose;
        copyPoseAttrs(*(void **)(attached + 0x28), (pose = (u8 *)0x080CF1B0));
        copyPoseAttrs(*(void **)(p48), pose + 8);
        state = 0x28;
        break;
    }
    default:
        return;
    }
    *(u16 *)(sprite + 0x28) = state;
    *(u8 *)(sprite + 0x2A) |= 0x40;
    *(u8 *)(*(u8 **)(attached + 0x28) + 1) = 1;
    *(u8 *)(*(u8 **)(p48) + 1) = 1;
}
