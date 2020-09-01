//
// Created by liuky on 2020-08-07.
//

#include <time.h>
#include <math.h>
#include <unistd.h>
#include "SSDModel.hpp"
#include "img_save.hpp"

//HI_S32 SVP_NNIE_Overlap(HI_S32 s32XMin1, HI_S32 s32YMin1, HI_S32 s32XMax1, HI_S32 s32YMax1, HI_S32 s32XMin2,
//                        HI_S32 s32YMin2, HI_S32 s32XMax2, HI_S32 s32YMax2,  HI_S32* s32AreaSum, HI_S32* s32AreaInter)
//{
//    HI_S32 s32Inter = 0;
//    HI_S32 s32Total = 0;
//    HI_S32 s32XMin = 0;
//    HI_S32 s32YMin = 0;
//    HI_S32 s32XMax = 0;
//    HI_S32 s32YMax = 0;
//    HI_S32 s32Area1 = 0;
//    HI_S32 s32Area2 = 0;
//    HI_S32 s32InterWidth = 0;
//    HI_S32 s32InterHeight = 0;
//
//    s32XMin = SAMPLE_SVP_NNIE_MAX(s32XMin1, s32XMin2);
//    s32YMin = SAMPLE_SVP_NNIE_MAX(s32YMin1, s32YMin2);
//    s32XMax = SAMPLE_SVP_NNIE_MIN(s32XMax1, s32XMax2);
//    s32YMax = SAMPLE_SVP_NNIE_MIN(s32YMax1, s32YMax2);
//
//    s32InterWidth = s32XMax - s32XMin + 1;
//    s32InterHeight = s32YMax - s32YMin + 1;
//
//    s32InterWidth = ( s32InterWidth >= 0 ) ? s32InterWidth : 0;
//    s32InterHeight = ( s32InterHeight >= 0 ) ? s32InterHeight : 0;
//
//    s32Inter = s32InterWidth * s32InterHeight;
//    s32Area1 = (s32XMax1 - s32XMin1 + 1) * (s32YMax1 - s32YMin1 + 1);
//    s32Area2 = (s32XMax2 - s32XMin2 + 1) * (s32YMax2 - s32YMin2 + 1);
//
//    s32Total = s32Area1 + s32Area2 - s32Inter;
//
//    *s32AreaSum = s32Total;
//    *s32AreaInter = s32Inter;
//    return HI_SUCCESS;
//}

//HI_S32 SVP_NNIE_NonMaxSuppression( HI_S32* ps32Proposals, HI_U32 u32AnchorsNum,
//                                   HI_U32 u32NmsThresh,HI_U32 u32MaxRoiNum)
//{
//    HI_S32 s32XMin1 = 0;
//    HI_S32 s32YMin1 = 0;
//    HI_S32 s32XMax1 = 0;
//    HI_S32 s32YMax1 = 0;
//    HI_S32 s32XMin2 = 0;
//    HI_S32 s32YMin2 = 0;
//    HI_S32 s32XMax2 = 0;
//    HI_S32 s32YMax2 = 0;
//    HI_S32 s32AreaTotal = 0;
//    HI_S32 s32AreaInter = 0;
//    HI_U32 i = 0;
//    HI_U32 j = 0;
//    HI_U32 u32Num = 0;
//    bool bNoOverlap = true;
////    HI_BOOL bNoOverlap  = HI_TRUE;
//    for (i = 0; i < u32AnchorsNum && u32Num < u32MaxRoiNum; i++)
//    {
//        if( ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*i+5] == 0 )
//        {
//            u32Num++;
//            s32XMin1 =  ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*i];
//            s32YMin1 =  ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*i+1];
//            s32XMax1 =  ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*i+2];
//            s32YMax1 =  ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*i+3];
//            for(j= i+1;j< u32AnchorsNum; j++)
//            {
//                if( ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*j+5] == 0 )
//                {
//                    s32XMin2 = ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*j];
//                    s32YMin2 = ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*j+1];
//                    s32XMax2 = ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*j+2];
//                    s32YMax2 = ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*j+3];
//
//                    bNoOverlap = (s32XMin2>s32XMax1)||(s32XMax2<s32XMin1)||(s32YMin2>s32YMax1)||(s32YMax2<s32YMin1);
//                    if(bNoOverlap)
//                    {
//                        continue;
//                    }
//                    (void)SVP_NNIE_Overlap(s32XMin1, s32YMin1, s32XMax1, s32YMax1, s32XMin2, s32YMin2, s32XMax2, s32YMax2, &s32AreaTotal, &s32AreaInter);
//                    if(s32AreaInter*SAMPLE_SVP_NNIE_QUANT_BASE > ((HI_S32)u32NmsThresh*s32AreaTotal))
//                    {
//                        if( ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*i+4] >= ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*j+4] )
//                        {
//                            ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*j+5] = 1;
//                        }
//                        else
//                        {
//                            ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*i+5] = 1;
//                        }
//                    }
//                }
//            }
//        }
//    }
//    return HI_SUCCESS;
//}

//void SVP_NNIE_Argswap(HI_S32* ps32Src1, HI_S32* ps32Src2)
//{
//    HI_U32 i = 0;
//    HI_S32 u32Tmp = 0;
//    for( i = 0; i < SAMPLE_SVP_NNIE_PROPOSAL_WIDTH; i++ )
//    {
//        u32Tmp = ps32Src1[i];
//        ps32Src1[i] = ps32Src2[i];
//        ps32Src2[i] = u32Tmp;
//    }
//}

void SSDModel::SVP_NNIE_Argswap(HI_S32 *ps32Src1, HI_S32 *ps32Src2) {
    HI_U32 i = 0;
    HI_S32 u32Tmp = 0;
    for( i = 0; i < SAMPLE_SVP_NNIE_PROPOSAL_WIDTH; i++ )
    {
        u32Tmp = ps32Src1[i];
        ps32Src1[i] = ps32Src2[i];
        ps32Src2[i] = u32Tmp;
    }
}

HI_S32 SSDModel::SVP_NNIE_NonRecursiveArgQuickSort(HI_S32 *ps32Array, HI_S32 s32Low, HI_S32 s32High,
                                                   SAMPLE_SVP_NNIE_STACK_S *pstStack, HI_U32 u32MaxNum)
{
    HI_S32 i = s32Low;
    HI_S32 j = s32High;
    HI_S32 s32Top = 0;
    HI_S32 s32KeyConfidence = ps32Array[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH * s32Low + 4];
    pstStack[s32Top].s32Min = s32Low;
    pstStack[s32Top].s32Max = s32High;

    while(s32Top > -1)
    {
        s32Low = pstStack[s32Top].s32Min;
        s32High = pstStack[s32Top].s32Max;
        i = s32Low;
        j = s32High;
        s32Top--;

        s32KeyConfidence = ps32Array[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH * s32Low + 4];

        while(i < j)
        {
            while((i < j) && (s32KeyConfidence > ps32Array[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 4]))
            {
                j--;
            }
            if(i < j)
            {
                SVP_NNIE_Argswap(&ps32Array[i*SAMPLE_SVP_NNIE_PROPOSAL_WIDTH], &ps32Array[j*SAMPLE_SVP_NNIE_PROPOSAL_WIDTH]);
                i++;
            }

            while((i < j) && (s32KeyConfidence < ps32Array[i*SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 4]))
            {
                i++;
            }
            if(i < j)
            {
                SVP_NNIE_Argswap(&ps32Array[i*SAMPLE_SVP_NNIE_PROPOSAL_WIDTH], &ps32Array[j*SAMPLE_SVP_NNIE_PROPOSAL_WIDTH]);
                j--;
            }
        }

        if(s32Low <= u32MaxNum)
        {
            if(s32Low < i-1)
            {
                s32Top++;
                pstStack[s32Top].s32Min = s32Low;
                pstStack[s32Top].s32Max = i-1;
            }

            if(s32High > i+1)
            {
                s32Top++;
                pstStack[s32Top].s32Min = i+1;
                pstStack[s32Top].s32Max = s32High;
            }
        }
    }
    return HI_SUCCESS;
}
//HI_S32 SVP_NNIE_NonRecursiveArgQuickSort(HI_S32* ps32Array,
//                                         HI_S32 s32Low, HI_S32 s32High, SAMPLE_SVP_NNIE_STACK_S *pstStack,HI_U32 u32MaxNum)
//{
//    HI_S32 i = s32Low;
//    HI_S32 j = s32High;
//    HI_S32 s32Top = 0;
//    HI_S32 s32KeyConfidence = ps32Array[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH * s32Low + 4];
//    pstStack[s32Top].s32Min = s32Low;
//    pstStack[s32Top].s32Max = s32High;
//
//    while(s32Top > -1)
//    {
//        s32Low = pstStack[s32Top].s32Min;
//        s32High = pstStack[s32Top].s32Max;
//        i = s32Low;
//        j = s32High;
//        s32Top--;
//
//        s32KeyConfidence = ps32Array[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH * s32Low + 4];
//
//        while(i < j)
//        {
//            while((i < j) && (s32KeyConfidence > ps32Array[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 4]))
//            {
//                j--;
//            }
//            if(i < j)
//            {
//                SVP_NNIE_Argswap(&ps32Array[i*SAMPLE_SVP_NNIE_PROPOSAL_WIDTH], &ps32Array[j*SAMPLE_SVP_NNIE_PROPOSAL_WIDTH]);
//                i++;
//            }
//
//            while((i < j) && (s32KeyConfidence < ps32Array[i*SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 4]))
//            {
//                i++;
//            }
//            if(i < j)
//            {
//                SVP_NNIE_Argswap(&ps32Array[i*SAMPLE_SVP_NNIE_PROPOSAL_WIDTH], &ps32Array[j*SAMPLE_SVP_NNIE_PROPOSAL_WIDTH]);
//                j--;
//            }
//        }
//
//        if(s32Low <= u32MaxNum)
//        {
//            if(s32Low < i-1)
//            {
//                s32Top++;
//                pstStack[s32Top].s32Min = s32Low;
//                pstStack[s32Top].s32Max = i-1;
//            }
//
//            if(s32High > i+1)
//            {
//                s32Top++;
//                pstStack[s32Top].s32Min = i+1;
//                pstStack[s32Top].s32Max = s32High;
//            }
//        }
//    }
//    return HI_SUCCESS;
//}

HI_S32 SSDModel::SVP_NNIE_Ssd_PriorBoxForward(HI_U32 u32PriorBoxWidth, HI_U32 u32PriorBoxHeight, HI_U32 u32OriImWidth,
                                              HI_U32 u32OriImHeight, HI_FLOAT *pf32PriorBoxMinSize,
                                              HI_U32 u32MinSizeNum, HI_FLOAT *pf32PriorBoxMaxSize, HI_U32 u32MaxSizeNum,
                                              HI_BOOL bFlip, HI_BOOL bClip, HI_U32 u32InputAspectRatioNum,
                                              HI_FLOAT *af32PriorBoxAspectRatio, HI_FLOAT f32PriorBoxStepWidth,
                                              HI_FLOAT f32PriorBoxStepHeight, HI_FLOAT f32Offset,
                                              HI_S32 *as32PriorBoxVar, HI_S32 *ps32PriorboxOutputData)
{
    HI_U32 u32AspectRatioNum = 0;
    HI_U32 u32Index = 0;
    HI_FLOAT af32AspectRatio[SAMPLE_SVP_NNIE_SSD_ASPECT_RATIO_NUM] = { 0 };
    HI_U32 u32NumPrior = 0;
    HI_FLOAT f32CenterX = 0;
    HI_FLOAT f32CenterY = 0;
    HI_FLOAT f32BoxHeight = 0;
    HI_FLOAT f32BoxWidth = 0;
    HI_FLOAT f32MaxBoxWidth = 0;
    HI_U32 i = 0;
    HI_U32 j = 0;
    HI_U32 n = 0;
    HI_U32 h = 0;
    HI_U32 w = 0;
    SAMPLE_SVP_CHECK_EXPR_RET((HI_TRUE == bFlip && u32InputAspectRatioNum >
                                                   (SAMPLE_SVP_NNIE_SSD_ASPECT_RATIO_NUM-1)/2),HI_INVALID_VALUE,SAMPLE_SVP_ERR_LEVEL_ERROR,
                              "Error,when bFlip is true, u32InputAspectRatioNum(%d) can't be greater than %d!\n",
                              u32InputAspectRatioNum, (SAMPLE_SVP_NNIE_SSD_ASPECT_RATIO_NUM-1)/2);
    SAMPLE_SVP_CHECK_EXPR_RET((HI_FALSE == bFlip && u32InputAspectRatioNum >
                                                    (SAMPLE_SVP_NNIE_SSD_ASPECT_RATIO_NUM-1)),HI_INVALID_VALUE,SAMPLE_SVP_ERR_LEVEL_ERROR,
                              "Error,when bFlip is false, u32InputAspectRatioNum(%d) can't be greater than %d!\n",
                              u32InputAspectRatioNum, (SAMPLE_SVP_NNIE_SSD_ASPECT_RATIO_NUM-1));

    // generate aspect_ratios
    u32AspectRatioNum = 0;
    af32AspectRatio[0] = 1;
    u32AspectRatioNum++;
    for (i = 0; i < u32InputAspectRatioNum; i++)
    {
        af32AspectRatio[u32AspectRatioNum++] = af32PriorBoxAspectRatio[i];
        if (bFlip)
        {
            af32AspectRatio[u32AspectRatioNum++] = 1.0f / af32PriorBoxAspectRatio[i];
        }
    }
    u32NumPrior = u32MinSizeNum * u32AspectRatioNum + u32MaxSizeNum;

    u32Index = 0;
    for (h = 0; h < u32PriorBoxHeight; h++)
    {
        for (w = 0; w < u32PriorBoxWidth; w++)
        {
            f32CenterX = (w + f32Offset) * f32PriorBoxStepWidth;
            f32CenterY = (h + f32Offset) * f32PriorBoxStepHeight;
            for (n = 0; n < u32MinSizeNum; n++)
            {
                /*** first prior ***/
                f32BoxHeight = pf32PriorBoxMinSize[n];
                f32BoxWidth = pf32PriorBoxMinSize[n];
                ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterX - f32BoxWidth * SAMPLE_SVP_NNIE_HALF);
                ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterY - f32BoxHeight * SAMPLE_SVP_NNIE_HALF);
                ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterX + f32BoxWidth * SAMPLE_SVP_NNIE_HALF);
                ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterY + f32BoxHeight * SAMPLE_SVP_NNIE_HALF);
                /*** second prior ***/
                if(u32MaxSizeNum>0)
                {

                    f32MaxBoxWidth = sqrt(pf32PriorBoxMinSize[n] * pf32PriorBoxMaxSize[n]);
                    f32BoxHeight = f32MaxBoxWidth;
                    f32BoxWidth = f32MaxBoxWidth;
                    ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterX - f32BoxWidth * SAMPLE_SVP_NNIE_HALF);
                    ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterY - f32BoxHeight * SAMPLE_SVP_NNIE_HALF);
                    ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterX + f32BoxWidth * SAMPLE_SVP_NNIE_HALF);
                    ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterY + f32BoxHeight * SAMPLE_SVP_NNIE_HALF);
                }
                /**** rest of priors, skip AspectRatio == 1 ****/
                for (i = 1; i < u32AspectRatioNum; i++)
                {

                    f32BoxWidth = (HI_FLOAT)(pf32PriorBoxMinSize[n] * sqrt( af32AspectRatio[i] ));
                    f32BoxHeight = (HI_FLOAT)(pf32PriorBoxMinSize[n]/sqrt( af32AspectRatio[i] ));
                    ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterX - f32BoxWidth * SAMPLE_SVP_NNIE_HALF);
                    ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterY - f32BoxHeight * SAMPLE_SVP_NNIE_HALF);
                    ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterX + f32BoxWidth * SAMPLE_SVP_NNIE_HALF);
                    ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterY + f32BoxHeight * SAMPLE_SVP_NNIE_HALF);
                }
            }
        }
    }
    /************ clip the priors' coordidates, within [0, u32ImgWidth] & [0, u32ImgHeight] *************/
    if (bClip)
    {
        for (i = 0; i < (HI_U32)(u32PriorBoxWidth * u32PriorBoxHeight * SAMPLE_SVP_NNIE_COORDI_NUM*u32NumPrior / 2); i++)
        {
            ps32PriorboxOutputData[2 * i] = SAMPLE_SVP_NNIE_MIN((HI_U32)SAMPLE_SVP_NNIE_MAX(ps32PriorboxOutputData[2 * i], 0), u32OriImWidth);
            ps32PriorboxOutputData[2 * i + 1] = SAMPLE_SVP_NNIE_MIN((HI_U32)SAMPLE_SVP_NNIE_MAX(ps32PriorboxOutputData[2 * i + 1], 0), u32OriImHeight);
        }
    }
    /*********************** get var **********************/
    for (h = 0; h < u32PriorBoxHeight; h++)
    {
        for (w = 0; w < u32PriorBoxWidth; w++)
        {
            for (i = 0; i < u32NumPrior; i++)
            {
                for (j = 0; j < SAMPLE_SVP_NNIE_COORDI_NUM; j++)
                {
                    ps32PriorboxOutputData[u32Index++] = (HI_S32)as32PriorBoxVar[j];
                }
            }
        }
    }
    return HI_SUCCESS;
}

