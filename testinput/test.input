-------------------------------------------------------------------------------
-- File Downloaded from http://www.nandland.com
-------------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;
 
entity example_entity_architecture is
  port (
    i_bit_1 : in  std_logic;
    i_bit_2 : in  std_logic;
    o_bit   : out std_logic
    );  
end example_entity_architecture;
 
architecture behave of example_entity_architecture is
 
begin
 
  p_PROCESS: process (i_bit_1, i_bit_2) 
  begin
 
    o_bit <= i_bit_1 and i_bit_2;
 
  end process p_PROCESS;
   
end behave;
