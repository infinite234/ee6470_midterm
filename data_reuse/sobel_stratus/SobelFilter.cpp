#include <cmath>
#ifndef NATIVE_SYSTEMC
#include "stratus_hls.h"
#endif

#include "SobelFilter.h"

SobelFilter::SobelFilter( sc_module_name n ): sc_module( n )
{
#ifndef NATIVE_SYSTEMC
	//HLS_FLATTEN_ARRAY(val);
#endif
	SC_THREAD( do_filter );
	sensitive << i_clk.pos();
	dont_initialize();
	reset_signal_is(i_rst, false);
        
#ifndef NATIVE_SYSTEMC
	i_rgb.clk_rst(i_clk, i_rst);
  o_result.clk_rst(i_clk, i_rst);
#endif
}

SobelFilter::~SobelFilter() {}

/*// SHARPEN
const int mask[MASK_Y][MASK_X] = {
{1, 1, 1},
{1, -7, 1},
{1, 1, 1}
};*/


/*// emboss
const int mask[MASK_Y][MASK_X] = {
{-1, -1, 0},
{-1, 0, 1},
{0, 1, 1}
};*/

// emboss
const int mask[MASK_Y][MASK_X] =
{
  -1, -1, -1, -1,  0,
  -1, -1, -1,  0,  1,
  -1, -1,  0,  1,  1,
  -1,  0,  1,  1,  1,
   0,  1,  1,  1,  1
};


/*// SHARPEN
const int mask[MASK_Y][MASK_X] = {
{2, 0, 0},
{0, 1, 0},
{0, 0, -1}
};*/

void SobelFilter::do_filter() {
	{
#ifndef NATIVE_SYSTEMC
		HLS_DEFINE_PROTOCOL("main_reset");
		i_rgb.reset();
		o_result.reset();
#endif
		wait();
	}
	while (true) {
			HLS_CONSTRAIN_LATENCY(0, 1, "lat00");
			Red = 0,Green = 0, Blue = 0;
      int tot = 0;
      int bias =128;
		for (unsigned int v = 0; v<MASK_Y; ++v) {
			for (unsigned int u = 0; u<MASK_X; ++u) {
				sc_dt::sc_uint<24> rgb;
#ifndef NATIVE_SYSTEMC
				{
					HLS_DEFINE_PROTOCOL("input");
					rgb = i_rgb.get();
					wait();
				}
#else
				rgb = i_rgb.read();
#endif
				//unsigned char grey = (rgb.range(7,0) + rgb.range(15,8) + rgb.range(23, 16))/3;
					HLS_CONSTRAIN_LATENCY(0, 1, "lat01");
					Red += rgb.range(7,0) * mask[u][v];
          Green+= rgb.range(15,8) * mask[u][v];
          Blue+= rgb.range(23,16) * mask[u][v];
          
          tot+= mask[u][v];
			}
		}
			HLS_CONSTRAIN_LATENCY(0, 1, "lat01");
			 unsigned char result1 = std::min(std::max(int(Red + bias), 0), 255);
			 unsigned char result2 = std::min(std::max(int(Green + bias), 0), 255);
			 unsigned char result3 = std::min(std::max(int(Blue + bias), 0), 255);
        //unsigned char result1 = int(Red/total);
        //unsigned char result2 = int(Green/total);
        //unsigned char result3 = int(Blue/total);
      sc_dt::sc_uint<24> result;
					result.range(7, 0) = result1;
					result.range(15, 8) = result2;
					result.range(23, 16) = result3;
          //result = int((result1 + result2 + result3)/3);
#ifndef NATIVE_SYSTEMC
		{
			HLS_DEFINE_PROTOCOL("output");
			o_result.put(result);
			wait();
		}
#else
		o_result.write(result);
#endif
	}
}
