#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <blake2.h>

#include <svz/svz.h>
#include <svz/lzcompress.h>
#include <svz/encode.h>
#include <svz/decode.h>

svz_t *svz_decode_from_file(char *filename)
{
	FILE *fp;
	char magic[4];
	svz_t *svz;
	uint16_t width, height;
	uint8_t hash[HASH_LEN];
	uint64_t max_indexes;

	uint8_t *in_buffer, *out_buffer;
	long in_size = 0, out_size = 0;

	long offset = 0;
	
	/* fp = fopen(filename, "rb"); */
	/* if (!fp) { */
	/* 	fprintf(stderr, "Cannot open file: %s\n", filename); */
	/* 	return NULL; */
	/* } */

	in_buffer = read_file(filename, &in_size);
	if( !in_buffer ) return NULL;
	out_buffer = lzdecompress(in_buffer, in_size, &out_size );
	if (!out_buffer) {
		fprintf(stderr, "Error reading compression from file!\n");
		return NULL;
	}
	
	memcpy(&magic, out_buffer, 4);
	
	/* fread(&magic, 4, 1, fp); */
	magic[4] = '\0';
	printf("got[%s]\n", magic);
	if (strncmp(magic, SVZ_MAGIC, 4)) {
		fprintf(stderr, "Not a SVZ file!\n");
		return NULL;
	}
	offset += 4;
	
	memcpy(&width, out_buffer + offset, sizeof(uint16_t));
	offset += sizeof(uint16_t);
	memcpy(&height, out_buffer + offset, sizeof(uint16_t));
	offset += sizeof(uint16_t);

	/* printf("Width:%ld\n", width); */
	/* printf("height:%ld\n", height); */
	
	/* fread(&width, sizeof(uint16_t), 1, fp); */
	/* fread(&height, sizeof(uint16_t), 1, fp); */
	svz = svz_new(width, height);
	memcpy(&svz->options, out_buffer + offset, sizeof(svz_options_t));
	offset += sizeof(svz_options_t);
	memcpy(&hash, out_buffer + offset, HASH_LEN);
	offset += HASH_LEN;

	memcpy(&svz->number_of_features, out_buffer + offset, sizeof(uint8_t));
	offset += sizeof(uint8_t);

	for (int i = 0; i < svz->number_of_features; i++) {
		memcpy(&svz->features[i].type, out_buffer + offset, sizeof(uint8_t));
		offset += sizeof(uint8_t);
		max_indexes = (svz->width * svz->height)/SVZ_BITFIELD_EL_SIZE;

		for (int j = 0; j < max_indexes; j++) {
			memcpy(&svz->features[i].bitfield[j], out_buffer + offset, sizeof(int));
			offset += sizeof(int);
		}
	}
	/* fread(&svz->options, sizeof(svz_options_t), 1, fp); */
	/* fread(&hash, HASH_LEN, 1, fp); */
	
	/* fread(&svz->number_of_features, sizeof(uint8_t), 1, fp); */
	/* printf("features:%d\n", svz->number_of_features); */
	
	/* for (int i=0; i < svz->number_of_features; i++) { */
	/* 	fread(&svz->features[i].type, sizeof(uint8_t), 1, fp); */
	/* 	max_indexes = (svz->width * svz->height)/SVZ_BITFIELD_EL_SIZE; */
		
	/* 	for (int j=0; j < max_indexes; j++) { */
	/* 		fread(&svz->features[i].bitfield[j], sizeof(int), 1, fp); */
	/* 	} */
	/* } */
	
	/* fclose(fp); */
	
	return svz;
}
