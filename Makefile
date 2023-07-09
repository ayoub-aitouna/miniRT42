SRC		:= $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/**/**/*.c)
OBJ_DIR	:= .compiled
OBJ		:= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
NAME	:= miniRT
cc		:= gcc #-O2 -g -fsanitize=address
CFLAGS  := -Werror -Wall -Wextra
MLXFLAG := -lmlx
GREEN	:= \033[32m
RESET	:= \033[0m
OS 	:= $(shell uname)

ifeq ($(OS), Darwin)
	MLXFLAG += -framework OpenGl -framework Appkit 
else
	MLXFLAG += -lXext -lX11
endif

all: $(NAME)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@echo " *$<  ${GREEN}Created.${RESET} "
	@$(cc) $(CFLAGS) $(I_SDL) -c $< -o $@

$(NAME) : $(OBJ)
	@echo "to run the Program Type : ${GREEN}./$(NAME)${RESET}"
	@ $(cc) $(CFLAGS) $(OBJ) $(MLXFLAG) -lm -o $(NAME)

clean:
	@rm -rf $(OBJ) $(OBJ_DIR)

fclean: clean
	@rm -rf $(NAME) 

re: clean fclean $(NAME)

.PHONY: clean fclean
