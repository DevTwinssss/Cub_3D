--------------------------------------------------------------------
in 
	-> validate_map.c 
	-> init_game [	game->config.floor_color = 0; 
    				game->config.ceiling_color = 0;]

	[ should check -1 not 0 (0 is black)]


--------------------------------------------------------------------
-> parse_rgb.c [should check the range (0-255)]


--------------------------------------------------------------------[ DONE ]
-> add function to make map as rectangle to prevent segfault
	parse_map.c [ void make_map_rectangular(t_game *game) ]


--------------------------------------------------------------------[ DONE ]
-> update function ( void search_pos(int y,int x, t_game *game) )
	→ calculate with angle + calculate position based on tile-size,