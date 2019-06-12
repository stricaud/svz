
#include <stdio.h>
#include <blake2.h>

#include <svz/svz.h>
#include <svz/encode.h>

int svz_encode_to_file(svz_t *svz, char *filename)
{
  FILE *fp;
  blake2b_state b2state;
  uint8_t hash[HASH_LEN];
  uint64_t max_indexes;
  
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
      max_indexes = (svz->width * svz->height)/SVZ_BITFIELD_EL_SIZE;
      for (int j=0; j < max_indexes; j++) {
	fwrite(&svz->features[SVZ_DISPLAYED_PIXELS_INDEX], sizeof(int), max_indexes, fp);
      }
      break;
    case SELECTED_PIXELS:
      max_indexes = (svz->width * svz->height)/SVZ_BITFIELD_EL_SIZE;
      for (int j=0; j < max_indexes; j++) {
	fwrite(&svz->features[SVZ_SELECTED_PIXELS_INDEX], sizeof(int), max_indexes, fp);
      }
      break;
      break;
    default:
      fprintf(stderr, "%s Error[%d]: unknown feature type: %d\n", __FUNCTION__, i, svz->features[i].type);
      break;      
    }
  }
  
  fclose(fp);
  
  return 0;
}
