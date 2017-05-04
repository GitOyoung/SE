#include <se/facepp/faceset.h>


namespace se {
    namespace facepp {


        FaceSet::FaceSet() {}


        std::string FaceSet::displayName() const {
            return data.displayName;
        }

        std::string FaceSet::outerId() const {
            return data.outerId;
        }

        std::string FaceSet::token() const {
            return data.token;
        }

        int FaceSet::faceAdded() const {
            return data.faceAdded;
        }

        int FaceSet::faceCount() const {
            return data.faceCount;
        }

        std::vector<std::string> FaceSet::faceTokens() const {
            return data.faceTokens;
        }

        bool FaceSet::add(const std::string &faceToken) {
            bool ret = false;
            //TODO
            return ret;
        }

        bool FaceSet::update() {
            bool ret = false;
            //TODO
            return ret;
        }


        SearchResult FaceSet::search(const std::string &faceToken) {
            SearchResult result;
            //TODO



            return result;
        }

    }
}