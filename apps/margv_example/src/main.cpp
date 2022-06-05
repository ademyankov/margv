#include <stdio.h>

#include <margv/margv.hpp>

#include <string>

using namespace std;

static
void usage()
{
    printf(
        "usage: margv [-d] [-s] STRING [-l] VALUE\n"
        "             { -optA [param], -optB [param], -req param }\n\n"
        "These are common examples how to use it:\n"
        "\n"
        "-optA [param]          An exclusive optional switch with an optional parameter \n"
        "-optB [param]\n"
        "\n"
        "-req param             An exclusive optional switch with a required parameter\n"
        "\n"
        "[-d]                   An optional simple true switch\n"
        "\n"
        "[-s] string            An optional switch with a required parameter;\n"
        "[-l] param             if not present the default value is used\n"
        "\n"
    );

    exit(1);
}

int main(int argc, char** argv)
{
    margv::argv arg;

    // An exclusive optional switch with an optional parameter;
    arg.add_optional("optA");
    arg.add_optional("optB");

    // An exclusive optional switch with a required parameter;
    // has empty string if not present
    arg.add_required("req");

    // An optional simple true switch; false if not present
    arg.add_switch("d");

    // An optional switch with a required parameter;
    // if not present the default value is used
    arg.add("s", "default string");
    arg.add("l", "42");

    if (arg.parse(argc, argv)) usage();

    auto optA = arg.get<bool>("optA");
    auto optB = arg.get<bool>("optB");
    auto req  = arg.get<bool>("req");
    auto d    = arg.get<bool>("d");
    auto s    = arg.get<string>("s");
    auto l    = arg.get<int>("l");

    if (optA) printf("optA: %s\n", arg.get<string>("optA").c_str());
    if (optB) printf("optB: %s\n", arg.get<string>("optB").c_str());
    if (req)  printf("req: %s\n", arg.get<string>("req").c_str());

    printf("d: %s\n", d ? "true" : "false");
    printf("s: %s\n", s.c_str());
    printf("l: %d\n", l);

    return 0;
}

