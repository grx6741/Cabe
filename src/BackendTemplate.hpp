#pragma once

#include "IBackend.hpp"

#define CABE_BACKEND_TEMPLATE                                                  \
  public:                                                                      \
    void Populate(const std::string& content) override;                        \
    std::string Dump() override;

#define CABE_BACKEND_TEMPLATE_CREATOR(name)                                    \
    inline std::unique_ptr<IBackend> createBackend()                           \
    {                                                                          \
        return std::make_unique<name>();                                       \
    }