//
//  DirtyWordFilter.h
//  HoolaiEngine
//
//  Created by liji  on 14-1-18.
//  Copyright (c) 2014年 Hoolai. All rights reserved.
//

#ifndef __HoolaiEngine__DirtyWordFilter__
#define __HoolaiEngine__DirtyWordFilter__

#include <string>
#include "dart.h"

#define I_WORD_LEN_MAX 512
class DirtyWordFilter{
//private:
public:
    DirtyWordFilter();
    
    char pszDes[I_WORD_LEN_MAX];
public:
    Darts::DoubleArray da;
    bool bLoad;
    
    ~DirtyWordFilter();
    
    bool loadDic(const char* dicPath);
    
    //替换strsrc中的敏感词，返回值为包含敏感词的个数
    int replaceDirtyWords(std::string strSrc, std::string &strDesc);
    
    //检查是否包含敏感词
    bool checkHasDirtyWord(std::string strSrc);
};

#endif /* defined(__HoolaiEngine__DirtyWordFilter__) */
