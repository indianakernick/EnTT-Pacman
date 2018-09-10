//
//  console color.hpp
//  Simpleton Engine
//
//  Created by Indi Kernick on 24/6/18.
//  Copyright © 2018 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_console_color_hpp
#define engine_utils_console_color_hpp

#include <cstdint>
#include <cassert>
#include <iostream>
#include <string_view>

#define ESC "\x1B"
#define CSI "\x1B["
#define CONSTR constexpr std::string_view

namespace con {
  // commented constants aren't supported by the MacOS Terminal or iTerm2

  /// Reset all formatting states to their default values. Disable italic and
  /// underline, set text color and background colors to their defaults, etc.
  CONSTR reset         = CSI "0m";
  
  /// Either change to a bolder font, use a brighter text color or both
  CONSTR bold          = CSI "1m";
  /// Either change to a lighter font, use a dimmer text color or both
  CONSTR faint         = CSI "2m";
  /// Change font to an italic one [iTerm2 but not Terminal.app]
  CONSTR italic        = CSI "3m";
  /// Put a line underneath text
  CONSTR underline     = CSI "4m";
  /// Blink text slowly [Terminal.app but not iTerm2]
  CONSTR blink_slow    = CSI "5m";
  /// Set text color to background color and background color to text color
  CONSTR video_neg     = CSI "7m";
  /// Hide or "conceal" text [Terminal.app but not iTerm2]
  CONSTR conceal       = CSI "8m";
  
  /*
  CONSTR blink_fast    = CSI "6m";
  CONSTR strikethrough = CSI "9m";
  CONSTR primaryFont   = CSI "10m";
  CONSTR altFont[9] = {
    CSI "11m",
    CSI "12m",
    CSI "13m",
    CSI "14m",
    CSI "15m",
    CSI "16m",
    CSI "17m",
    CSI "18m",
    CSI "19m"
  };
  CONSTR fraktur       = CSI "20m";
  */
  
  /// Disable bold and faint modes
  CONSTR no_bold_faint = CSI "22m";
  /// Disable italic mode [iTerm2 but not Terminal.app]
  CONSTR no_italic     = CSI "23m";
  /// Disable underline mode
  CONSTR no_underline  = CSI "24m";
  /// Undo the effects of `video_neg`
  CONSTR video_pos     = CSI "27m";
  /// Undo the effects of `conceal` and show the text [Terminal.app but not iTerm2]
  CONSTR reveal        = CSI "28m";
  
  // CONSTR no_blink      = CSI "25m";
  // CONSTR no_strike     = CSI "29m";

  /// Set text color to black
  CONSTR text_black    = CSI "30m";
  /// Set text color to red
  CONSTR text_red      = CSI "31m";
  /// Set text color to green
  CONSTR text_green    = CSI "32m";
  /// Set text color to yellow
  CONSTR text_yellow   = CSI "33m";
  /// Set text color to blue
  CONSTR text_blue     = CSI "34m";
  /// Set text color to magenta
  CONSTR text_magenta  = CSI "35m";
  /// Set text color to cyan
  CONSTR text_cyan     = CSI "36m";
  /// Set text color to white
  CONSTR text_white    = CSI "37m";
  /// Set text color to its default
  CONSTR text_default  = CSI "39m";
  
  /// Set background color to black
  CONSTR back_black    = CSI "40m";
  /// Set background color to red
  CONSTR back_red      = CSI "41m";
  /// Set background color to green
  CONSTR back_green    = CSI "42m";
  /// Set background color to yellow
  CONSTR back_yellow   = CSI "43m";
  /// Set background color to blue
  CONSTR back_blue     = CSI "44m";
  /// Set background color to magenta
  CONSTR back_magenta  = CSI "45m";
  /// Set background color to cyan
  CONSTR back_cyan     = CSI "46m";
  /// Set background color to white
  CONSTR back_white    = CSI "47m";
  /// Set background color to its default
  CONSTR back_default  = CSI "49m";
  
  /*
  CONSTR frame         = CSI "51m";
  CONSTR encircle      = CSI "52m";
  CONSTR overline      = CSI "53m";
  CONSTR no_frame_circ = CSI "54m";
  CONSTR no_overline   = CSI "55m";
  */
  
  namespace detail {
    template <bool Back>
    struct color_256 {
      constexpr explicit color_256(const unsigned index)
        : index{index} {
        assert(index < 256);
      }
      
    private:
      unsigned index;
      
      friend std::ostream &operator<<(std::ostream &stream, const color_256 color) {
        if constexpr (Back) {
          stream << CSI "48;5;";
        } else {
          stream << CSI "38;5;";
        }
        return stream << color.index << 'm';
      }
    };
  }
  
  /// Set the text color using RGB values between 0-5. This is part of
  /// 256-color mode
  constexpr auto text_rgb_6(const unsigned r, const unsigned g, const unsigned b) {
    assert(r < 6);
    assert(g < 6);
    assert(b < 6);
    return detail::color_256<false>{16 + 36 * r + 6 * g + b};
  }
  
  /// Set the background color using RGB values between 0-5. This is part of
  /// 256-color mode
  constexpr auto back_rgb_6(const unsigned r, const unsigned g, const unsigned b) {
    assert(r < 6);
    assert(g < 6);
    assert(b < 6);
    return detail::color_256<true>{16 + 36 * r + 6 * g + b};
  }
  
  /// Set the text color to one of 24 shades of gray where 0 is black and 23 is
  /// white. This is part of 256-color mode
  constexpr auto text_gray_24(const unsigned gray) {
    assert(gray < 24);
    return detail::color_256<false>{232 + gray};
  }
  