//HI_S32 SVP_NNIE_Ssd_PriorBoxForward(HI_U32 u32PriorBoxWidth,
//                                    HI_U32 u32PriorBoxHeight, HI_U32 u32OriImWidth, HI_U32 u32OriImHeight,
//                                    HI_FLOAT* pf32PriorBoxMinSize, HI_U32 u32MinSizeNum, HI_FLOAT* pf32PriorBoxMaxSize,
//                                    HI_U32 u32MaxSizeNum, HI_BOOL bFlip, HI_BOOL bClip, HI_U32 u32InputAspectRatioNum,
//                                    HI_FLOAT af32PriorBoxAspectRatio[],HI_FLOAT f32PriorBoxStepWidth,
//                                    HI_FLOAT f32PriorBoxStepHeight,HI_FLOAT f32Offset,HI_S32 as32PriorBoxVar[],
//                                    HI_S32* ps32PriorboxOutputData)
//{
//    HI_U32 u32AspectRatioNum = 0;
//    HI_U32 u32Index = 0;
//    HI_FLOAT af32AspectRatio[SAMPLE_SVP_NNIE_SSD_ASPECT_RATIO_NUM] = { 0 };
//    HI_U32 u32NumPrior = 0;
//    HI_FLOAT f32CenterX = 0;
//    HI_FLOAT f32CenterY = 0;
//    HI_FLOAT f32BoxHeight = 0;
//    HI_FLOAT f32BoxWidth = 0;
//    HI_FLOAT f32MaxBoxWidth = 0;
//    HI_U32 i = 0;
//    HI_U32 j = 0;
//    HI_U32 n = 0;
//    HI_U32 h = 0;
//    HI_U32 w = 0;
//    SAMPLE_SVP_CHECK_EXPR_RET((HI_TRUE == bFlip && u32InputAspectRatioNum >
//                                                   (SAMPLE_SVP_NNIE_SSD_ASPECT_RATIO_NUM-1)/2),HI_INVALID_VALUE,SAMPLE_SVP_ERR_LEVEL_ERROR,
//                              "Error,when bFlip is true, u32InputAspectRatioNum(%d) can't be greater than %d!\n",
//                              u32InputAspectRatioNum, (SAMPLE_SVP_NNIE_SSD_ASPECT_RATIO_NUM-1)/2);
//    SAMPLE_SVP_CHECK_EXPR_RET((HI_FALSE == bFlip && u32InputAspectRatioNum >
//                                                    (SAMPLE_SVP_NNIE_SSD_ASPECT_RATIO_NUM-1)),HI_INVALID_VALUE,SAMPLE_SVP_ERR_LEVEL_ERROR,
//                              "Error,when bFlip is false, u32InputAspectRatioNum(%d) can't be greater than %d!\n",
//                              u32InputAspectRatioNum, (SAMPLE_SVP_NNIE_SSD_ASPECT_RATIO_NUM-1));
//
//    // generate aspect_ratios
//    u32AspectRatioNum = 0;
//    af32AspectRatio[0] = 1;
//    u32AspectRatioNum++;
//    for (i = 0; i < u32InputAspectRatioNum; i++)
//    {
//        af32AspectRatio[u32AspectRatioNum++] = af32PriorBoxAspectRatio[i];
//        if (bFlip)
//        {
//            af32AspectRatio[u32AspectRatioNum++] = 1.0f / af32PriorBoxAspectRatio[i];
//        }
//    }
//    u32NumPrior = u32MinSizeNum * u32AspectRatioNum + u32MaxSizeNum;
//
//    u32Index = 0;
//    for (h = 0; h < u32PriorBoxHeight; h++)
//    {
//        for (w = 0; w < u32PriorBoxWidth; w++)
//        {
//            f32CenterX = (w + f32Offset) * f32PriorBoxStepWidth;
//            f32CenterY = (h + f32Offset) * f32PriorBoxStepHeight;
//            for (n = 0; n < u32MinSizeNum; n++)
//            {
//                /*** first prior ***/
//                f32BoxHeight = pf32PriorBoxMinSize[n];
//                f32BoxWidth = pf32PriorBoxMinSize[n];
//                ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterX - f32BoxWidth * SAMPLE_SVP_NNIE_HALF);
//                ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterY - f32BoxHeight * SAMPLE_SVP_NNIE_HALF);
//                ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterX + f32BoxWidth * SAMPLE_SVP_NNIE_HALF);
//                ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterY + f32BoxHeight * SAMPLE_SVP_NNIE_HALF);
//                /*** second prior ***/
//                if(u32MaxSizeNum>0)
//                {
//
//                    f32MaxBoxWidth = sqrt(pf32PriorBoxMinSize[n] * pf32PriorBoxMaxSize[n]);
//                    f32BoxHeight = f32MaxBoxWidth;
//                    f32BoxWidth = f32MaxBoxWidth;
//                    ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterX - f32BoxWidth * SAMPLE_SVP_NNIE_HALF);
//                    ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterY - f32BoxHeight * SAMPLE_SVP_NNIE_HALF);
//                    ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterX + f32BoxWidth * SAMPLE_SVP_NNIE_HALF);
//                    ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterY + f32BoxHeight * SAMPLE_SVP_NNIE_HALF);
//                }
//                /**** rest of priors, skip AspectRatio == 1 ****/
//                for (i = 1; i < u32AspectRatioNum; i++)
//                {
//
//                    f32BoxWidth = (HI_FLOAT)(pf32PriorBoxMinSize[n] * sqrt( af32AspectRatio[i] ));
//                    f32BoxHeight = (HI_FLOAT)(pf32PriorBoxMinSize[n]/sqrt( af32AspectRatio[i] ));
//                    ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterX - f32BoxWidth * SAMPLE_SVP_NNIE_HALF);
//                    ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterY - f32BoxHeight * SAMPLE_SVP_NNIE_HALF);
//                    ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterX + f32BoxWidth * SAMPLE_SVP_NNIE_HALF);
//                    ps32PriorboxOutputData[u32Index++] = (HI_S32)(f32CenterY + f32BoxHeight * SAMPLE_SVP_NNIE_HALF);
//                }
//            }
//        }
//    }
//    /************ clip the priors' coordidates, within [0, u32ImgWidth] & [0, u32ImgHeight] *************/
//    if (bClip)
//    {
//        for (i = 0; i < (HI_U32)(u32PriorBoxWidth * u32PriorBoxHeight * SAMPLE_SVP_NNIE_COORDI_NUM*u32NumPrior / 2); i++)
//        {
//            ps32PriorboxOutputData[2 * i] = SAMPLE_SVP_NNIE_MIN((HI_U32)SAMPLE_SVP_NNIE_MAX(ps32PriorboxOutputData[2 * i], 0), u32OriImWidth);
//            ps32PriorboxOutputData[2 * i + 1] = SAMPLE_SVP_NNIE_MIN((HI_U32)SAMPLE_SVP_NNIE_MAX(ps32PriorboxOutputData[2 * i + 1], 0), u32OriImHeight);
//        }
//    }
//    /*********************** get var **********************/
//    for (h = 0; h < u32PriorBoxHeight; h++)
//    {
//        for (w = 0; w < u32PriorBoxWidth; w++)
//        {
//            for (i = 0; i < u32NumPrior; i++)
//            {
//                for (j = 0; j < SAMPLE_SVP_NNIE_COORDI_NUM; j++)
//                {
//                    ps32PriorboxOutputData[u32Index++] = (HI_S32)as32PriorBoxVar[j];
//                }
//            }
//        }
//    }
//    return HI_SUCCESS;
//}


HI_S32 SSDModel::SVP_NNIE_SSD_SoftMax(HI_S32 *ps32Src, HI_S32 s32ArraySize, HI_S32 *ps32Dst)
{
    HI_S32 s32Max = 0;
    HI_S32 s32Sum = 0;
    HI_S32 i = 0;
    for (i = 0; i < s32ArraySize; ++i)
    {
        if (s32Max < ps32Src[i])
        {
            s32Max = ps32Src[i];
        }
    }
    for (i = 0; i < s32ArraySize; ++i)
    {
        ps32Dst[i] = (HI_S32)(SAMPLE_SVP_NNIE_QUANT_BASE* exp((HI_FLOAT)(ps32Src[i] - s32Max) / SAMPLE_SVP_NNIE_QUANT_BASE));
        s32Sum += ps32Dst[i];
    }
    for (i = 0; i < s32ArraySize; ++i)
    {
        ps32Dst[i] = (HI_S32)(((HI_FLOAT)ps32Dst[i] / (HI_FLOAT)s32Sum) * SAMPLE_SVP_NNIE_QUANT_BASE);
    }
    return HI_SUCCESS;
}

//HI_S32 SVP_NNIE_SSD_SoftMax(HI_S32* ps32Src, HI_S32 s32ArraySize, HI_S32* ps32Dst)
//{
//    HI_S32 s32Max = 0;
//    HI_S32 s32Sum = 0;
//    HI_S32 i = 0;
//    for (i = 0; i < s32ArraySize; ++i)
//    {
//        if (s32Max < ps32Src[i])
//        {
//            s32Max = ps32Src[i];
//        }
//    }
//    for (i = 0; i < s32ArraySize; ++i)
//    {
//        ps32Dst[i] = (HI_S32)(SAMPLE_SVP_NNIE_QUANT_BASE* exp((HI_FLOAT)(ps32Src[i] - s32Max) / SAMPLE_SVP_NNIE_QUANT_BASE));
//        s32Sum += ps32Dst[i];
//    }
//    for (i = 0; i < s32ArraySize; ++i)
//    {
//        ps32Dst[i] = (HI_S32)(((HI_FLOAT)ps32Dst[i] / (HI_FLOAT)s32Sum) * SAMPLE_SVP_NNIE_QUANT_BASE);
//    }
//    return HI_SUCCESS;
//}

HI_S32 SSDModel::SVP_NNIE_Ssd_SoftmaxForward(HI_U32 u32SoftMaxInHeight, HI_U32 *au32SoftMaxInChn, HI_U32 u32ConcatNum,
                                             HI_U32 *au32ConvStride, HI_U32 *au32SoftMaxWidth,
                                             HI_S32 **aps32SoftMaxInputData, HI_S32 *ps32SoftMaxOutputData)
{
    HI_S32* ps32InputData = NULL;
    HI_S32* ps32OutputTmp = NULL;
    HI_U32 u32OuterNum = 0;
    HI_U32 u32InnerNum = 0;
    HI_U32 u32InputChannel = 0;
    HI_U32 i = 0;
    HI_U32 u32ConcatCnt = 0;
    HI_S32 s32Ret = 0;
    HI_U32 u32Stride = 0;
    HI_U32 u32Skip = 0;
    HI_U32 u32Left = 0;
    ps32OutputTmp = ps32SoftMaxOutputData;
    for (u32ConcatCnt = 0; u32ConcatCnt < u32ConcatNum; u32ConcatCnt++)
    {
        ps32InputData = aps32SoftMaxInputData[u32ConcatCnt];
        u32Stride = au32ConvStride[u32ConcatCnt];
        u32InputChannel = au32SoftMaxInChn[u32ConcatCnt];
        u32OuterNum = u32InputChannel / u32SoftMaxInHeight;
        u32InnerNum = u32SoftMaxInHeight;
        u32Skip = au32SoftMaxWidth[u32ConcatCnt] / u32InnerNum;
        u32Left = u32Stride - au32SoftMaxWidth[u32ConcatCnt];
        for (i = 0; i < u32OuterNum; i++)
        {
            s32Ret = SVP_NNIE_SSD_SoftMax(ps32InputData, (HI_S32)u32InnerNum,ps32OutputTmp);
            if ((i + 1) % u32Skip == 0)
            {
                ps32InputData += u32Left;
            }
            ps32InputData += u32InnerNum;
            ps32OutputTmp += u32InnerNum;
        }
    }
    return s32Ret;
}

//HI_S32 SVP_NNIE_Ssd_SoftmaxForward(HI_U32 u32SoftMaxInHeight,
//                                   HI_U32 au32SoftMaxInChn[], HI_U32 u32ConcatNum, HI_U32 au32ConvStride[],
//                                   HI_U32 au32SoftMaxWidth[],HI_S32* aps32SoftMaxInputData[], HI_S32* ps32SoftMaxOutputData)
//{
//    HI_S32* ps32InputData = NULL;
//    HI_S32* ps32OutputTmp = NULL;
//    HI_U32 u32OuterNum = 0;
//    HI_U32 u32InnerNum = 0;
//    HI_U32 u32InputChannel = 0;
//    HI_U32 i = 0;
//    HI_U32 u32ConcatCnt = 0;
//    HI_S32 s32Ret = 0;
//    HI_U32 u32Stride = 0;
//    HI_U32 u32Skip = 0;
//    HI_U32 u32Left = 0;
//    ps32OutputTmp = ps32SoftMaxOutputData;
//    for (u32ConcatCnt = 0; u32ConcatCnt < u32ConcatNum; u32ConcatCnt++)
//    {
//        ps32InputData = aps32SoftMaxInputData[u32ConcatCnt];
//        u32Stride = au32ConvStride[u32ConcatCnt];
//        u32InputChannel = au32SoftMaxInChn[u32ConcatCnt];
//        u32OuterNum = u32InputChannel / u32SoftMaxInHeight;
//        u32InnerNum = u32SoftMaxInHeight;
//        u32Skip = au32SoftMaxWidth[u32ConcatCnt] / u32InnerNum;
//        u32Left = u32Stride - au32SoftMaxWidth[u32ConcatCnt];
//        for (i = 0; i < u32OuterNum; i++)
//        {
//            s32Ret = SVP_NNIE_SSD_SoftMax(ps32InputData, (HI_S32)u32InnerNum,ps32OutputTmp);
//            if ((i + 1) % u32Skip == 0)
//            {
//                ps32InputData += u32Left;
//            }
//            ps32InputData += u32InnerNum;
//            ps32OutputTmp += u32InnerNum;
//        }
//    }
//    return s32Ret;
//}

