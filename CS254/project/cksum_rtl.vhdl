----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    16:17:26 02/20/2018 
-- Design Name: 
-- Module Name:    buffer - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

--
-- Copyright (C) 2009-2012 Chris McClelland
--
-- This program is free software: you can redistribute it and/or modify
-- it under the terms of the GNU Lesser General Public License as published by
-- the Free Software Foundation, either version 3 of the License, or
-- (at your option) any later version.
--
-- This program is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
-- GNU Lesser General Public License for more details.
--
-- You should have received a copy of the GNU Lesser General Public License
-- along with this program.  If not, see <http://www.gnu.org/licenses/>.
--
library ieee;
use IEEE.std_logic_unsigned.all;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

architecture rtl of swled is
	-- Flags for display on the 7-seg decimal points
	signal flags                   : std_logic_vector(3 downto 0);
	signal coords : std_logic_vector(7 downto 0) ;
	signal tim							 : integer range 0 to 1000000000 := 0;
	signal sleep						 : integer range 0 to 1000000000 := 0;
	signal counter						 : integer range 0 to 256 := 0;
	signal temp							 : std_logic_vector(63 downto 0):= (others => '0');
	signal temp1			    		 : std_logic_vector(31 downto 0);
	signal temp2			    		 : std_logic_vector(31 downto 0);
	signal X						 : integer range 0 to 31:= 0;
	signal Y						 : integer range 0 to 31:= 0;
	signal Z						 : integer range 0 to 7 := 0;
	-- Registers implementing the channels
   signal reg0_next,reg0,outreg0 : std_logic_vector(7 downto 0)  := (others => '0');
	signal tmp2 : std_logic_vector(7 downto 0) := (others =>'1');
	signal encryption_over,decryption_over: std_logic;
	signal key : std_logic_vector(31 downto 0);
	signal ciphertext_out : std_logic_vector(31 downto 0);
	signal plaintext_out : std_logic_vector(31 downto 0);
	signal plaintext_out1 : std_logic_vector(31 downto 0);
	signal ack1 : std_logic_vector(31 downto 0):= "01001000101011101100000000101111";
	signal ack2 : std_logic_vector(31 downto 0):= "00000101010111111101001001011010";	
	signal padding : std_logic_vector(23 downto 0):=(others =>'0');
	signal e_reset : std_logic := '0';
	signal d_reset : std_logic := '0';
	signal e_enable : std_logic := '0';
	signal d_enable : std_logic := '0';
	signal f2h :std_logic:= '0';
	signal h2f :std_logic:= '0';
	signal reset :std_logic;
	--signal h2fData_32 : std_logic_vector(23 downto 0):=(others =>'0');

	--Needed so that the comm_fpga_fx2 module can drive both fx2Read_out and fx2OE_out
	signal fx2Read   : std_logic;

	-- Reset signal so host can delay startup
	signal fx2Reset  : std_logic;
	
	COMPONENT encrypter
		   PORT(
				 clock : IN  std_logic;
			    K : IN  std_logic_vector(31 downto 0);
       		 P : IN  std_logic_vector(31 downto 0);
         	 C : OUT  std_logic_vector(31 downto 0);
         	 reset : IN  std_logic;
         	 enable : IN  std_logic;
				 done : OUT std_logic
             );
    	END COMPONENT;

	component decrypter
        port( clock : in  STD_LOGIC;
           K : in  STD_LOGIC_VECTOR (31 downto 0);
           C : in  STD_LOGIC_VECTOR (31 downto 0);
           P : out  STD_LOGIC_VECTOR (31 downto 0);
           reset : in  STD_LOGIC;
           done : out STD_LOGIC;
           enable : in  STD_LOGIC);
        end component;
	
	
begin              
                                                       --BEGIN_SNIPPET(registers)
encrypt: encrypter
              port map (clock => clk_in,
                        reset => e_reset,
								P => temp2,
                        enable => e_enable,
                        C => ciphertext_out,
                        done => encryption_over,
                        K => key);

