----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    05:19:03 01/23/2018 
-- Design Name: 
-- Module Name:    decrypter - Behavioral 
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
use IEEE.std_logic_unsigned.all;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity decrypter is
    Port ( clock : in  STD_LOGIC;
           K : in  STD_LOGIC_VECTOR (31 downto 0);
           C : in  STD_LOGIC_VECTOR (31 downto 0);
           P : out  STD_LOGIC_VECTOR (31 downto 0);
           reset : in  STD_LOGIC;
			  done : out STD_LOGIC;
           enable : in  STD_LOGIC);
end decrypter;

architecture Behavioral of decrypter is
signal N1:integer range 0 to 63:= 0; -- Signal used in implementing the loop
signal T : std_logic_vector(3 downto 0):=(others=>'0');
signal X : std_logic_vector(31 downto 0);

begin
   process(clock, reset, enable)
	 begin
		if (reset = '1') then
			P <= "00000000000000000000000000000000";
			N1<=0;
			T<="0000";
			done<='1';
		elsif (clock'event and clock = '1') then
			if(enable = '1')  then 
				if(N1<1) then --Intitiallization step for T
				done<='0';
				T(3) <= K(31) XOR K(27) XOR K(23) XOR K(19) XOR K(15) XOR K(11) XOR K(7) XOR K(3);
				T(2) <= K(30) XOR K(26) XOR K(22) XOR K(18) XOR K(14) XOR K(10) XOR K(6) XOR K(2);
				T(1) <= K(29) XOR K(25) XOR K(21) XOR K(17) XOR K(13) XOR K(9) XOR K(5) XOR K(1);
				T(0) <= K(28) XOR K(24) XOR K(20) XOR K(16) XOR K(12) XOR K(8) XOR K(4) XOR K(0);
				N1<=N1+1;
				elsif(N1=1) then --Initialization of X
					N1<=N1+1; 
					T<=T+"1111";
					X <= C;
				elsif(N1 < 34) then --Execution Loop
					if(K(N1-2) = '0') then
						X<=X xor T&T&T&T&T&T&T&T;
						T<=T+"1111";
					end if;
					N1<=N1+1;
				elsif(N1=34) then --Outputing
					P<=X;
					done<='1';
					N1<=N1+1;
				end if;	

			elsif(enable='0') then --resetting the N1 
				N1<=0;
				T<="0000";
			end if;	
		end if;	
	 end process;

	  
end Behavioral;


