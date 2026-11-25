/* Text-line helper: overwrites the last written glyph (index-1) with `glyph`
 * and clears the remaining halfwords from the cursor up to the line's
 * end/count slot pointed to by `end`. */
void sub_080C3B28(u16 *line, s16 *end, u32 glyph)
{
    s16 idx = *end;
    if (idx > 0) {
        u16 *p = line + (idx - 1);
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
