module clickingNoise(i_clk, o_led, i_sel);

input i_clk;
input [3:0]i_sel;
output reg o_led = 0;

reg[31:0] r_counter = 31'b0;
reg[31:0] r_offCounter = 0; //0x2FAF080


//wire[6:0] sel = i_sel;

reg s = 0;
reg reset = 0;

wire onPulse;
wire offPulse;

always @(posedge i_clk)
begin


	if(reset == 1) begin
		r_counter = 0;
		r_offCounter <= 0;
		s <= 0;
		reset <= 0;
	end else begin
		if(offPulse == 1) s <= 1;
		r_counter = r_counter + 1'b1;
		if(s == 0) begin
			o_led = 0;	
		end
		if(s == 1) begin	
			o_led <= 1;
			r_offCounter <= r_offCounter + 1'b1;
			if(r_offCounter >= (50/i_sel) << 20)
			begin
				reset <= 1;
			end
		end

	end
end


//always @(posedge offPulse) s <= 1;

assign offPulse = (r_counter == 30000); //pulses when counter == 30000


 
/*
always @(posedge i_clk) begin
if((sel & r_counter[26:20]) == sel)
begin
	if(opt == 1)begin
		if(r_counter[14] == 0)
		begin o_led = 0; if(r_counter[15] == 1) opt = 0; end
		else o_led = 1;
	end
	else o_led = 1;
end else begin
	opt = 1;
	o_led = 1;
end
end
*/

endmodule