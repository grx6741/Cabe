#pragma once

#include "IFrontend.hpp"

#define CABE_FRONTEND_TEMPLATE                                                 \
  public:                                                                      \
    void PollEvent(Cabe::EventPayload& event) override;                        \
    bool IsRunning() override;                                                 \
    void RenderContent(const std::vector<Cabe::File>& files) override;

#define CABE_FRONTEND_TEMPLATE_CREATOR(name)                                   \
    inline std::unique_ptr<IFrontend> createFrontend()                         \
    {                                                                          \
        return std::make_unique<name>();                                       \
    }