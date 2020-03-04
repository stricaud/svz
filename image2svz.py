#!/usr/bin/python3

import sys
from PIL import Image, ImageDraw

im = Image.open(sys.argv[1])
pix = im.load()
print("image.size %d %d" % (im.size[0]-1, im.size[1]-1))
xmax=im.size[0]
ymax=im.size[1]
ymax=10

outpix = [None] * xmax
for i, ox in enumerate(outpix):
    outpix[i] = [None] * ymax

x = 0
y = 0
while y < ymax - 1:
    while x < xmax - 1:
        out = pix[x,y]
#       print(pix[x,y])
#        if out[3] > 128:
        if out[0] > 128 and out[1] > 250 and out[2] > 128:
            outpix[x][y] = out
            print("point %d %d" % (x+1, y+1))
        x += 1
    x = 0
    y += 1

outimg = Image.new('RGB', (xmax, ymax), color=(255,255,255))
d = ImageDraw.Draw(outimg)

# for xi, x in enumerate(outpix):
#     for yi, y in enumerate(outpix[xi]):
#         if (outpix[xi][yi] != None) :
#             print(xi, yi)
#            d.point(xi, yi)
        # if x != None:
        #     print(str(x[yi]))

d.point((10, 10), fill=(0,0,0))
outimg.save("foo.png")


    

#print(im.size)
# col = 0
# line = 0
# while line < im.size[1]:
#     while col < im.size[0]:
#         print(pix[col,line])
#         col += 1
#     line += 1

    
    

