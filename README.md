# scorched_project
A project that uses OneLoneCoder's PixelGameEngine

This is a fun project for two friends

# Compile
In root folder create a folder called "build" got to "build" and run:
```
build> cmake ..
build> make
```

## Need packages
X11: ```libx11-dev```
OpenGl: ```libgl1-mesa-dev```
PNG: ```libpng-dev```
Threads: ```libpthread-stubs0-dev```
Alsa: ```alsa-lib-dev```

# Korte bullet-list af features:
- [ ] 2d, set fra siden, projektiler og tanks er i hvert fald sprites
-  [ ] Landskab er procedural genereret (ingen ide hvordan, måske med normalized perlin noise som OLC brugte i hans Worms video?)
-  [ ] 2 eller flere tanks (mindste 1 spiller, resten AI)
-  [ ] Våben, i forskellige former med forskellige stats (damage, explosion radius etc)
-  [ ] Våben bliver skudt fra tanks, hvor du styrer kraft og vinkel
-  [ ] Alle våben er projektiler som kan kollidere med ting og bliver påvirket af physics (vind, tyngdekraft etc)
-  [ ] Våben eksplosioner er cirkler (nemt at regne kollision ud fra) og skader tanks og fjerner terræn. Muligvis scale skaden på hvor langt væk tanken er fra midten af cirklen?
-  [ ] Tanks er som udgangspunkt statiske, og bevæger sig kun hvis terrænet under/omkring dem bliver fjernet via våbenskade (tyngdekraft går jeg ud fra)