HI_S32 SSDModel::SVP_NNIE_Ssd_DetectionOutForward(HI_U32 u32ConcatNum,
                                        HI_U32 u32ConfThresh,HI_U32 u32ClassNum, HI_U32 u32TopK, HI_U32 u32KeepTopK, HI_U32 u32NmsThresh,
                                        HI_U32 au32DetectInputChn[], HI_S32* aps32AllLocPreds[], HI_S32* aps32AllPriorBoxes[],
                                        HI_S32* ps32ConfScores, HI_S32* ps32AssistMemPool, HI_S32* ps32DstScoreSrc,
                                        HI_S32* ps32DstBboxSrc, HI_S32* ps32RoiOutCntSrc)
{
    HI_S32* ps32LocPreds = NULL;
    HI_S32* ps32PriorBoxes = NULL;
    HI_S32* ps32PriorVar = NULL;
    HI_S32* ps32AllDecodeBoxes = NULL;
    HI_S32* ps32DstScore = NULL;
    HI_S32* ps32DstBbox = NULL;
    HI_S32* ps32ClassRoiNum = NULL;
    HI_U32 u32RoiOutCnt = 0;
    HI_S32* ps32SingleProposal = NULL;
    HI_S32* ps32AfterTopK = NULL;
    SAMPLE_SVP_NNIE_STACK_S* pstStack = NULL;
    HI_U32 u32PriorNum = 0;
    HI_U32 u32NumPredsPerClass = 0;
    HI_FLOAT f32PriorWidth = 0;
    HI_FLOAT f32PriorHeight = 0;
    HI_FLOAT f32PriorCenterX = 0;
    HI_FLOAT f32PriorCenterY = 0;
    HI_FLOAT f32DecodeBoxCenterX = 0;
    HI_FLOAT f32DecodeBoxCenterY = 0;
    HI_FLOAT f32DecodeBoxWidth = 0;
    HI_FLOAT f32DecodeBoxHeight = 0;
    HI_U32 u32SrcIdx = 0;
    HI_U32 u32AfterFilter = 0;
    HI_U32 u32AfterTopK = 0;
    HI_U32 u32KeepCnt = 0;
    HI_U32 i = 0;
    HI_U32 j = 0;
    HI_U32 u32Offset = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    u32PriorNum = 0;
    for (i = 0; i < u32ConcatNum; i++)
    {
        u32PriorNum += au32DetectInputChn[i] / SAMPLE_SVP_NNIE_COORDI_NUM;
    }
    //prepare for Assist MemPool
    ps32AllDecodeBoxes = ps32AssistMemPool;
    ps32SingleProposal = ps32AllDecodeBoxes + u32PriorNum * SAMPLE_SVP_NNIE_COORDI_NUM;
    ps32AfterTopK = ps32SingleProposal + SAMPLE_SVP_NNIE_PROPOSAL_WIDTH * u32PriorNum;
    pstStack = (SAMPLE_SVP_NNIE_STACK_S*)(ps32AfterTopK + u32PriorNum * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH);
    u32SrcIdx = 0;
    for (i = 0; i < u32ConcatNum; i++)
    {
        /********** get loc predictions ************/
        ps32LocPreds = aps32AllLocPreds[i];
        u32NumPredsPerClass = au32DetectInputChn[i] / SAMPLE_SVP_NNIE_COORDI_NUM;
        /********** get Prior Bboxes ************/
        ps32PriorBoxes = aps32AllPriorBoxes[i];
        ps32PriorVar = ps32PriorBoxes + u32NumPredsPerClass*SAMPLE_SVP_NNIE_COORDI_NUM;
        for (j = 0; j < u32NumPredsPerClass; j++)
        {
            f32PriorWidth = (HI_FLOAT)(ps32PriorBoxes[j*SAMPLE_SVP_NNIE_COORDI_NUM+2] - ps32PriorBoxes[j*SAMPLE_SVP_NNIE_COORDI_NUM]);
            f32PriorHeight = (HI_FLOAT)(ps32PriorBoxes[j*SAMPLE_SVP_NNIE_COORDI_NUM+3] - ps32PriorBoxes[j*SAMPLE_SVP_NNIE_COORDI_NUM + 1]);
            f32PriorCenterX = (ps32PriorBoxes[j*SAMPLE_SVP_NNIE_COORDI_NUM+2] + ps32PriorBoxes[j*SAMPLE_SVP_NNIE_COORDI_NUM])*SAMPLE_SVP_NNIE_HALF;
            f32PriorCenterY = (ps32PriorBoxes[j*SAMPLE_SVP_NNIE_COORDI_NUM+3] + ps32PriorBoxes[j*SAMPLE_SVP_NNIE_COORDI_NUM+1])*SAMPLE_SVP_NNIE_HALF;

            f32DecodeBoxCenterX = ((HI_FLOAT)ps32PriorVar[j*SAMPLE_SVP_NNIE_COORDI_NUM]/SAMPLE_SVP_NNIE_QUANT_BASE)*
                                  ((HI_FLOAT)ps32LocPreds[j*SAMPLE_SVP_NNIE_COORDI_NUM]/SAMPLE_SVP_NNIE_QUANT_BASE)*f32PriorWidth+f32PriorCenterX;

            f32DecodeBoxCenterY = ((HI_FLOAT)ps32PriorVar[j*SAMPLE_SVP_NNIE_COORDI_NUM+1]/SAMPLE_SVP_NNIE_QUANT_BASE)*
                                  ((HI_FLOAT)ps32LocPreds[j*SAMPLE_SVP_NNIE_COORDI_NUM+1]/SAMPLE_SVP_NNIE_QUANT_BASE)*f32PriorHeight+f32PriorCenterY;

            f32DecodeBoxWidth = exp(((HI_FLOAT)ps32PriorVar[j*SAMPLE_SVP_NNIE_COORDI_NUM+2]/SAMPLE_SVP_NNIE_QUANT_BASE)*
                                    ((HI_FLOAT)ps32LocPreds[j*SAMPLE_SVP_NNIE_COORDI_NUM+2]/SAMPLE_SVP_NNIE_QUANT_BASE))*f32PriorWidth;

            f32DecodeBoxHeight = exp(((HI_FLOAT)ps32PriorVar[j*SAMPLE_SVP_NNIE_COORDI_NUM+3]/SAMPLE_SVP_NNIE_QUANT_BASE)*
                                     ((HI_FLOAT)ps32LocPreds[j*SAMPLE_SVP_NNIE_COORDI_NUM+3]/SAMPLE_SVP_NNIE_QUANT_BASE))*f32PriorHeight;

            ps32AllDecodeBoxes[u32SrcIdx++] = (HI_S32)(f32DecodeBoxCenterX - f32DecodeBoxWidth * SAMPLE_SVP_NNIE_HALF);
            ps32AllDecodeBoxes[u32SrcIdx++] = (HI_S32)(f32DecodeBoxCenterY - f32DecodeBoxHeight * SAMPLE_SVP_NNIE_HALF);
            ps32AllDecodeBoxes[u32SrcIdx++] = (HI_S32)(f32DecodeBoxCenterX + f32DecodeBoxWidth * SAMPLE_SVP_NNIE_HALF);
            ps32AllDecodeBoxes[u32SrcIdx++] = (HI_S32)(f32DecodeBoxCenterY + f32DecodeBoxHeight * SAMPLE_SVP_NNIE_HALF);
        }
    }
    /********** do NMS for each class *************/
    u32AfterTopK = 0;
    for (i = 0; i < u32ClassNum; i++)
    {
        for (j = 0; j < u32PriorNum; j++)
        {
            ps32SingleProposal[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH] = ps32AllDecodeBoxes[j * SAMPLE_SVP_NNIE_COORDI_NUM];
            ps32SingleProposal[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 1] = ps32AllDecodeBoxes[j * SAMPLE_SVP_NNIE_COORDI_NUM + 1];
            ps32SingleProposal[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 2] = ps32AllDecodeBoxes[j * SAMPLE_SVP_NNIE_COORDI_NUM + 2];
            ps32SingleProposal[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 3] = ps32AllDecodeBoxes[j * SAMPLE_SVP_NNIE_COORDI_NUM + 3];
            ps32SingleProposal[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 4] = ps32ConfScores[j*u32ClassNum + i];
            ps32SingleProposal[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 5] = 0;
        }
        s32Ret = SVP_NNIE_NonRecursiveArgQuickSort(ps32SingleProposal, 0, u32PriorNum - 1, pstStack,u32TopK);
        u32AfterFilter = (u32PriorNum < u32TopK) ? u32PriorNum : u32TopK;
        s32Ret = SVP_NNIE_NonMaxSuppression(ps32SingleProposal, u32AfterFilter, u32NmsThresh, u32AfterFilter);
        u32RoiOutCnt = 0;
        ps32DstScore = (HI_S32*)ps32DstScoreSrc;
        ps32DstBbox = (HI_S32*)ps32DstBboxSrc;
        ps32ClassRoiNum = (HI_S32*)ps32RoiOutCntSrc;
        ps32DstScore += (HI_S32)u32AfterTopK;
        ps32DstBbox += (HI_S32)(u32AfterTopK * SAMPLE_SVP_NNIE_COORDI_NUM);
        for (j = 0; j < u32TopK; j++)
        {
            if (ps32SingleProposal[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 5] == 0 &&
                ps32SingleProposal[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 4] > (HI_S32)u32NmsThresh)
            {
                ps32DstScore[u32RoiOutCnt] = ps32SingleProposal[j * 6 + 4];
                ps32DstBbox[u32RoiOutCnt * SAMPLE_SVP_NNIE_COORDI_NUM] = ps32SingleProposal[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH];
                ps32DstBbox[u32RoiOutCnt * SAMPLE_SVP_NNIE_COORDI_NUM + 1] = ps32SingleProposal[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 1];
                ps32DstBbox[u32RoiOutCnt * SAMPLE_SVP_NNIE_COORDI_NUM + 2] = ps32SingleProposal[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 2];
                ps32DstBbox[u32RoiOutCnt * SAMPLE_SVP_NNIE_COORDI_NUM + 3] = ps32SingleProposal[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 3];
                u32RoiOutCnt++;
            }
        }
        ps32ClassRoiNum[i] = (HI_S32)u32RoiOutCnt;
        u32AfterTopK += u32RoiOutCnt;
    }

    u32KeepCnt = 0;
    u32Offset = 0;
    if (u32AfterTopK > u32KeepTopK)
    {
        u32Offset = ps32ClassRoiNum[0];
        for (i = 1; i < u32ClassNum; i++)
        {
            ps32DstScore = (HI_S32*)ps32DstScoreSrc;
            ps32DstBbox = (HI_S32*)ps32DstBboxSrc;
            ps32ClassRoiNum = (HI_S32*)ps32RoiOutCntSrc;
            ps32DstScore += (HI_S32)(u32Offset);
            ps32DstBbox += (HI_S32)(u32Offset * SAMPLE_SVP_NNIE_COORDI_NUM);
            for (j = 0; j < (HI_U32)ps32ClassRoiNum[i]; j++)
            {
                ps32AfterTopK[u32KeepCnt * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH] = ps32DstBbox[j * SAMPLE_SVP_NNIE_COORDI_NUM];
                ps32AfterTopK[u32KeepCnt * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 1] = ps32DstBbox[j * SAMPLE_SVP_NNIE_COORDI_NUM + 1];
                ps32AfterTopK[u32KeepCnt * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 2] = ps32DstBbox[j * SAMPLE_SVP_NNIE_COORDI_NUM + 2];
                ps32AfterTopK[u32KeepCnt * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 3] = ps32DstBbox[j * SAMPLE_SVP_NNIE_COORDI_NUM + 3];
                ps32AfterTopK[u32KeepCnt * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 4] = ps32DstScore[j];
                ps32AfterTopK[u32KeepCnt * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 5] = i;
                u32KeepCnt++;
            }
            u32Offset = u32Offset + ps32ClassRoiNum[i];
        }
        s32Ret = SVP_NNIE_NonRecursiveArgQuickSort(ps32AfterTopK, 0, u32KeepCnt - 1, pstStack,u32KeepCnt);

        u32Offset = 0;
        u32Offset = ps32ClassRoiNum[0];
        for (i = 1; i < u32ClassNum; i++)
        {
            u32RoiOutCnt = 0;
            ps32DstScore = (HI_S32*)ps32DstScoreSrc;
            ps32DstBbox = (HI_S32*)ps32DstBboxSrc;
            ps32ClassRoiNum = (HI_S32*)ps32RoiOutCntSrc;
            ps32DstScore += (HI_S32)(u32Offset);
            ps32DstBbox += (HI_S32)(u32Offset * SAMPLE_SVP_NNIE_COORDI_NUM);
            for (j = 0; j < u32KeepTopK; j++)
            {
                if (ps32AfterTopK[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 5] == i)
                {
                    ps32DstScore[u32RoiOutCnt] = ps32AfterTopK[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 4];
                    ps32DstBbox[u32RoiOutCnt * SAMPLE_SVP_NNIE_COORDI_NUM] = ps32AfterTopK[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH];
                    ps32DstBbox[u32RoiOutCnt * SAMPLE_SVP_NNIE_COORDI_NUM + 1] = ps32AfterTopK[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 1];
                    ps32DstBbox[u32RoiOutCnt * SAMPLE_SVP_NNIE_COORDI_NUM + 2] = ps32AfterTopK[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 2];
                    ps32DstBbox[u32RoiOutCnt * SAMPLE_SVP_NNIE_COORDI_NUM + 3] = ps32AfterTopK[j * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH + 3];
                    u32RoiOutCnt++;
                }
            }
            ps32ClassRoiNum[i] = (HI_S32)u32RoiOutCnt;
            u32Offset += u32RoiOutCnt;
        }
    }
    return s32Ret;
}

SSDModel::SSDModel(AlgorithmService *algorithm_service,
                   UtilsService *utils_service,
                   EventService *event_service,
                   SVP_NNIE_MODEL_WITH_FILE_S *model,
                   HI_U32 duration_num,
                   HI_U32 class_num,
                   HI_U32 input_height,
                   HI_U32 input_width,
                   HI_FLOAT thresh) {
    m_algorithm_service = algorithm_service;
    m_utils_service = utils_service;
    m_event_service = event_service;
    ssd_model = model;
    m_class_num = class_num;
    m_input_size.ImageWidth=input_width;
    m_input_size.ImageHeight=input_height;

    infer_params.thresh = thresh;/*阈值*/
    infer_params.astMetaInfo = astMetaInfo;/*用于保存算法的检测结果*/
    infer_params.cLabelSendBuf = cLabelSendBuf;
    infer_params.auTempBuf = auTempBuf;
    infer_params.InputSize = &m_input_size;
    infer_params.pstResult = &result;

    m_duration_num = duration_num;
    result.numOfObject=10;
    result.thresh = thresh;
    /*申请内存用于保存检测结果*/
    result.pObjInfo = (SDC_SSD_OBJECT_INFO_S *) malloc(result.numOfObject * sizeof(SDC_SSD_OBJECT_INFO_S));

}

void SSDModel::data_connect(VW_YUV_FRAME_S *rgb_data_ptr){
    infer_params.rgb_img = rgb_data_ptr;/*获取YUV_RGB通道图像的内存地址,模型推导时会从这个地址取图像数据*/

};

HI_S32 SSDModel::SVP_NNIE_FillForwardInfo() {
    HI_U32 i = 0, j = 0;
    HI_U32 u32Offset = 0;
    HI_U32 u32Num = 0;
    //网络的模块数量
    for (i = 0; i < m_nnie_param->pstModel->u32NetSegNum; i++) {
        /*fill forwardCtrl info*/
        printf("Seg idx: %i-------------------------------------------------------------------------------------\n", i);

        // 1.导入Seg相关的参数-------------------------------------------------------------------------

        if (SVP_NNIE_NET_TYPE_ROI == m_nnie_param->pstModel->astSeg[i].enNetType)//网络模块的类型为ROI
        {
            m_nnie_param->astForwardWithBboxCtrl[i].enNnieId = m_nnie_cfg->aenNnieCoreId[i];//模块运行的NNIE内核编号
            m_nnie_param->astForwardWithBboxCtrl[i].u32SrcNum = m_nnie_param->pstModel->astSeg[i].u16SrcNum;//模块的输入数量
            m_nnie_param->astForwardWithBboxCtrl[i].u32DstNum = m_nnie_param->pstModel->astSeg[i].u16DstNum;//模块的输出数量
            m_nnie_param->astForwardWithBboxCtrl[i].u32ProposalNum = 1;
            m_nnie_param->astForwardWithBboxCtrl[i].u32NetSegId = i;//模块的id
            printf("Seg type:ROI:-------------------------------------------------------------------------------\n "
                   "pstNnieCfg->aenNnieCoreId[i]: %i\n "
                   "pstNnieParam->pstModel->astSeg[i].u16SrcNum:%u\n "
                   "pstNnieParam->pstModel->astSeg[i].u16DstNum: %u\n "
                   "u32NetSegId: %u\n",
                   m_nnie_cfg->aenNnieCoreId[i],
                   m_nnie_param->pstModel->astSeg[i].u16SrcNum,
                   m_nnie_param->pstModel->astSeg[i].u16DstNum,
                   i);
        } else if (SVP_NNIE_NET_TYPE_CNN == m_nnie_param->pstModel->astSeg[i].enNetType ||
                   SVP_NNIE_NET_TYPE_RECURRENT == m_nnie_param->pstModel->astSeg[i].enNetType) {


            m_nnie_param->astForwardCtrl[i].enNnieId = m_nnie_cfg->aenNnieCoreId[i];//使用的NNIE内核ID
            m_nnie_param->astForwardCtrl[i].u32SrcNum = m_nnie_param->pstModel->astSeg[i].u16SrcNum;//输入的blob数量，一般为1
            m_nnie_param->astForwardCtrl[i].u32DstNum = m_nnie_param->pstModel->astSeg[i].u16DstNum;//输出的blob数量，ssd为12
            m_nnie_param->astForwardCtrl[i].u32NetSegId = i;

            printf("Seg type idx: %i----------------------------------------------------------------------------\n"
                   "pstNnieCfg->aenNnieCoreId[i]: %i\n"
                   "pstNnieParam->pstModel->astSeg[i].u16SrcNum:%u\n"
                   "pstNnieParam->pstModel->astSeg[i].u16DstNum: %u\n"
                   "u32NetSegId: %u\n",
                   m_nnie_param->pstModel->astSeg[i].enNetType,
                   m_nnie_cfg->aenNnieCoreId[i],
                   m_nnie_param->pstModel->astSeg[i].u16SrcNum,
                   m_nnie_param->pstModel->astSeg[i].u16DstNum,
                   i);
#if 0
            pstNnieParam->astForwardCtrl[i].stTmpBuf = pstNnieParam->stTmpBuf;
            pstNnieParam->astForwardCtrl[i].stTskBuf.u64PhyAddr= pstNnieParam->stTaskBuf.u64PhyAddr+u32Offset;
            pstNnieParam->astForwardCtrl[i].stTskBuf.u64VirAddr= pstNnieParam->stTaskBuf.u64VirAddr+u32Offset;
            pstNnieParam->astForwardCtrl[i].stTskBuf.u32Size= pstNnieParam->au32TaskBufSize[i];
#endif
        }
        u32Offset += m_nnie_param->au32TaskBufSize[i];/*这里赋值要审视下，好像参数没用*/

        // 2.导入Seg下所有(src)输入blob的相关参数-------------------------------------------------------------------------
        //填充模块内每个blob的信息
        printf("填充src(输入) blob信息---------------------------------------------------------------------------\n");
        for (j = 0; j < m_nnie_param->pstModel->astSeg[i].u16SrcNum; j++) {
            /*Recurrent blob*/
            printf("Src Blob idx: %i----------------------------------------------------------------------------\n", j);
            if (SVP_BLOB_TYPE_SEQ_S32 == m_nnie_param->pstModel->astSeg[i].astSrcNode[j].enType) {
                m_nnie_param->astSegData[i].astSrc[j].enType = m_nnie_param->pstModel->astSeg[i].astSrcNode[j].enType;
                m_nnie_param->astSegData[i].astSrc[j].unShape.stSeq.u32Dim = m_nnie_param->pstModel->astSeg[i].astSrcNode[j].unShape.u32Dim;
                m_nnie_param->astSegData[i].astSrc[j].u32Num = m_nnie_cfg->u32MaxInputNum;
                m_nnie_param->astSegData[i].astSrc[j].unShape.stSeq.u64VirAddrStep = m_nnie_cfg->au64StepVirAddr[i *
                                                                                                                 SAMPLE_SVP_NNIE_EACH_SEG_STEP_ADDR_NUM];

                printf("Blob type: SVP_BLOB_TYPE_SEQ_S32:----------\n"
                       "pstNnieParam->pstModel->astSeg[i].astSrcNode[j].enType: SVP_BLOB_TYPE_SEQ_S32 \n"
                       "pstNnieParam->pstModel->astSeg[i].astSrcNode[j].unShape.u32Dim: %u\n"
                       "pstNnieCfg->u32MaxInputNum: %u\n"
                       "pstNnieCfg->au64StepVirAddr[i*SAMPLE_SVP_NNIE_EACH_SEG_STEP_ADDR_NUM]: %llu \n",
                       m_nnie_param->pstModel->astSeg[i].astSrcNode[j].unShape.u32Dim,
                       m_nnie_cfg->u32MaxInputNum,
                       m_nnie_cfg->au64StepVirAddr[i * SAMPLE_SVP_NNIE_EACH_SEG_STEP_ADDR_NUM]);
            } else {
                m_nnie_param->astSegData[i].astSrc[j].enType = m_nnie_param->pstModel->astSeg[i].astSrcNode[j].enType;
                m_nnie_param->astSegData[i].astSrc[j].unShape.stWhc.u32Chn = m_nnie_param->pstModel->astSeg[i].astSrcNode[j].unShape.stWhc.u32Chn;
                m_nnie_param->astSegData[i].astSrc[j].unShape.stWhc.u32Height = m_nnie_param->pstModel->astSeg[i].astSrcNode[j].unShape.stWhc.u32Height;
                m_nnie_param->astSegData[i].astSrc[j].unShape.stWhc.u32Width = m_nnie_param->pstModel->astSeg[i].astSrcNode[j].unShape.stWhc.u32Width;
                m_nnie_param->astSegData[i].astSrc[j].u32Num = m_nnie_cfg->u32MaxInputNum;

                printf("Blob type idx: %i-----------------------------------------------------------------------\n"
                       "src blob enType: OTHER(except SEQ_S32)\n"
                       "src blob channel: %u\n"//channel
                       "src blob height: %u\n"//height
                       "src blob width: %u\n"//width
                       "src blob input batch size: %u\n",//batch size
                       m_nnie_param->pstModel->astSeg[i].astSrcNode[j].enType,
                       m_nnie_param->astSegData[i].astSrc[j].unShape.stWhc.u32Chn,
                       m_nnie_param->astSegData[i].astSrc[j].unShape.stWhc.u32Height,
                       m_nnie_param->astSegData[i].astSrc[j].unShape.stWhc.u32Width,
                       m_nnie_param->astSegData[i].astSrc[j].u32Num);
            }
        }

        // 3.导入Seg下所有(dst)输出blob的相关参数-------------------------------------------------------------------------
        printf("填充dst blob信息---------------------------------------------------------------------------------\n");
        //当前seg的网络类型
        if (SVP_NNIE_NET_TYPE_ROI == m_nnie_param->pstModel->astSeg[i].enNetType) {
            u32Num = m_nnie_cfg->u32MaxRoiNum * m_nnie_cfg->u32MaxInputNum;
        } else u32Num = m_nnie_cfg->u32MaxInputNum;
        //循环导入dst blob参数
        for (j = 0; j < m_nnie_param->pstModel->astSeg[i].u16DstNum; j++) {
            printf("Dst Blob idx: %i----------------------------------------------------------------------------\n", j);
            if (SVP_BLOB_TYPE_SEQ_S32 == m_nnie_param->pstModel->astSeg[i].astDstNode[j].enType) {
                m_nnie_param->astSegData[i].astDst[j].enType = m_nnie_param->pstModel->astSeg[i].astDstNode[j].enType;
                m_nnie_param->astSegData[i].astDst[j].unShape.stSeq.u32Dim = m_nnie_param->pstModel->astSeg[i].astDstNode[j].unShape.u32Dim;
                m_nnie_param->astSegData[i].astDst[j].u32Num = u32Num;
                m_nnie_param->astSegData[i].astDst[j].unShape.stSeq.u64VirAddrStep =
                        m_nnie_cfg->au64StepVirAddr[i * SAMPLE_SVP_NNIE_EACH_SEG_STEP_ADDR_NUM + 1];
                printf("Blob type: SVP_BLOB_TYPE_SEQ_S32:----------\n"
                       "dst blob enType: SVP_BLOB_TYPE_SEQ_S32 \n"
                       "dst blob Dim: %u\n"
                       "dst blob input size: %u\n "
                       "pstNnieCfg->au64StepVirAddr[i*SAMPLE_SVP_NNIE_EACH_SEG_STEP_ADDR_NUM]: %llu \n",
                       m_nnie_param->astSegData[i].astDst[j].unShape.stSeq.u32Dim,
                       m_nnie_param->astSegData[i].astDst[j].u32Num,
                       m_nnie_param->astSegData[i].astDst[j].unShape.stSeq.u64VirAddrStep);
            } else {
                m_nnie_param->astSegData[i].astDst[j].enType = m_nnie_param->pstModel->astSeg[i].astDstNode[j].enType;//blob类型
                m_nnie_param->astSegData[i].astDst[j].unShape.stWhc.u32Chn = m_nnie_param->pstModel->astSeg[i].astDstNode[j].unShape.stWhc.u32Chn;//channel
                m_nnie_param->astSegData[i].astDst[j].unShape.stWhc.u32Height = m_nnie_param->pstModel->astSeg[i].astDstNode[j].unShape.stWhc.u32Height;//height
                m_nnie_param->astSegData[i].astDst[j].unShape.stWhc.u32Width = m_nnie_param->pstModel->astSeg[i].astDstNode[j].unShape.stWhc.u32Width;//width
                m_nnie_param->astSegData[i].astDst[j].u32Num = u32Num;//输出时batch size大小

                printf("Blob type idx: %i-----------------------------------------------------------------------\n "
                       "dst blob enType: OTHER(except SEQ_S32) \n"
                       "dst blob channel: %u\n"
                       "dst blob height: %u\n"
                       "dst blob width: %u \n"
                       "dst blob input size: %u \n",
                       m_nnie_param->astSegData[i].astDst[j].enType,
                       m_nnie_param->pstModel->astSeg[i].astDstNode[j].unShape.stWhc.u32Chn,
                       m_nnie_param->pstModel->astSeg[i].astDstNode[j].unShape.stWhc.u32Height,
                       m_nnie_param->astSegData[i].astDst[j].unShape.stWhc.u32Width,
                       m_nnie_param->astSegData[i].astDst[j].u32Num);
            }
        }
    }
    return HI_SUCCESS;
}

