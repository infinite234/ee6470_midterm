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
	cynw_p2p< sc_dt::sc_uint<8> >::in i_r;
 cynw_p2p< sc_dt::sc_uint<8> >::in i_g;
 cynw_p2p< sc_dt::sc_uint<8> >::in i_b;
	cynw_p2p< sc_dt::sc_uint<8> >::out o_resultr;
 cynw_p2p< sc_dt::sc_uint<8> >::out o_resultg;
 cynw_p2p< sc_dt::sc_uint<8> >::out o_resultb;
#else
	sc_fifo_in< sc_dt::sc_uint<8> > i_r;
 sc_fifo_in< sc_dt::sc_uint<8> > i_g;
 sc_fifo_in< sc_dt::sc_uint<8> > i_b;
	sc_fifo_out< sc_dt::sc_uint<8> > o_resultr;
 sc_fifo_out< sc_dt::sc_uint<8> > o_resultg;
 sc_fifo_out< sc_dt::sc_uint<8> > o_resultb;
#endif

	SC_HAS_PROCESS( SobelFilter );
	SobelFilter( sc_module_name n );
	~SobelFilter();
private:
	void do_filter();
  sc_dt::sc_uint<32> val[3];
};
#endif
