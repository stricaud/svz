#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <blake2.h>

#include <svz/svz.h>
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
  
  fp = fopen(filename, "rb");
  if (!fp) {
    fprintf(stderr, "Cannot open file: %s\n", filename);
    return NULL;
  }
  fread(&magic, 4, 1, fp);
  magic[4] = '\0';
  printf("got[%s]\n", magic);
  if (strncmp(magic, SVZ_MAGIC, 4)) {
    fprintf(stderr, "Not a SVZ file!\n");
    return NULL;
  }

  fread(&width, sizeof(uint16_t), 1, fp);
  fread(&height, sizeof(uint16_t), 1, fp);
  svz = svz_new(width, height);
  fread(&svz->options, sizeof(svz_options_t), 1, fp);
  fread(&hash, HASH_LEN, 1, fp);

  fread(&svz->number_of_features, sizeof(uint8_t), 1, fp);
  printf("features:%d\n", svz->number_of_features);

  for (int i=0; i < svz->number_of_features; i++) {
    fread(&svz->features[i].type, sizeof(uint8_t), 1, fp);
    max_indexes = (svz->width * svz->height)/SVZ_BITFIELD_EL_SIZE;
    for (int j=0; j < max_indexes; j++) {
      fread(&svz->features[i].bitfield[j], sizeof(int), max_indexes, fp);
    }
  }
  
  fclose(fp);
  
  
  return svz;
}
