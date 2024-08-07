//
// A compact byte-oriented AES-256 implementation.
// All lookup tables replaced with 'on the fly' calculations.
//
// Copyright (c) 2007-2011 Literatecode, http://www.literatecode.com
// Copyright (c) 2022 Ilia Levin (ilia@levin.sg)
//
// Other contributors: Hal Finney.
//
// Permission to use, copy, modify, and distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
// WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
// ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
// WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
// ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
// OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

#ifndef AES256_H__
#define AES256_H__ 1

#ifndef uint8_t
#define uint8_t  unsigned char
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define AES_SUCCESS (0)
#define AES_ERROR   (1)

typedef struct aes256_key_t { uint8_t raw[32]; } aes256_key_t;
typedef struct aes256_blk_t { uint8_t raw[16]; } aes256_blk_t;

typedef struct aes256_context_t {
    aes256_key_t key;
    aes256_key_t enckey;
    aes256_key_t deckey;
} aes256_context_t;


/// @function aes256_init
/// @brief Initialize a context structure.
/// @param[in,out] ctx Pointer to a pre-allocated context structure.
/// @param[in] key Pointer to a key initialized buffer.
/// @return AES_SUCCESS on success, AES_ERROR on failure.
///
uint8_t aes256_init(
    aes256_context_t *ctx,
    aes256_key_t *key
);

/// @brief Clear the context structure.
/// @param[in,out] ctx Pointer to a context structure.
/// @return AES_SUCCESS on success, AES_ERROR on failure.
///
uint8_t aes256_done(
    aes256_context_t *ctx
);

/// @brief Encrypt a single data block in place.
/// @param[in] ctx Pointer to an initialized context structure.
/// @param[in,out] buf Plaintext in, ciphertext out.
/// @return AES_SUCCESS on success, AES_ERROR on failure.
///
uint8_t aes256_encrypt_ecb(
    aes256_context_t *ctx,
    aes256_blk_t *buf
);

/// @brief Decrypt a single data block in place.
/// @param[in] ctx Pointer to an initialized context structure.
/// @param[in,out] buf Ciphertext in, plaintext out.
/// @return AES_SUCCESS on success, AES_ERROR on failure.
///
uint8_t aes256_decrypt_ecb(
    aes256_context_t *ctx,
    aes256_blk_t *buf
);

#ifdef __cplusplus
}
#endif

#endif // AES256_H__

static struct {
    aes256_key_t key;
    uint8_t pt[16];
    uint8_t ct[16];
} test[] = {
    {
        .key.raw = {
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
            0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
        },
        .pt = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff},
        .ct = {0x8e, 0xa2, 0xb7, 0xca, 0x51, 0x67, 0x45, 0xbf, 0xea, 0xfc, 0x49, 0x90, 0x4b, 0x49, 0x60, 0x89},
    }};
