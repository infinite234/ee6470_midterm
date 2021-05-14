#include <cmath>
#ifndef NATIVE_SYSTEMC
#include "stratus_hls.h"
#endif

#include "SobelFilter.h"

SobelFilter::SobelFilter( sc_module_name n ): sc_module( n )
{

	SC_THREAD( do_filter );
	sensitive << i_clk.pos();
	dont_initialize();
	reset_signal_is(i_rst, false);
        
#ifndef NATIVE_SYSTEMC
	i_r.clk_rst(i_clk, i_rst);
 i_g.clk_rst(i_clk, i_rst);
 i_b.clk_rst(i_clk, i_rst);
  o_resultr.clk_rst(i_clk, i_rst);
  o_resultg.clk_rst(i_clk, i_rst);
  o_resultb.clk_rst(i_clk, i_rst);
#endif
}

SobelFilter::~SobelFilter() {}

// sobel mask
const int mask[MASK_Y][MASK_X] = {
{-1, -1, 0},
{-1, 0, 1},
{0, 1, 1}
};

void SobelFilter::do_filter() {
   				sc_dt::sc_uint<8> r;
        sc_dt::sc_uint<8> g;
        sc_dt::sc_uint<8> b;
	{
#ifndef NATIVE_SYSTEMC
		HLS_DEFINE_PROTOCOL("main_reset");
		i_r.reset();
   i_g.reset();
   i_b.reset();
		o_resultr.reset();
    o_resultg.reset();
    o_resultb.reset();
#endif
		wait();
	}
	while (true) {
		for (unsigned int i = 0; i<3; ++i) {
			HLS_CONSTRAIN_LATENCY(0, 1, "lat00");
			val[i] = 0;
      		
		}
   int tot = 0;
   int bias =128;
		for (unsigned int v = 0; v<MASK_Y; ++v) {
			for (unsigned int u = 0; u<MASK_X; ++u) {

#ifndef NATIVE_SYSTEMC
				{
					HLS_DEFINE_PROTOCOL("input");
					r = i_r.get();
          g = i_g.get();
          b = i_b.get();
					wait();
				}
#else
				r = i_r.read();
        g = i_g.read();
        b = i_b.read();
#endif
				//unsigned char grey = (rgb.range(7,0) + rgb.range(15,8) + rgb.range(23, 16))/3;
					// HLS_CONSTRAIN_LATENCY(0, 6, "lat01");
          HLS_UNROLL_LOOP (ALL,"SHIFT");
					val[0] += r * mask[u][v];
          val[1]+= g * mask[u][v];
          val[2]+= b * mask[u][v];
          
          tot += mask[u][v];
				
			}
		}
    //HLS_CONSTRAIN_LATENCY(0, 8, "lat01");
			 val[0] = int(std::min(std::max(int(val[0] + bias), 0), 255));
			 val[1] = int(std::min(std::max(int(val[1] + bias), 0), 255));
			 val[2] = int(std::min(std::max(int(val[2] + bias), 0), 255));

#ifndef NATIVE_SYSTEMC
		{
			HLS_DEFINE_PROTOCOL("output");
			o_resultr.put(val[0]);
      o_resultg.put(val[1]);
      o_resultb.put(val[2]);
			wait();
		}
#else
		o_resultr.write(val[0]);
   o_resultg.write(val[1]);
   o_resultb.write(val[2]);
#endif
	}
}
