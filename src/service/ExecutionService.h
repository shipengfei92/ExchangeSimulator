#pragma once



class ExecutionService {
private:

    ExecutionService(const ExecutionService&) = delete;

public:
    static ExecutionService& getInstance();


};