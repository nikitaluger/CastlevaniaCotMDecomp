extern s64 sub_080C37B4(s64, s64);
extern s64 D_080C3218(s64, s64);
extern s32 sub_080133A4(s32, s32);
s32 sub_08015BA8(u8 *p, s32 x, s32 y, s32 dx, s32 dy, s32 *outA, s32 *outB, u16 *outC, s32 flags)
{
    s32 r6 = y + dy;
    s32 r7 = x + dx;
    u16 hits = 0;
    s16 cx = *(s16 *)(p + 4);
    s16 cy = *(s16 *)(p + 8);
    s16 ty = *(s16 *)(p + 6);
    s16 th = *(s16 *)(p + 0xA);
    s32 left = ((s32)cx - cy) << 16;
    s32 top = ((s32)ty - th) << 16;
    s32 right = ((s32)cx + cy) << 16;
    s32 bottom = ((s32)ty + th) << 16;
    s32 bx = left;
    s32 by = top;
    

s32 __repair_phase___repair_phase_t;
u8 temp;
    
    if ((temp = p[1]) & 2)
    {
        if (x < bx && !(flags & 0x200))
        {
            __repair_phase___repair_phase_t = bx - 0x10000;
            if (x < __repair_phase___repair_phase_t)
            {
                if (dy > 0 && r7 >= __repair_phase___repair_phase_t)
                {
                    __repair_phase___repair_phase_t = y + (s32)D_080C3218(sub_080C37B4(dy, bx - x), dx);
                    if (dy > 0) { if (r6 < __repair_phase___repair_phase_t) __repair_phase___repair_phase_t = r6; }
                    else if (__repair_phase___repair_phase_t < r6) __repair_phase___repair_phase_t = r6;
                    if (__repair_phase___repair_phase_t >= top && __repair_phase___repair_phase_t < bottom) { bx = left - 0x8000; by = __repair_phase___repair_phase_t; hits |= 2; }
                }
            }
            else if (r7 >= __repair_phase___repair_phase_t)
            {
                if (dx >= 0)
                {
                    if (r6 < by && y >= by) { bx -= 0x8000; hits = 0x20; }
                    else if (r6 >= bottom && y < bottom) { bx = left - 0x8000; by = bottom - 1; hits |= 0x20; }
                    else if (r6 >= top && r6 < bottom) { bx = left - 0x8000; by = r6; hits |= 2; }
                }
                else if (r6 >= by && r6 < bottom) { bx = r7; hits = 2; by = r6; }
            }
        }
        if (x >= right && !(flags & 0x400) && !(hits & 0xFF))
        {
            __repair_phase___repair_phase_t = right + 0x10000;
            if (x >= __repair_phase___repair_phase_t)
            {
                if (dx < 0 && r7 < __repair_phase___repair_phase_t)
                {
                    s32 __repair_phase___repair_phase_t_a1;
                    __repair_phase___repair_phase_t_a1 = y + (s32)D_080C3218(sub_080C37B4(dy, right - x), dx);
                    if (dy > 0) { if (__repair_phase___repair_phase_t_a1 > r6) __repair_phase___repair_phase_t_a1 = r6; }
                    else if (__repair_phase___repair_phase_t_a1 < r6) __repair_phase___repair_phase_t_a1 = r6;
                    if (__repair_phase___repair_phase_t_a1 >= top && __repair_phase___repair_phase_t_a1 < bottom) { bx = __repair_phase___repair_phase_t_a1 + 0x8000; by = __repair_phase___repair_phase_t_a1; hits |= 4; }
                }
            }
            else if (r7 < __repair_phase___repair_phase_t)
            {
                if (dy <= 0)
                {
                    if (r6 < top && y >= top) { bx = right + 0x8000; by = top; hits |= 0x40; }
                    else if (r6 >= bottom && y < bottom) { bx = right + 0x8000; by = bottom - 1; hits |= 0x40; }
                    else if (r6 >= top && r6 < bottom) { bx = right + 0x8000; by = r6; hits |= 4; }
                }
                else if (r6 >= top && r6 < bottom) { bx = r7; by = r6; hits |= 4; }
            }
        }
    }
    if (p[1] & 1)
    {
        if (y < top && !(flags & 0x100) && !(hits & 0xFF))
        {
            if (sub_080133A4(left + 0x8000, top - 0x8000) == 0 || sub_080133A4(right - 0x8000, top - 0x8000) == 0)
            {
                __repair_phase___repair_phase_t = top - 0x10000;
                if (y < __repair_phase___repair_phase_t)
                {
                    if (dy > 0 && r6 >= __repair_phase___repair_phase_t)
                    {
                        __repair_phase___repair_phase_t = x + (s32)D_080C3218(sub_080C37B4(dx, top - y), dy);
                        if (__repair_phase___repair_phase_t >= left && __repair_phase___repair_phase_t < right) { bx = __repair_phase___repair_phase_t; by = top - 0x8000; hits |= 1; }
                    }
                }
                else if (r6 >= __repair_phase___repair_phase_t)
                {
                    if (dy >= 0)
                    {
                        if (r7 < left && x >= left) { bx = left; by = top - 0x8000; hits |= 0x10; }
                        else if (r7 >= right && x < right) { bx = right - 1; by = top - 0x8000; hits |= 0x10; }
                        else if (r7 >= left && r7 < right) { bx = r7; by = top - 0x8000; hits |= 1; }
                    }
                    else if (r7 >= left && r7 < right) { bx = r7; by = r6; hits |= 1; }
                }
            }
        }
    }
    if (p[1] & 4)
    {
        if (y >= bottom && !(flags & 0x800))
        {
            if (hits & 0xFF) goto write;
            if (sub_080133A4(left + 0x8000, bottom + 0x8000) == 0 || sub_080133A4(right - 0x8000, bottom + 0x8000) == 0)
            {
                __repair_phase___repair_phase_t = bottom + 0x10000;
                if (y >= __repair_phase___repair_phase_t)
                {
                    if (dx < 0 && r6 < __repair_phase___repair_phase_t)
                    {
                        __repair_phase___repair_phase_t = x + (s32)D_080C3218(sub_080C37B4(dx, bottom - y), dy);
                        do { if (dx > 0) { if (__repair_phase___repair_phase_t > r7) __repair_phase___repair_phase_t = r7; }
                        else if (__repair_phase___repair_phase_t < r7) __repair_phase___repair_phase_t = r7; } while (0);
                        if (__repair_phase___repair_phase_t >= left && __repair_phase___repair_phase_t < right) { hits |= 8; by = bottom + 0x8000; bx = __repair_phase___repair_phase_t; }
                    }
                }
                else if (r6 < __repair_phase___repair_phase_t)
                {
                    if (dy <= 0)
                    {
                        if (r7 < left && x >= left) { by = bottom + 0x8000; bx = left; hits |= 0x80; }
                        else if (r7 >= right && x < right) { by = bottom + 0x8000; bx = right - 1; hits |= 0x80; }
                        else if (r7 >= left && r7 < right) { by = bottom + 0x8000; bx = r7; hits |= 8; }
                    }
                    else if (r7 >= left && r7 < right) { by = r6; bx = r7; hits |= 8; }
                }
            }
        }
    }
    if (!(hits & 0xFF)) return 0;
write:
    *outA = bx;
    *outB = by;
    *outC = hits;
    return 1;
}
