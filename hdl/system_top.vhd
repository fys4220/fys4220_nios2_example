library ieee;
use ieee.std_logic_1164.all;

entity system_top is
  port (
    clk : in std_logic;
    arst_n : in std_logic;
    sw : in std_logic_vector(9 downto 0);
    led : out std_logic_vector(9 downto 0)
  );
end entity;

architecture rtl of system_top is

  component nios2_system is
    port (
      clk_clk : in std_logic := 'X'; -- clk
      reset_reset_n : in std_logic := 'X' -- reset_n
    );
  end component nios2_system;

begin

  led <= sw;
  u0 : component nios2_system
    port map(
      clk_clk => clk, --   clk.clk
      reset_reset_n => arst_n -- reset.reset_n
    );
  end architecture;