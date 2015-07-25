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

#ifndef INCLUDED_OFDM_80211_SHORT_MATCH_FILTER_IMPL_H
#define INCLUDED_OFDM_80211_SHORT_MATCH_FILTER_IMPL_H

#include <ofdm_80211/short_match_filter.h>

#include <gnuradio/filter/fir_filter.h>

#include <gnuradio/fft/fft.h>



namespace gr {
  namespace ofdm_80211 {

    class short_match_filter_impl : public short_match_filter
    {
     private:
       //std::vector<gr_complex> vector_complejo;
       static const std::vector<gr_complex> CORTO;
       static const std::vector<gr_complex> UNOS;
       static const gr_complex concom;
       static const int terito;
       static const int arreglo[4];
       static const gr_complex preamble_short[16];
       gr_complex preamble_memory[160];
       gr_complex aver;
       gr_complex ma_power;
       
       gr_complex *d_correlation;
       gr_complex *d_p;
       
       //std::array<gr_complex,160> preamble_memory;
       std::vector<gr_complex> pea_mem;
       std::vector<gr_complex> pow_mem;
       
       static const std::vector<int> vectorint;

       
       gr::filter::kernel::fir_filter_ccc kefir;
       gr::filter::kernel::fir_filter_ccc mafir;

     public:
      short_match_filter_impl();
      ~short_match_filter_impl();

      // Where all the action really happens
      
    
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
		       gr_vector_int &ninput_items,
		       gr_vector_const_void_star &input_items,
		       gr_vector_void_star &output_items);
    };

  } // namespace ofdm_80211
} // namespace gr

#endif /* INCLUDED_OFDM_80211_SHORT_MATCH_FILTER_IMPL_H */

