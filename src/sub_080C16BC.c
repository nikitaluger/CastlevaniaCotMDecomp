/* Script reader: copy the next byte from the stream pointer at +0x40 into the
 * byte field at +0x24, then advance the pointer. */
struct ScriptReader {
    u8 pad[0x24];
    u8 cmd;
    u8 pad2[0x40 - 0x25];
    u8 *data;
};

void sub_080C16BC(void *unused, struct ScriptReader *state)
{
    u8 byte = *state->data;
    state->cmd = byte;
    state->data++;
}
