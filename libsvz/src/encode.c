#include <stdio.h>
#include <blake2.h>

#include <svz/svz.h>
#include <svz/lzcompress.h>
#include <svz/encode.h>

int svz_encode_to_file(svz_t *svz, char *filename)
{
	FILE *fp;
	blake2b_state b2state;
	uint8_t hash[HASH_LEN];
	uint64_t max_indexes;
	uint8_t feature_id;
	size_t outlen;

	uint8_t *in_buffer, *compressed_buffer;
	long in_size = 0;
	int level = 9;
	long compressed_size = 0;

	if (!svz) {
		fprintf(stderr, "Cannot encode to a file, since the image structure is empty!\n");
		return -1;
	}
	
	fp = fopen(filename, "wb");
	if (!fp) {
		fprintf(stderr, "Cannot write to %s\n", filename);
		return -1;
	}
	
	fwrite(SVZ_MAGIC, 4, 1, fp);
	fwrite(&svz->width, sizeof(uint16_t), 1, fp);
	fwrite(&svz->height, sizeof(uint16_t), 1, fp);
	fwrite(&svz->options, sizeof(svz_options_t), 1, fp);
	
	blake2b_init(&b2state, HASH_LEN);  
	for (int i=0; i < svz->number_of_features; i++) {
		switch(svz->features[i].type) {
		case DISPLAYED_PIXELS:
			max_indexes = (svz->width * svz->height)/SVZ_BITFIELD_EL_SIZE;
			blake2b_update(&b2state, (const uint8_t *)&svz->features[SVZ_DISPLAYED_PIXELS_INDEX], sizeof(int) * max_indexes);
			break;
		case SELECTED_PIXELS:
			max_indexes = (svz->width * svz->height)/SVZ_BITFIELD_EL_SIZE;
			blake2b_update(&b2state, (const uint8_t *)&svz->features[SVZ_SELECTED_PIXELS_INDEX], sizeof(int) * max_indexes);
			break;      
		default:
			break;
		}
	}
	blake2b_final(&b2state, hash, HASH_LEN);
	fwrite(hash, HASH_LEN, 1, fp);
	
	fwrite(&svz->number_of_features, sizeof(uint8_t), 1, fp);
	
	for (int i=0; i < svz->number_of_features; i++) {
		switch(svz->features[i].type) {
		case DISPLAYED_PIXELS:
			feature_id = SVZ_DISPLAYED_PIXELS_ID;
			fwrite(&feature_id, sizeof(uint8_t), 1, fp);
			max_indexes = (svz->width * svz->height)/SVZ_BITFIELD_EL_SIZE;
			for (int j=0; j < max_indexes; j++) {
				fwrite(&svz->features[SVZ_DISPLAYED_PIXELS_INDEX].bitfield[j], sizeof(int), 1, fp);
			}
			break;
		case SELECTED_PIXELS:
			feature_id = SVZ_SELECTED_PIXELS_ID;
			fwrite(&feature_id, sizeof(uint8_t), 1, fp);
			max_indexes = (svz->width * svz->height)/SVZ_BITFIELD_EL_SIZE;
			for (int j=0; j < max_indexes; j++) {
				fwrite(&svz->features[SVZ_SELECTED_PIXELS_INDEX].bitfield[j], sizeof(int), 1, fp);
			}
			break;
		default:
			fprintf(stderr, "%s Error[%d]: unknown feature type: %d\n", __FUNCTION__, i, svz->features[i].type);
			break;      
		}
	}
	
	fclose(fp);
	
	in_buffer = read_file(filename, &in_size);
	if (!in_buffer) {
		fprintf(stderr, "Cannot read file: %s\n", filename);
		return -1;
	}
	
	compressed_buffer = lzcompress(in_buffer, in_size, level, &compressed_size);
	fp = fopen(filename, "wb");
	fwrite(compressed_buffer, compressed_size, 1, fp);
	fclose(fp);
	
	return 0;
}
