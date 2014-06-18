`timescale 1ns / 1ps

module simulate;
	// Inputs
	reg sw_0;
	reg sw_1;

	// Outputs
	wire led_0;
	wire led_1;
	wire led_4;
	wire led_5;
	wire led_6;

	top uut(
		.sw_0(sw_0), 
		.sw_1(sw_1), 
		.led_0(led_0), 
		.led_1(led_1), 
		.led_4(led_4), 
		.led_5(led_5), 
		.led_6(led_6)
	);

	initial begin
		// Initialize Inputs
		sw_0 = 0;
		sw_1 = 0;

		// Wait 100 ns for global reset to finish
		#100;

		sw_0 = 0;
		sw_1 = 0;
		#100;

		sw_0 = 0;
		sw_1 = 1;
		#100;

		sw_0 = 1;
		sw_1 = 0;
		#100;

		sw_0 = 1;
		sw_1 = 1;
		#100;

		$finish;
	end
endmodule
