//
// Created by liuky on 2020-08-12.
//

#include "img_save.hpp"
#include <cmath>

void SaveImgTxt::int2char(uint8_t *intData, char *charData) {
    uint8_t intTmp_data = *intData;
    for (int idx = 2; idx > -1; idx--) {
        charData[idx] = intTmp_data % 10 + '0';
        intTmp_data = intTmp_data / 10;
    }
};
void SaveImgTxt::char2int(char *charData, uint8_t *intData) {
    uint8_t number_u8=0;
    int intSize = strlen(charData);
    for(int idx=0;idx<intSize;idx++){
        number_u8+=(uint8_t)(charData[intSize-1-idx]-'0')*pow(10,idx);;
    }
    *intData = number_u8;
}



int SaveImgTxt::SDC_RGB_save(SDC_YUV_FRAME_S *yuv_rgb_s,char* file_name) {
    //保存图像数据
    FILE *img_file = fopen(file_name, "w");
    char charPixel_data[4] = "000";

    uint32_t item_size = sizeof(uint8_t);
    uint32_t width = yuv_rgb_s->width, height = yuv_rgb_s->height, channel = 3;
    uint64_t yuv_data = yuv_rgb_s->addr_virt;

    uint8_t *pixel_data = NULL;
    uint32_t idx_channel, idx_height, idx_width, yuv_pixel_addr_idx = 0, img_pixel_idx = 0;
    for (idx_channel = 0; idx_channel < channel; idx_channel++) {
        for (idx_height = 0; idx_height < height; idx_height++) {
            for (idx_width = 0; idx_width < width; idx_width++) {
                yuv_pixel_addr_idx = idx_channel * (height * width) + idx_height * width + idx_width;
                pixel_data = (uint8_t *) yuv_data + yuv_pixel_addr_idx;
                int2char(pixel_data, charPixel_data);
                fputs(charPixel_data, img_file);
                fputs(",", img_file);
            }
        }
    }
    fclose(img_file);
    printf("close file\n");
    fflush(stdout);
    return PAS;
};

int SaveImgTxt::SDC_RGB_save(VW_YUV_FRAME_S *yuv_rgb_s) {
    //保存图像数据
    FILE *img_file = fopen("./img.txt", "w");
    char charPixel_data[4] = "000";

    uint32_t item_size = sizeof(uint8_t);
    uint32_t width = yuv_rgb_s->uWidth, height = yuv_rgb_s->uHeight, channel = 3;
    uint64_t yuv_data = (uint64_t)yuv_rgb_s->pYuvImgAddr;

    uint8_t *pixel_data = NULL;
    uint32_t idx_channel, idx_height, idx_width, yuv_pixel_addr_idx = 0, img_pixel_idx = 0;
    for (idx_channel = 0; idx_channel < channel; idx_channel++) {
        for (idx_height = 0; idx_height < height; idx_height++) {
            for (idx_width = 0; idx_width < width; idx_width++) {
                yuv_pixel_addr_idx = idx_channel * (height * width) + idx_height * width + idx_width;
                pixel_data = (uint8_t *) yuv_data + yuv_pixel_addr_idx;
                int2char(pixel_data, charPixel_data);
                fputs(charPixel_data, img_file);
                fputs(",", img_file);
            }
        }
    }
    fclose(img_file);
    printf("close file\n");
    fflush(stdout);
    exit(0);
    return PAS;
};

int SaveImgTxt::SDC_RGB_save(char *data_add, unsigned int width, unsigned height,char *file_name) {
    //保存图像数据
    FILE *img_file = fopen(file_name, "w");
    char charPixel_data[4] = "000";

    uint32_t item_size = sizeof(uint8_t);
    uint32_t channel = 3;
    uint64_t yuv_data = (uint64_t)data_add;

    uint8_t *pixel_data = NULL;
    uint32_t idx_channel, idx_height, idx_width, yuv_pixel_addr_idx = 0, img_pixel_idx = 0;
    for (idx_channel = 0; idx_channel < channel; idx_channel++) {
        for (idx_height = 0; idx_height < height; idx_height++) {
            for (idx_width = 0; idx_width < width; idx_width++) {
                yuv_pixel_addr_idx = idx_channel * (height * width) + idx_height * width + idx_width;
                pixel_data = (uint8_t *) yuv_data + yuv_pixel_addr_idx;
                int2char(pixel_data, charPixel_data);
                fputs(charPixel_data, img_file);
                fputs(",", img_file);
            }
        }
    }
    fclose(img_file);
    printf("close file\n");
    fflush(stdout);
//    exit(0);
    return PAS;
};

int SaveImgTxt::SDC_RGB_save(HI_U8 *r_pts,HI_U8 *g_pts,HI_U8 *b_pts, unsigned int width, unsigned height,char *file_name) {
    //保存图像数据
    FILE *img_file = fopen(file_name, "w");
    char charPixel_data[4] = "000";

    uint32_t item_size = sizeof(uint8_t);
    uint32_t channel = 3;

    uint8_t *pixel_data = NULL;
    uint32_t idx_channel, idx_height, idx_width, yuv_pixel_addr_idx = 0, img_pixel_idx = 0;
    for (idx_channel = 0; idx_channel < channel; idx_channel++) {
        for (idx_height = 0; idx_height < height; idx_height++) {
            for (idx_width = 0; idx_width < width; idx_width++) {
//                yuv_pixel_addr_idx = idx_channel * (height * width) + idx_height * width + idx_width;
                if(idx_channel==0){
                    yuv_pixel_addr_idx = idx_height * width + idx_width;
                    pixel_data = b_pts + yuv_pixel_addr_idx;
                }
                else if(idx_channel==1){
                    yuv_pixel_addr_idx = idx_height * width + idx_width;
                    pixel_data = g_pts + yuv_pixel_addr_idx;
                } else{
                    yuv_pixel_addr_idx = idx_height * width + idx_width;
                    pixel_data = r_pts + yuv_pixel_addr_idx;
                }
                int2char(pixel_data, charPixel_data);
                fputs(charPixel_data, img_file);
                fputs(",", img_file);
            }
        }
    }
    fclose(img_file);
    printf("close file\n");
    fflush(stdout);
    exit(0);
    return PAS;
}

int SaveImgTxt::SDC_RGB_read(HI_U8 *ptr, char *file_name, int height, int width,int channel) {
    uint8_t number_u8=0;
    FILE *img_file = fopen(file_name,"r");
    char charNumber[4]="000";
    char charValue='0';
    int c_idx,h_idx,w_idx;
    int pixel_idx=0;
    for(c_idx=0;c_idx<channel;c_idx++){
        for(h_idx=0;h_idx<height;h_idx++){
            for(w_idx=0;w_idx<width;w_idx++){
                for(pixel_idx=0;;pixel_idx++){
                    charValue = (char)fgetc(img_file);
                    if(charValue == ',') break;
                    charNumber[pixel_idx] = charValue;
                }
                char2int(charNumber,&number_u8);
//                printf("befor transform: %s,aft transform: %i\n",charNumber,number_u8);
                *(ptr+c_idx*height*width+h_idx*width+w_idx) = number_u8;
            }
        }
    }
    fclose(img_file);
    return PAS;
}