#==============================================================================#
#                                 Files and Paths                              #
#==============================================================================#

SRCS = $(addprefix $(SRCS_PATH)/, main.c inputs.c data_ini.c ft_exit.c raycaster.c calculation.c draw.c fps_counter.c textures.c \
minimap.c enemies.c enemies_utils.c)

OBJS = $(addprefix $(BUILD_PATH)/, $(notdir $(SRCS:.c=.o)))

NAME = cub3d

BUILD_PATH = .build
SRCS_PATH = ./srcs
LIBFT_ARC = ./libft/libft.a
LIBFT_PATH = libft
MLX_PATH = minilibx-linux

#==============================================================================#
#                                   Alias                                      #
#==============================================================================#

RM = rm -rf
AR = ar rcs
CFLAGS = -g -Wall -Werror -Wextra
SILENT_MAKE = make -s extra

#==============================================================================#
#                                    Rules                                     #
#==============================================================================#

all: deps $(BUILD_PATH) $(LIBFT_ARC) $(OBJS) $(NAME)

$(BUILD_PATH):
	@mkdir $(BUILD_PATH)

$(NAME): 
	@cc $(CFLAGS) $(OBJS) $(LIBFT_ARC) -L$(MLX_PATH) -lmlx_Linux -Lusr/lib -Iminilibx-linux -lXext -lX11 -lm -lz -o $(NAME)
	@echo "$(GRN)[Cub3d successfully compiled]$(D)"
	
$(BUILD_PATH)/%.o: $(SRCS_PATH)/%.c
	@cc $(CFLAGS) -I/usr/include -Iminilibx-linux -o $@ -c $<

$(LIBFT_ARC): $(LIBFT_PATH)
	@$(SILENT_MAKE) -C $(LIBFT_PATH)

dominilibx: $(MLX_PATH)
	@echo "$(MAG)[Compiling minilibx ...]$(D)"
	@make -sC $(MLX_PATH)
	@echo "$(MAG)[Minilibx successfully compiled!]$(D)"

deps:
	@if test ! -d "$(LIBFT_PATH)"; then make -s get_libft; \
		else echo "$(GRN)[Libft folder found]$(D)"; fi
	@if test ! -d "$(MLX_PATH)"; then make -s get_minilibx; \
		else echo "$(MAG)[Minilibx folder found]$(D)"; fi
	@if test ! -d "$(MLX_PATH)/obj"; then make -s dominilibx; \
		else echo "$(GRN)[All folders found. No relink!]$(D)"; fi

get_libft:
	@echo "[$(CYA)Downloading Libft$(D)]"
	git clone git@github.com:rfpoliveira/42_Libft.git $(LIBFT_PATH)
	@echo "$(CYA)[Libft successfully downloaded]$(D)"

get_minilibx:
	@echo "[$(MAG)Downloading Minilibx$(D)]"
	git clone git@github.com:42Paris/minilibx-linux.git $(MLX_PATH)
	@echo "$(MAG)[Minilibx successfully downloaded]$(D)"

clean: 
	@$(RM) $(BUILD_PATH)
	@echo "$(BCYA)[clean] Objects removed$(D)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIB_NAME)
	@$(RM) $(LIBFT_PATH)
	@$(RM) $(MLX_PATH)
	@echo "$(BCYA)[fclean] Archive, Libft and Minilibx removed$(D)"

re: fclean all

again: clean
	@echo "$(BCYA)[rebuilding...]$(D)"
	@$(RM) $(NAME)
	@$(RM) $(LIB_NAME)
	@$(MAKE) -s
#==============================================================================#
#                                  UTILS                                       #
#==============================================================================#

# Colors
#
# Run the following command to get list of available colors
# bash -c 'for c in {0..255}; do tput setaf $c; tput setaf $c | cat -v; echo =$c; done'
#
B  		= $(shell tput bold)
BLA		= $(shell tput setaf 0)
RED		= $(shell tput setaf 1)
GRN		= $(shell tput setaf 2)
YEL		= $(shell tput setaf 3)
BLU		= $(shell tput setaf 4)
MAG		= $(shell tput setaf 5)
CYA		= $(shell tput setaf 6)
WHI		= $(shell tput setaf 7)
GRE		= $(shell tput setaf 8)
BRED 	= $(shell tput setaf 9)
BGRN	= $(shell tput setaf 10)
BYEL	= $(shell tput setaf 11)
BBLU	= $(shell tput setaf 12)
BMAG	= $(shell tput setaf 13)
BCYA	= $(shell tput setaf 14)
BWHI	= $(shell tput setaf 15)
D 		= $(shell tput sgr0)
BEL 	= $(shell tput bel)
CLR 	= $(shell tput el 1)
