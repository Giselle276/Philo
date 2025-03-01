NAME = philo
SRC = main.c \
      init.c \
	  check.c\
	  utils.c\
	  dinner.c\
	  dinner_util.c\
	  get_set.c\
	  sync.c\
	  print.c\
	  controller.c

OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror

GREEN = \033[1;32m
RESET = \033[0m
HEADER = "\n$(GREEN)\
██████╗ ██╗  ██╗██╗██╗     ██████╗  ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗\n\
██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝\n\
██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗\n\
██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║\n\
██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║\n\
╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝\n\
$(RESET)\n"

INCLUDES = philo.h
%.o: %.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@printf $(HEADER)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "\033[1;33;213mCompiled ✅\n\033[0m"
all: $(NAME)
clean:
	@rm -f $(OBJ)
	@printf "\033[1;36;213mCleaned 🗑️\n\033[0m"
fclean:
	@rm -f $(NAME) $(OBJ)
	@printf "\033[1;34;213mFully cleaned 🗑️🧹\n\033[0m"
re: fclean all
.PHONY: clean fclean all re
