#include <data/data.hpp>
#include <string>

class global_var : public crank::data
{
protected:
    global_var() = default;

public:
    explicit global_var(int n, const std::string& s) 
    : num(n) 
    , str(s)
    {}

    static global_var* instance()
    { return &m_globals; }

private:

    static global_var m_globals;

public:

    int num;
    std::string str;
};