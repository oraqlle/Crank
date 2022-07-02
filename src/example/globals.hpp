#include <crank/crank.hpp>
#include <string>

class global_vars : public crank::data
{
protected:
    global_vars() = default;

public:
    explicit global_vars(int n, const std::string& s) 
    : num(n) 
    , str(s)
    {}

    static global_vars* instance()
    { return &m_globals; }

private:

    static global_vars m_globals;

public:

    int num;
    std::string str;
};