void SSDModel::SVP_NNIE_GetBlobMemSize(SVP_NNIE_NODE_S *astNnieNode, HI_U32 u32NodeNum,
                                       HI_U32 u32TotalStep, SVP_BLOB_S *astBlob, HI_U32 u32Align, HI_U32 *pu32TotalSize,
                                       HI_U32 *au32BlobSize) {
    HI_U32 i = 0;
    HI_U32 u32Size = 0;
    HI_U32 u32Stride = 0;

    for (i = 0; i < u32NodeNum; i++) {
        if (SVP_BLOB_TYPE_S32 == astNnieNode[i].enType || SVP_BLOB_TYPE_VEC_S32 == astNnieNode[i].enType ||
            SVP_BLOB_TYPE_SEQ_S32 == astNnieNode[i].enType) {
            u32Size = sizeof(HI_U32);
        } else {
            u32Size = sizeof(HI_U8);
        }
        if (SVP_BLOB_TYPE_SEQ_S32 == astNnieNode[i].enType) {
            if (SAMPLE_SVP_NNIE_ALIGN_16 == u32Align) {
                u32Stride = SAMPLE_SVP_NNIE_ALIGN16(astNnieNode[i].unShape.u32Dim * u32Size);
            } else {
                u32Stride = SAMPLE_SVP_NNIE_ALIGN32(astNnieNode[i].unShape.u32Dim * u32Size);
            }
            au32BlobSize[i] = u32TotalStep * u32Stride;
        } else {
            if (SAMPLE_SVP_NNIE_ALIGN_16 == u32Align) {
                u32Stride = SAMPLE_SVP_NNIE_ALIGN16(astNnieNode[i].unShape.stWhc.u32Width * u32Size);
            } else {
                u32Stride = SAMPLE_SVP_NNIE_ALIGN32(astNnieNode[i].unShape.stWhc.u32Width * u32Size);
            }
            au32BlobSize[i] = astBlob[i].u32Num * u32Stride * astNnieNode[i].unShape.stWhc.u32Height *
                              astNnieNode[i].unShape.stWhc.u32Chn;
        }
        *pu32TotalSize += au32BlobSize[i];
        astBlob[i].u32Stride = u32Stride;
    }
}

HI_S32 SSDModel::SVP_NNIE_GetTaskAndBlobBufSize(SVP_NNIE_BLOB_SIZE_S astBlobSize[],
                                                HI_U32 *pu32TotalSize) {
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 i = 0, j = 0;
    HI_U32 u32TotalStep = 0;

    /*计算blob的内存大小*/
    for (i = 0; i < m_nnie_param->pstModel->u32NetSegNum; i++) {
        /*我们的网络输入blob不采用SVP_NNIE_NET_TYPE_RECURRENT类型*/
        if (SVP_NNIE_NET_TYPE_RECURRENT == m_nnie_param->pstModel->astSeg[i].enNetType) {
            /*u32Num表示batch size*/
            DEBUG_LOG("---SVP_NNIE_NET_TYPE_RECURRENT---");
            for (j = 0; j < m_nnie_param->astSegData[i].astSrc[0].u32Num; j++) {
                u32TotalStep += *((HI_S32 *) m_nnie_param->astSegData[i].astSrc[0].unShape.stSeq.u64VirAddrStep + j);
            }
        }
        /*just the first seg's Src Blob mem size.
        * other seg's src blobs from the output blobs of those segs before it or from software output results*/
        /*计算输入blob的内存,注意只有第一个Seg的输入blob需要申请,因为其余Seg的输入节点都是以其他输出节点数据作为输入的,不需要再申请内存*/
        if (i == 0) {
            SVP_NNIE_GetBlobMemSize(
                    &(m_nnie_param->pstModel->astSeg[i].astSrcNode[0]),/*来自SVP_NNIE_MODEL_S结构体的第i个Seg下的第一个输入节点blob[0]的指针*/
                    m_nnie_param->pstModel->astSeg[i].u16SrcNum, /*有多少个输入blob节点,会一次性把所有节点的内存大小都计算出来*/
                    u32TotalStep,/*在非SVP_NNIE_NET_TYPE_RECURRENT类型下,该值为0*/
                    &(m_nnie_param->astSegData[i].astSrc[0]),/*来自SVP_NNIE_PARAM_S结构体的第i个Seg下的第一个输入节点blob[0]的指针*/
                    SAMPLE_SVP_NNIE_ALIGN_16,
                    pu32TotalSize,/*用于保存需要的内存大小值*/
                    &(astBlobSize[i].au32SrcSize[0]));
        }

        /*Get each seg's Dst Blob mem size*/
        /*计算输出节点的内存,参数同上*/
        SVP_NNIE_GetBlobMemSize(&(m_nnie_param->pstModel->astSeg[i].astDstNode[0]),
                                m_nnie_param->pstModel->astSeg[i].u16DstNum,
                                u32TotalStep,
                                &(m_nnie_param->astSegData[i].astDst[0]),
                                SAMPLE_SVP_NNIE_ALIGN_16,
                                pu32TotalSize,
                                &(astBlobSize[i].au32DstSize[0]));
    }
    return s32Ret;
}

//SVP NNIE初始化，申请内存并将物理地址的模型映射到NNIE内存中
HI_S32 SSDModel::SVP_NNIE_ParamInit(
) {
    HI_U32 i = 0, j = 0;
    HI_U32 u32TotalSize = 0;//模型所需的内存大小占位符
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U64 u64PhyAddr = 0;
    HI_U8 *pu8VirAddr = NULL;
    SVP_NNIE_BLOB_SIZE_S astBlobSize[SVP_NNIE_MAX_NET_SEG_NUM] = {0};/*储存各个blob的信息*/
    SDC_MMZ_ALLOC_S stMemParas;

    //1. 填充信息，将模型结构与m_nnie_cfg的配置整合，提取输入/输出blob信息后重新放进m_nnie_param------------------------------
    s32Ret = SVP_NNIE_FillForwardInfo();
    if (s32Ret != HI_SUCCESS) {
        DEBUG_LOG("ERR: SVP_NNIE_FillForwardInfo failed.");
        return ERR;
    }
    //2. 获取任务信息和Blob所需的内存大小---------------------------------------------------------------------------------
    s32Ret = SVP_NNIE_GetTaskAndBlobBufSize(astBlobSize, &u32TotalSize);
    if (s32Ret != HI_SUCCESS) {
        DEBUG_LOG("ERR: SVP_NNIE_GetTaskAndBlobBufSize failed.");
        return ERR;
    }
    /*Malloc mem*/
    //3. 申请SDC内存地址到stMemParas中-----------------------------------------------------------------------------------
    s32Ret = m_utils_service->SDC_MemAlloc(u32TotalSize, &stMemParas);
    if (s32Ret < 0) {
        DEBUG_LOG("ERR: SDC_MemAlloc failed.");
        return ERR;
    }
    u64PhyAddr = stMemParas.addr_phy;
    pu8VirAddr = (HI_U8 *) stMemParas.addr_virt;
    u32TotalSize = stMemParas.size;
    memset(pu8VirAddr, 0, u32TotalSize);//初始化内存位置的值
    //4. 内存映射加载模型------------------------------------------------------------------------------------------------
    m_utils_service->SDC_FlushCache(u64PhyAddr, (void *) pu8VirAddr, u32TotalSize);//刷新缓存，将物理地址中的数据映射到SDC内存中

    /*fill each blob's mem addr*/
    //5. 设置各个blob的指针地址------------------------------------------------------------------------------------------
    //3~4两步申请到了一块内存并且用于保存整个模型，这里需要根据每个blob的大小进行指针偏移，计算得到blob的具体的指针地址
    u64PhyAddr = u64PhyAddr;//+u32TotalTaskBufSize+u32TmpBufSize;
    pu8VirAddr = pu8VirAddr;//+u32TotalTaskBufSize+u32TmpBufSize;
    for (i = 0; i < m_nnie_param->pstModel->u32NetSegNum; i++) {
        //第一个seg模块才有输入blob，其余的seg模块的输入blob都来自于其他blob的输出
        if (0 == i) {
            for (j = 0; j < m_nnie_param->pstModel->astSeg[i].u16SrcNum; j++) {
                if (j != 0)//从第二个blob开始根据上一个blob的大小进行内存地址偏移
                {
                    u64PhyAddr += astBlobSize[i].au32SrcSize[j - 1];
                    pu8VirAddr += astBlobSize[i].au32SrcSize[j - 1];
                }
                //导入各个blob的内存地址
                m_nnie_param->astSegData[i].astSrc[j].u64PhyAddr = u64PhyAddr;
                m_nnie_param->astSegData[i].astSrc[j].u64VirAddr = (HI_U64) pu8VirAddr;
            }
            //进行最后一个blob的内存地址偏移
            u64PhyAddr += astBlobSize[i].au32SrcSize[j - 1];
            pu8VirAddr += astBlobSize[i].au32SrcSize[j - 1];
        }

        /*fill the mem addrs of each seg's output blobs*/
        // 输出blob的地址信息
        for (j = 0; j < m_nnie_param->pstModel->astSeg[i].u16DstNum; j++) {
            if (j != 0) {
                u64PhyAddr += astBlobSize[i].au32DstSize[j - 1];
                pu8VirAddr += astBlobSize[i].au32DstSize[j - 1];
            }
            m_nnie_param->astSegData[i].astDst[j].u64PhyAddr = u64PhyAddr;
            m_nnie_param->astSegData[i].astDst[j].u64VirAddr = (HI_U64) pu8VirAddr;
        }
        u64PhyAddr += astBlobSize[i].au32DstSize[j - 1];
        pu8VirAddr += astBlobSize[i].au32DstSize[j - 1];
    }
    return HI_SUCCESS;
}

HI_S32 SSDModel::SDC_NNIE_ParamDeinit() {
    SDC_MMZ_ALLOC_S stMemParas;

    if (0 != m_nnie_param->stStepBuf.u64PhyAddr && 0 != m_nnie_param->stStepBuf.u64VirAddr) {
        stMemParas.addr_phy = m_nnie_param->stStepBuf.u64PhyAddr;
        stMemParas.addr_virt = m_nnie_param->stStepBuf.u64VirAddr;

        m_utils_service->SDC_MemFree(&stMemParas);

        m_nnie_param->stStepBuf.u64PhyAddr = 0;
        m_nnie_param->stStepBuf.u64VirAddr = 0;
    }
    return HI_SUCCESS;
}

HI_S32 SSDModel::SDC_NNIE_ParamInit() {
    HI_S32 s32Ret = HI_SUCCESS;
    /*NNIE parameter initialization NNEI初始化
     * 1 整合pstNnieCfg与pstNnieParam的信息，构建模型的输入/输出信息后重新放入pstNnieParam
     * 2 申请内存，将物理内存中的模型结构映射进SDC虚拟内存*/
    s32Ret = SVP_NNIE_ParamInit();
    SAMPLE_SVP_CHECK_EXPR_GOTO(HI_SUCCESS != s32Ret, FAIL, SAMPLE_SVP_ERR_LEVEL_ERROR,
                               "Error, SAMPLE_SVP_NNIE_ParamInit failed!\n");

    return s32Ret;
    // 失败则析构初始化
    FAIL:
    s32Ret = SDC_NNIE_ParamDeinit();
    SAMPLE_SVP_CHECK_EXPR_RET(HI_SUCCESS != s32Ret, s32Ret, SAMPLE_SVP_ERR_LEVEL_ERROR,
                              "Error, SDC_NNIE_ParamDeinit failed!\n");
    return HI_FAILURE;
}

