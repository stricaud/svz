#ifndef _LZCOMPRESS_H_
#define _LZCOMPRESS_H_

#include <stdint.h>

uint8_t * read_file( const char * const name, long * const file_sizep );
uint8_t * lzcompress( const uint8_t * const data, const long size,
                      const int level, long * const out_sizep );
uint8_t * lzdecompress( const uint8_t * const data, const long size,
                        long * const out_sizep );


#endif /* _LZCOMPRESS_H_ */
