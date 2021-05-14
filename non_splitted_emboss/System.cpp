#include "System.h"
System::System( sc_module_name n, string input_bmp, string output_bmp ): sc_module( n ), 
	tb("tb"), sobel_filter("sobel_filter"), clk("clk", CLOCK_PERIOD, SC_NS), rst("rst"), _output_bmp(output_bmp)
{
	tb.i_clk(clk);
	tb.o_rst(rst);
	sobel_filter.i_clk(clk);
	sobel_filter.i_rst(rst);
	tb.o_rgb(rgb);
	tb.i_result1(result1);
  tb.i_result2(result2);
  tb.i_result3(result3);
	sobel_filter.i_rgb(rgb);
	sobel_filter.o_result1(result1);
  sobel_filter.o_result2(result2);
  sobel_filter.o_result3(result3);

  tb.read_bmp(input_bmp);
}

System::~System() {
  tb.write_bmp(_output_bmp);
}
