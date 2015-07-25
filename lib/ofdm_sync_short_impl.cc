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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "ofdm_sync_short_impl.h"

namespace gr {
  namespace ofdm_80211 {

    ofdm_sync_short::sptr
    ofdm_sync_short::make(double threshold, unsigned int min_plateau, bool log, bool debug)
    {
      return gnuradio::get_initial_sptr
        (new ofdm_sync_short_impl(threshold, min_plateau, log, debug));
    }

    /*
     * The private constructor
     */
    ofdm_sync_short_impl::ofdm_sync_short_impl(double threshold, unsigned int min_plateau, bool log, bool debug)
      : gr::block("ofdm_sync_short",
			gr::io_signature::make3(3, 3, sizeof(gr_complex), sizeof(gr_complex), sizeof(float)),
			gr::io_signature::make(1, 1, sizeof(gr_complex))),
		d_log(log),
		d_debug(debug),
		d_state(SEARCH),
		d_plateau(0),
		d_freq_offset(0),
		d_copied(0),
		MIN_PLATEAU(min_plateau),
		d_threshold(threshold)
		{
			set_tag_propagation_policy(block::TPP_DONT);
        }

    /*
     * Our virtual destructor.
     */
    ofdm_sync_short_impl::~ofdm_sync_short_impl()
    {
    }

    void
    ofdm_sync_short_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
        ninput_items_required[0] = noutput_items;
    }

    int
    ofdm_sync_short_impl::general_work(int noutput_items, gr_vector_int& ninput_items,
		gr_vector_const_void_star& input_items,
		gr_vector_void_star& output_items) {

	const gr_complex *in = (const gr_complex*)input_items[0];
	const gr_complex *in_abs = (const gr_complex*)input_items[1];
	const float *in_cor = (const float*)input_items[2];
	gr_complex *out = (gr_complex*)output_items[0];

	int noutput = noutput_items;
	int ninput = std::min(std::min(ninput_items[0], ninput_items[1]), ninput_items[2]);

	// dout << "SHORT noutput : " << noutput << " ninput: " << ninput_items[0] << std::endl;
		int i;

   		for(i = 0; i < ninput; i++) {
			if(in_cor[i] > d_threshold) {
			out[i] = in[i] + in_abs[i]  ;
			} 
			else{
				out[i] = in[i] ;
			}			
		}
	
	consume_each(i);	
	return i;
   }

  } /* namespace ofdm_80211 */
} /* namespace gr */

