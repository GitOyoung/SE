//
// Created by 欧阳建华 on 2017/4/25.
//
#include <se/network/http/client.h>
#include <se/network/http/request.h>
#include <iostream>


int main(int argc, char **argv)
{

    se::network::http::Client http;

//    se::network::http::Request req("https://api-cn.faceplusplus.com/facepp/v3/detect");//    req.header("Content-Type", "application/json;charset=UTF-8");
    se::network::http::Request req("https://www.faceplusplus.com.cn/api/official/demo/facepp/v3/detect");//    req.header("Content-Type", "application/json;charset=UTF-8");

    std::string body;
//
//    req.header("Cache-Control", " no-cache");
//    req.header("Content-Type", " multipart/form-data; boundary=-----WebKitFormBoundary7MA4YWxkTrZu0gW");
//    body.append("-----WebKitFormBoundary7MA4YWxkTrZu0gW").append("\r\n");
//    body.append("Content-Disposition: form-data; name=\"").append("image_url\"\r\n\r\n")
//            .append("https://www.faceplusplus.com.cn/images/detection/group-case.jpg\r\n");
//    body.append("-----WebKitFormBoundary7MA4YWxkTrZu0gW").append("\r\n");
//    body.append("Content-Disposition: form-data; name=\"").append("return_attributes\"\r\n\r\n")
//            .append("gender,age\r\n");
//    body.append("-----WebKitFormBoundary7MA4YWxkTrZu0gW--");


    req.header("Content-Type", "multipart/form-data");

    se::network::http::Request::FormData formData;
    formData.type = se::network::http::Request::FORM_NAME_FILE;
    formData.name = "image_file";
    formData.file = "./timg.jpeg";
    req.formdata(formData);


    auto res = http.post(req).response();

    body = res.body();

    std::cout << body << std::endl;

    return 0;
}