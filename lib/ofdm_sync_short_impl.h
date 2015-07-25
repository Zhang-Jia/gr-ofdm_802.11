/* -*- c++ -*- */
/* 
 * Copyright 2015 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_OFDM_80211_OFDM_SYNC_SHORT_IMPL_H
#define INCLUDED_OFDM_80211_OFDM_SYNC_SHORT_IMPL_H

#include <ofdm_80211/ofdm_sync_short.h>

namespace gr {
  namespace ofdm_80211 {

    class ofdm_sync_short_impl : public ofdm_sync_short
    {
    private:
      	enum {SEARCH, COPY} d_state;
		int d_copied;
		int d_plateau;
		float d_freq_offset;
		const double d_threshold;
		const bool d_log;
		const bool d_debug;
		const unsigned int MIN_PLATEAU;
      // Nothing to declare in this block.

     public:
      ofdm_sync_short_impl(double threshold, unsigned int min_plateau, bool log, bool debug);
      ~ofdm_sync_short_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace ofdm_80211
} // namespace gr

#endif /* INCLUDED_OFDM_80211_OFDM_SYNC_SHORT_IMPL_H */

