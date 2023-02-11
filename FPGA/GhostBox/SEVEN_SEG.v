module SEVEN_SEG(i_clk, o_led,o_led2,o_led3,o_seg,num);
	input wire i_clk;
	output wire o_led;
	output wire o_led2;
	output wire o_led3;
	output reg[6:0] o_seg;
	input [7:0] num;
reg [512:0] counter = 0;
reg [512:0] i_count = 0;
reg [3:0] bcd = 0;


task sevseg;
input [3:0] bcd;
output reg[6:0] _o_seg;
	case (bcd) //case statement
            0 : _o_seg <= 7'b0000001;
            1 : _o_seg <= 7'b1001111;
            2 : _o_seg <= 7'b0010010;
            3 : _o_seg <= 7'b0000110;
            4 : _o_seg <= 7'b1001100;
            5 : _o_seg <= 7'b0100100;
            6 : _o_seg <= 7'b0100000;
            7 : _o_seg <= 7'b0001111;
            8 : _o_seg <= 7'b0000000;
            9 : _o_seg <= 7'b0000100;
            //switch off 7 segment character when the bcd digit is not a decimal number.
            default : _o_seg <= 7'b1111111; 
	endcase

endtask

always @(posedge i_clk) begin
	counter <= counter + 1'b1;
end

always @(posedge i_clk)
begin
if(!o_led)
begin
	bcd <= num % 10;
	sevseg(bcd,o_seg);
end
if(!o_led2)
begin
	bcd <= (num % 100) / 10;
	sevseg(bcd, o_seg);
end
if(!o_led3)
begin
	bcd <= (num % 1000) /100;
	sevseg(bcd,o_seg);
end

end

//always @(posedge counter[25]) num <= num + 1;

//assign o_seg = 7'b1001111;
assign o_led = !(counter[12:11] == 2'b11);
assign o_led2 = !(counter[12:11] == 2'b01);
assign o_led3 =  !(counter[12:11] == 2'b10);
endmodule


/*
module Blinky(i_clk, o_led,i_dat);
input i_clk;
input i_dat;
output reg o_led;

always @(posedge i_clk) begin
	o_led <= !i_dat;
end
endmodule
*/