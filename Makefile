SRC		:= $(wildcard src/*.c) $(wildcard src/**/*.c)
OBJ_DIR	:= OBJECT_FILES
OBJ		:= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
NAME	:= App
cc		:= gcc
MLXFLAG = -lmlx -lXext -lX11
all: $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@echo "$< Created."
	@$(cc) $(CFLAGS) $(I_SDL) -c $< -o $@

$(NAME) : $(OBJ)
	@echo "$(NAME) Created."
	$(cc) $(CFLAGS) $(OBJ) $(MLXFLAG) -lm -o $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: clean fclean $(NAME)

.PHONY: clean fclean
