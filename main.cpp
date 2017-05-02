//
// Created by 欧阳建华 on 2017/4/25.
//
#include <se/network/http/client.h>
#include <se/network/http/request.h>
#include <iostream>


int main(int argc, char **argv)
{

    se::network::http::Client client;

    se::network::http::Request req("http://www.tuling123.com/openapi/api");
    req.header("Content-Type", "application/json;charset=UTF-8");

    req.body("{ \"key\":\"f7b67526c4395f273abd6ea0fc8f2e20\", \"info\":\"吃饭啦\", \"loc\":\"紫金创业园\", \"userid\":\"123456\"}");


        auto res = client.post(req).response();

        auto body = res.body();

        std::cout << body << std::endl;

    return 0;
}