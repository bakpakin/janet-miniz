#include <janet.h>
#include "miniz.h"

static Janet cfun_compress(int32_t argc, Janet *argv) {
    janet_arity(argc, 1, 3);
    JanetByteView bytes = janet_getbytes(argv, 0);
    int32_t level = janet_optinteger(argv, argc, 1, 5);
    if (level < 0 || level > 10) {
        janet_panicf("compression level must be between 0 and 10, got %d", level);
    }
    JanetBuffer *buffer = janet_optbuffer(argv, argc, 2, (bytes.len / 2) + 10);
    mz_ulong dest_len;
    int status;
    do {
        dest_len = buffer->capacity - buffer->count;
        status = mz_compress2(buffer->data + buffer->count, &dest_len, bytes.bytes, bytes.len, level);
        if (status == MZ_BUF_ERROR) {
            if (buffer->capacity == INT32_MAX) {
                janet_panic("too large to compress");
            }
            janet_buffer_ensure(buffer, 1 + buffer->capacity, 2);
        }
    } while (status == MZ_BUF_ERROR);
    if (status != MZ_OK) janet_panicf("compression failed with code %d", status);
    buffer->count += (int32_t) dest_len;
    return janet_wrap_buffer(buffer);
}

static Janet cfun_decompress(int32_t argc, Janet *argv) {
    janet_arity(argc, 1, 2);
    JanetByteView bytes = janet_getbytes(argv, 0);
    JanetBuffer *buffer = janet_optbuffer(argv, argc, 1, bytes.len);
    mz_ulong dest_len;
    int status;
    do {
        dest_len = buffer->capacity - buffer->count;
        status = mz_uncompress(buffer->data + buffer->count, &dest_len, bytes.bytes, bytes.len);
        if (status == MZ_BUF_ERROR) {
            if (buffer->capacity == INT32_MAX) {
                janet_panic("too large to decompress");
            }
            janet_buffer_ensure(buffer, buffer->capacity + 1, 2);
        }
    } while (status == MZ_BUF_ERROR);
    if (status != MZ_OK) janet_panicf("compression failed with code %d", status);
    buffer->count += (int32_t) dest_len;
    return janet_wrap_buffer(buffer);
}

static JanetReg cfuns[] = {
    {"compress", cfun_compress,
        "(miniz/compress bytes &opt level buffer)\n\n"
        "Compress a byte sequence into a buffer. Takes an optional compression level from 1-10, where 6 is the default. "
        "Returns the modified buffer, or a new buffer if no buffer is provided."},
    {"decompress", cfun_decompress,
        "(miniz/decompress bytes &opt buffer)\n\n"
        "Takes previously compressed bytes and decompresses them into the original byte sequence. Returns a modified buffer "
        "containing the result, or a new buffer if no buffer is provided."},
    {NULL, NULL, NULL}
};

JANET_MODULE_ENTRY(JanetTable *env) {
    janet_cfuns(env, "miniz", cfuns);
}
