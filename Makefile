SRC		:= $(wildcard src/*.c) $(wildcard src/**/*.c)
OBJ_DIR	:= OBJECT_FILES
OBJ		:= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
I_SDL	:= -I$(shell brew --prefix)/include
L_SDL	:= -L$(shell brew --prefix sdl2)/lib
NAME	:= App
cc		:= gcc

all: $(NAME)

minilibx :
	git clone https://github.com/42Paris/minilibx-linux.git minilibx


$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@echo "$< Created."
	@$(cc) $(CFLAGS) $(I_SDL) -c $< -o $@

$(NAME) : $(minilibx) $(OBJ)
	@echo "$(NAME) Created."
	$(cc) $(CFLAGS) $(OBJ) -lmlx -framework OpenGl -framework Appkit  -o $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: clean fclean $(NAME)

.PHONY: clean fclean
