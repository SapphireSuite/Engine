// Copyright (c) 2022 Sapphire's Suite. All Rights Reserved.

#pragma once

#ifndef SAPPHIRE_ENGINE_ASHADER_GUARD
#define SAPPHIRE_ENGINE_ASHADER_GUARD

#include <SA/Engine/HI/HardwareInterface.hpp>

#include <SA/Engine/Render/Base/Shader/RawShader.hpp>

namespace Sa
{
    class AShader : protected HardwareInterface
    {
        using HardwareInterface::Clear; // not used.
    };
}

#endif // GUARD