  /// Set the background color to one of 24 shades of gray where 0 is black and
  /// 23 is white. This is part of 256-color mode
  constexpr auto back_gray_24(const unsigned gray) {
    assert(gray < 24);
    return detail::color_256<true>{232 + gray};
  }
  
  namespace detail {
    template <bool Back>
    struct color_24bit {
      constexpr color_24bit(const unsigned r, const unsigned g, const unsigned b)
        : r{r}, g{g}, b{b} {}
    
    private:
      unsigned r, g, b;
      
      friend std::ostream &operator<<(std::ostream &stream, const color_24bit color) {
        if constexpr (Back) {
          stream << CSI "48;2;";
        } else {
          stream << CSI "38;2;";
        }
        return stream << color.r << ';' << color.g << ';' << color.b << 'm';
      }
    };
  }
  
  /// Set the text color to one of 24 shades of gray where 0 is black and 23 is
  /// white. This is part of 24-bit color mode [iTerm2 but not Terminal.app]
  constexpr auto text_rgb_256(const unsigned r, const unsigned g, const unsigned b) {
    assert(r < 256);
    assert(g < 256);
    assert(b < 256);
    return detail::color_24bit<false>{r, g, b};
  }
  
  /// Set the background color using RGB values between 0-255. This is part of
  /// 24-bit color mode [iTerm2 but not Terminal.app]
  constexpr auto back_rgb_256(const unsigned r, const unsigned g, const unsigned b) {
    assert(r < 256);
    assert(g < 256);
    assert(b < 256);
    return detail::color_24bit<true>{r, g, b};
  }
  
  namespace detail {
    template <char Suffix>
    struct number {
      constexpr explicit number(const unsigned num)
        : num{num} {}
      
    private:
      unsigned num;
      
      friend std::ostream &operator<<(std::ostream &stream, const number n) {
        return stream << CSI << n.num << Suffix;
      }
    };
  }
  
  /// Move the cursor up n lines
  constexpr auto cursor_up(const unsigned n = 1) {
    return detail::number<'A'>{n};
  }
  /// Move the cursor down n lines
  constexpr auto cursor_down(const unsigned n = 1) {
    return detail::number<'B'>{n};
  }
  /// Move the cursor forward (right) n characters
  constexpr auto cursor_forward(const unsigned n = 1) {
    return detail::number<'C'>{n};
  }
  /// Move the cursor back (left) n characters
  constexpr auto cursor_back(const unsigned n = 1) {
    return detail::number<'D'>{n};
  }
  
  /// Move the cursor to the beginning of the line n lines down
  constexpr auto cursor_next_line(const unsigned n = 1) {
    return detail::number<'E'>{n};
  }
  /// Move the cursor to the beginning of the line n lines up
  constexpr auto cursor_prev_line(const unsigned n = 1) {
    return detail::number<'F'>{n};
  }
  /// Move the cursor to column n on the current line
  constexpr auto cursor_column(const unsigned n = 1) {
    return detail::number<'G'>{n};
  }
  
  namespace detail {
    template <char Suffix>
    struct row_col {
      constexpr row_col(const unsigned row, const unsigned col)
        : row{row}, col{col} {}
      
    private:
      unsigned row, col;
      
      friend std::ostream &operator<<(std::ostream &stream, const row_col rc) {
        return stream << CSI << rc.row << ';' << rc.col << Suffix;
      }
    };
  }
  
  /// Move the cursor to a row and column
  constexpr auto cursor_pos(const unsigned row, const unsigned col) {
    return detail::row_col<'H'>{row, col};
  }
  
  /// Clear characters from the cursor to the end of the screen
  CONSTR erase_end_screen = CSI "0J";
  /// Clear characters from the cursor to the beginning of the screen
  CONSTR erase_beg_screen = CSI "1J";
  /// Clear all characters on the screen
  CONSTR erase_screen     = CSI "2J";
  
  /// Clear characters from the cursor to the end of the line
  CONSTR erase_end_line   = CSI "0K";
  /// Clear characters from the cursor to the beginning of the line
  CONSTR erase_beg_line   = CSI "1K";
  /// Clear all characters on the line
  CONSTR erase_line       = CSI "2K";
  
  /// Scroll the page up by n lines
  constexpr auto scroll_up(const unsigned n = 1) {
    return detail::number<'S'>{n};
  }
  /// Scroll the page down by n lines
  constexpr auto scroll_down(const unsigned n = 1) {
    return detail::number<'T'>{n};
  }
  
  /// Write the cursor position to stdin to later be read
  CONSTR ask_cursor_pos = CSI "6n";
  
  struct row_col {
    unsigned r, c;
  };
  
  inline row_col read_cursor_pos() {
    row_col rc;
    char ch;
    std::cin >> ch;
    assert(ch == ESC[0]);
    std::cin >> ch;
    assert(ch == '[');
    std::cin >> rc.r;
    std::cin >> ch;
    assert(ch == ';');
    std::cin >> rc.c;
    std::cin >> ch;
    assert(ch == 'R');
    return rc;
  }
  
  /// Save the position of the cursor to be later restored
  CONSTR save_cursor    = CSI "s";
  /// Restore the position of the cursor that was previously saved
  CONSTR restore_cursor = CSI "u";
  
  /// Hide the cursor to be later shown
  CONSTR hide_cursor    = CSI "?25l";
  /// Show the cursor that was previously hidden
  CONSTR show_cursor    = CSI "?25h";
}

#undef CONSTR
#undef CSI
#undef ESC

#endif
