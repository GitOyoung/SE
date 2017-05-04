//
// Created by 欧阳建华 on 2017/4/25.
//



#include <se/facepp/faceplusplus.h>

int main(int argc, char **argv)
{


    se::facepp::FacePlusPlus facepp;
    if(facepp.load("./facepp_config.json"))
    {
        facepp.detect("./timg.jpeg", se::facepp::FacePlusPlus::IMAGE_FILE);
    }


    return 0;
}