library ieee;
use ieee.std_logic_1164.all;

entity receptor is
  port(
    clock:         in  std_logic;
    reset:         in  std_logic;
    dado_serial:   in  std_logic;
    recebe_dado:   in  std_logic;
	 saida_disp: 	 out std_logic_vector(6 downto 0)
	);
end receptor;

architecture behavioral of receptor is
	component rx_serial_8N2
	  port(
		 clock:         in  std_logic;
		 reset:         in  std_logic;
		 dado_serial:   in  std_logic;
		 recebe_dado:   in  std_logic;
		 pronto_rx:     out std_logic;
		 tem_dado:      out std_logic;
		 dado_recebido: out std_logic_vector(7 downto 0);
		 db_estado:     out std_logic_vector(3 downto 0)
	  );
	end component;
	
	component hex7seg
    port (
        hexa : in  std_logic_vector(3 downto 0);
        sseg : out std_logic_vector(6 downto 0)
    );
	end component;
	
	signal s_dado_recebido: std_logic_vector(7 downto 0);
	
	begin
	rx: rx_serial_8N2 port map(
		 clock => clock,
		 reset => reset,
		 dado_serial => dado_serial,
		 recebe_dado => recebe_dado,
		 pronto_rx => open,
		 tem_dado => open,
		 dado_recebido => s_dado_recebido,
		 db_estado => open
	  );
	
	-- se usar modelsim concatenar no sinal e jogar o sinal na entrada do 7seg
	 hex0: hex7seg port map(
        hexa => "00" & s_dado_recebido(1 downto 0),
        sseg => saida_disp
    );
	 
end architecture;