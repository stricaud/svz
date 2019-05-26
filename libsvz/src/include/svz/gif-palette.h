#ifndef _GIF_PALETTE_
#define _GIF_PALETTE_

#define GIF_COLOR_COUNT 117

#define GIF_COLOR_WHITE 104
#define GIF_COLOR_BLACK 0

unsigned char palette[GIF_COLOR_COUNT][3] = { /* { r, g, b } */
                                           {0, 0, 0}, 
                                           {51, 0, 25},
                                           {51, 0, 51},
                                           {25, 0, 51},
                                           {0, 0, 51},
                                           {0, 25, 51},
                                           {0, 51, 51},
                                           {0, 51, 25},
                                           {0, 51, 0},
                                           {25, 51, 0},
                                           {51, 51, 0},
                                           {51, 25, 0},
                                           {51, 0, 0},
                                           
                                           {32, 32, 32},
                                           {102, 0, 51},
                                           {102, 0, 102},
                                           {51, 0, 102},
                                           {0, 0, 102},
                                           {0, 51, 102},
                                           {0, 102, 102},
                                           {0, 102, 51},
                                           {0, 102, 0},
                                           {51, 102, 0},
                                           {102, 102, 0},
                                           {102, 51, 0},
                                           {102, 0, 0},

                                           {64, 64, 64},
                                           {153, 0, 76},
                                           {153, 0, 153},
                                           {76, 0, 153},
                                           {0, 0, 153},
                                           {0, 76, 153},
                                           {0, 153, 153},
                                           {0, 153, 76},
                                           {0, 153, 0},
                                           {76, 153, 0},
                                           {153, 153, 0},
                                           {153, 76, 0},
                                           {153, 0, 0},

                                           {96, 96, 96},
                                           {204, 0, 102},
                                           {204, 0, 204},
                                           {102, 0, 204},
                                           {0, 0, 204},
                                           {0, 102, 204},
                                           {0, 204, 204},
                                           {0, 204, 102},
                                           {0, 204, 0},
                                           {102, 204, 0},
                                           {204, 204, 0},
                                           {204, 102, 0},
                                           {204, 0, 0},

                                           {128, 128, 128},
                                           {255, 0, 127},
                                           {255, 0, 255},
                                           {127, 0, 255},
                                           {0, 0, 255},
                                           {0, 128, 255},
                                           {0, 255, 255},
                                           {0, 255, 128},
                                           {0, 255, 0},
                                           {128, 255, 0},
                                           {255, 255, 0},
                                           {255, 128, 0},
                                           {255, 0, 0},

                                           {160, 160, 160},
                                           {255, 51, 153},
                                           {255, 51, 255},
                                           {153, 51, 255},
                                           {51, 51, 255},
                                           {51, 153, 255},
                                           {51, 255, 255},
                                           {51, 255, 153},
                                           {51, 255, 51},
                                           {153, 255, 51},
                                           {255, 255, 51},
                                           {255, 153, 51},
                                           {255, 51, 51},

                                           {192, 192, 192},
                                           {255, 102, 178},
                                           {255, 102, 255},
                                           {178, 102, 255},
                                           {102, 102, 255},
                                           {102, 178, 255},
                                           {102, 255, 255},
                                           {102, 255, 178},
                                           {102, 255, 102},
                                           {178, 255, 102},
                                           {255, 255, 102},
                                           {255, 178, 102},
                                           {255, 102, 102},

                                           {224, 224, 224},
                                           {255, 153, 204},
                                           {255, 153, 255},
                                           {204, 153, 255},
                                           {153, 153, 255},
                                           {153, 204, 255},
                                           {153, 255, 255},
                                           {153, 255, 204},
                                           {153, 255, 153},
                                           {204, 255, 153},
                                           {255, 255, 153},
                                           {255, 204, 153},
                                           {255, 153, 153},

                                           {255, 255, 255},
                                           {255, 204, 229},
                                           {255, 204, 255},
                                           {229, 204, 255},
                                           {204, 204, 255},
                                           {204, 229, 255},
                                           {204, 255, 255},
                                           {204, 255, 229},
                                           {204, 255, 204},
                                           {229, 255, 204},
                                           {255, 255, 204},
                                           {255, 229, 204},
                                           {255, 204, 204},
  };

#endif // _GIF_PALETTE_
