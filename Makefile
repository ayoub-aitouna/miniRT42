SRC		:= $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/**/**/*.c)
OBJ_DIR	:= .compiled
OBJ		:= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
NAME	:= App
cc		:= gcc 
MLXFLAG := -lmlx 
OS 	:= $(shell uname)

ifeq ($(OS), Darwin)
	MLXFLAG += -framework OpenGl -framework Appkit
else
	MLXFLAG += -lXext -lX11
endif

all: $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@echo "$< Created."
	@$(cc) $(CFLAGS) $(I_SDL) -c $< -o $@

$(NAME) : $(OBJ)
	@echo "$(NAME) Created."
	$(cc) $(CFLAGS) $(OBJ) $(MLXFLAG) -lm -o $(NAME)

clean:
	@rm -rf $(OBJ) $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME) 

re: clean fclean $(NAME)

.PHONY: clean fclean
