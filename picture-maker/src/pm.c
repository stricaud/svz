#include <stdio.h>

#include <svz/svz.h>
#include <svz/encode.h>
#include <parser.h>

FILE *svzlin;

int main(int argc, char **argv)
{
	svz_t *svz;
	int retval;
	int foo;
	
	svzlin = fopen(argv[1], "r");

	svzlrestart(svzlin);
	retval = svzlparse(&svz, &foo);
	printf("--->FOO:%d\n", foo);
	fflush(svzlin);
	fclose(svzlin);
	svzlin = NULL;

	/* if (!svzi) { */
	/* 	printf("svz is null\n"); */
	/* } */
	
	svz_encode_to_file(svz, "out.svz");	
	svz_free(svz);
	
	return 0;
}
