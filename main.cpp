//
// Created by 欧阳建华 on 2017/4/25.
//



#include <se/facepp/faceplusplus.h>
#include <se/facepp/faceset.h>

int main(int argc, char **argv)
{


    se::facepp::FacePlusPlus facepp;
    if(facepp.load("./facepp_config.json"))
    {
        auto faceset = facepp.createFaceSet("faceset_20170505", "test_20170505").faceSet();
        if(faceset.token().empty() && faceset.outerId().empty()) {
            faceset.reload();
        }
        auto faces = facepp.detect("./timg.jpeg", se::facepp::FacePlusPlus::IMAGE_FILE).faces();
        se::facepp::AddFaceResult result;

        if(!faces.empty()) {
            std::string faceToken = faces[0].faceToken();
            for(auto& face: faces) {
                faceset.add(face.faceToken(), result);
            }

            faceset.search(faceToken);
        }

    }


    return 0;
}