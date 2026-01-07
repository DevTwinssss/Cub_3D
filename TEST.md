

------------------------------------------------------------------
in -> validate_map.c 
	-> init_game [	game->config.floor_color = 0;  
    				game->config.ceiling_color = 0;] 
	
	[ should check -1 not 0 (0 is black)]
[nada][change the config flor and ceilling's value into -1]
--------------------------------------------------------------------
-> parse_rgb.c [should check the range (0-255)] [Done] [nada]


--------------------------------------------------------------------[ DONE ]
-> add function to make map as rectangle to prevent segfault
	parse_map.c [ void make_map_rectangular(t_game *game) ]


--------------------------------------------------------------------[ DONE ]
-> update function ( void search_pos(int y,int x, t_game *game) )
	→ calculate with angle + calculate position based on tile-size,


-------------------------------
C 200,200,200 66 [done]

C 200,200,2000 // max 255 [done]

C C 200,200,20 [done]

SO SO textures/south.xpm [done]
