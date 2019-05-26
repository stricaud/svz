#include <stdio.h>
#include <blake2.h>

#include <svz/svz.h>
#include <svz/encode.h>

int svz_encode_to_file(svz_t *svz, char *filename)
{
  FILE *fp;
  blake2b_state b2state;
  uint8_t hash[HASH_LEN];
  
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
  blake2b_update(&b2state, (const uint8_t *)"foo", 4);
  blake2b_final(&b2state, hash, HASH_LEN);
  fwrite(hash, HASH_LEN, 1, fp);

  fwrite(&svz->number_of_features, sizeof(uint8_t), 1, fp);
  
  fclose(fp);
  
  return 0;
}
