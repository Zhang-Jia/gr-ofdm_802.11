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

#include <iostream>

#include <gnuradio/io_signature.h>

//#include "short_match_filter_impl.h"

//#include <ofdm_80211/cdshort_match_filter_impl.h>
#include "short_match_filter_impl.h"
#include <gnuradio/filter/fir_filter.h>

#include <gnuradio/fft/fft.h>


#include <list>
#include <tuple>

using namespace gr::ofdm_80211;
using namespace std;


namespace gr {
  namespace ofdm_80211 {

    short_match_filter::sptr
    short_match_filter::make()
    {
      return gnuradio::get_initial_sptr
        (new short_match_filter_impl());
    }

    /*
     * The private constructor
     */
    short_match_filter_impl::short_match_filter_impl(): 
		block("short_match_filter",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(gr_complex) ) 
               ), 	kefir(gr::filter::kernel::fir_filter_ccc(1, CORTO))
              
    {  auto it0 = pea_mem.begin();
	   for(int k = 0; k<160 ; k++){
			preamble_memory[k] = gr_complex( 0.0 + k  ,  0.0);
            it0 = pea_mem.insert ( it0 ,         gr_complex( 159 - k  ,0.0)      );
       
       };
       d_correlation = gr::fft::malloc_complex(8192);
       //pea_mem.assign (160,     gr_complex(00000, 0000)  );
       
    }

    /*
     * Our virtual destructor.
     */
    short_match_filter_impl::~short_match_filter_impl()
    {
    }

    void
    short_match_filter_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        /* <+forecast+> e.g. ninput_items_required[0] = noutput_items */
	ninput_items_required[0] = noutput_items;
	//ninput_items_required[0] = 16;
    }

    int
    short_match_filter_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const gr_complex *in = (const gr_complex*) input_items[0];
        
	gr_complex *out = (gr_complex*)output_items[0];
	

        // Do <+signal processing+>
		//kefir.filterN(out, in, std::min(SYNC_LENGTH, std::max(ninput - 63, 0)));
		
		kefir.filterN(d_correlation, in, noutput_items  );
		
		//out = outfir;
		cout << "sizeof(out)"<< sizeof(out)  << "noutput_items " << noutput_items << endl;
		
		//cout << "noutput_items " << noutput_items << "sizeof(preamble_memory)" <<sizeof(preamble_memory)     << endl;

		for(int i= 0; i < noutput_items; i++){
			pea_mem.at(0)=  d_correlation[i];
			aver = d_correlation[i];
			    for ( auto it = pea_mem.begin() + 16; it < pea_mem.end(); it+=16 )  aver += *it;
                	//cout << ' '  << *it ;
                	
		    out[i] = aver;
		    
		    std::rotate( pea_mem.begin(), pea_mem.begin()+1, pea_mem.end());
		    //if(i<16 ){ cout << "preamble_short[" <<  i<< "] ="<<preamble_short[i] <<endl;    }
		    //if(i<16 ){ cout << "preamble_memory[" <<  i<< "] ="<<preamble_memory[i] <<endl;    }
		    //cout << " -" <<endl;
		    if (i==1010){ 
					//std::vector<gr_complex> myvector = {        gr_complex(  0.03125000,0.03125),
					//gr_complex( -0.08997779,0.00158944),
					//gr_complex( -0.00915291,-0.05334709) };
       
                //for ( auto it = pea_mem.begin() + 16; it < pea_mem.end(); it+=16 ) 
                	//cout << ' '  << *it ;
				    //std::vector<int>::iterator it;

				    //auto it2 = myvector.begin();
				    //it2 = myvector.insert ( it2 ,         gr_complex(  0.03125000,0.03125)      );

				  ////myvector.insert (it,2,300);
                  //std::rotate( myvector.begin(), myvector.begin()+2, myvector.end());                
                  
				  //std::cout << "pea_mem contains:" << endl;
				  //for ( auto it = pea_mem.begin(); it != pea_mem.end(); ++it ) 	cout << ' '  << *it ;
					//cout<< "sais" << myvector.size() << "";
				  //std::cout << '\n'; }
					//cout << "" << endl;
			}
		}	
		
		
		
		
        // Tell runtime system how many input items we consumed on
        // each input stream.
        consume_each (noutput_items);

        // Tell runtime system how many output items we produced.
        return noutput_items;
    }

  } /* namespace ofdm_80211 */
} /* namespace gr */



const std::vector<gr_complex> short_match_filter_impl::CORTO = {
       gr_complex(  0.03125000,0.03125),
       gr_complex( -0.08997779,0.00158944),
       gr_complex( -0.00915291,-0.05334709), 
       gr_complex(  0.09698312,-0.00859478),
       gr_complex(  0.06250000,0.0 )       ,  
       gr_complex(  0.09698312,-0.00859478),
       gr_complex( -0.00915291,-0.05334709), 
       gr_complex( -0.08997779,0.00158944),
       gr_complex(  0.03125000,0.03125)   ,  
       gr_complex(  0.00158944,-0.08997779),
       gr_complex( -0.05334709,-0.00915291), 
       gr_complex( -0.00859478,0.09698312),
       gr_complex( 0.00000000,0.0625 )   , 
       gr_complex(  -0.00859478,0.09698312),
       gr_complex( -0.05334709,-0.00915291), 
       gr_complex(  0.00158944,-0.08997779)
       };
       
       
