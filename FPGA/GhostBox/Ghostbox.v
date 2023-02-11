module Ghostbox(i_clk, o_buzzer,i_uart_serial,i_mode,o_sel1,o_sel10,o_sel100,o_sevseg);

parameter SEV_SEG = 1;
parameter CLICKER = 2;

input [1:0]i_mode;
input i_uart_serial;
input i_clk;

output o_sel1;
output o_sel10;
output o_sel100;

output [6:0] o_sevseg;

output o_buzzer;


wire uartDone;
wire[7:0]w_UARTrx;
reg [3:0]r_buzz_freq = 1; 
reg [7:0]r_sevseg_num = 0;



clickingNoise CLICKER_INST(
	i_clk,
	o_buzzer,
	r_buzz_freq,
);

UARTrx UARTRX_INST
(
	i_clk,
	i_uart_serial,
	uartDone,
	w_UARTrx,
);

SEVEN_SEG SEV_SEG_INST
(
	i_clk,
	o_sel1,
	o_sel10,
	o_sel100,
	o_sevseg,
	r_sevseg_num,
);
always @(posedge i_clk) begin
//if(uartDone) r_sevseg_num <= ~w_UARTrx;
if(i_mode[0] == 1) r_sevseg_num <= ~w_UARTrx;
if(i_mode[1] == 1) r_buzz_freq <= ~w_UARTrx[3:0]; 
/*if(uartDone)begin
case (i_mode) 
	SEV_SEG: 
	begin
		r_sevseg_num <= w_UARTrx;
	end
	CLICKER:
	begin
		r_buzz_freq <= w_UARTrx;
	end
endcase//case(i_mode)
end //if uartDone*/
end

endmodule