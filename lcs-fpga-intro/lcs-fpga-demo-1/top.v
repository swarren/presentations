`timescale 1ns / 1ps

module top(
    input wire sw_0,
    input wire sw_1,
    output wire led_0,
    output wire led_1,
    output wire led_4,
    output wire led_5,
    output wire led_6
);
    assign led_0 = sw_0;
    assign led_1 = sw_1;
    assign led_4 = sw_0 & sw_1;
    assign led_5 = sw_0 | sw_1;
    assign led_6 = sw_0 ^ sw_1;
endmodule