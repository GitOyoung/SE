//
// Created by 欧阳建华 on 2017/4/25.
//

#include <se/network/http/client.h>
#include <string>

int main(int argc, char **argv)
{

    se::network::http::Client client;

    auto res = client.get("www.baidu.com").response();



    return 0;
}