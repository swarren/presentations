`timescale 1ns / 1ps

module divider(
	input wire clk,
	input wire rst,
	output wire do_count
);
	reg [24:0] counter;

	always @(posedge clk) begin
		if (~rst) begin
			counter <= 0;
		end else begin
			counter <= counter + 1;
		end
	end

`ifdef XILINX_ISIM
	assign do_count = &counter[3:0];
`else
	assign do_count = &counter;
`endif
endmodule