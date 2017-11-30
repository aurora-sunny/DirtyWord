//
//  main.cpp
//  Test
//
//  Created by liji  on 14-3-3.
//  Copyright (c) 2014年 hoolai. All rights reserved.
//

#include <iostream>
#include "DirtyWordFilter.h"
#include <string>

int main(int argc, const char * argv[])
{
    DirtyWordFilter * dwFilter = new DirtyWordFilter();
    if(!dwFilter->loadDic("/Users/liji/SQ2/Projects/DirtyWord/exec/dirty.dic"))
    {
        std::cout << "load dic error\n";
        return -1;
    }
    
    std::string dw;
//    while (1) {
//        std::cout << "input :";
//        std::cin>>dw;
//        if(dw == "jj")
//            break;
//        
//        if(dwFilter->checkHasDirtyWord(dw))
//            std::cout << "Has Dirty Word\n";
//        else
//            std::cout << "clean\n";
//    }
    
    dw = "习 大大 颛孙 鸡把alksdjfj";
    bool bFind = dwFilter->checkHasDirtyWord(dw);
    if(bFind)
       std::cout << "Has Dirty Word\n";
    
//    std::cout << "Hello, World!\n";
    return 0;
}

