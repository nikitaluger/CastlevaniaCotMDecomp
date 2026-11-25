/* Text-line helper: writes `glyph` one slot past the current index and clears
 * the remaining halfwords up to the line's end/count slot pointed to by `end`. */
void sub_080C3B54(u16 *line, s16 *end, u32 glyph)
{
    s16 idx = *end;
    s32 off;
    u16 *p;
    off = idx;
    off = off * 2;
    off = off + 2;
    p = (u16 *)((u8 *)line + off);
    if (p < (u16 *)end) {
        *p = (u16)glyph;
        p++;
        if (p < (u16 *)end) {
            do {
                *p = 0;
                p++;
            } while (p < (u16 *)end);
        }
    }
}
