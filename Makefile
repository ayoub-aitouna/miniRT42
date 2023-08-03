NAME			:= miniRT
NAMEBONUS		:= miniRTBONUS

OBJ_DIR			:= .compiled

SRC				:= $(wildcard src/*.c) $(wildcard src/**/*.c) $(wildcard src/**/**/*.c)  $(wildcard src/**/**/**/*.c)
MNDATORY_OBJ	:= $(OBJ_DIR)/App/App.o
BONUS_OBJ   	:= $(OBJ_DIR)/App/BonusApp.o
OBJ				:= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
Sanitize		:= #-g -fsanitize=address

cc				:= gcc ${Sanitize}
CFLAGS  		:= -Werror -Wall -Wextra
MLXFLAG 		:= -lmlx

GREEN			:= \033[32m
RESET			:= \033[0m

OS 	:= $(shell uname)

ifeq ($(OS), Darwin)
	MLXFLAG += -framework OpenGl -framework Appkit 
else
	MLXFLAG += -lXext -lX11
endif

all : $(NAME)
bonus : $(NAMEBONUS)


$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(dir $@)
	@echo "=> $@  ${GREEN}Created.${RESET} "
	@$(cc) $(CFLAGS) $(I_SDL) -c $< -o $@

$(NAME) : $(OBJ) $(MNDATORY_OBJ)
	@echo "to run the Program Type : ${GREEN}./$(NAME) <scene '.rt' file path >  ${RESET}"
	@ $(cc) $(CFLAGS) $(OBJ) $(MNDATORY_OBJ) $(MLXFLAG) -lm -o $(NAME)

$(NAMEBONUS) : $(OBJ) $(BONUS_OBJ)
	@echo "to run the Program Type : ${GREEN}./$(NAMEBONUS) <scene '.rt' file path >  ${RESET}"
	@ $(cc) $(CFLAGS) $(OBJ) $(BONUS_OBJ) $(MLXFLAG) -DBONUS -lm -o $(NAMEBONUS)

clean:
	@rm -rf $(OBJ) $(OBJ_DIR)  $(BONUS_OBJ) $(MNDATORY_OBJ)

fclean: clean
	@rm -rf $(NAME) $(NAMEBONUS)

re: clean fclean $(NAME)

.PHONY: clean fclean
