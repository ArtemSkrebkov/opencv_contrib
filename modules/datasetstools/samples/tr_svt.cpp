/*M///////////////////////////////////////////////////////////////////////////////////////
//
//  IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING.
//
//  By downloading, copying, installing or using the software you agree to this license.
//  If you do not agree to this license, do not download, install,
//  copy or use the software.
//
//
//                           License Agreement
//                For Open Source Computer Vision Library
//
// Copyright (C) 2014, Itseez Inc, all rights reserved.
// Third party copyrights are property of their respective owners.
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistribution's of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//
//   * Redistribution's in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//
//   * The name of the copyright holders may not be used to endorse or promote products
//     derived from this software without specific prior written permission.
//
// This software is provided by the copyright holders and contributors "as is" and
// any express or implied warranties, including, but not limited to, the implied
// warranties of merchantability and fitness for a particular purpose are disclaimed.
// In no event shall the Itseez Inc or contributors be liable for any direct,
// indirect, incidental, special, exemplary, or consequential damages
// (including, but not limited to, procurement of substitute goods or services;
// loss of use, data, or profits; or business interruption) however caused
// and on any theory of liability, whether in contract, strict liability,
// or tort (including negligence or otherwise) arising in any way out of
// the use of this software, even if advised of the possibility of such damage.
//
//M*/

#include "opencv2/datasetstools/tr_svt.hpp"

#include <opencv2/core.hpp>

#include <cstdio>
#include <cstdlib> // atoi

#include <string>
#include <vector>

using namespace std;
using namespace cv;
using namespace cv::datasetstools;

int main(int argc, char *argv[])
{
    const char *keys =
            "{ help h usage ? |    | show this message }"
            "{ path p         |true| path to dataset xml files }";
    CommandLineParser parser(argc, argv, keys);
    string path(parser.get<string>("path"));
    if (parser.has("help") || path=="true")
    {
        parser.printMessage();
        return -1;
    }

    // loading train & test images description
    Ptr<TR_svt> dataset = TR_svt::create();
    dataset->load(path);

    // ***************
    // dataset. train & test contains images description.
    // For example, let output the last element in train set and it's description.
    // And their sizes.
    printf("train size: %u\n", (unsigned int)dataset->getTrain().size());
    printf("test size: %u\n", (unsigned int)dataset->getTest().size());

    TR_svtObj *example = static_cast<TR_svtObj *>(dataset->getTrain().back().get());
    printf("last element:\nfile name: %s", example->fileName.c_str());
    printf("\nlex: ");
    for (vector<string>::iterator it=example->lex.begin(); it!=example->lex.end(); ++it)
    {
        printf("%s,", (*it).c_str());
    }
    printf("\ntags:\n");
    for (vector<tag>::iterator it=example->tags.begin(); it!=example->tags.end(); ++it)
    {
        tag &t = (*it);
        printf("%s\nheight: %u, width: %u, x: %u, y: %u\n",
               t.value.c_str(), t.height, t.width, t.x, t.y);
    }

    return 0;
}