HI_U32 SSDModel::SVP_NNIE_Ssd_GetResultTmpBuf() {
    HI_U32 u32PriorBoxSize = 0;
    HI_U32 u32SoftMaxSize = 0;
    HI_U32 u32DetectionSize = 0;
    HI_U32 u32TotalSize = 0;
    HI_U32 u32PriorNum = 0;
    HI_U32 i = 0;

    /*priorbox size*/
    for (i = 0; i < m_nnie_param->pstModel->astSeg[0].u16DstNum / 2; i++) {
        u32PriorBoxSize +=
                m_model_software_param->au32PriorBoxHeight[i] * m_model_software_param->au32PriorBoxWidth[i] *
                SAMPLE_SVP_NNIE_COORDI_NUM * 2 *
                (m_model_software_param->u32MaxSizeNum + m_model_software_param->u32MinSizeNum +
                 m_model_software_param->au32InputAspectRatioNum[i] * 2 * m_model_software_param->u32MinSizeNum) *
                sizeof(HI_U32);
    }
    m_model_software_param->stPriorBoxTmpBuf.u32Size = u32PriorBoxSize;
    u32TotalSize += u32PriorBoxSize;

    /*softmax size*/
    for (i = 0; i < m_model_software_param->u32ConcatNum; i++) {
        u32SoftMaxSize += m_model_software_param->au32SoftMaxInChn[i] * sizeof(HI_U32);
    }
    m_model_software_param->stSoftMaxTmpBuf.u32Size = u32SoftMaxSize;
    u32TotalSize += u32SoftMaxSize;

    /*detection size*/
    for (i = 0; i < m_model_software_param->u32ConcatNum; i++) {
        u32PriorNum += m_model_software_param->au32DetectInputChn[i] / SAMPLE_SVP_NNIE_COORDI_NUM;
    }
    u32DetectionSize += u32PriorNum * SAMPLE_SVP_NNIE_COORDI_NUM * sizeof(HI_U32);
    u32DetectionSize += u32PriorNum * SAMPLE_SVP_NNIE_PROPOSAL_WIDTH * sizeof(HI_U32) * 2;
    u32DetectionSize += u32PriorNum * 2 * sizeof(HI_U32);
    m_model_software_param->stGetResultTmpBuf.u32Size = u32DetectionSize;
    u32TotalSize += u32DetectionSize;

    return u32TotalSize;
}

HI_S32 SSDModel::SVP_NNIE_Ssd_SoftwareInit() {
    HI_U32 i = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 u32ClassNum = m_class_num;//分类数
    HI_U32 u32TotalSize = 0;
    HI_U32 u32DstRoiSize = 0;
    HI_U32 u32DstScoreSize = 0;
    HI_U32 u32ClassRoiNumSize = 0;
    HI_U32 u32TmpBufTotalSize = 0;
    HI_U64 u64PhyAddr = 0;
    HI_U8 *pu8VirAddr = NULL;
    SDC_MMZ_ALLOC_S stMemParas;

    /*Set Conv Parameters*/
    /*the SSD sample report resule is after permute operation,
     conv result is (C, H, W), after permute, the report node's
     (C1, H1, W1) is (H, W, C), the stride of report result is aligned according to C dim*/
    /*if your net dont have permute node after feature map, dont change the dim map*/

    /* 根据nnie params中输出blob的参数,设置后处理模块的参数
     * 注意如果你的模型输出是经过permute operation操作的,则输出的dims为CxHxW,而NNIE的结构格式为HxWxC,要注意进行修正
     * 本文所使用的模型是经过permute operation操作的*/
    for (i = 0; i < 12; i++) {/*一共12个输出blob,其中6个loc 6个conf*/
        m_model_software_param->au32ConvHeight[i] = m_nnie_param->pstModel->astSeg[0].astDstNode[i].unShape.stWhc.u32Chn;
        m_model_software_param->au32ConvWidth[i] = m_nnie_param->pstModel->astSeg[0].astDstNode[i].unShape.stWhc.u32Height;
        m_model_software_param->au32ConvChannel[i] = m_nnie_param->pstModel->astSeg[0].astDstNode[i].unShape.stWhc.u32Width;
        if (i % 2 == 1) {
            m_model_software_param->au32ConvStride[i / 2] =
                    SAMPLE_SVP_NNIE_ALIGN16(m_model_software_param->au32ConvChannel[i] * sizeof(HI_U32)) /
                    sizeof(HI_U32);
        }
        printf("dst blob idx: %i----------\n"
               "m_model_software_param->height: %u\n"
               "m_model_software_param->width: %u\n"
               "m_model_software_param->channel: %u\n",
               i,
               m_model_software_param->au32ConvHeight[i],
               m_model_software_param->au32ConvWidth[i],
               m_model_software_param->au32ConvChannel[i]
        );


    }

    /*Set PriorBox Parameters*/
    //6个feature的大小设置
    //width
    m_model_software_param->au32PriorBoxWidth[0] = 38;
    m_model_software_param->au32PriorBoxWidth[1] = 19;
    m_model_software_param->au32PriorBoxWidth[2] = 10;
    m_model_software_param->au32PriorBoxWidth[3] = 5;
    m_model_software_param->au32PriorBoxWidth[4] = 3;
    m_model_software_param->au32PriorBoxWidth[5] = 1;
    //height
    m_model_software_param->au32PriorBoxHeight[0] = 38;
    m_model_software_param->au32PriorBoxHeight[1] = 19;
    m_model_software_param->au32PriorBoxHeight[2] = 10;
    m_model_software_param->au32PriorBoxHeight[3] = 5;
    m_model_software_param->au32PriorBoxHeight[4] = 3;
    m_model_software_param->au32PriorBoxHeight[5] = 1;
    //input image Height & Width
    m_model_software_param->u32OriImHeight = m_nnie_param->astSegData[0].astSrc[0].unShape.stWhc.u32Height;
    m_model_software_param->u32OriImWidth = m_nnie_param->astSegData[0].astSrc[0].unShape.stWhc.u32Width;
    //prior box Max/Min size
    m_model_software_param->af32PriorBoxMinSize[0][0] = 30.0f;
    m_model_software_param->af32PriorBoxMinSize[1][0] = 60.0f;
    m_model_software_param->af32PriorBoxMinSize[2][0] = 111.0f;
    m_model_software_param->af32PriorBoxMinSize[3][0] = 162.0f;
    m_model_software_param->af32PriorBoxMinSize[4][0] = 213.0f;
    m_model_software_param->af32PriorBoxMinSize[5][0] = 264.0f;

    m_model_software_param->af32PriorBoxMaxSize[0][0] = 60.0f;
    m_model_software_param->af32PriorBoxMaxSize[1][0] = 111.0f;
    m_model_software_param->af32PriorBoxMaxSize[2][0] = 162.0f;
    m_model_software_param->af32PriorBoxMaxSize[3][0] = 213.0f;
    m_model_software_param->af32PriorBoxMaxSize[4][0] = 264.0f;
    m_model_software_param->af32PriorBoxMaxSize[5][0] = 315.0f;

    m_model_software_param->u32MinSizeNum = 1;
    m_model_software_param->u32MaxSizeNum = 1;
    m_model_software_param->bFlip = HI_TRUE;
    m_model_software_param->bClip = HI_FALSE;
    //prior box ratio
    m_model_software_param->au32InputAspectRatioNum[0] = 1;
    m_model_software_param->au32InputAspectRatioNum[1] = 2;
    m_model_software_param->au32InputAspectRatioNum[2] = 2;
    m_model_software_param->au32InputAspectRatioNum[3] = 2;
    m_model_software_param->au32InputAspectRatioNum[4] = 1;
    m_model_software_param->au32InputAspectRatioNum[5] = 1;

    m_model_software_param->af32PriorBoxAspectRatio[0][0] = 2;
    m_model_software_param->af32PriorBoxAspectRatio[0][1] = 0;
    m_model_software_param->af32PriorBoxAspectRatio[1][0] = 2;
    m_model_software_param->af32PriorBoxAspectRatio[1][1] = 3;
    m_model_software_param->af32PriorBoxAspectRatio[2][0] = 2;
    m_model_software_param->af32PriorBoxAspectRatio[2][1] = 3;
    m_model_software_param->af32PriorBoxAspectRatio[3][0] = 2;
    m_model_software_param->af32PriorBoxAspectRatio[3][1] = 3;
    m_model_software_param->af32PriorBoxAspectRatio[4][0] = 2;
    m_model_software_param->af32PriorBoxAspectRatio[4][1] = 0;
    m_model_software_param->af32PriorBoxAspectRatio[5][0] = 2;
    m_model_software_param->af32PriorBoxAspectRatio[5][1] = 0;
    // feature map step size
    m_model_software_param->af32PriorBoxStepWidth[0] = 8;
    m_model_software_param->af32PriorBoxStepWidth[1] = 16;
    m_model_software_param->af32PriorBoxStepWidth[2] = 32;
    m_model_software_param->af32PriorBoxStepWidth[3] = 64;
    m_model_software_param->af32PriorBoxStepWidth[4] = 100;
    m_model_software_param->af32PriorBoxStepWidth[5] = 300;

    m_model_software_param->af32PriorBoxStepHeight[0] = 8;
    m_model_software_param->af32PriorBoxStepHeight[1] = 16;
    m_model_software_param->af32PriorBoxStepHeight[2] = 32;
    m_model_software_param->af32PriorBoxStepHeight[3] = 64;
    m_model_software_param->af32PriorBoxStepHeight[4] = 100;
    m_model_software_param->af32PriorBoxStepHeight[5] = 300;

    m_model_software_param->f32Offset = 0.5f;
    //variance
    m_model_software_param->as32PriorBoxVar[0] = (HI_S32) (0.1f * SAMPLE_SVP_NNIE_QUANT_BASE);
    m_model_software_param->as32PriorBoxVar[1] = (HI_S32) (0.1f * SAMPLE_SVP_NNIE_QUANT_BASE);
    m_model_software_param->as32PriorBoxVar[2] = (HI_S32) (0.2f * SAMPLE_SVP_NNIE_QUANT_BASE);
    m_model_software_param->as32PriorBoxVar[3] = (HI_S32) (0.2f * SAMPLE_SVP_NNIE_QUANT_BASE);

    /*Set Softmax Parameters conf输出层*/
    //6个feature map输出的channel数量
    m_model_software_param->u32SoftMaxInHeight = u32ClassNum;//分类数 21
    m_model_software_param->au32SoftMaxInChn[0] = u32ClassNum * 4 * 38 * 38;//分类数(21)*候选框数(4)*H(38)*W(38)=121296
    m_model_software_param->au32SoftMaxInChn[1] = u32ClassNum * 6 * 19 * 19;//21*6*19*19=45486
    m_model_software_param->au32SoftMaxInChn[2] = u32ClassNum * 6 * 10 * 10;//21*6*10*10=12600
    m_model_software_param->au32SoftMaxInChn[3] = u32ClassNum * 6 * 5 * 5;//21*6*5*5=3150
    m_model_software_param->au32SoftMaxInChn[4] = u32ClassNum * 4 * 3 * 3;//21*4*3*3=756
    m_model_software_param->au32SoftMaxInChn[5] = u32ClassNum * 4 * 1 * 1;//21*4*1*1=84
    // BCHW 1x8732x21x1
    m_model_software_param->u32ConcatNum = 6;//6 feature map
    m_model_software_param->u32SoftMaxOutWidth = 1;
    m_model_software_param->u32SoftMaxOutHeight = u32ClassNum;//最大分类数 21
    m_model_software_param->u32SoftMaxOutChn = 8732;//6层feature map的prior box数量之和

    /*Set DetectionOut Parameters loc输出层*/
    m_model_software_param->u32ClassNum = u32ClassNum; //
    m_model_software_param->u32TopK = 400;
    m_model_software_param->u32KeepTopK = 200;
    m_model_software_param->u32NmsThresh = (HI_U16) (0.3f * SAMPLE_SVP_NNIE_QUANT_BASE);
    m_model_software_param->u32ConfThresh = 1;
    m_model_software_param->au32DetectInputChn[0] = 23104;//两个坐标点(4)*候选框数(4)*H(38)*W(38)
    m_model_software_param->au32DetectInputChn[1] = 8664;//4*6*19*19
    m_model_software_param->au32DetectInputChn[2] = 2400;//4*6*10*10
    m_model_software_param->au32DetectInputChn[3] = 600;//4*6*5*5
    m_model_software_param->au32DetectInputChn[4] = 144;//4*4*3*3
    m_model_software_param->au32DetectInputChn[5] = 16;//4*4*1*1

    /*Malloc assist buffer memory*/
    //申请内存
//    u32ClassNum = m_model_software_param->u32ClassNum;
    //获得结果所需的内存大小
    u32TotalSize = SVP_NNIE_Ssd_GetResultTmpBuf();
    //Roi所需的内存大小
    u32DstRoiSize = SAMPLE_SVP_NNIE_ALIGN16(
            u32ClassNum * m_model_software_param->u32TopK * sizeof(HI_U32) * SAMPLE_SVP_NNIE_COORDI_NUM);
    //计算BBox topK所需的内存大小
    u32DstScoreSize = SAMPLE_SVP_NNIE_ALIGN16(u32ClassNum * m_model_software_param->u32TopK * sizeof(HI_U32));
    // Roi区域保存分类数据所需的内存大小
    u32ClassRoiNumSize = SAMPLE_SVP_NNIE_ALIGN16(u32ClassNum * sizeof(HI_U32));
    u32TotalSize = u32TotalSize + u32DstRoiSize + u32DstScoreSize + u32ClassRoiNumSize;
    s32Ret = m_utils_service->SDC_MemAlloc(u32TotalSize, &stMemParas);
    u64PhyAddr = stMemParas.addr_phy;
    pu8VirAddr = (HI_U8 *) stMemParas.addr_virt;
    u32TotalSize = stMemParas.size;

    SAMPLE_SVP_CHECK_EXPR_RET(u32TotalSize != s32Ret, s32Ret, SAMPLE_SVP_ERR_LEVEL_ERROR,
                              "Error,Malloc memory failed!\n");
    memset(pu8VirAddr, 0, u32TotalSize);
    m_utils_service->SDC_FlushCache(u64PhyAddr, (void *) pu8VirAddr, u32TotalSize);

    /*set each tmp buffer addr*/
    //设定后处理函数的地址
    m_model_software_param->stPriorBoxTmpBuf.u64PhyAddr = u64PhyAddr;
    m_model_software_param->stPriorBoxTmpBuf.u64VirAddr = (HI_U64) (pu8VirAddr);

    m_model_software_param->stSoftMaxTmpBuf.u64PhyAddr = u64PhyAddr +
                                                         m_model_software_param->stPriorBoxTmpBuf.u32Size;
    m_model_software_param->stSoftMaxTmpBuf.u64VirAddr = (HI_U64) (pu8VirAddr +
                                                                   m_model_software_param->stPriorBoxTmpBuf.u32Size);

    m_model_software_param->stGetResultTmpBuf.u64PhyAddr = u64PhyAddr +
                                                           m_model_software_param->stPriorBoxTmpBuf.u32Size +
                                                           m_model_software_param->stSoftMaxTmpBuf.u32Size;
    m_model_software_param->stGetResultTmpBuf.u64VirAddr = (HI_U64) (pu8VirAddr +
                                                                     m_model_software_param->stPriorBoxTmpBuf.u32Size +
                                                                     m_model_software_param->stSoftMaxTmpBuf.u32Size);

    u32TmpBufTotalSize = m_model_software_param->stPriorBoxTmpBuf.u32Size +
                         m_model_software_param->stSoftMaxTmpBuf.u32Size +
                         m_model_software_param->stGetResultTmpBuf.u32Size;

    /*set result blob*/
    m_model_software_param->stDstRoi.enType = SVP_BLOB_TYPE_S32;
    m_model_software_param->stDstRoi.u64PhyAddr = u64PhyAddr + u32TmpBufTotalSize;
    m_model_software_param->stDstRoi.u64VirAddr = (HI_U64) (pu8VirAddr + u32TmpBufTotalSize);
    m_model_software_param->stDstRoi.u32Stride = SAMPLE_SVP_NNIE_ALIGN16(u32ClassNum*
                                                                                 m_model_software_param->u32TopK *
                                                                                 sizeof(HI_U32) *
                                                                                 SAMPLE_SVP_NNIE_COORDI_NUM);
    m_model_software_param->stDstRoi.u32Num = 1;
    m_model_software_param->stDstRoi.unShape.stWhc.u32Chn = 1;
    m_model_software_param->stDstRoi.unShape.stWhc.u32Height = 1;
    m_model_software_param->stDstRoi.unShape.stWhc.u32Width = u32ClassNum *
                                                              m_model_software_param->u32TopK *
                                                              SAMPLE_SVP_NNIE_COORDI_NUM;

    m_model_software_param->stDstScore.enType = SVP_BLOB_TYPE_S32;
    m_model_software_param->stDstScore.u64PhyAddr = u64PhyAddr + u32TmpBufTotalSize + u32DstRoiSize;
    m_model_software_param->stDstScore.u64VirAddr = (HI_U64) (pu8VirAddr + u32TmpBufTotalSize + u32DstRoiSize);
    m_model_software_param->stDstScore.u32Stride = SAMPLE_SVP_NNIE_ALIGN16(u32ClassNum*
                                                                                   m_model_software_param->u32TopK *
                                                                                   sizeof(HI_U32));
    m_model_software_param->stDstScore.u32Num = 1;
    m_model_software_param->stDstScore.unShape.stWhc.u32Chn = 1;
    m_model_software_param->stDstScore.unShape.stWhc.u32Height = 1;
    m_model_software_param->stDstScore.unShape.stWhc.u32Width = u32ClassNum *
                                                                m_model_software_param->u32TopK;

    m_model_software_param->stClassRoiNum.enType = SVP_BLOB_TYPE_S32;
    m_model_software_param->stClassRoiNum.u64PhyAddr = u64PhyAddr + u32TmpBufTotalSize +
                                                       u32DstRoiSize + u32DstScoreSize;
    m_model_software_param->stClassRoiNum.u64VirAddr = (HI_U64) (pu8VirAddr + u32TmpBufTotalSize +
                                                                 u32DstRoiSize + u32DstScoreSize);
    m_model_software_param->stClassRoiNum.u32Stride = SAMPLE_SVP_NNIE_ALIGN16(u32ClassNum * sizeof(HI_U32));
    m_model_software_param->stClassRoiNum.u32Num = 1;
    m_model_software_param->stClassRoiNum.unShape.stWhc.u32Chn = 1;
    m_model_software_param->stClassRoiNum.unShape.stWhc.u32Height = 1;
    m_model_software_param->stClassRoiNum.unShape.stWhc.u32Width = u32ClassNum;

    return HI_SUCCESS;
}

