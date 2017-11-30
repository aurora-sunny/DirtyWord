//
//  main.cpp
//  DirtyWord
//
//  Created by liji  on 14-2-11.
//  Copyright (c) 2014年 hoolai. All rights reserved.
//

#include <iostream>

extern int build(const char* sensewordList, const char* sensewordDic);

int main(int argc, const char * argv[])
{

    if (argc != 3) {
        std::cout << "DirtyWord sensewordListFile sensewordDicFile" << std::endl;
        return -1;
    }
    
//    build(argv[1], argv[2]);
    
    build("/Users/hoolai/Downloads/DirtyWord/dirty.txt", "/Users/hoolai/Downloads/DirtyWord/dirty.dic");
    
    return 0;
}

