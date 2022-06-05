#include <stdio.h>

#include <margv/margv.hpp>

static
void usage()
{
    printf(
        "usage: Session [-d] [-l LIFETIME-SECONDS] [-addr SERVER-ADDRESS] [-message MSG]\n"
        "   {-setup [SERVER-ADDRESS] | -server | -check | -remove} [EPS-NAME]\n\n"
        "These are common Session commands used in various situations:\n\n"
        "working with an XPN session\n"
        "   server [EPS-NAME]         Create a new XPN server instance on localhost with\n"
        "                             EPS-NAME specified as an optional parameter; if not\n"
        "                             specified the default 'EPS0' is used\n"
        "\n"
    );

    exit(1);
}

int main(int argc, char** argv)
{
    margv::argv arg;

    arg.add_optional("server");
    arg.add_optional("setup");
    arg.add_optional("check");
    arg.add_optional("remove");

    arg.add_required("message");

    arg.add("addr", "https://ec2-34-209-177-147.us-west-2.compute.amazonaws.com:8443/stsxpnserver-1.0-SNAPSHOT/stsxpn-servlet");
    arg.add("f", "b");
    arg.add("l", "0");
    arg.add("d");

    if (arg.parse(argc, argv)) usage();

    auto server = arg.get<bool>("server");
    auto setup  = arg.get<bool>("setup");
    auto check  = arg.get<bool>("check");
    auto remove = arg.get<bool>("remove");
    auto debug  = arg.get<bool>("d");

    using namespace std;

    auto address  = arg.get<string>("addr");
    auto message  = arg.get<string>("message");
    auto flags    = arg.get<string>("f");

    return 0;
}

