CC := cc
CFLAGS := -Wall -Werror -Wextra -O2 -foptimize-sibling-calls
NAME := pipex
BFLAGS := -Lft_printf -lftprintf
BONUS_NAME := pipex_bonus

BUILD_DIR := build
SRC_DIR := src

SRCS := src/fdc.c src/path.c src/main.c
BONUS_SRCS := src/main_bonus.c src/fdc.c src/path.c \
              src/fps_bonus.c src/fps2_bonus.c

OBJS := $(patsubst src/%.c, build/%.o, $(SRCS))
BONUS_OBJS := $(patsubst src/%.c,build/%.o,$(BONUS_SRCS))


all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJS)
	make -C ft_printf
	$(CC) $(OBJS) $(BFLAGS) -o $(NAME)

build/%.o: src/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(SRCS): $(SRC_DIR)/pipex.h $(SRC_DIR)/pipex_bonus.h

clean:
	rm -rf $(BUILD_DIR)
	make clean -C ft_printf

fclean:	clean
	rm -f $(NAME)
	rm -f $(BONUS_NAME)
	make fclean -C ft_printf

$(BONUS_NAME): $(BONUS_OBJS)
	make -C ft_printf
	$(CC) $(BONUS_OBJS) $(BFLAGS) -o $(BONUS_NAME)


$(BONUS_OBJS): $(BONUS_SRCS)
	$(CC) $(CFLAGS) -c $(patsubst build/%.o,src/%.c,$@)
	mkdir -p build
	mv $(patsubst build/%.o,%.o,$@) $@

re:	fclean all

.PNONY: all clean fclean re bonus