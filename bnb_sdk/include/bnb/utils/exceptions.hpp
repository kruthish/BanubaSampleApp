#pragma once

#include <bnb/utils/defs.hpp>

#include <stdexcept>
#include <string>
#include <iostream>


#if BNB_OS_EMSCRIPTEN
    #define BNB_THROW(exception, message)                             \
        std::cout << "BanubaSDK Exception: " << message << std::endl; \
        _BNB_THROW(exception, message)

    #define BNB_THROW_DOMAIN(exception, domain, message)                               \
        std::cout << "BanubaSDK Exception:" << domain << ": " << message << std::endl; \
        _BNB_THROW_DOMAIN(exception, domain, message)
#else
    #define BNB_THROW(exception, message) \
        _BNB_THROW(exception, message)

    #define BNB_THROW_DOMAIN(exception, domain, message) \
        _BNB_THROW_DOMAIN(exception, domain, message)
#endif

#define _BNB_THROW(exception, message) \
    throw exception(std::string("At ") + __FILE__ + ":" + std::to_string(__LINE__) + ". " + message)

#define _BNB_THROW_DOMAIN(exception, domain, message) \
    throw exception(                                  \
        domain,                                       \
        std::string("At ") + __FILE__ + ":" + std::to_string(__LINE__) + ". " + message)

namespace bnb
{
    class domain_specific_data
    {
    public:
        const char* domain() const noexcept
        {
            return m_domain.c_str();
        }
        virtual ~domain_specific_data() = default;

    protected:
        explicit domain_specific_data(std::string domain) noexcept
            : m_domain(std::move(domain))
        {
        }
        std::string m_domain;
    };

    class runtime_error : public std::runtime_error, public domain_specific_data
    {
    public:
        runtime_error(std::string domain, std::string message) noexcept
            : std::runtime_error(message)
            , domain_specific_data(std::move(domain))
        {
        }
    };

    class logic_error : public std::logic_error, public domain_specific_data
    {
    public:
        logic_error(std::string domain, std::string message) noexcept
            : std::logic_error(message)
            , domain_specific_data(std::move(domain))
        {
        }
    };

    class resource_loading_error : public bnb::runtime_error
    {
    public:
        resource_loading_error(
            std::string domain, std::string message, std::string resource) noexcept
            : bnb::runtime_error(std::move(domain), message + ". For: " + resource)
            , m_resource(std::move(resource))
        {
        }

        const char* resource() const noexcept
        {
            return m_resource.c_str();
        }

    protected:
        std::string m_resource;
    };
} // namespace bnb
