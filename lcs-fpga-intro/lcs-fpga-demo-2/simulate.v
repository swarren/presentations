`timescale 1ns / 1ps

module simulate;
	// Inputs
	reg btn_center;
	reg gclk10;
	reg sw_0;

	// Outputs
	wire led_7;
	wire led_6;
	wire led_5;
	wire led_4;
	wire led_3;
	wire led_2;
	wire led_1;
	wire led_0;

	// Instantiate the Unit Under Test (UUT)
	top uut(
		.btn_center(btn_center), 
		.gclk10(gclk10), 
		.sw_0(sw_0), 
		.led_7(led_7), 
		.led_6(led_6), 
		.led_5(led_5), 
		.led_4(led_4), 
		.led_3(led_3), 
		.led_2(led_2), 
		.led_1(led_1), 
		.led_0(led_0)
	);

	initial begin
		// Initialize Inputs
		gclk10 = 0;
		btn_center = 1;
		sw_0 = 0;

		// Wait 100 ns for global reset to finish
		#100;

		// Remove reset
		btn_center = 0;

		// Count for a while
		#10000;
		// Start counting backwards
		sw_0 = 1;
		// Count for a while
		#10000;
		// Done with simulation
		$finish;
	end

	always begin
		#10 gclk10 = ~gclk10;
	end
endmodule
