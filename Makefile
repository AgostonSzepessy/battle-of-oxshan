CC=g++
CFLAGS=-c -Wall -Wextra -I./include -std=c++11 -O2 -s
LDFLAGS= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
SOURCES=main.cpp Game.cpp GameStateManager.cpp GameState.cpp MenuState.cpp PlayState.cpp PauseState.cpp Entity.cpp \
	Player.cpp Bullet.cpp Enemy.cpp BlueThing.cpp PlayerBullet.cpp EnemyBullet.cpp AnimatedSprite.cpp Frame.cpp \
	HealthBar.cpp Brick.cpp BoundingBox.cpp Powerup.cpp HealthUp.cpp Background.cpp Sorcerer.cpp GameOverState.cpp \
	InvincibilityUp.cpp ParticleSystem.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=battle-of-oxshan

all: depend $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o

wipe:
	rm -f *.o $(EXECUTABLE) depend
	
depend: $(SOURCES)
	gcc -M $(CFLAGS) $(SOURCES) >depend

include depend
