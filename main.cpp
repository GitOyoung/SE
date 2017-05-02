//
// Created by 欧阳建华 on 2017/4/25.
//
#include <se/network/http/client.h>
#include <se/network/http/request.h>
#include <iostream>


int main(int argc, char **argv)
{

    se::network::http::Client http;

    se::network::http::Request req("https://api-cn.faceplusplus.com/facepp/v3/detect");//    req.header("Content-Type", "application/json;charset=UTF-8");
//
//    req.body("{ \"key\":\"f7b67526c4395f273abd6ea0fc8f2e20\", \"info\":\"吃饭啦\", \"loc\":\"紫金创业园\", \"userid\":\"123456\"}");

    req.header("Content-Type", "multipart/formdata");

    req.query("api_key", "78MCSFFqMIN_LoPPB0-K5QadTq2a0ZQb");
    req.query("api_secret", "SpowA-Z4s_7_kwtqPlRRoGNZTQ9uyUug");
//    req.formdata("api_key", "78MCSFFqMIN_LoPPB0-K5QadTq2a0ZQb");
//    req.formdata("api_secret", "SpowA-Z4s_7_kwtqPlRRoGNZTQ9uyUug");
    se::network::http::Request::FormData fdata;
    fdata.type = se::network::http::Request::FORM_NAME_FILE_FILENAME_CONTENTTYPE;
    fdata.file = "timg.jpeg";
    fdata.fileName = "timg.jpeg";
    fdata.contentType = "image/jpeg";
    req.formdata("image_file", fdata);

    auto res = http.post(req).response();

    auto body = res.body();

    std::cout << body << std::endl;

    return 0;
}