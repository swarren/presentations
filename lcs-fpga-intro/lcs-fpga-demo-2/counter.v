`timescale 1ns / 1ps

module counter(
	input wire clk,
	input wire do_count,
	input wire increment,
	input wire rst,
	output wire [7:0] leds
);
	reg [7:0] counter;

	always @(posedge clk) begin
		if (~rst) begin
			counter <= 8'h0;
		end else begin
			if (do_count) begin
				if (increment == 1'b1) begin
					counter <= counter + 8'b1;
				end else begin
					counter <= counter - 8'b1;
				end
			end
		end
	end

	assign leds = counter;
endmodule
