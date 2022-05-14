// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#include <Render/Base/ARenderInterface.hpp>

namespace SA
{
    void ARenderInterface::Create(const AWindowInterface* _winIntf)
    {
        HardwareInterface::Create();
        
        (void)_winIntf;
    }
}
