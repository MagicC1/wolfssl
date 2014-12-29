/* aes.h
 *
 * Copyright (C) 2006-2014 wolfSSL Inc.
 *
 * This file is part of wolfSSL. (formerly known as CyaSSL)
 *
 * wolfSSL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * wolfSSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */


#ifndef NO_AES

#ifndef WOLF_CRYPT_AES_H
#define WOLF_CRYPT_AES_H


#include <wolfssl/wolfcrypt/types.h>

/* included for fips*/
#include <cyassl/ctaocrypt/aes.h>

#ifdef __cplusplus
    extern "C" {
#endif

 WOLFSSL_API int  wc_AesSetKey(Aes* aes, const byte* key, word32 len, const byte* iv,
                          int dir);
 WOLFSSL_API int  wc_AesSetIV(Aes* aes, const byte* iv);
 WOLFSSL_API int  wc_AesCbcEncrypt(Aes* aes, byte* out, const byte* in, word32 sz);
 WOLFSSL_API int  wc_AesCbcDecrypt(Aes* aes, byte* out, const byte* in, word32 sz);
 WOLFSSL_API int  wc_AesCbcDecryptWithKey(byte* out, const byte* in, word32 inSz,
                                 const byte* key, word32 keySz, const byte* iv);
 
/* AES-CTR */
#ifdef CYASSL_AES_COUNTER
 WOLFSSL_API void wc_AesCtrEncrypt(Aes* aes, byte* out, const byte* in, word32 sz);
#endif
/* AES-DIRECT */
#if defined(CYASSL_AES_DIRECT)
 WOLFSSL_API void wc_AesEncryptDirect(Aes* aes, byte* out, const byte* in);
 WOLFSSL_API void wc_AesDecryptDirect(Aes* aes, byte* out, const byte* in);
 WOLFSSL_API int  wc_AesSetKeyDirect(Aes* aes, const byte* key, word32 len,
                                const byte* iv, int dir);
#endif
#ifdef HAVE_AESGCM
 WOLFSSL_API int  wc_AesGcmSetKey(Aes* aes, const byte* key, word32 len);
 WOLFSSL_API int  wc_AesGcmEncrypt(Aes* aes, byte* out, const byte* in, word32 sz,
                              const byte* iv, word32 ivSz,
                              byte* authTag, word32 authTagSz,
                              const byte* authIn, word32 authInSz);
 WOLFSSL_API int  wc_AesGcmDecrypt(Aes* aes, byte* out, const byte* in, word32 sz,
                              const byte* iv, word32 ivSz,
                              const byte* authTag, word32 authTagSz,
                              const byte* authIn, word32 authInSz);

 WOLFSSL_API int wc_GmacSetKey(Gmac* gmac, const byte* key, word32 len);
 WOLFSSL_API int wc_GmacUpdate(Gmac* gmac, const byte* iv, word32 ivSz,
                              const byte* authIn, word32 authInSz,
                              byte* authTag, word32 authTagSz);
#endif /* HAVE_AESGCM */
#ifdef HAVE_AESCCM
 WOLFSSL_API void wc_AesCcmSetKey(Aes* aes, const byte* key, word32 keySz);
 WOLFSSL_API void wc_AesCcmEncrypt(Aes* aes, byte* out, const byte* in, word32 inSz,
                              const byte* nonce, word32 nonceSz,
                              byte* authTag, word32 authTagSz,
                              const byte* authIn, word32 authInSz);
 WOLFSSL_API int  wc_AesCcmDecrypt(Aes* aes, byte* out, const byte* in, word32 inSz,
                              const byte* nonce, word32 nonceSz,
                              const byte* authTag, word32 authTagSz,
                              const byte* authIn, word32 authInSz);
#endif /* HAVE_AESCCM */

#ifdef HAVE_CAVIUM
     WOLFSSL_API int  wc_AesInitCavium(Aes*, int);
     WOLFSSL_API void wc_AesFreeCavium(Aes*);
#endif


#ifdef HAVE_FIPS
    /* fips wrapper calls, user can call direct */
     WOLFSSL_API int  wc_AesSetKey_fips(Aes* aes, const byte* key, word32 len,
                                   const byte* iv, int dir);
     WOLFSSL_API int  wc_AesSetIV_fips(Aes* aes, const byte* iv);
     WOLFSSL_API int  wc_AesCbcEncrypt_fips(Aes* aes, byte* out, const byte* in,
                                       word32 sz);
     WOLFSSL_API int  wc_AesCbcDecrypt_fips(Aes* aes, byte* out, const byte* in,
                                       word32 sz);
     WOLFSSL_API int  wc_AesGcmSetKey_fips(Aes* aes, const byte* key, word32 len);
     WOLFSSL_API int  wc_AesGcmEncrypt_fips(Aes* aes, byte* out, const byte* in,
                              word32 sz, const byte* iv, word32 ivSz,
                              byte* authTag, word32 authTagSz,
                              const byte* authIn, word32 authInSz);
     WOLFSSL_API int  wc_AesGcmDecrypt_fips(Aes* aes, byte* out, const byte* in,
                              word32 sz, const byte* iv, word32 ivSz,
                              const byte* authTag, word32 authTagSz,
                              const byte* authIn, word32 authInSz);
//    #ifndef FIPS_NO_WRAPPERS
//        /* if not impl or fips.c impl wrapper force fips calls if fips build */
//        #define AesSetKey     AesSetKey_fips
//        #define AesSetIV      AesSetIV_fips
//        #define AesCbcEncrypt AesCbcEncrypt_fips
//        #define AesCbcDecrypt AesCbcDecrypt_fips
//        #define AesGcmSetKey  AesGcmSetKey_fips
//        #define AesGcmEncrypt AesGcmEncrypt_fips
//        #define AesGcmDecrypt AesGcmDecrypt_fips
//    #endif /* FIPS_NO_WRAPPERS */

#endif /* HAVE_FIPS */


#ifdef __cplusplus
    } /* extern "C" */
#endif


#endif /* WOLF_CRYPT_AES_H */
#endif /* NO_AES */