const int short_match_filter_impl::terito = 66;

const gr_complex short_match_filter_impl::concom = gr_complex( 1.3868,  0.0000);

const int short_match_filter_impl::arreglo[4] = {1,2,3,4};

//const std::vector<int> short_match_filter_impl::vectorint = {1, 2, 3, 4};

const gr_complex short_match_filter_impl::preamble_short[16] =  {
       gr_complex(  0.03125000,0.03125),
       gr_complex( -0.08997779,0.00158944),
       gr_complex( -0.00915291,-0.05334709), 
       gr_complex(  0.09698312,-0.00859478),
       gr_complex(  0.06250000,0.0 )       ,  
       gr_complex(  0.09698312,-0.00859478),
       gr_complex( -0.00915291,-0.05334709), 
       gr_complex( -0.08997779,0.00158944),
       gr_complex(  0.03125000,0.03125)   ,  
       gr_complex(  0.00158944,-0.08997779),
       gr_complex( -0.05334709,-0.00915291), 
       gr_complex( -0.00859478,0.09698312),
       gr_complex( 0.00000000,0.0625 )   , 
       gr_complex(  -0.00859478,0.09698312),
       gr_complex( -0.05334709,-0.00915291), 
       gr_complex(  0.00158944,-0.08997779)
       };
       

//std::vector<gr_complex> short_match_filter_impl::pea =    
//{      gr_complex(  0.03125000,0.03125),
       //gr_complex( -0.08997779,0.00158944),
       //gr_complex( -0.00915291,-0.05334709), 
       //gr_complex(  0.09698312,-0.00859478),
       //gr_complex(  0.06250000,0.0 )       ,  
       //gr_complex(  0.09698312,-0.00859478),
       //gr_complex( -0.00915291,-0.05334709), 
       //gr_complex( -0.08997779,0.00158944),
       //gr_complex(  0.03125000,0.03125)   ,  
       //gr_complex(  0.00158944,-0.08997779),
       //gr_complex( -0.05334709,-0.00915291), 
       //gr_complex( -0.00859478,0.09698312),
       //gr_complex( 0.00000000,0.0625 )   , 
       //gr_complex(  -0.00859478,0.09698312),
       //gr_complex( -0.05334709,-0.00915291), 
       //gr_complex(  0.00158944,-0.08997779)
       //};

//const std::vector<gr_complex> short_match_filter_impl::CORTO = {

//gr_complex( 1.3868,  0.0000), gr_complex(-0.0455, -1.0679), gr_complex( 0.3528, -0.9865), gr_complex( 0.8594,  0.7348),
//gr_complex( 0.1874,  0.2475), gr_complex( 0.5309, -0.7784), gr_complex(-1.0218, -0.4897), gr_complex(-0.3401, -0.9423),
//gr_complex( 0.8657, -0.2298), gr_complex( 0.4734,  0.0362), gr_complex( 0.0088, -1.0207), gr_complex(-1.2142, -0.4205),
//gr_complex( 0.2172, -0.5195), gr_complex( 0.5207, -0.1326), gr_complex(-0.1995,  1.4259), gr_complex( 1.0583, -0.0363),
//gr_complex( 0.5547, -0.5547), gr_complex( 0.3277,  0.8728), gr_complex(-0.5077,  0.3488), gr_complex(-1.1650,  0.5789),
//gr_complex( 0.7297,  0.8197), gr_complex( 0.6173,  0.1253), gr_complex(-0.5353,  0.7214), gr_complex(-0.5011, -0.1935),
//gr_complex(-0.3110, -1.3392), gr_complex(-1.0818, -0.1470), gr_complex(-1.1300, -0.1820), gr_complex( 0.6663, -0.6571),
//gr_complex(-0.0249,  0.4773), gr_complex(-0.8155,  1.0218), gr_complex( 0.8140,  0.9396), gr_complex( 0.1090,  0.8662),
//gr_complex(-1.3868,  0.0000), gr_complex( 0.1090, -0.8662), gr_complex( 0.8140, -0.9396), gr_complex(-0.8155, -1.0218),
//gr_complex(-0.0249, -0.4773), gr_complex( 0.6663,  0.6571), gr_complex(-1.1300,  0.1820), gr_complex(-1.0818,  0.1470),
//gr_complex(-0.3110,  1.3392), gr_complex(-0.5011,  0.1935), gr_complex(-0.5353, -0.7214), gr_complex( 0.6173, -0.1253),
//gr_complex( 0.7297, -0.8197), gr_complex(-1.1650, -0.5789), gr_complex(-0.5077, -0.3488), gr_complex( 0.3277, -0.8728),
//gr_complex( 0.5547,  0.5547), gr_complex( 1.0583,  0.0363), gr_complex(-0.1995, -1.4259), gr_complex( 0.5207,  0.1326),
//gr_complex( 0.2172,  0.5195), gr_complex(-1.2142,  0.4205), gr_complex( 0.0088,  1.0207), gr_complex( 0.4734, -0.0362),
//gr_complex( 0.8657,  0.2298), gr_complex(-0.3401,  0.9423), gr_complex(-1.0218,  0.4897), gr_complex( 0.5309,  0.7784),
//gr_complex( 0.1874, -0.2475), gr_complex( 0.8594, -0.7348), gr_complex( 0.3528,  0.9865), gr_complex(-0.0455,  1.0679)

//};
