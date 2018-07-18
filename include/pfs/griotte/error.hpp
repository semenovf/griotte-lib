#pragma once
#include <system_error>
#include <stdexcept>

namespace pfs {
namespace griotte {

enum class errc
{
      success = 0
    , bad_path
};

class error_category : public std::error_category
{
public:
    virtual char const * name () const noexcept override
    {
        return "pfs::griotte";
    }

    virtual std::string message (int ev) const override;
};

std::error_category const & category ();

inline std::error_code make_error_code (errc e)
{
    return std::error_code(static_cast<int>(e), category());
}

class exception : public std::logic_error
{
public:
    exception (errc ec)
        : std::logic_error(make_error_code(ec).message())
    {}

    exception (errc ec, char const * s)
        : std::logic_error(make_error_code(ec).message() + ": " + s)
    {}

    exception (errc ec, std::string const & s)
        : std::logic_error(make_error_code(ec).message() + ": " + s)
    {}

    exception (std::error_code const & ec)
        : std::logic_error(ec.message())
    {}

    exception (std::error_code const & ec, char const * s)
        : std::logic_error(ec.message() + ": " + s)
    {}

    exception (std::error_code const & ec, std::string const & s)
        : std::logic_error(ec.message() + ": " + s)
    {}
};

#ifdef PFS_GRIOTTE_SOURCE

std::string error_category::message (int ev) const
{
    switch (static_cast<griotte::errc>(ev)) {
    case griotte::errc::success: return std::string("no error");
    case griotte::errc::bad_path: return std::string("bad path");
    default: return std::string("unknown pfs::griotte error");
    }
}

std::error_category const & category ()
{
    static error_category instance;
    return instance;
}

#endif

}} // namespace pfs::griotte
