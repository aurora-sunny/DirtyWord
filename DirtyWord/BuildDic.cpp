//
//  build.cpp
//  used for building Dirty Word dic
//
//  Created by liji  on 14-1-18.
//  Copyright (c) 2014年 Hoolai. All rights reserved.
//

#include "DirtyWordFilter.h"

#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 

using namespace std;

int progress_bar(size_t current, size_t total) {
	static char bar[] = "*******************************************";
	static int scale = sizeof(bar) - 1;
	static int prev = 0;

	int cur_percentage  = static_cast<int>(100.0 * current/total);
	int bar_len         = static_cast<int>(1.0   * current*scale/total);

	if (prev != cur_percentage) {
		printf("Making Dic: %3d%% |%.*s%*s| ",
			cur_percentage, bar_len, bar, scale - bar_len, "");
		if (cur_percentage == 100)  printf("\n");
		else                        printf("\r");
		fflush(stdout);
	}

	prev = cur_percentage;

	return 1;
};

int build(const char* sensewordList, const char* sensewordDic) 
{
	std::string file  = sensewordList;
	std::string index = sensewordDic;

	Darts::DoubleArray da;

	std::vector<const char *> key;
	std::istream *is;

	is = new std::ifstream(file.c_str());
	if (!*is) {
		std::cerr << "Cannot Open: " << file << std::endl;
		return -1;
	}

	//sort the dic*
	vector<string> vecDic;
	std::string line;
	while (std::getline(*is, line)) {
        if (line.length() < 1) {
            std::cout << "空行\n";
            continue;
        }
		std::cout << line << std::endl;
        auto itr = std::find(vecDic.begin(), vecDic.end(), line);
        if (itr != vecDic.end())
        {
            continue;
            std::cout << "重复" << std::endl;
        }
		vecDic.push_back(line);
	}
	sort (vecDic.begin(), vecDic.end());
	//sort end
 
	const char ** pStrAry = (const char **)malloc (vecDic.size() * sizeof(char *));  
	vector<string>::iterator pIter = vecDic.begin();  
	int i = 0;  
	while (pIter != vecDic.end())  
	{  
		pStrAry[i] = (char*)pIter->c_str();  
		pIter++;  
		i++;  
	}

	if (da.build(vecDic.size(), pStrAry, 0, 0, &progress_bar) != 0
		|| da.save(index.c_str()) != 0) {
			std::cerr << "Error: cannot build dic  " << file << std::endl;
			return -1;
	};

	// 	for (unsigned int i = 0; i < key.size(); i++)
	// 		delete [] key[i];

	std::cout << "Done!, Compression Ratio: " <<
		100.0 * da.nonzero_size() / da.size() << " %" << std::endl;

	return 0;
}
