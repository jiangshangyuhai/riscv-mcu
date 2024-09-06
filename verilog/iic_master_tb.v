`timescale 1ns/1ns

module iic_master_tb;

    reg clk;
    reg rst;
    reg rw;
    reg [1:0]mode;
    reg [7:0] data;
    reg start;
    reg stop;
    inout sda;
    wire scl;
    wire proc_ing;
    wire done;
    wire [7:0] data_out;
    wire ack;

    initial begin            
        $dumpfile("wave.vcd"); // 指定用作dumpfile的文件
        $dumpvars; // dump all vars
    end

iic_master iic_master(
    .clk(clk),
    .rst(rst),
    .rw(rw), 
    .mode(mode), 
    .data(data),
    .start(start),
    .stop(start),
    .sda(sda),
    .scl(scl),
    .proc_ing(proc_ing),
    .done(done),
    .data_out(data_out),
    .ack(ack)
);

always #20 clk = ~clk;

initial begin
  rst = 1'b1;
  clk = 1'b1;
  #201
  rst = 1'b0;
  #201
  mode = 2'd3;
  rw = 1'b0;
  data = 8'hA5;
  start = 1'b1;
  #201
  wait (proc_ing);
  start = 1'b0;
  #201
  wait (done);
  $finish;
end

endmodule