decrypt: decrypter
              port map (clock => clk_in,
                        reset => d_reset,
								C => temp1,
                        enable => d_enable,
                        P => plaintext_out,
                        done => decryption_over,
                        K => key);

	-- Infer registers
	process(clk_in)
	begin
		if ( rising_edge(clk_in) ) then
			reg0<=reg0_next;
			if ( reset_in = '1' ) then
				reset<='1';
				tim<=0;
				Y<=0;
			elsif(reset='1') then
				if(X<18) then
					if(Y<4) then
						f2h<='1';
						Y<=Y+1;
					else
						f2h<='0';
						X<=19;
					end if;
				else
					if(tim > 143999999) then
						Y<=0;
						X<=0;
						Z<=0;
						tim<=0;
						reset<='0';
						outreg0<=(others=>'0');
					else
						outreg0<=(others=>'1');
						tim<=tim+1;
					end if;
				end if;
			elsif(Y=0) then
				temp2<=(others => '0');
				temp2(7 downto 0)<= coords;
				e_enable<='1';
				Y<=1;
			elsif(Y=1) then
				Y<=Y+1;
			elsif(X<4) then  --------this loop send data to host
				if(encryption_over = '1' and f2hReady_in = '1') then
					f2h<='1';
					tmp2<=ciphertext_out( 8*X+7 downto 8*X);
					X<=X+1;
					e_enable<='0';
				end if;			
			elsif(X<8) then-----this loop receives data from host depending does next things depending on Y....See down
				f2h<='0';
				h2f<='1';
				if(h2fValid_in = '1') then
					temp1( 8*(X-4)+7 downto 8*(X-4))<=reg0_next;
					X<=X+1;
				else
					if(Y>6) then
						X<=Y;
					else	
						sleep<=sleep+1;
						if(sleep>48000000) then
							counter<=counter+1;
							sleep<=0;
						end if;
						if(counter = 256) then
							sleep<=0;
							counter<=0;
							X<=0;
							Y<=0;
						end if;
					end if;		
				end if;
				if(X=7) then
					d_enable<='1';
				end if;
			elsif(X=8) then
			X<=X+1; 
			elsif(X=9) then
				h2f<='0';
				if(decryption_over = '1') then ---- From now things happen depending on Y.... Check what is inside each Y condition
					d_enable<='0';
					if(Y=2) then  -----Y =1 recevies cords
						if(plaintext_out(7 downto 0)=coords) then
							if(e_enable='1') then
							Y<=3;
							X<=0;
							else
								e_enable<='1';
								temp2<=ack1;
							end if;	
						else
							if(sleep<48000000) then
								f2h<='1';
								sleep<=sleep+1;
							else	
							Y<=0;
							X<=0;
							f2h<='0';
							sleep<=0;
							end if;
						end if;
					elsif(Y=3) then
						--outreg0<=temp1(7 downto 0);
						if(plaintext_out=ack2) then -----Y =2 receives ack
							Y<=4;
							X<=4;
						end if;
						
					elsif(Y=4) then ---- Y =3 receives fist 32 bits of look up data
						if(e_enable='1') then
						X<=0;	
						Y<=5;
						else
							temp(31 downto 0) <= plaintext_out;
							--temp(31 downto 0)<=(others=>'1');
							temp2<=ack1;
							e_enable<='1';
						end if;
					elsif(Y=5) then	---- Y=4 next 32 bits of look up data
						if(e_enable='1') then
						X<=0;	
						Y<=6;
						else
							temp(63 downto 32) <= plaintext_out;
							temp2<=ack1;
							e_enable<='1';
						end if;
					elsif(Y=6) then --- last ack from host
						if(plaintext_out=ack2) then
							--X<=X+1;
							--outreg0<="11111111";
							X<=X+1;
						end if;
					end if;
				end if;		
			elsif(X<18) then
	
