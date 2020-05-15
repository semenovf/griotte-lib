////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2020 Vladislav Trifochkin
//
// This file is part of [pfs-griotte](https://github.com/semenovf/pfs-griotte) library.
//
// Changelog:
//      2020.04.26 Initial version
////////////////////////////////////////////////////////////////////////////////
#include "glyph.hpp"
#include "ft2build.h"
#include FT_FREETYPE_H
#include <utility>

namespace pfs {
namespace griotte {

class context;

enum class font_style
{
      normal
    , italic
    , bold
    , unknown
};

class font
{
    friend class context;

    FT_Face _face {nullptr};

private:
    font (FT_Face face)
    {
        _face = face;
    }

public:
    font () = default;
    font (font const &) = delete;
    font & operator = (font const &) = delete;

    font (font && other)
    {
        swap(other);
    }

    font & operator = (font && other)
    {
        font tmp;
        tmp.swap(other);
        tmp.swap(*this);
        return *this;
    }

    ~font ()
    {
        FT_Done_Face(_face);
    }

    operator bool ()
    {
        return _face != nullptr;
    }

    void swap (font & other)
    {
        using std::swap;
        swap(_face, other._face);
    }

    ////////////////////////////////////////////////////////////////////////////
    // Font info
    ////////////////////////////////////////////////////////////////////////////

    font_style style () const
    {
        switch (_face->style_flags) {
            case 0: return font_style::normal;
            case 1: return font_style::italic;
            case 2: return font_style::bold;
            default:
                break;
        }

        return font_style::unknown;
    }

    std::string style_name () const
    {
        return _face->style_name ? std::string{_face->style_name} : std::string{};
    }

    std::string family_name () const
    {
        return _face->family_name ? std::string{_face->family_name} : std::string{};
    }

    int glyphs_count () const
    {
        return _face ? _face->num_glyphs : -1;
    }

    bool is_scalable () const
    {
        return _face ? (_face->face_flags & FT_FACE_FLAG_SCALABLE) : false;
    }

    bool has_kerning () const
    {
        return _face ? (_face->face_flags & FT_FACE_FLAG_KERNING) : false;
    }

    /**
     * @return The number of font units covered by the EM.
     */
    int units_per_em () const
    {
        return (_face->face_flags & FT_FACE_FLAG_SCALABLE) ? _face->units_per_EM : 0;
    }

    /**
     * @return Number of embedded bitmap strikes in the face.
     */
    int strikes_count () const
    {
        return _face->num_fixed_sizes;
    }

    int charmaps_count () const
    {
        return _face->num_charmaps;
    }

    ////////////////////////////////////////////////////////////////////////////
    // Font operations
    ////////////////////////////////////////////////////////////////////////////

    /*   FT_LOAD_DEFAULT
     *   FT_LOAD_RENDER
     *   FT_LOAD_MONOCHROME
     *   FT_LOAD_LINEAR_DESIGN
     *   FT_LOAD_NO_SCALE
     *   FT_LOAD_NO_HINTING
     *   FT_LOAD_NO_BITMAP
     *   FT_LOAD_NO_AUTOHINT
     *   FT_LOAD_COLOR
     *
     *   FT_LOAD_VERTICAL_LAYOUT
     *   FT_LOAD_IGNORE_TRANSFORM
     *   FT_LOAD_FORCE_AUTOHINT
     *   FT_LOAD_NO_RECURSE
     *   FT_LOAD_PEDANTIC
     *
     *   FT_LOAD_TARGET_NORMAL
     *   FT_LOAD_TARGET_LIGHT
     *   FT_LOAD_TARGET_MONO
     *   FT_LOAD_TARGET_LCD
     *   FT_LOAD_TARGET_LCD_V
     *
     *   FT_LOAD_TARGET_MODE
     */
    glyph load_glyph (uint32_t uc, int pixel_size)
    {
        bool ok = true;
        return load_glyph(uc, pixel_size, ok);
    }

    glyph load_glyph (uint32_t uc, int pixel_size, bool & ok)
    {
        auto ec = FT_Set_Pixel_Sizes(_face, 0, pixel_size);

        if (ec != 0) {
            ok = false;
            return glyph{};
        }

        ec = FT_Load_Char(_face, uc, FT_LOAD_RENDER);

        if (ec != 0) {
            ok = false;
            return glyph{};
        }

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        unsigned int texture_id;
        glGenTextures(1, & texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexImage2D(GL_TEXTURE_2D                // target
                , 0                               // level
                , GL_RED                          // internalFormat
                , _face->glyph->bitmap.width      // width
                , _face->glyph->bitmap.rows       // height
                , 0                               // border
                , GL_RED                          // format
                , GL_UNSIGNED_BYTE                // type
                , _face->glyph->bitmap.buffer);   // pixels

        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glyph result{texture_id};
        result.set_size(_face->glyph->bitmap.width, _face->glyph->bitmap.rows);
        result.set_bearings(_face->glyph->bitmap_left, _face->glyph->bitmap_top);

        // The horizontal distance (in 1/64th pixels) from the origin to the
        // origin of the next glyph
        result.set_advance(_face->glyph->advance.x);

        return result;
    }
};

inline std::string to_string (font_style value)
{
    switch (value) {
        case font_style::normal:
            return "normal";
        case font_style::italic:
            return "italic";
        case font_style::bold:
            return "bold";
        default:
            break;
    }

    return "unknown";
}

}} // namespace pfs::griotte
