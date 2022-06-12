#OBJS1 = scene_node.cpp sprite_node.cpp world.cpp entity.cpp aircraft.cpp player.cpp main.cpp
#OBJS2 = command.cpp command_queue.cpp utility.cpp parallel_task.cpp application.cpp
#OBJS3 = state.cpp state_stack.cpp title_state.cpp menu_state.cpp game_state.cpp pause_state.cpp loading_state.cpp  
#OBJS4 = component.cpp container.cpp label.cpp button.cpp settings_state.cpp

OBJS = source/*.cpp

CC = g++ -std=c++17

COMPILER_FLAGS = -Wall -Wextra

LINKER_FLAGS = -L/usr/lib/x86-64-linux-gnu -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

INCLUDE_FLAGS = -I/usr/include/SFML -Iinclude

OUT_NAME = -o airfight


all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(INCLUDE_FLAGS) $(OUT_NAME)