HI_S32 SSDModel::SVP_NNIE_Ssd_SoftwareDeinit() {
    HI_S32 s32Ret = HI_SUCCESS;
    SDC_MMZ_ALLOC_S stMemParas;

    if (0 != m_model_software_param->stPriorBoxTmpBuf.u64PhyAddr &&
        0 != m_model_software_param->stPriorBoxTmpBuf.u64VirAddr) {
        stMemParas.addr_phy = m_model_software_param->stPriorBoxTmpBuf.u64PhyAddr,
                stMemParas.addr_virt = m_model_software_param->stPriorBoxTmpBuf.u64VirAddr;

        m_utils_service->SDC_MemFree(&stMemParas);


        m_model_software_param->stPriorBoxTmpBuf.u64PhyAddr = 0;
        m_model_software_param->stPriorBoxTmpBuf.u64VirAddr = 0;
    }
    return s32Ret;
}

/*初始化失败时释放模型资源*/
HI_S32 SSDModel::SVP_NNIE_Ssd_Deinit() {
    HI_S32 s32Ret = HI_SUCCESS;
    /*hardware deinit*/
    if (m_nnie_param != NULL) {
        s32Ret = SDC_NNIE_ParamDeinit();
        SAMPLE_SVP_CHECK_EXPR_TRACE(HI_SUCCESS != s32Ret, SAMPLE_SVP_ERR_LEVEL_ERROR,
                                    "Error,SDC_NNIE_ParamDeinit failed!\n");
    }
    /*software deinit*/
    if (m_model_software_param != NULL) {
        s32Ret = SVP_NNIE_Ssd_SoftwareDeinit();
        SAMPLE_SVP_CHECK_EXPR_TRACE(HI_SUCCESS != s32Ret, SAMPLE_SVP_ERR_LEVEL_ERROR,
                                    "Error,SVP_NNIE_Ssd_SoftwareDeinit failed!\n");
    }
    /*model deinit*/
    if (ssd_model != NULL) {
        s32Ret = m_algorithm_service->SDC_UnLoadModel(&ssd_model->stModel);
        if (s32Ret != PAS) {
            DEBUG_LOG("Err in SDC_UnLoadModel.");
        }
    }
    return s32Ret;
}

HI_S32 SSDModel::SVP_NNIE_Ssd_ParamInit() {
    HI_S32 s32Ret = HI_SUCCESS;//0表示success
    /*init hardware para 硬件(SDC,NNIE)初始化，模型二进制文件解析，申请内存加载模型*/
    DEBUG_LOG("硬件(SDC,NNIE)初始化");
    s32Ret = SDC_NNIE_ParamInit();
    //初始化失败，则执行INIT_FAIL_0
    SAMPLE_SVP_CHECK_EXPR_GOTO(HI_SUCCESS != s32Ret, INIT_FAIL_0, SAMPLE_SVP_ERR_LEVEL_ERROR,
                               "Error(%#x),SDC_NNIE_ParamInit failed!\n", s32Ret);

    /*init software para 初始化SSD 后处理相关函数*/
    s32Ret = SVP_NNIE_Ssd_SoftwareInit();

    //初始化失败，则执行INIT_FAIL_0
    SAMPLE_SVP_CHECK_EXPR_GOTO(HI_SUCCESS != s32Ret, INIT_FAIL_0, SAMPLE_SVP_ERR_LEVEL_ERROR,
                               "Error(%#x),SVP_NNIE_Ssd_SoftwareInit failed!\n", s32Ret);

    return s32Ret;
    INIT_FAIL_0:
    s32Ret = SVP_NNIE_Ssd_Deinit();
    SAMPLE_SVP_CHECK_EXPR_RET(HI_SUCCESS != s32Ret, s32Ret, SAMPLE_SVP_ERR_LEVEL_ERROR,
                              "Error(%#x),SVP_NNIE_Ssd_Deinit failed!\n", s32Ret);
    return HI_FAILURE;

}

int SSDModel::ssd_param_init(HI_U32 max_input_num, HI_U32 max_roi_num) {
    //NNIE模块初始化，并加载模型结构
    int nnie_ret = 0;
    m_nnie_cfg->u32MaxInputNum = max_input_num;
    m_nnie_cfg->u32MaxRoiNum = max_roi_num;
    /*这里写死了使用内核0*/
    m_nnie_cfg->aenNnieCoreId[0] = SVP_NNIE_ID_0;
    m_nnie_param->pstModel = &ssd_model->stModel;

    nnie_ret = SVP_NNIE_Ssd_ParamInit();
    if (nnie_ret != PAS) {
        printf("svp nnie param init fail.\n");
        return ERR;
    } else printf("svp nnie param init success.\n");
    return PAS;
}

HI_S32 SSDModel::SAMPLE_SVP_NNIE_Forward(
                               SAMPLE_SVP_NNIE_INPUT_DATA_INDEX_S* pstInputDataIdx,
                               SAMPLE_SVP_NNIE_PROCESS_SEG_INDEX_S* pstProcSegIdx)
{
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 i = 0, j = 0;
    SDC_NNIE_FORWARD_S sdc_nnie_forward;

    /*set input blob according to node name*/
    if(pstInputDataIdx->u32SegIdx != pstProcSegIdx->u32SegIdx)
    {
        for(i = 0; i < m_nnie_param->pstModel->astSeg[pstProcSegIdx->u32SegIdx].u16SrcNum; i++)
        {
            for(j = 0; j < m_nnie_param->pstModel->astSeg[pstInputDataIdx->u32SegIdx].u16DstNum; j++)
            {
                if(0 == strncmp(m_nnie_param->pstModel->astSeg[pstInputDataIdx->u32SegIdx].astDstNode[j].szName,
                                m_nnie_param->pstModel->astSeg[pstProcSegIdx->u32SegIdx].astSrcNode[i].szName,
                                SVP_NNIE_NODE_NAME_LEN))
                {
                    m_nnie_param->astSegData[pstProcSegIdx->u32SegIdx].astSrc[i] =
                            m_nnie_param->astSegData[pstInputDataIdx->u32SegIdx].astDst[j];
                    break;
                }
            }
            SAMPLE_SVP_CHECK_EXPR_RET((j == m_nnie_param->pstModel->astSeg[pstInputDataIdx->u32SegIdx].u16DstNum),
                                      HI_FAILURE,SAMPLE_SVP_ERR_LEVEL_ERROR,"Error,can't find %d-th seg's %d-th src blob!\n",
                                      pstProcSegIdx->u32SegIdx,i);
        }
    }

    /*NNIE_Forward*/

    memcpy(&sdc_nnie_forward.model, m_nnie_param->pstModel, sizeof(SVP_NNIE_MODEL_S));
    sdc_nnie_forward.forward_ctrl.max_batch_num = 1;
    sdc_nnie_forward.forward_ctrl.max_bbox_num = 0;/*此处需要根据算法模型的ROI个数决定，max_bbox_num = max_roi_num(ROI个数)*/
    sdc_nnie_forward.forward_ctrl.netseg_id = m_nnie_param->astForwardCtrl[pstProcSegIdx->u32SegIdx].u32NetSegId;

    memcpy(sdc_nnie_forward.astSrc, m_nnie_param->astSegData[pstProcSegIdx->u32SegIdx].astSrc, 16 * sizeof(SVP_DST_BLOB_S));
    memcpy(sdc_nnie_forward.astDst, m_nnie_param->astSegData[pstProcSegIdx->u32SegIdx].astDst, 16 * sizeof(SVP_DST_BLOB_S));

    s32Ret = m_algorithm_service->SDC_Nnie_Forward(&sdc_nnie_forward);
    if(s32Ret != PAS)
    {
        fprintf(stderr, "Err in SDC_Nnie_Forward, s32Ret: %d\n", s32Ret);
        return ERR;
    }
    return s32Ret;
}

int SSDModel::SDC_SVP_ForwardBGR(
//        HI_CHAR *pcSrcBGR,
        SDC_SSD_RESULT_S *pstResult
        ){
    HI_S32 s32Ret = HI_SUCCESS;
    SAMPLE_SVP_NNIE_INPUT_DATA_INDEX_S stInputDataIdx = {0};
    SAMPLE_SVP_NNIE_PROCESS_SEG_INDEX_S stProcSegIdx = {0};
    struct timespec time1 = {0, 0};
    struct timespec time2 = {0, 0};
    struct timespec time3 = {0, 0};
    unsigned int uiTimeCout = 0;

    /*Set configuration parameter*/
    m_nnie_cfg->pszPic = HI_NULL;
    m_nnie_cfg->pszYUV = HI_NULL;
//    m_nnie_cfg->pszBGR = pcSrcBGR;
    m_nnie_cfg->rgb_adds = infer_params.rgb_img;
    m_nnie_cfg->pszBGR = infer_params.rgb_img->pYuvImgAddr;

    /*Fill src data*/
    //  SAMPLE_SVP_TRACE_INFO("Ssd start!\n");
    stInputDataIdx.u32SegIdx = 0;
    stInputDataIdx.u32Node_num = m_duration_num;
    stInputDataIdx.u32NodeIdx = 0;
    /*从data_connect获取到的数据地址中拷贝数据到模型的输入blob的数据内存地址中*/
    s32Ret = SAMPLE_SVP_NNIE_FillSrcData(&stInputDataIdx);

    /*前向推导*/
    clock_gettime(CLOCK_BOOTTIME, &time1);
    stProcSegIdx.u32SegIdx = 0;
    s32Ret = SAMPLE_SVP_NNIE_Forward(&stInputDataIdx,&stProcSegIdx);

    clock_gettime(CLOCK_BOOTTIME, &time2);
    uiTimeCout = (unsigned int)(time2.tv_sec - time1.tv_sec)*1000 + (unsigned int)((time2.tv_nsec - time1.tv_nsec)/1000000);
    fprintf(stdout,"timeforward:%d\n", uiTimeCout);

    /*software process*/
    /*if user has changed net struct, please make sure SAMPLE_SVP_NNIE_Ssd_GetResult
     function's input datas are correct*/
    //获取模型的输出结果
    s32Ret = SAMPLE_SVP_NNIE_Ssd_GetResult(m_nnie_param,m_model_software_param);
    //  printf("SAMPLE_SVP_NNIE_Ssd_GetResult s32Ret = %d\n", s32Ret);

    clock_gettime(CLOCK_BOOTTIME, &time3);
    uiTimeCout = (unsigned int)(time3.tv_sec - time2.tv_sec)*1000 + (unsigned int)((time3.tv_nsec - time2.tv_nsec)/1000000);
    fprintf(stdout,"timeSsd_GetResult:%d\n", uiTimeCout);

    SDC_SVP_NNIE_Detection_GetResult(&m_model_software_param->stDstScore,
                                     &m_model_software_param->stDstRoi, &m_model_software_param->stClassRoiNum, infer_params.pstResult);
    return s32Ret;
}
/*多帧填充*/
HI_S32 SSDModel::SAMPLE_SVP_NNIE_FillSrcData(SAMPLE_SVP_NNIE_INPUT_DATA_INDEX_S* pstInputDataIdx)
{

    FILE* fp = NULL;
    HI_U32 i =0, j = 0, n = 0;
    HI_U32 u32Height = 0, u32Width = 0, u32Chn = 0, u32Stride = 0, u32Dim = 0;
    HI_U32 u32VarSize = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U8*pu8PicAddr = NULL;
    HI_U32*pu32StepAddr = NULL;
    HI_U32 u32SegIdx = pstInputDataIdx->u32SegIdx;
    HI_U32 u32NodeIdxs = pstInputDataIdx->u32Node_num;
    HI_U32 u32NodeIdx;
    HI_U32 u32TotalStepNum = 0;
    HI_U8 *pu8BGR = HI_NULL;
    VW_YUV_FRAME_S *rgb_adds=HI_NULL;
    HI_U8 *pu8YUV = HI_NULL;
    HI_BOOL bRBG2BGR = HI_TRUE;

    // RBG => BGR
#define B_BASE_OFFSET (1*u32Stride*u32Height)
#define G_BASE_OFFSET (2*u32Stride*u32Height)
#define R_BASE_OFFSET (0*u32Stride*u32Height)
    HI_U8 *p_B_data = HI_NULL;
    HI_U8 *p_G_data = HI_NULL;
    HI_U8 *p_R_data = HI_NULL;

    /*储存了rgb数据的VM_YUV_FRAME头指针*/
    rgb_adds = m_nnie_cfg->rgb_adds;
    for(u32NodeIdx=0;u32NodeIdx<u32NodeIdxs;u32NodeIdx++){
        /*取出图像数据的指针*/
//        DEBUG_LOG("SAMPLE_SVP_NNIE_FillSrcData u32NodeIdx:%i",u32NodeIdx);
        pu8BGR = (HI_U8*)(rgb_adds+u32NodeIdx)->pYuvImgAddr;
//        char file_name[100];
//        sprintf(file_name,"video_img_%i.txt",u32NodeIdx);
//        SaveImgTxt::SDC_RGB_read(pu8BGR,file_name,300,304,3);

        /*get data size*/

        if(SVP_BLOB_TYPE_U8 <= m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].enType &&
           SVP_BLOB_TYPE_YVU422SP >= m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].enType)
        {
            u32VarSize = sizeof(HI_U8);
        }
        else
        {
            u32VarSize = sizeof(HI_U32);
        }
        /*fill src data*/
        if(SVP_BLOB_TYPE_SEQ_S32 == m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].enType)
        {
            u32Dim = m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].unShape.stSeq.u32Dim;
            u32Stride = m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u32Stride;
            pu32StepAddr = (HI_U32*)(m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].unShape.stSeq.u64VirAddrStep);
            pu8PicAddr = (HI_U8*)(m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u64VirAddr);
            for(n = 0; n < m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u32Num; n++)
            {
                for(i = 0;i < *(pu32StepAddr+n); i++)
                {
                    s32Ret = fread(pu8PicAddr,u32Dim*u32VarSize,1,fp);
                    SAMPLE_SVP_CHECK_EXPR_GOTO(1 != s32Ret,FAIL,SAMPLE_SVP_ERR_LEVEL_ERROR,"Error,Read image file failed!\n");
                    pu8PicAddr += u32Stride;
                }
                u32TotalStepNum += *(pu32StepAddr+n);
            }

            m_utils_service->SDC_FlushCache(m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u64PhyAddr,
                                            (HI_VOID *) m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u64VirAddr,
                                            u32TotalStepNum*u32Stride);
        }
        else
        {
            u32Height = m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].unShape.stWhc.u32Height;
            u32Width = m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].unShape.stWhc.u32Width;
            u32Chn = m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].unShape.stWhc.u32Chn;
            u32Stride = m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u32Stride;
            pu8PicAddr = (HI_U8*)(m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u64VirAddr);
            if(SVP_BLOB_TYPE_YVU420SP == m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].enType)
            {
                for(n = 0; n < m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u32Num; n++)
                {
                    for(i = 0; i < u32Chn*u32Height/2; i++)
                    {
                        if(fp)
                        {
                            s32Ret = fread(pu8PicAddr,u32Width*u32VarSize,1,fp);
                        }
                        else
                        {
                            //printf("pu8YUV current = %p\n", pu8YUV);
                            memcpy_s(pu8PicAddr, u32Width*u32VarSize, pu8YUV, u32Width*u32VarSize);
                            //printf("pu8YUV current2 = %p\n", pu8YUV);
                            pu8YUV += 304;
                        }
                        //SAMPLE_SVP_CHECK_EXPR_GOTO(1 != s32Ret,FAIL,SAMPLE_SVP_ERR_LEVEL_ERROR,"Error,Read image file failed!\n");
                        //printf("u32Stride = %d\n", u32Stride);
                        pu8PicAddr += u32Stride;
                    }
                }
            }
            else if(SVP_BLOB_TYPE_YVU422SP == m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].enType)
            {
                for(n = 0; n < m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u32Num; n++)
                {
                    for(i = 0; i < u32Height*2; i++)
                    {
                        s32Ret = fread(pu8PicAddr,u32Width*u32VarSize,1,fp);
                        SAMPLE_SVP_CHECK_EXPR_GOTO(1 != s32Ret,FAIL,SAMPLE_SVP_ERR_LEVEL_ERROR,"Error,Read image file failed!\n");
                        pu8PicAddr += u32Stride;
                    }
                }
            }
            else
            {
                if(bRBG2BGR) // RBG => BGR
                {
                    p_B_data = pu8BGR + B_BASE_OFFSET;
                    p_G_data = pu8BGR + G_BASE_OFFSET;
                    p_R_data = pu8BGR + R_BASE_OFFSET;
                }
                for(n = 0; n < m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u32Num; n++)
                {
                    for(i = 0;i < u32Chn; i++)
                    {
                        for(j = 0; j < u32Height; j++)
                        {
                            if(HI_NULL != fp)
                            {
                                s32Ret = fread(pu8PicAddr,u32Width*u32VarSize,1,fp);
                                SAMPLE_SVP_CHECK_EXPR_GOTO(1 != s32Ret,FAIL,SAMPLE_SVP_ERR_LEVEL_ERROR,"Error,Read image file failed!\n");
                            }
                            else if(HI_NULL != m_nnie_cfg->pszBGR)
                            {
                                //printf("u32Width*u32VarSize = %d\n", u32Width*u32VarSize);
                                if(bRBG2BGR) // RBG => BGR
                                {
                                    if(i == 0) //copy B
                                    {
//                                    DEBUG_LOG("p_B_data value: %i",*p_B_data);
                                        memcpy_s(pu8PicAddr, u32Width*u32VarSize, p_B_data, u32Width*u32VarSize);
                                        p_B_data += u32Stride;
                                    }
                                    else if(i == 1) //copy G
                                    {
//                                    DEBUG_LOG("p_G_data value: %i",*p_G_data);
                                        memcpy_s(pu8PicAddr, u32Width*u32VarSize, p_G_data, u32Width*u32VarSize);
                                        p_G_data += u32Stride;
                                    }
                                    else // copy R
                                    {
//                                    DEBUG_LOG("p_R_data value: %i",*p_R_data);
                                        memcpy_s(pu8PicAddr, u32Width*u32VarSize, p_R_data, u32Width*u32VarSize);
                                        p_R_data += u32Stride;
                                    }
                                }
                                else
                                {
                                    memcpy_s(pu8PicAddr, u32Width*u32VarSize, pu8BGR, u32Width*u32VarSize);
                                    pu8BGR += u32Stride;
                                }
                            }
                            pu8PicAddr += u32Stride;
                        }
                    }
                }
            }
            m_utils_service->SDC_FlushCache(m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u64PhyAddr,
                                            (HI_VOID *) m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u64VirAddr,
                                            m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u32Num * u32Chn * u32Height * u32Stride);
        }
    }
    if(fp != HI_NULL)
        fclose(fp);
    return HI_SUCCESS;

    FAIL:
    if(fp != HI_NULL)
        fclose(fp);
    fclose(fp);
    return HI_FAILURE;
}

