//
// Created by liuky on 2020-08-07.
//

#include "SSDModel.hpp"

SSDModel::SSDModel(AlgorithmService *algorithm_service , UtilsService *utils_service,SVP_NNIE_MODEL_WITH_FILE_S *model){
    m_algorithm_service = algorithm_service;
    m_utils_service = utils_service;
    ssd_model = model;
}

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
            DEBUG_LOG("u32TotalStep: %i",u32TotalStep);
            SVP_NNIE_GetBlobMemSize(&(m_nnie_param->pstModel->astSeg[i].astSrcNode[0]),/*来自SVP_NNIE_MODEL_S结构体的第i个Seg下的第一个输入节点blob[0]的指针*/
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
    if (s32Ret!=HI_SUCCESS){
        DEBUG_LOG("ERR: SVP_NNIE_FillForwardInfo failed.");
        return ERR;
    }
    //2. 获取任务信息和Blob所需的内存大小---------------------------------------------------------------------------------
    s32Ret = SVP_NNIE_GetTaskAndBlobBufSize(astBlobSize, &u32TotalSize);
    if (s32Ret!=HI_SUCCESS){
        DEBUG_LOG("ERR: SVP_NNIE_GetTaskAndBlobBufSize failed.");
        return ERR;
    }
    /*Malloc mem*/
    //3. 申请SDC内存地址到stMemParas中-----------------------------------------------------------------------------------
    s32Ret = m_utils_service->SDC_MemAlloc(u32TotalSize, &stMemParas);
    if(s32Ret<0){
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
        u32PriorBoxSize += m_model_software_param->au32PriorBoxHeight[i] * m_model_software_param->au32PriorBoxWidth[i] *
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
    HI_U32 u32ClassNum = 9;//分类数
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
                    SAMPLE_SVP_NNIE_ALIGN16(m_model_software_param->au32ConvChannel[i] * sizeof(HI_U32)) / sizeof(HI_U32);
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
    s32Ret=m_utils_service->SDC_MemAlloc(u32TotalSize, &stMemParas);
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
                         m_model_software_param->stSoftMaxTmpBuf.u32Size + m_model_software_param->stGetResultTmpBuf.u32Size;

    /*set result blob*/
    m_model_software_param->stDstRoi.enType = SVP_BLOB_TYPE_S32;
    m_model_software_param->stDstRoi.u64PhyAddr = u64PhyAddr + u32TmpBufTotalSize;
    m_model_software_param->stDstRoi.u64VirAddr = (HI_U64) (pu8VirAddr + u32TmpBufTotalSize);
    m_model_software_param->stDstRoi.u32Stride = SAMPLE_SVP_NNIE_ALIGN16(u32ClassNum*
                                                                                 m_model_software_param->u32TopK * sizeof(HI_U32) *
                                                                                 SAMPLE_SVP_NNIE_COORDI_NUM);
    m_model_software_param->stDstRoi.u32Num = 1;
    m_model_software_param->stDstRoi.unShape.stWhc.u32Chn = 1;
    m_model_software_param->stDstRoi.unShape.stWhc.u32Height = 1;
    m_model_software_param->stDstRoi.unShape.stWhc.u32Width = u32ClassNum *
                                                              m_model_software_param->u32TopK * SAMPLE_SVP_NNIE_COORDI_NUM;

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

    if (0 != m_model_software_param->stPriorBoxTmpBuf.u64PhyAddr && 0 != m_model_software_param->stPriorBoxTmpBuf.u64VirAddr) {
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

int SSDModel::ssd_param_init(HI_U32 max_input_num, HI_U32 max_roi_num){
    //NNIE模块初始化，并加载模型结构
    int nnie_ret = 0;
    m_nnie_cfg->u32MaxInputNum = max_input_num;
    m_nnie_cfg->u32MaxRoiNum = max_roi_num;
    /*这里写死了使用内核0*/
    m_nnie_cfg->aenNnieCoreId[0] = SVP_NNIE_ID_0;
    m_nnie_param->pstModel = &ssd_model->stModel;

    nnie_ret = SVP_NNIE_Ssd_ParamInit();
    if (nnie_ret!=PAS){
        printf("svp nnie param init fail.\n");
        return ERR;
    } else printf("svp nnie param init success.\n");
    return PAS;


}

