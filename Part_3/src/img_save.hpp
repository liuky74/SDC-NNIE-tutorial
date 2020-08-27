//
// Created by liuky on 2020-08-12.
//

#ifndef NNIE_TUTORIAL_IMG_SAVE_HPP
#define NNIE_TUTORIAL_IMG_SAVE_HPP


#include <cstdint>
#include <sdc.hpp>
class SaveImgTxt{

public:
    static void int2char(uint8_t *intData, char *charData);
    static void char2int(char *charData, uint8_t *intData);
    static int SDC_RGB_save(SDC_YUV_FRAME_S *yuv_rgb_s, char* file_name);

    static int SDC_RGB_save(VW_YUV_FRAME_S *yuv_rgb_s);
    static int SDC_RGB_save(char *data_add, unsigned int width, unsigned height,char *file_name);
    static int SDC_RGB_save(HI_U8 *r_pts,HI_U8 *g_pts,HI_U8 *b_pts, unsigned int width, unsigned height,char *file_name);

    static int SDC_RGB_read(HI_U8* ptr,char* file_name,int height,int width,int channel);
};


#endif //NNIE_TUTORIAL_IMG_SAVE_HPP