//HI_S32 SSDModel::SAMPLE_SVP_NNIE_FillSrcData(SAMPLE_SVP_NNIE_INPUT_DATA_INDEX_S* pstInputDataIdx)
//{
//
//    FILE* fp = NULL;
//    HI_U32 i =0, j = 0, n = 0;
//    HI_U32 u32Height = 0, u32Width = 0, u32Chn = 0, u32Stride = 0, u32Dim = 0;
//    HI_U32 u32VarSize = 0;
//    HI_S32 s32Ret = HI_SUCCESS;
//    HI_U8*pu8PicAddr = NULL;
//    HI_U32*pu32StepAddr = NULL;
//    HI_U32 u32SegIdx = pstInputDataIdx->u32SegIdx;
//    HI_U32 u32NodeIdx = pstInputDataIdx->u32NodeIdx;
//    HI_U32 u32TotalStepNum = 0;
//    HI_U8 *pu8BGR = HI_NULL;
//    HI_U8 *pu8YUV = HI_NULL;
//    HI_BOOL bRBG2BGR = HI_TRUE;
//
//    // RBG => BGR 应该不对,从保存下来得图像显示,摄像头读入得就是BGR,不需要转换.是BGR->BGR
//#define B_BASE_OFFSET (1*u32Stride*u32Height)
//#define G_BASE_OFFSET (2*u32Stride*u32Height)
//#define R_BASE_OFFSET (0*u32Stride*u32Height)
////#define B_BASE_OFFSET (1*u32Stride*u32Height)
////#define G_BASE_OFFSET (2*u32Stride*u32Height)
////#define R_BASE_OFFSET (0*u32Stride*u32Height)
//    HI_U8 *p_B_data = HI_NULL;
//    HI_U8 *p_G_data = HI_NULL;
//    HI_U8 *p_R_data = HI_NULL;
//
//
//    /*open file*/
//    if (NULL != m_nnie_cfg->pszPic)
//    {
//        fp = fopen(m_nnie_cfg->pszPic, "rb");
//        SAMPLE_SVP_CHECK_EXPR_RET(NULL == fp,HI_INVALID_VALUE,SAMPLE_SVP_ERR_LEVEL_ERROR,
//                                  "Error, open file failed!\n");
//    }
//    else if(NULL != m_nnie_cfg->pszBGR)
//    {
//        pu8BGR = (HI_U8*)m_nnie_cfg->pszBGR;
//        DEBUG_LOG("---------------------------------------save img txt-----------------------------------------------");
////        SaveImgTxt::SDC_RGB_save(m_nnie_cfg->pszBGR,304,304,"img1.txt");
//        //printf("pu8BGR = %p\n", pu8BGR);
//    }
//    else if(NULL != m_nnie_cfg->pszYUV)
//    {
//        pu8YUV = (HI_U8*)m_nnie_cfg->pszYUV;
//        //printf("pu8YUV = %p\n", pu8YUV);
//    }
//
//    /*get data size*/
//
//    if(SVP_BLOB_TYPE_U8 <= m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].enType &&
//       SVP_BLOB_TYPE_YVU422SP >= m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].enType)
//    {
//        u32VarSize = sizeof(HI_U8);
//    }
//    else
//    {
//        u32VarSize = sizeof(HI_U32);
//    }
//
//    /*fill src data*/
//    if(SVP_BLOB_TYPE_SEQ_S32 == m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].enType)
//    {
//        DEBUG_LOG("错误的分支");
//        exit(-1);
//        u32Dim = m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].unShape.stSeq.u32Dim;
//        u32Stride = m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u32Stride;
//        pu32StepAddr = (HI_U32*)(m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].unShape.stSeq.u64VirAddrStep);
//        pu8PicAddr = (HI_U8*)(m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u64VirAddr);
//        for(n = 0; n < m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u32Num; n++)
//        {
//            for(i = 0;i < *(pu32StepAddr+n); i++)
//            {
//                s32Ret = fread(pu8PicAddr,u32Dim*u32VarSize,1,fp);
//                SAMPLE_SVP_CHECK_EXPR_GOTO(1 != s32Ret,FAIL,SAMPLE_SVP_ERR_LEVEL_ERROR,"Error,Read image file failed!\n");
//                pu8PicAddr += u32Stride;
//            }
//            u32TotalStepNum += *(pu32StepAddr+n);
//        }
//
//        m_utils_service->SDC_FlushCache(m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u64PhyAddr,
//                                        (HI_VOID *) m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u64VirAddr,
//                       u32TotalStepNum*u32Stride);
//    }
//    else
//    {
//        u32Height = m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].unShape.stWhc.u32Height;
//        u32Width = m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].unShape.stWhc.u32Width;
//        u32Chn = m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].unShape.stWhc.u32Chn;
//        u32Stride = m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u32Stride;
//        pu8PicAddr = (HI_U8*)(m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u64VirAddr);
//        if(SVP_BLOB_TYPE_YVU420SP == m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].enType)
//        {
//            DEBUG_LOG("ERR:错误的分支");
//            exit(-1);
//            for(n = 0; n < m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u32Num; n++)
//            {
//                for(i = 0; i < u32Chn*u32Height/2; i++)
//                {
//                    if(fp)
//                    {
//                        s32Ret = fread(pu8PicAddr,u32Width*u32VarSize,1,fp);
//                    }
//                    else
//                    {
//                        //printf("pu8YUV current = %p\n", pu8YUV);
//                        memcpy_s(pu8PicAddr, u32Width*u32VarSize, pu8YUV, u32Width*u32VarSize);
//                        //printf("pu8YUV current2 = %p\n", pu8YUV);
//                        pu8YUV += 304;
//                    }
//                    //SAMPLE_SVP_CHECK_EXPR_GOTO(1 != s32Ret,FAIL,SAMPLE_SVP_ERR_LEVEL_ERROR,"Error,Read image file failed!\n");
//                    //printf("u32Stride = %d\n", u32Stride);
//                    pu8PicAddr += u32Stride;
//                }
//            }
//        }
//        else if(SVP_BLOB_TYPE_YVU422SP == m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].enType)
//        {
//            DEBUG_LOG("ERR:错误的分支");
//            exit(-1);
//            for(n = 0; n < m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u32Num; n++)
//            {
//                for(i = 0; i < u32Height*2; i++)
//                {
//                    s32Ret = fread(pu8PicAddr,u32Width*u32VarSize,1,fp);
//                    SAMPLE_SVP_CHECK_EXPR_GOTO(1 != s32Ret,FAIL,SAMPLE_SVP_ERR_LEVEL_ERROR,"Error,Read image file failed!\n");
//                    pu8PicAddr += u32Stride;
//                }
//            }
//        }
//        else
//        {
//            if(bRBG2BGR) // RBG => BGR
//            {
//                p_B_data = pu8BGR + B_BASE_OFFSET;
//                p_G_data = pu8BGR + G_BASE_OFFSET;
//                p_R_data = pu8BGR + R_BASE_OFFSET;
//                DEBUG_LOG("INFO:|u32Stride:%i,|u32Height:%i|,",u32Stride,u32Height);
//
////                SaveImgTxt::SDC_RGB_save(p_R_data,p_G_data,p_B_data,304,300,"img2.txt");
////                exit(0);
//            }
//            for(n = 0; n < m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u32Num; n++)
//            {
//                for(i = 0;i < u32Chn; i++)
//                {
//                    for(j = 0; j < u32Height; j++)
//                    {
//                        if(HI_NULL != fp)
//                        {
//                            s32Ret = fread(pu8PicAddr,u32Width*u32VarSize,1,fp);
//                            SAMPLE_SVP_CHECK_EXPR_GOTO(1 != s32Ret,FAIL,SAMPLE_SVP_ERR_LEVEL_ERROR,"Error,Read image file failed!\n");
//                        }
//                        else if(HI_NULL != m_nnie_cfg->pszBGR)
//                        {
//                            //printf("u32Width*u32VarSize = %d\n", u32Width*u32VarSize);
//                            if(bRBG2BGR) // RBG => BGR
//                            {
//
//                                if(i == 0) //copy B
//                                {
////                                    DEBUG_LOG("p_B_data value: %i",*p_B_data);
//                                    memcpy_s(pu8PicAddr, u32Width*u32VarSize, p_B_data, u32Width*u32VarSize);
//                                    p_B_data += u32Stride;
//                                }
//                                else if(i == 1) //copy G
//                                {
////                                    DEBUG_LOG("p_G_data value: %i",*p_G_data);
//                                    memcpy_s(pu8PicAddr, u32Width*u32VarSize, p_G_data, u32Width*u32VarSize);
//                                    p_G_data += u32Stride;
//                                }
//                                else // copy R
//                                {
////                                    DEBUG_LOG("p_R_data value: %i",*p_R_data);
//                                    memcpy_s(pu8PicAddr, u32Width*u32VarSize, p_R_data, u32Width*u32VarSize);
//                                    p_R_data += u32Stride;
//                                }
//                            }
//                            else
//                            {
//                                memcpy_s(pu8PicAddr, u32Width*u32VarSize, pu8BGR, u32Width*u32VarSize);
//                                pu8BGR += u32Stride;
//                            }
//                        }
//                        //pu8BGR += u32Width*u32VarSize;
//                        //printf("u32Stride = %d\n", u32Stride);
//                        pu8PicAddr += u32Stride;
//                    }
//                }
//            }
//        }
//        m_utils_service->SDC_FlushCache(m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u64PhyAddr,
//                                        (HI_VOID *) m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u64VirAddr,
//                                        m_nnie_param->astSegData[u32SegIdx].astSrc[u32NodeIdx].u32Num * u32Chn * u32Height * u32Stride);
//    }
//    if(fp != HI_NULL)
//        fclose(fp);
//    return HI_SUCCESS;
//
//    FAIL:
//    if(fp != HI_NULL)
//        fclose(fp);
//    fclose(fp);
//    return HI_FAILURE;
//}

HI_S32 SSDModel::SAMPLE_SVP_NNIE_Ssd_GetResult(SVP_NNIE_PARAM_S*pstNnieParam,
                                     SVP_NNIE_SSD_SOFTWARE_PARAM_S* pstSoftwareParam)
{
    HI_S32* aps32PermuteResult[SAMPLE_SVP_NNIE_SSD_REPORT_NODE_NUM];
    HI_S32* aps32PriorboxOutputData[SAMPLE_SVP_NNIE_SSD_PRIORBOX_NUM];
    HI_S32* aps32SoftMaxInputData[SAMPLE_SVP_NNIE_SSD_SOFTMAX_NUM];
    HI_S32* aps32DetectionLocData[SAMPLE_SVP_NNIE_SSD_SOFTMAX_NUM];
    HI_S32* ps32SoftMaxOutputData = NULL;
    HI_S32* ps32DetectionOutTmpBuf = NULL;
    HI_U32  au32SoftMaxWidth[SAMPLE_SVP_NNIE_SSD_SOFTMAX_NUM];
    HI_U32 u32Size = 0;
    HI_S32 s32Ret = HI_SUCCESS;
    HI_U32 i = 0;

    /*get permut result*/
    for(i = 0; i < SAMPLE_SVP_NNIE_SSD_REPORT_NODE_NUM; i++)
    {
        aps32PermuteResult[i] = (HI_S32*)pstNnieParam->astSegData[0].astDst[i].u64VirAddr;
    }

    /*priorbox*/
    aps32PriorboxOutputData[0] = (HI_S32*)pstSoftwareParam->stPriorBoxTmpBuf.u64VirAddr;
    for (i = 1; i < SAMPLE_SVP_NNIE_SSD_PRIORBOX_NUM; i++)
    {
        u32Size = pstSoftwareParam->au32PriorBoxHeight[i-1]*pstSoftwareParam->au32PriorBoxWidth[i-1]*
                  SAMPLE_SVP_NNIE_COORDI_NUM*2*(pstSoftwareParam->u32MaxSizeNum+pstSoftwareParam->u32MinSizeNum+
                                                pstSoftwareParam->au32InputAspectRatioNum[i-1]*2*pstSoftwareParam->u32MinSizeNum);
        aps32PriorboxOutputData[i] = aps32PriorboxOutputData[i - 1] + u32Size;
    }

    for (i = 0; i < SAMPLE_SVP_NNIE_SSD_PRIORBOX_NUM; i++)
    {
        s32Ret = SVP_NNIE_Ssd_PriorBoxForward(pstSoftwareParam->au32PriorBoxWidth[i],
                                              pstSoftwareParam->au32PriorBoxHeight[i], pstSoftwareParam->u32OriImWidth,
                                              pstSoftwareParam->u32OriImHeight, pstSoftwareParam->af32PriorBoxMinSize[i],
                                              pstSoftwareParam->u32MinSizeNum,pstSoftwareParam->af32PriorBoxMaxSize[i],
                                              pstSoftwareParam->u32MaxSizeNum, pstSoftwareParam->bFlip, pstSoftwareParam->bClip,
                                              pstSoftwareParam->au32InputAspectRatioNum[i],pstSoftwareParam->af32PriorBoxAspectRatio[i],
                                              pstSoftwareParam->af32PriorBoxStepWidth[i],pstSoftwareParam->af32PriorBoxStepHeight[i],
                                              pstSoftwareParam->f32Offset,pstSoftwareParam->as32PriorBoxVar,
                                              aps32PriorboxOutputData[i]);
        SAMPLE_SVP_CHECK_EXPR_RET(HI_SUCCESS != s32Ret,s32Ret,SAMPLE_SVP_ERR_LEVEL_ERROR,
                                  "Error,SVP_NNIE_Ssd_PriorBoxForward failed!\n");
    }

    /*softmax*/
    ps32SoftMaxOutputData = (HI_S32*)pstSoftwareParam->stSoftMaxTmpBuf.u64VirAddr;
    for(i = 0; i < SAMPLE_SVP_NNIE_SSD_SOFTMAX_NUM; i++)
    {
        aps32SoftMaxInputData[i] = aps32PermuteResult[i*2+1];
        au32SoftMaxWidth[i] = pstSoftwareParam->au32ConvChannel[i*2+1];
    }

    (void)SVP_NNIE_Ssd_SoftmaxForward(pstSoftwareParam->u32SoftMaxInHeight,
                                      pstSoftwareParam->au32SoftMaxInChn, pstSoftwareParam->u32ConcatNum,
                                      pstSoftwareParam->au32ConvStride, au32SoftMaxWidth,
                                      aps32SoftMaxInputData, ps32SoftMaxOutputData);

    /*detection*/
    ps32DetectionOutTmpBuf = (HI_S32*)pstSoftwareParam->stGetResultTmpBuf.u64VirAddr;
    for(i = 0; i < SAMPLE_SVP_NNIE_SSD_PRIORBOX_NUM; i++)
    {
        aps32DetectionLocData[i] = aps32PermuteResult[i*2];
    }

    (void)SVP_NNIE_Ssd_DetectionOutForward(pstSoftwareParam->u32ConcatNum,
                                           pstSoftwareParam->u32ConfThresh,pstSoftwareParam->u32ClassNum, pstSoftwareParam->u32TopK,
                                           pstSoftwareParam->u32KeepTopK, pstSoftwareParam->u32NmsThresh,pstSoftwareParam->au32DetectInputChn,
                                           aps32DetectionLocData, aps32PriorboxOutputData, ps32SoftMaxOutputData,
                                           ps32DetectionOutTmpBuf, (HI_S32*)pstSoftwareParam->stDstScore.u64VirAddr,
                                           (HI_S32*)pstSoftwareParam->stDstRoi.u64VirAddr,
                                           (HI_S32*)pstSoftwareParam->stClassRoiNum.u64VirAddr);

    return s32Ret;
}

