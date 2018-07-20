#pragma once
#include <memory>
#include <pfs/griotte/point.hpp>
#include <pfs/griotte/line.hpp>
#include <pfs/griotte/path.hpp>
#include <pfs/griotte/pen.hpp>
#include <pfs/griotte/error.hpp>

namespace pfs {
namespace griotte {

/**
 * \class painter
 * \brief The painter class performs low-level painting on paint devices.
 */
template <typename Backend>
class painter
{
    std::unique_ptr<Backend> _d;

private:
    painter (Backend * backend) : _d(backend) {}

public:
    painter () = delete;
    painter (painter const &) = delete;
    painter & operator = (painter const &) = delete;
    painter (painter && ) = default;
    painter & operator = (painter && ) = default;

    /**
     * @fn void painter::draw_line (point const & p1, point const & p2, pen const & apen)
     * @brief Draws a line from point @a p1 to point @a p2 using pen @a apen.
     * @param p1 The start point.
     * @param p2 The end point.
     */
    template <typename UnitT>
    inline void draw_line (point<UnitT> const & p1
            , point<UnitT> const & p2
            , pen<UnitT> const & apen)
    {
        _d->draw_line<UnitT>(p1, p2, apen);
    }

    /**
     * @fn void painter::draw_line (line const & aline, pen const & apen)
     * @brief Draws a line defined by @a aline.
     * @param aline The line to draw.
     */
    template <typename UnitT>
    void draw_line (line<UnitT> const & aline
            , pen<UnitT> const & apen)
    {
        draw_line(aline.get_start_point()
                , aline.get_end_point()
                , apen);
    }

    /**
     *
     */
    template <typename UnitT>
    void draw_curve (point<UnitT> const & start_point
            , point<UnitT> const & c1
            , point<UnitT> const & c2
            , point<UnitT> const & end_point
            , pen<UnitT> const & apen)
    {
        _d->draw_curve(start_point, c1, c2, end_point, apen);
    }

    template <typename BackendU, typename ...Args>
    friend inline painter<BackendU> make_painter (Args... args)
    {
        return painter<BackendU>(new BackendU(std::forward<Args...>(args...)));
    }
};

}} // namespace pfs::griotte
