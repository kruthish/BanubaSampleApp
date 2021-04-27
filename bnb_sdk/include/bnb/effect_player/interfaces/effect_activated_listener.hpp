/// \file
/// \addtogroup EffectPlayer
/// @{
///
// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from effect_player.djinni

#pragma once

#include <bnb/utils/defs.hpp>
#include <string>

namespace bnb { namespace interfaces {

/** Interface to receive notifications on effect change */
class BNB_EXPORT effect_activated_listener {
public:
    virtual ~effect_activated_listener() {}

    /** called when effect is activated */
    virtual void on_effect_activated(const std::string & url) = 0;
};

} }  // namespace bnb::interfaces
/// @}
