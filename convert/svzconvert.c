/* Public domain, converts a SVZ image into anything cairo supports */
#include <stdio.h>
#include <gd.h>

#include <svz/svz.h>
#include <svz/decode.h>
#include <svz/image.h>
#include <svz/features.h>

int main(int argc, char **argv)
{
	svz_t *svz;
	
	
	gdImagePtr im;
	FILE *imout;

	int black, white;
	size_t bitcount = 0;
	int line_no = -1;
	int col_no = 1;

	int x = 0;

	if (argc < 3) {
		fprintf(stderr, "%s <file.svz> <file.png>\n", argv[0]);
		return -1;
	}

	svz = svz_decode_from_file(argv[1]);
	if (!svz) {
		fprintf(stderr, "Error reading SVZ file!\n");
		return -1;
	}

	im = gdImageCreate(svz->width,svz->height);
	white = gdImageColorAllocate(im, 255, 255, 255);
	black = gdImageColorAllocate(im, 0, 0, 0);

	for (int i = 0; i < svz->number_of_features; i++) {
		switch(svz->features[i].type) {
		case DISPLAYED_PIXELS:
			while (bitcount < (svz->width * svz->height)) {
				if (!(bitcount%svz->width)) {
					x = 0;
					line_no++;
				}

				if (svz_get_bit(svz->features->bitfield, bitcount)) {
					gdImageSetPixel(im, x, line_no, black);
				}
				x++;
				bitcount++;
			}
			break;
		case SELECTED_PIXELS:
			break;
		default:
			fprintf(stderr, "%s Error[%d]: unknown feature type: %d\n", __FUNCTION__, i, svz->features[i].type);
			break;
		}
	}

	
	imout = fopen(argv[2], "wb");
	gdImagePng(im, imout);

	fclose(imout);
	gdImageDestroy(im);
	svz_free(svz);
	
	return 0;
}
