struct AnimState {
    u8 flags;
    u8 index;
    u16 duration;
    s32 timer;
};

struct AnimFrame {
    u16 duration;
    u16 frame;
};

/* Advance an animation by delta ticks, looping or stopping at the end marker and
 * writing the current frame number to the entity. */
void sub_08010E70(void *entity, struct AnimState *anim, struct AnimFrame *frameTable, s32 delta) {
    struct AnimFrame *frame;
    if (anim->flags & 2)
        return;
    anim->timer += delta;
    while (1) {
        s32 durationFixed = (s32)anim->duration << 16;
        if (delta > 0) {
            s32 timer = anim->timer;
            if (timer > durationFixed) {
                frame = &frameTable[anim->index];
                if (!(frame->duration & 0x8000)) {
                    anim->duration = frame->duration;
                    anim->timer = timer - durationFixed;
                    anim->index++;
                    *(u16 *)((u8 *)entity + 0x28) = frame->frame;
                    continue;
                }
                if (anim->flags & 1) {
                    anim->index = 0;
                    continue;
                }
                anim->flags |= 2;
                return;
            }
        }
        if (delta < 0) {
            s32 timer = anim->timer;
            if (timer < 0) {
                frame = &frameTable[anim->index];
                if (!(frame->duration & 0x8000)) {
                    anim->duration = frame->duration;
                    anim->timer = timer + ((s32)anim->duration << 16);
                    if (anim->index != 0) {
                        anim->index--;
                    } else {
                        anim->index = 0;
                        while (!(frameTable[anim->index].duration & 0x8000))
                            anim->index++;
                    }
                    *(u16 *)((u8 *)entity + 0x28) = frame->frame;
                    continue;
                }
                if (anim->flags & 1) {
                    anim->index--;
                    continue;
                }
                anim->flags |= 2;
                return;
            }
        }
        return;
    }
}