HI_S32 SSDModel::SDC_SVP_NNIE_Detection_GetResult(SVP_BLOB_S *pstDstScore,
                                        SVP_BLOB_S *pstDstRoi, SVP_BLOB_S *pstClassRoiNum, SDC_SSD_RESULT_S *pstResult)
{
    HI_U32 i = 0, j = 0;
    HI_U32 u32RoiNumBias = 0;
    HI_U32 u32ScoreBias = 0;
    HI_U32 u32BboxBias = 0;
    HI_FLOAT f32Score = 0.0f;
    HI_S32* ps32Score = (HI_S32*)pstDstScore->u64VirAddr;
    HI_S32* ps32Roi = (HI_S32*)pstDstRoi->u64VirAddr;
    HI_S32* ps32ClassRoiNum = (HI_S32*)pstClassRoiNum->u64VirAddr;
    HI_U32 u32ClassNum = pstClassRoiNum->unShape.stWhc.u32Width;
    HI_S32 s32XMin = 0,s32YMin= 0,s32XMax = 0,s32YMax = 0;

    HI_S32 MaxObjectNum = pstResult->numOfObject;
    pstResult->numOfObject = 0;

    u32RoiNumBias += ps32ClassRoiNum[0];
    for (i = 1; i < u32ClassNum; i++)
    {
        u32ScoreBias = u32RoiNumBias;
        u32BboxBias = u32RoiNumBias * SAMPLE_SVP_NNIE_COORDI_NUM;
        /*if the confidence score greater than result threshold, the result will be printed*/
        if((HI_FLOAT)ps32Score[u32ScoreBias] / SAMPLE_SVP_NNIE_QUANT_BASE >=
           pstResult->thresh && ps32ClassRoiNum[i]!=0)
        {
            //           SAMPLE_SVP_TRACE_INFO("==== The %dth class box info====\n", i);
        }
        for (j = 0; j < (HI_U32)ps32ClassRoiNum[i]; j++)
        {
            f32Score = (HI_FLOAT)ps32Score[u32ScoreBias + j] / SAMPLE_SVP_NNIE_QUANT_BASE;
            if (f32Score < pstResult->thresh)
            {
                break;
            }
            s32XMin = ps32Roi[u32BboxBias + j*SAMPLE_SVP_NNIE_COORDI_NUM];
            s32YMin = ps32Roi[u32BboxBias + j*SAMPLE_SVP_NNIE_COORDI_NUM + 1];
            s32XMax = ps32Roi[u32BboxBias + j*SAMPLE_SVP_NNIE_COORDI_NUM + 2];
            s32YMax = ps32Roi[u32BboxBias + j*SAMPLE_SVP_NNIE_COORDI_NUM + 3];
            //SAMPLE_SVP_TRACE_INFO("%d %d %d %d %f\n", s32XMin, s32YMin, s32XMax, s32YMax, f32Score);
            pstResult->pObjInfo[pstResult->numOfObject].clazz = i;
            pstResult->pObjInfo[pstResult->numOfObject].confidence = f32Score;
            pstResult->pObjInfo[pstResult->numOfObject].x_left = s32XMin;
            pstResult->pObjInfo[pstResult->numOfObject].y_top = s32YMin;
            pstResult->pObjInfo[pstResult->numOfObject].x_right = s32XMax;
            pstResult->pObjInfo[pstResult->numOfObject].y_bottom = s32YMax;
            pstResult->pObjInfo[pstResult->numOfObject].w = s32XMax - s32XMin;
            pstResult->pObjInfo[pstResult->numOfObject].h = s32YMax - s32YMin;
            pstResult->numOfObject += 1;
            if(pstResult->numOfObject == MaxObjectNum)
                return HI_SUCCESS;
        }
        u32RoiNumBias += ps32ClassRoiNum[i];
    }
    return HI_SUCCESS;
}

int SSDModel::infer(){
    /*取出数据,方便调用*/
//    META_INFO_S* astMetaInfo = infer_params.astMetaInfo;
//    char* cLabelSendBuf = infer_params.cLabelSendBuf;
//    VW_YUV_FRAME_S* rgb_img = infer_params.rgb_img;
    SDC_SSD_RESULT_S *pstResult= infer_params.pstResult;
    SDC_SSD_INPUT_SIZE_S* InputSize = infer_params.InputSize;
//    char* auTempBuf = infer_params.auTempBuf;
//    char* pYuvImageAddrs = rgb_img[0].pYuvImgAddr;

    if (SDC_SVP_ForwardBGR(pstResult)<0)
    {
        printf("Err in SDC_SVP_ForwardBGR!\n");
        return ERR;
    } else printf("SDC_SVP_ForwardBGR sucess!\n");

    /*清理元数据*/
    m_event_service->SDC_LabelEventDel(0,0);

    UINT32 idx=0,i=0; //统计box数量
    idx = 0;
    memset_s(infer_params.astMetaInfo,sizeof(META_INFO_S) * 10, 0, sizeof(META_INFO_S) * 10);
    for(i = 0; i < pstResult->numOfObject; i++)
    {
        if(pstResult->pObjInfo[i].confidence > infer_params.thresh)//&&  stResult.pObjInfo[i].class==2
        {
            if(pstResult->pObjInfo[i].x_left < 0) pstResult->pObjInfo[i].x_left = 0;
            if(pstResult->pObjInfo[i].y_top < 0) pstResult->pObjInfo[i].y_top = 0;
            if(pstResult->pObjInfo[i].w < 0) pstResult->pObjInfo[i].w = 0;
            if(pstResult->pObjInfo[i].h < 0) pstResult->pObjInfo[i].h = 0;

            printf("Object[%d] class[%u] confidece[%f] {%03d, %03d, %03d, %03d, %03d, %03d}\n",
                   i,
                   pstResult->pObjInfo[i].clazz,
                   pstResult->pObjInfo[i].confidence,
                   pstResult->pObjInfo[i].x_left,
                   pstResult->pObjInfo[i].y_top,
                   pstResult->pObjInfo[i].x_right,
                   pstResult->pObjInfo[i].y_bottom,
                   pstResult->pObjInfo[i].w,
                   pstResult->pObjInfo[i].h);

            //#else
            infer_params.astMetaInfo[idx].uclazz = pstResult->pObjInfo[i].clazz;
            infer_params.astMetaInfo[idx].usX = pstResult->pObjInfo[i].x_left*10000/InputSize->ImageWidth;
            infer_params.astMetaInfo[idx].usY = pstResult->pObjInfo[i].y_top*10000/InputSize->ImageHeight;
            infer_params.astMetaInfo[idx].usWidth = pstResult->pObjInfo[i].w*10000/InputSize->ImageWidth;
            infer_params.astMetaInfo[idx].usHeight = pstResult->pObjInfo[i].h*10000/InputSize->ImageHeight;

            idx++;
            //break;
        }
    }


    return idx;
}


int SSDModel::show(UINT32 idx,char* app_name,UINT64 pts) {
    uint32_t iObjectNum = idx;
    char *pcTemp = NULL;
    int i;
    int iTagLen = 0;
    int iLength=0;
    int iRetCode = PAS;

//    DisplayChannelData(pts, stResult.numOfObject);
    memset_s(cLabelSendBuf,4096, 0, 4096);
    if (iObjectNum > 0)
    {

        pcTemp = cLabelSendBuf;
        *(uint32_t *)pcTemp = 1;//add
        pcTemp += sizeof(uint32_t);

        strcpy_s(pcTemp, 32, app_name); //app name
        pcTemp += 32;

        *(uint64_t *)pcTemp = 0;//id
        pcTemp += sizeof(uint64_t);

        *(uint16_t *)pcTemp = iObjectNum;//polygon_cnt
        pcTemp += sizeof(uint16_t);

        for (i=0; i < iObjectNum; i++)
        {

            *(int32_t *)pcTemp = 0xFF0000;//color = 345455;
            pcTemp += sizeof(int32_t);

            *(int32_t *)pcTemp = 5;//edge_width = 3;
            pcTemp += sizeof(int32_t);

            *(uint32_t *)pcTemp = 0;//pstPolygon->attr = 1;
            pcTemp += sizeof(uint32_t);

            *(int32_t *)pcTemp = 0xFFFFFF;//pstPolygon->bottom_color = 345455;
            pcTemp += sizeof(int32_t);

            *(int32_t *)pcTemp = 0;//pstPolygon->transparency = 128;
            pcTemp += sizeof(int32_t);

            *(int32_t *)pcTemp = 4;//pstPolygon->iPointcnt = 4;
            pcTemp += sizeof(int32_t);


            /*以下是矩形框坐标*/
            *(uint32_t *)pcTemp = astMetaInfo[i].usX;//x1;
            pcTemp += sizeof(uint32_t);

            *(uint32_t *)pcTemp = astMetaInfo[i].usY;//y1;
            pcTemp += sizeof(uint32_t);

            *(uint32_t *)pcTemp = astMetaInfo[i].usX;//x2;
            pcTemp += sizeof(uint32_t);

            *(uint32_t *)pcTemp = astMetaInfo[i].usY + astMetaInfo[i].usHeight;//y2;
            pcTemp += sizeof(uint32_t);

            *(uint32_t *)pcTemp = astMetaInfo[i].usX + astMetaInfo[i].usWidth;//x3;
            pcTemp += sizeof(uint32_t);

            *(uint32_t *)pcTemp = astMetaInfo[i].usY + astMetaInfo[i].usHeight;//y3;
            pcTemp += sizeof(uint32_t);

            *(uint32_t *)pcTemp = astMetaInfo[i].usX + astMetaInfo[i].usWidth;//x4;
            pcTemp += sizeof(uint32_t);

            *(uint32_t *)pcTemp = astMetaInfo[i].usY;//y4;
            pcTemp += sizeof(uint32_t);
        }

        /*给tag_cnt 赋值，一个目标两条字串，置信度和目标*/
        //iObjectNum = 1;
        *pcTemp = iObjectNum * 2;//tag_cnt
        pcTemp++;

        for (i=0; i < iObjectNum; i++)
        {

            *(int32_t *)pcTemp = 0xFF0000;//color = 345455;
            pcTemp += sizeof(int32_t);

            strcpy_s(pcTemp, 32, "宋体"); //font
            pcTemp += 32;

            *(int32_t *)pcTemp = 16;//size
            pcTemp += sizeof(int32_t);

            *(uint32_t *)pcTemp = astMetaInfo[i].usX + 25;//pos-x
            pcTemp += sizeof(uint32_t);

            *(uint32_t *)pcTemp = astMetaInfo[i].usY + 25;//pos-y
            pcTemp += sizeof(uint32_t);

            switch(astMetaInfo[i].uclazz)
            {
                case 1:
                    iTagLen = 20;//sizeof("安全帽");
                    *(uint32_t *)pcTemp = iTagLen;//len
                    pcTemp += sizeof(uint32_t);

                    strcpy_s(pcTemp, 127, "cls1");
                    pcTemp += iTagLen;

                    break;

                case 2:
                    iTagLen = 20;//sizeof("未戴安全帽");
                    *(uint32_t *)pcTemp = iTagLen;//len
                    pcTemp += sizeof(uint32_t);

                    strcpy_s(pcTemp, 127, "cls2");
                    pcTemp += iTagLen;

                    break;

                default:
                    iTagLen = 20;//sizeof("未知");
                    *(uint32_t *)pcTemp = iTagLen;//len
                    pcTemp += sizeof(uint32_t);

                    strcpy_s(pcTemp, 127, "other");
                    pcTemp += iTagLen;

                    //fprintf(stderr, "class:%d\r\n",stResult.pObjInfo[i].class);
                    break;
            }

            *(uint32_t *)pcTemp = 0xFF0000;//color = 345455;
            pcTemp += sizeof(uint32_t);

            strcpy_s(pcTemp, 32, "宋体"); //font
            pcTemp += 32;

            *(uint32_t *)pcTemp = 16;//size
            pcTemp += sizeof(uint32_t);

            *(uint32_t *)pcTemp = astMetaInfo[i].usX + 25;//pos-x
            pcTemp += sizeof(uint32_t);


            *(uint32_t *)pcTemp = astMetaInfo[i].usY + 300;//pos-y
            pcTemp += sizeof(uint32_t);

            /*先增加置信度内容*/

            memset_s(auTempBuf, 32,0,32);
            sprintf(auTempBuf, "Conf: %2.2f%%", (float)astMetaInfo[i].confidence*100);

            iTagLen = sizeof(auTempBuf);
            *(uint32_t *)pcTemp = iTagLen;//len
            pcTemp += sizeof(uint32_t);

            strcpy_s(pcTemp, 32, auTempBuf);
            pcTemp += iTagLen;
        }

        /*超时时间*/
        *pcTemp = 1;
        pcTemp++;
        iLength = (int)(pcTemp - cLabelSendBuf);
        iRetCode = m_event_service->SDC_LabelEventPublish(0, iLength, cLabelSendBuf, pts);
        if (iRetCode != PAS)
        {
            printf("Err in SDC_LabelEventPublish!\n");
        }
    }

}

HI_S32 SSDModel::SVP_NNIE_Overlap(HI_S32 s32XMin1, HI_S32 s32YMin1, HI_S32 s32XMax1, HI_S32 s32YMax1, HI_S32 s32XMin2,
                                  HI_S32 s32YMin2, HI_S32 s32XMax2, HI_S32 s32YMax2, HI_S32 *s32AreaSum,
                                  HI_S32 *s32AreaInter)
{
    HI_S32 s32Inter = 0;
    HI_S32 s32Total = 0;
    HI_S32 s32XMin = 0;
    HI_S32 s32YMin = 0;
    HI_S32 s32XMax = 0;
    HI_S32 s32YMax = 0;
    HI_S32 s32Area1 = 0;
    HI_S32 s32Area2 = 0;
    HI_S32 s32InterWidth = 0;
    HI_S32 s32InterHeight = 0;

    s32XMin = SAMPLE_SVP_NNIE_MAX(s32XMin1, s32XMin2);
    s32YMin = SAMPLE_SVP_NNIE_MAX(s32YMin1, s32YMin2);
    s32XMax = SAMPLE_SVP_NNIE_MIN(s32XMax1, s32XMax2);
    s32YMax = SAMPLE_SVP_NNIE_MIN(s32YMax1, s32YMax2);

    s32InterWidth = s32XMax - s32XMin + 1;
    s32InterHeight = s32YMax - s32YMin + 1;

    s32InterWidth = ( s32InterWidth >= 0 ) ? s32InterWidth : 0;
    s32InterHeight = ( s32InterHeight >= 0 ) ? s32InterHeight : 0;

    s32Inter = s32InterWidth * s32InterHeight;
    s32Area1 = (s32XMax1 - s32XMin1 + 1) * (s32YMax1 - s32YMin1 + 1);
    s32Area2 = (s32XMax2 - s32XMin2 + 1) * (s32YMax2 - s32YMin2 + 1);

    s32Total = s32Area1 + s32Area2 - s32Inter;

    *s32AreaSum = s32Total;
    *s32AreaInter = s32Inter;
    return HI_SUCCESS;
}

HI_S32 SSDModel::SVP_NNIE_NonMaxSuppression(HI_S32 *ps32Proposals, HI_U32 u32AnchorsNum, HI_U32 u32NmsThresh,
                                            HI_U32 u32MaxRoiNum) {

    {
        HI_S32 s32XMin1 = 0;
        HI_S32 s32YMin1 = 0;
        HI_S32 s32XMax1 = 0;
        HI_S32 s32YMax1 = 0;
        HI_S32 s32XMin2 = 0;
        HI_S32 s32YMin2 = 0;
        HI_S32 s32XMax2 = 0;
        HI_S32 s32YMax2 = 0;
        HI_S32 s32AreaTotal = 0;
        HI_S32 s32AreaInter = 0;
        HI_U32 i = 0;
        HI_U32 j = 0;
        HI_U32 u32Num = 0;
        bool bNoOverlap = true;
//    HI_BOOL bNoOverlap  = HI_TRUE;
        for (i = 0; i < u32AnchorsNum && u32Num < u32MaxRoiNum; i++)
        {
            if( ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*i+5] == 0 )
            {
                u32Num++;
                s32XMin1 =  ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*i];
                s32YMin1 =  ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*i+1];
                s32XMax1 =  ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*i+2];
                s32YMax1 =  ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*i+3];
                for(j= i+1;j< u32AnchorsNum; j++)
                {
                    if( ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*j+5] == 0 )
                    {
                        s32XMin2 = ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*j];
                        s32YMin2 = ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*j+1];
                        s32XMax2 = ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*j+2];
                        s32YMax2 = ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*j+3];

                        bNoOverlap = (s32XMin2>s32XMax1)||(s32XMax2<s32XMin1)||(s32YMin2>s32YMax1)||(s32YMax2<s32YMin1);
                        if(bNoOverlap)
                        {
                            continue;
                        }
                        (void)SVP_NNIE_Overlap(s32XMin1, s32YMin1, s32XMax1, s32YMax1, s32XMin2, s32YMin2, s32XMax2, s32YMax2, &s32AreaTotal, &s32AreaInter);
                        if(s32AreaInter*SAMPLE_SVP_NNIE_QUANT_BASE > ((HI_S32)u32NmsThresh*s32AreaTotal))
                        {
                            if( ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*i+4] >= ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*j+4] )
                            {
                                ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*j+5] = 1;
                            }
                            else
                            {
                                ps32Proposals[SAMPLE_SVP_NNIE_PROPOSAL_WIDTH*i+5] = 1;
                            }
                        }
                    }
                }
            }
        }
        return HI_SUCCESS;
    }
}
