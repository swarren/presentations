`timescale 1ns / 1ps

module top(
	input wire btn_center,
	input wire gclk10,
	input wire sw_0,
	output wire led_7,
	output wire led_6,
	output wire led_5,
	output wire led_4,
	output wire led_3,
	output wire led_2,
	output wire led_1,
	output wire led_0
);
	wire clk = gclk10;
	wire rst = ~btn_center;
	wire increment = ~sw_0;

	wire do_count;
	wire [7:0] leds;

	divider divider_instance(
		.clk(clk),
		.rst(rst),
		.do_count(do_count)
	);

	counter counter_instance(
		.clk(clk),
		.rst(rst),
		.do_count(do_count),
		.increment(increment),
		.leds(leds)
	);

	assign led_7 = leds[7];
	assign led_6 = leds[6];
	assign led_5 = leds[5];
	assign led_4 = leds[4];
	assign led_3 = leds[3];
	assign led_2 = leds[2];
	assign led_1 = leds[1];
	assign led_0 = leds[0];
endmodule
