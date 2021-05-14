#ifndef SOBEL_FILTER_H_
#define SOBEL_FILTER_H_
#include <systemc>
using namespace sc_core;

#ifndef NATIVE_SYSTEMC
#include <cynw_p2p.h>
#endif

#include "filter_def.h"

class SobelFilter: public sc_module
{
public:
	sc_in_clk i_clk;
	sc_in < bool >  i_rst;
#ifndef NATIVE_SYSTEMC
	cynw_p2p< sc_dt::sc_uint<24> >::in i_rgb;
	cynw_p2p< sc_dt::sc_uint<8> >::out o_result1;
  cynw_p2p< sc_dt::sc_uint<8> >::out o_result2;
  cynw_p2p< sc_dt::sc_uint<8> >::out o_result3;
#else
	sc_fifo_in< sc_dt::sc_uint<24> > i_rgb;
	sc_fifo_out< sc_dt::sc_uint<8> > o_result1;
  sc_fifo_out< sc_dt::sc_uint<8> > o_result2;
  sc_fifo_out< sc_dt::sc_uint<8> > o_result3;
#endif

	SC_HAS_PROCESS( SobelFilter );
	SobelFilter( sc_module_name n );
	~SobelFilter();
private:
	void do_filter();
  sc_dt::sc_uint<32> Red;
  sc_dt::sc_uint<32> Blue;
  sc_dt::sc_uint<32> Green;
  int val[MASK_N];
};
#endif
