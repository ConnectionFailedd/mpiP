#ifndef __TRACE_HPP__
#define __TRACE_HPP__

#include <memory>
#include <string>
#include <utility>
#include <vector>

class ArgumentValue {};

class TraceEntry {
private:
    std::string __functionName;
    std::vector<std::pair<std::string, std::shared_ptr<ArgumentValue>>> __arguments;
};

class Trace {
private:
    std::vector<TraceEntry> __trace;

public:
    void load(const std::string & traceFileName);

    inline auto begin() { return __trace.begin(); }
    inline auto end() { return __trace.end(); }
};

#endif