
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = cube3d

SFILES = 	./sources/main.c \
			./sources/draw.c \
			./sources/init.c \
			./sources/input.c \
			./sources/player.c \
			./sources/map.c
OFILES = $(SFILES:.c=.o)

all:$(NAME)

${NAME}: ${OFILES}
	make -C minilibx-linux 
	${CC} ${CFLAGS} ${OFILES} -Iminilibx-linux -Lminilibx-linux -lmlx -lXext -lX11 -lm -lz -o ${NAME}

clean:
	rm -f ${OFILES}

fclean: clean
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re