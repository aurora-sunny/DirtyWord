//
//  DirtyWordFilter.cpp
//  HoolaiEngine
//
//  Created by liji  on 14-1-18.
//  Copyright (c) 2014年 Hoolai. All rights reserved.
//

#include "DirtyWordFilter.h"

#define ONE_BYTE 0x8
#define TWO_BYTE 0x12
#define THREE_BYTE 0x14
#define FOUR_BYTE 0x15

DirtyWordFilter::DirtyWordFilter():bLoad(false)
{
    
}

DirtyWordFilter::~DirtyWordFilter()
{
}

bool DirtyWordFilter::loadDic(const char* dicPath = "dirty.dic")
{
//    const char* path = hoolai::HLResourceManager::getSingleton()->getSysPathForFile(dicPath);
    if (da.open(dicPath)) {
//		HLLOG("Error: open %s", dicPath);
		return false;
	}
    bLoad = true;
    return true;
}

bool DirtyWordFilter::checkHasDirtyWord(std::string strSrc)
{
    if (!bLoad)
	{
		return false;
	}
    const char* pszSrc = strSrc.c_str();
	size_t nLen = strlen(pszSrc);
	size_t nNum;
    size_t nIndex = 0;
    size_t cLen = 0;
    
	Darts::DoubleArray::result_pair_type pResult[I_WORD_LEN_MAX];
    
	while(nIndex < nLen)
	{
		nNum = da.commonPrefixSearch(pszSrc + nIndex, pResult, I_WORD_LEN_MAX, nLen - nIndex);
        
		if (nNum)
		{
            return true;
		}
        else
        {
            if (((*(pszSrc + nIndex) & 0xfe) == 0xfc)) {
                cLen = 6;
            }
            else if (((*(pszSrc + nIndex) & 0xfc) == 0xf8)) {
                cLen = 5;
            }
            else if (((*(pszSrc + nIndex) & 0xf8) == 0xf0)) {
                cLen = 4;
            }
            else if (((*(pszSrc + nIndex) & 0xf0) == 0xe0)) {
                cLen = 3;
            }
            else if (((*(pszSrc + nIndex) & 0xe0) == 0xc0)) {
                cLen = 2;
            }
            else {
                cLen = 1;
            }
            nIndex += cLen;
        }
	} //while
    return false;
}

int DirtyWordFilter::replaceDirtyWords(std::string strSrc, std::string &strDesc)
{
    if (!bLoad)
	{
		strDesc = strSrc;
		return 0;
	}
    
    const char* pszSrc = strSrc.c_str();
	size_t nLen = strlen(pszSrc);
	size_t nNum;
    size_t nIndex = 0;
    size_t nPos = 0;
    size_t maxMatchLen = 0;
    size_t cLen = 0;
    int dirtyWordNum = 0;
    
	Darts::DoubleArray::result_pair_type pResult[I_WORD_LEN_MAX];

	memset(pszDes, 0, I_WORD_LEN_MAX);
    
	while(nIndex < nLen)
	{
		nNum = da.commonPrefixSearch(pszSrc + nIndex, pResult, I_WORD_LEN_MAX, nLen - nIndex);
        
		if (nNum)
		{
            for (size_t i = 0; i < nNum; ++i) {
				
//                std::string dW;
//                for (int m = 0; m < pResult[i].length; m++) {
//                    dW += *(pszSrc + nIndex + m);
//                }
//                HLLOG("%s, %lu", dW.c_str(), pResult[i].length);
                
                if (maxMatchLen < pResult[i].length) {
                    maxMatchLen = pResult[i].length;
                }
			}
            nIndex += maxMatchLen;
            maxMatchLen = 0;
            strncpy(pszDes + nPos, "***", 3);
            nPos += 3;
            dirtyWordNum++;
		}
        else
        {
            if (((*(pszSrc + nIndex) & 0xfe) == 0xfc)) {
                cLen = 6;
            }
            else if (((*(pszSrc + nIndex) & 0xfc) == 0xf8)) {
                cLen = 5;
            }
            else if (((*(pszSrc + nIndex) & 0xf8) == 0xf0)) {
                cLen = 4;
            }
            else if (((*(pszSrc + nIndex) & 0xf0) == 0xe0)) {
                cLen = 3;
            }
            else if (((*(pszSrc + nIndex) & 0xe0) == 0xc0)) {
                cLen = 2;
            }
            else {
                cLen = 1;
            }
            strncpy(pszDes + nPos, pszSrc + nIndex, cLen);
            nPos += cLen;
            nIndex += cLen;
        }
	} //while
    strDesc = pszDes;
    return dirtyWordNum;
}