--					if(temp((X-10)*8+7) = '0' or temp((X-10)*8+6) = '0') then
--						outreg0(0) <='1';
--					else 
--						outreg0(0) <='0';
--					end if;
--					if(temp((X-10)*8+7) = '1' and temp((X-10)*8+6) = '1' and to_integer(unsigned(temp((X-10)*8+2 downto (X-10)*8+0)))<=1) then
--						outreg0(1) <= '1';
--					else 
--						outreg0(1) <= '0';
--					end if;
--					if(temp((X-10)*8+7) = '1' and temp((X-10)*8+6) = '1' and to_integer(unsigned(temp((X-10)*8+2 downto (X-10)*8+0)))>1) then
--						outreg0(2) <= '1';
--					else
--						outreg0(2) <= '0';
--					end if;
					outreg0(7 downto 5)<=temp((X-10)*8+5 downto (X-10)*8+3);
					if(Z=0) then
						if(tim<47999999) then
							tim<=tim+1;
							if(temp((x-10)*8 + 6) = '0') then
								outreg0(0) <= '1';
							else
								if(x-10<4) then
									if(sw_in(x-10)='1' and sw_in(x-6) ='0') then
										if(to_integer(unsigned(temp((X-10)*8+2 downto (X-10)*8+0)))>1) then
											outreg0(2) <= '1';
										else
											outreg0(1) <= '1';
										end if;
									else
										outreg0(0) <= '1';									
									end if;
								else
									if(sw_in(x-10)='1' and sw_in(x-14)='1') then
										outreg0(2) <= '1';
									elsif(sw_in(x-10)='1' and sw_in(x-14)='0') then
										if(to_integer(unsigned(temp((X-10)*8+2 downto (X-10)*8+0)))>1) then
											outreg0(2) <= '1';
										else
											outreg0(1) <= '1';
										end if;
									else 
										outreg0(0) <= '1';
									end if;
								end if;
							end if;	
						else
							Z<=1;
							tim<=0;
							outreg0(4 downto 0)<=(others=>'0');
						end if;
					elsif(Z=1) then
						if(tim<47999999) then
							tim<=tim+1;
							if(temp((x-10)*8 + 6) = '0') then
							outreg0(0) <= '1';
							else
								if(x-10<4) then
									if(sw_in(x-10)='1' and sw_in(x-6) ='0') then
										if(to_integer(unsigned(temp((X-10)*8+2 downto (X-10)*8+0)))>1) then
											outreg0(2) <= '1';
										else
											outreg0(1) <= '1';
										end if;
									else
										outreg0(0) <= '1';									
									end if;
								else
									if(sw_in(x-10)='1' and sw_in(x-14)='1') then
										outreg0(1) <= '1';
									elsif(sw_in(x-10)='1' and sw_in(x-14)='0') then
										if(to_integer(unsigned(temp((X-10)*8+2 downto (X-10)*8+0)))>1) then
											outreg0(2) <= '1';
										else
											outreg0(1) <= '1';
										end if;
									else
										outreg0(0) <= '1';
									end if;
								end if;
							end if;	
						else
							Z<=2;
							tim<=0;
							outreg0(4 downto 0)<=(others=>'0');
						end if;
					elsif(Z=2) then
						if(tim<47999999) then
							tim<=tim+1;
							if(temp((x-10)*8 + 6) = '0') then
								outreg0(0) <= '1';
							else
								if(x-10<4) then
									if(sw_in(x-10)='1' and sw_in(x-6) ='0') then
										if(to_integer(unsigned(temp((X-10)*8+2 downto (X-10)*8+0)))>1) then
											outreg0(2) <= '1';
										else
											outreg0(1) <= '1';
										end if;
									else
										outreg0(0) <= '1';									
									end if;
								else
									if(sw_in(x-10)='1' and sw_in(x-14)='1') then
										outreg0(0) <= '1';
									elsif(sw_in(x-10)='1' and sw_in(x-14)='0') then
										if(to_integer(unsigned(temp((X-10)*8+2 downto (X-10)*8+0)))>1) then
											outreg0(2) <= '1';
										else
											outreg0(1) <= '1';
										end if;
									else
										outreg0(0) <= '1';
									end if;
								end if;
							end if;	
						else
							if(X=17) then
								outreg0(7 downto 5)<=(others=>'0');
								X<=18;
								if(up='1') then
									Y<=10;
								end if;	
							else
								X<=X+1;
							end if;
							Z<=0;
							tim<=0;
							outreg0(4 downto 0)<=(others=>'0');
						end if;
					end if;

--					if(tim=47999999) then
--						X<=X+1;
--						tim<=0;
--					else	
--						outreg0(7 downto 5)<=temp((X-10)*8+5 downto (X-10)*8+3)	;
--						--outreg0<=temp((X-10)*8+7 downto (X-10)*8);
--						tim<=tim+1;
--					end if;
				elsif(X=18) then
					if(Y=10) then
						if(e_enable='1')then
							X<=0;
						elsif(down='1') then
							temp2<=(others => '0');
							temp2(7 downto 0)<= sw_in;
							e_enable<='1';
							if(left='1') then
								Y<=19;
							else
								Y<=20;
							end if;	
						end if;
					else
						if(e_enable='1')then
							X<=0;
							if(left='1') then
								Y<=19;
							else
								Y<=20;
							end if;
						else
							temp2<=(others => '1');
							e_enable<='1';	
						end if;
					end if;		
				elsif(X=19) then
					if(right='1') then
						start<='1';
						X<=20;	
					end if;
				elsif(X=20) then
					X<=21;
					if(empty='0') then
						pop<='1';
						outreg0<=data;
						if((temp(7+to_integer(unsigned(data(5 downto 3)))*8) xor data(7) )='1') then
							
							temp(5+to_integer(unsigned(data(5 downto 3)))*8 downto to_integer(unsigned(data(5 downto 3)))*8)
							<= data(5 downto 0);
							temp(6)<= temp(6) and data(6);
							
						end if;
					end if;
					start<='0';
				elsif(tim<143999999) then
					tim<=tim+1;
					pop<='0';
				else	
					X<=0;
					tim<=0;
					outreg0<=(others=>'0');
					Y<=0;
				end if;	
	
		end if;
		
	end process;


	-- Drive register inputs for each channel when the host is writing
	reg0_next <= h2fData_in when chanAddr_in = "0000001" and h2fValid_in = '1' else reg0;
--	if(chanAddr_in = "0000001" and h2fValid_in = '1') then
--		reg0_next <= h2fData_in;
--	else
--		reg0_next <= reg0;
--	end if;
	
	coords<= "00100010";
	key<="00100100010101111001101101100111";
	
	-- Select values to return for each channel when the host is reading
	with chanAddr_in select f2hData_out <=
		tmp2 when "0000000", x"00" when others;

--	if(chanAddr_in = "0000000") then
--		f2hData_out <=tmp2;
--	--else
--	end if;
	-- Assert that there's always data for reading, and always room for writing
	f2hValid_out <= f2h;
	h2fReady_out <= h2f;                                                     --END_SNIPPET(registers)

	-- LEDs and 7-seg display
	led_out <= outreg0;
	flags <= "00" & f2hReady_in & reset_in;
	
end architecture;


