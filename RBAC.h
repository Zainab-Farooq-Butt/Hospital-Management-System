#pragma once
#include <string>
using namespace std;

class RBAC {
public:
    static bool hasAccess(string role, string feature);
};